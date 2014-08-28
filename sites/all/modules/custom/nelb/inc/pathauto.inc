<?php
/**
 * Implements hook_node_operations().
 */
function nelb_node_operations() {
  $operations['nelb_pathauto_update_alias'] = array(
    'label' => t('Nelb Update URL alias'),
    'callback' => 'nelb_pathauto_node_update_alias_multiple',
    'callback arguments' => array('bulkupdate', array('message' => TRUE)),
  );
  return $operations;
}

/**
 * Implements hook_action_info().
 */
function nelb_action_info() {
  $info['nelb_pathauto_node_update_action'] = array(
    'type' => 'node',
    'label' => t('Nelb Update node alias'),
    'configurable' => FALSE,
  );
  $info['pathauto_taxonomy_term_update_action'] = array(
    'type' => 'taxonomy_term',
    'label' => t('Nelb Update taxonomy term alias'),
    'configurable' => FALSE,
  );
  $info['pathauto_user_update_action'] = array(
    'type' => 'user',
    'label' => t('Nelb Update user alias'),
    'configurable' => FALSE,
  );

  return $info;
}

/**
 * Update action wrapper for pathauto_node_update_alias().
 */
function nelb_pathauto_node_update_action($node, $context = array()) {
  nelb_pathauto_node_update_alias($node, 'bulkupdate', array('message' => TRUE));
}

/**
 * Update the URL aliases for multiple nodes.
 *
 * @param $nids
 *   An array of node IDs.
 * @param $op
 *   Operation being performed on the nodes ('insert', 'update' or
 *   'bulkupdate').
 * @param $options
 *   An optional array of additional options.
 */
function nelb_pathauto_node_update_alias_multiple(array $nids, $op, array $options = array()) {
  $options += array('message' => FALSE);

  $nodes = node_load_multiple($nids);
  foreach ($nodes as $node) {
    nelb_pathauto_node_update_alias($node, $op, $options);
  }

  if (!empty($options['message'])) {
    drupal_set_message(format_plural(count($nids), 'Updated URL alias for 1 node.', 'Updated URL aliases for @count nodes.'));
  }
}


/**
 *
 */
function nelb_pathauto_node_update_alias(stdClass $node, $op, array $options = array()) {
  // Skip processing if the user has disabled pathauto for the node.
  if (isset($node->path['pathauto']) && empty($node->path['pathauto'])) {
    return;
  }

  $options += array('language' => pathauto_entity_language('node', $node));

  // Skip processing if the node has no pattern.
  if (!pathauto_pattern_load_by_entity('node', $node->type, $options['language'])) {
    return;
  }

  module_load_include('inc', 'pathauto');
  $uri = entity_uri('node', $node);
  $node->path = nelb_pathauto_create_alias('node', $op, $uri['path'], array('node' => $node), $node->type, $options['language']);
  $node->path['processed'] = TRUE;
}

/**
 * Alter of function pathauto_create_alias.
 * Apply patterns to create an alias.
 *
 * @param $module
 *   The name of your module (e.g., 'node').
 * @param $op
 *   Operation being performed on the content being aliased
 *   ('insert', 'update', 'return', or 'bulkupdate').
 * @param $source
 *   An internal Drupal path to be aliased.
 * @param $data
 *   An array of keyed objects to pass to token_replace(). For simple
 *   replacement scenarios 'node', 'user', and others are common keys, with an
 *   accompanying node or user object being the value. Some token types, like
 *   'site', do not require any explicit information from $data and can be
 *   replaced even if it is empty.
 * @param $type
 *   For modules which provided pattern items in hook_pathauto(),
 *   the relevant identifier for the specific item to be aliased
 *   (e.g., $node->type).
 * @param $language
 *   A string specify the path's language.
 * @return
 *   The alias that was created.
 *
 * @see _pathauto_set_alias()
 * @see token_replace()
 */
