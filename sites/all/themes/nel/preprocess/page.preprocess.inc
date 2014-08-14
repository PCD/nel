<?php

/**
 * Implements hook_preprocess_page().
 */
function nel_preprocess_page(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
  
  // Proccess HTML for Nodes
  nel_preprocess_page_node($variables);
  
  // Proccess HTML for Taxonomy
  nel_preprocess_page_taxonomy($variables);
  
  // Apply Logo
  nel_preprocess_page_apply_logo($variables);
}

/**
 * Preprocess page for Node.
 */
function nel_preprocess_page_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
  if ( isset($node->field_category[LANGUAGE_NONE][0]['tid']) ) {
    // Look for any Category having Term Page.
    foreach($node->field_category[LANGUAGE_NONE] as $item) {
      if ( !($term = taxonomy_term_load($item['tid'])) ) {
        continue;
      }
      
      if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
        $variables['term_page'] = $term;
        break;
      }
    }
  }
}

/**
 * Preprocess page for Taxonomy.
 */
function nel_preprocess_page_taxonomy(&$variables) {
  if ( !(arg(0) == 'taxonomy' && arg(1) == 'term' && intval(arg(2)) > 0 && $term = taxonomy_term_load(arg(2))) ) {
    return;
  }
    
  if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
    $variables['term_page'] = $term;
  }
  
}

/**
 * Apply Logo class to Body.
 */
function nel_preprocess_page_apply_logo(&$variables) {
  if ( !isset($variables['term_page']) ) {
    return;
  }
  
  $term = $variables['term_page'];
  $url = url("taxonomy/term/{$term->tid}");
  $variables['front_page'] = $url;
}