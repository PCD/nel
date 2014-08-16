<?php
/**
 * Implements hook_menu.
 */
function nelb_menu() {
  $items = array();
  $items['portada'] = array(
    'page callback' => 'nelb_menu_home', 
    'access arguments' => array('access nelb pages'),
    'type' => MENU_CALLBACK, 
  );
  return $items;
}

/**
 * Implements hook_menu_alter.
 */
function nelb_menu_alter(&$items) {
  $items['taxonomy/term/%taxonomy_term']['page callback'] = 'nelb_taxonomy_term_page';
}

/**
 * Callback for HomePage.
 */
function nelb_menu_home() {
  // Get Node Blocks and Taxonomy Blocks for HomePage.
  $params = array(
    'promote_to' => 0, 
    'place' => 0, 
    'random' => TRUE, 
  );
  $blocks = nelb_data_get_blocks($params);
  return nelb_theme_blocks($blocks);
}

/**
 *
 */
function nelb_menu_taxonomy_home($term) {
  // Get Node Blocks and Taxonomy Blocks for HomePage.
  $params = array(
    'promote_to' => 1, 
    'pid' => $term->tid, 
    'place' => 0, 
    'random' => TRUE, 
  );
  $blocks = nelb_data_get_blocks($params);
  return nelb_theme_blocks($blocks);
}

/**
 * Overrides callback taxonomy_term_page.
 */
function nelb_taxonomy_term_page($term) {
  if ( !(isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1) ) {
    return nelb_taxonomy_term_page_generic($term);
  }
  
  // Common Logic
  nelb_taxonomy_term_page_common($term);

  // Content
  $build['term_heading'] = array(
    '#prefix' => '<div class="term-listing-heading">',
    '#suffix' => '</div>',
    '#markup' =>  nelb_menu_taxonomy_home($term), 
    //'term' => taxonomy_term_view($term, 'full'),
  );
  
  return $build;

  if ($nids = taxonomy_select_nodes($term->tid, TRUE, variable_get('default_nodes_main', 10))) {
    $nodes = node_load_multiple($nids);
    $build += node_view_multiple($nodes);
    $build['pager'] = array(
      '#theme' => 'pager',
      '#weight' => 5,
    );
  }
  else {
    $build['no_content'] = array(
      '#prefix' => '<p>',
      '#markup' => t('There is currently no content classified with this term.'),
      '#suffix' => '</p>',
    );
  }
  return $build;
}

/**
 * Overrides callback taxonomy_term_page.
 */
function nelb_taxonomy_term_page_generic($term) {
  // Common Logic
  nelb_taxonomy_term_page_common($term);
  
  // Content
  $build['term_heading'] = array(
    '#prefix' => '<div class="term-listing-heading">',
    '#suffix' => '</div>',
    '#markup' =>  views_embed_view('taxonomy_page_articles', 'block', $term->tid), 
    //'term' => taxonomy_term_view($term, 'full'),
  );
  
  return $build;
}

/**
 * Common taxonomy_term_page logic.
 */
function nelb_taxonomy_term_page_common($term) {
  // If there is a menu link to this term, the link becomes the last part of
  // the active trail, and the link name becomes the page title. Thus, we must
  // explicitly set the page title to be the term title.
  drupal_set_title($term->name);

  // Build breadcrumb based on the hierarchy of the term.
  $current = (object) array(
    'tid' => $term->tid,
  );
  // @todo This overrides any other possible breadcrumb and is a pure hard-coded
  //   presumption. Make this behavior configurable per vocabulary or term.
  $breadcrumb = array();
  while ($parents = taxonomy_get_parents($current->tid)) {
    $current = array_shift($parents);
    $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
  }
  $breadcrumb[] = l(t('Home'), NULL);
  $breadcrumb = array_reverse($breadcrumb);
  drupal_set_breadcrumb($breadcrumb);
  drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);

  // Set the term path as the canonical URL to prevent duplicate content.
  $uri = entity_uri('taxonomy_term', $term);
  drupal_add_html_head_link(array('rel' => 'canonical', 'href' => url($uri['path'], $uri['options'])), TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(array('rel' => 'shortlink', 'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE)))), TRUE);
}