function nelb_pathauto_create_alias($module, $op, $source, $data, $type = NULL, $language = LANGUAGE_NONE) {
  // Retrieve and apply the pattern for this content type.
  $pattern = pathauto_pattern_load_by_entity($module, $type, $language);
  if (empty($pattern)) {
    // No pattern? Do nothing (otherwise we may blow away existing aliases...)
    return '';
  }

  // Special handling when updating an item which is already aliased.
  $existing_alias = NULL;
  if ($op == 'update' || $op == 'bulkupdate') {
    if ($existing_alias = _pathauto_existing_alias_data($source, $language)) {
      switch (variable_get('pathauto_update_action', PATHAUTO_UPDATE_ACTION_DELETE)) {
        case PATHAUTO_UPDATE_ACTION_NO_NEW:
          // If an alias already exists, and the update action is set to do nothing,
          // then gosh-darn it, do nothing.
          return '';
      }
    }
  }

  // Replace any tokens in the pattern. Uses callback option to clean replacements. No sanitization.
  $pattern = nelb_pathauto_create_alias_article($pattern, $data['node']);

  $alias = token_replace($pattern, $data, array(
    'sanitize' => FALSE,
    'clear' => TRUE,
    'callback' => 'pathauto_clean_token_values',
    'language' => (object) array('language' => $language),
    'pathauto' => TRUE,
  ));

  // Check if the token replacement has not actually replaced any values. If
  // that is the case, then stop because we should not generate an alias.
  // @see token_scan()
  $pattern_tokens_removed = preg_replace('/\[[^\s\]:]*:[^\s\]]*\]/', '', $pattern);
  if ($alias === $pattern_tokens_removed) {
    return '';
  }

  $alias = pathauto_clean_alias($alias);

  // Allow other modules to alter the alias.
  $context = array(
    'module' => $module,
    'op' => $op,
    'source' => &$source,
    'data' => $data,
    'type' => $type,
    'language' => &$language,
    'pattern' => $pattern,
  );
  drupal_alter('pathauto_alias', $alias, $context);

  // If we have arrived at an empty string, discontinue.
  if (!drupal_strlen($alias)) {
    return '';
  }

  // If the alias already exists, generate a new, hopefully unique, variant.
  $original_alias = $alias;
  pathauto_alias_uniquify($alias, $source, $language);
  if ($original_alias != $alias) {
    // Alert the user why this happened.
    _pathauto_verbose(t('The automatically generated alias %original_alias conflicted with an existing alias. Alias changed to %alias.', array(
      '%original_alias' => $original_alias,
      '%alias' => $alias,
    )), $op);
  }

  // Return the generated alias if requested.
  if ($op == 'return') {
    return $alias;
  }

  // Build the new path alias array and send it off to be created.
  $path = array(
    'source' => $source,
    'alias' => $alias,
    'language' => $language,
  );
  $path = _pathauto_set_alias($path, $existing_alias, $op);
  return $path;
}

/**
 * Alter Pattern
 */
function nelb_pathauto_create_alias_article($pattern, $node) {
  // Search for a Category that has the flag active.
  $tids = array();
  $terms_found = array();
  if ( isset($node->field_category[LANGUAGE_NONE][0]['tid']) ) {
    foreach($node->field_category[LANGUAGE_NONE] as $raw_term) {
      $tids[] = $raw_term['tid'];
    }
    $terms = taxonomy_term_load_multiple($tids);
    foreach($terms as $term) {
      if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 && isset($term->field_url_prefix[LANGUAGE_NONE][0]['value']) && !empty($term->field_url_prefix[LANGUAGE_NONE][0]['value']) ) {
        $terms_found[$term->tid] = $term;
      }
    }
  }
  
  // Term found
  if ( !empty($terms_found) ) {
    $count = count($terms_found);
    $term_found = false;
    if ( $count > 1 ) {
      if ( isset($node->field_main_category[LANGUAGE_NONE][0]['value']) && !empty($node->field_main_category[LANGUAGE_NONE][0]['value']) ) {
        $term_found = taxonomy_term_load($node->field_main_category[LANGUAGE_NONE][0]['value']);
      } else {
        // Look for TV
        if ( isset($terms_found[14]) ) {
          $term_found = $terms_found[14];
        } // Look for Deportes 
        else if ( isset($terms_found[154]) ) {
          $term_found = $terms_found[154];
        } // Look for Estilos
        else if ( isset($terms_found[157]) ) {
          $term_found = $terms_found[157];
        }
      }
    }
    
    if ( !$term_found ) {
      $term_found = array_shift($terms_found);
    }
    $prefix = $term_found->field_url_prefix[LANGUAGE_NONE][0]['value'];
    $prefix = trim(strtolower($prefix));
    $prefix = preg_replace('/[^a-z0-9]+/', '', $prefix);
    return "{$prefix}/{$pattern}";
  }
  
  return $pattern;
}