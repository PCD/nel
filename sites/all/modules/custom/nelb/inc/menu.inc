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
  // Ajax Block
  $url = 'ajax/block';
  $j = 2;
  $page_arguments = array();
  for($i=0; $i<5; $i++) {
    $url .= '/%';
    $page_arguments[] = ($i+$j);
    $items[$url] = array(
      'page callback' => 'nelb_menu_ajax_block', 
      'page arguments' => $page_arguments, 
      'access arguments' => array('access nelb pages'), 
      'type' => MENU_CALLBACK, 
    );
  }
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
  $output = '';
  // Get Top Blocks
  $output .= nelb_menu_taxonomy_home_promoted_content($term);
  $output .= nelb_menu_taxonomy_home_popular_content($term);
  
  // Get Node Blocks and Taxonomy Blocks for HomePage.
  $params = array(
    'promote_to' => 1, 
    'pid' => $term->tid, 
    'place' => 0, 
    'random' => TRUE, 
  );
  $blocks = nelb_data_get_blocks($params);
  $output .= nelb_theme_blocks($blocks);
  return $output;
}

/**
 * Gets Promoted Content
 */
function nelb_menu_taxonomy_home_promoted_content($term) {
  $output = '';
  if ( isset($term->field_show_promoted_content[LANGUAGE_NONE][0]['value']) && $term->field_show_promoted_content[LANGUAGE_NONE][0]['value'] == 1 ) {
    if ( isset($term->field_videos_only[LANGUAGE_NONE][0]['value']) && $term->field_videos_only[LANGUAGE_NONE][0]['value'] == 1 ) {
      $output = views_embed_view('last_promoted', 'block_1', $term->tid);
    } else {
      $output = views_embed_view('last_promoted', 'block', $term->tid);
    }
  }
  return $output;
}

/**
 * Gets Popular Content.
 */
function nelb_menu_taxonomy_home_popular_content($term) {
  $output = '';
  if ( isset($term->field_most_popular_content[LANGUAGE_NONE][0]['value']) && $term->field_most_popular_content[LANGUAGE_NONE][0]
  ['value'] == 1 ) {
    $output = "<div id=\"popular-content\" class=\"block\">
    <h2 class=\"block__title\">Lo Mas Visto</h2>
    <div class=\"block__content\">\n";
    if ( isset($term->field_videos_only[LANGUAGE_NONE][0]['value']) && $term->field_videos_only[LANGUAGE_NONE][0]['value'] == 1 ) {
      $output .= views_embed_view('most_popular_content', 'block_1', $term->tid);
    } else {
      $output .= views_embed_view('most_popular_content', 'block', $term->tid);
    }
    $output .= "</div></div>\n";
  }
  return $output;
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
}

/**
 * Overrides callback taxonomy_term_page.
 */
function nelb_taxonomy_term_page_generic($term) {
  // Common Logic
  nelb_taxonomy_term_page_common($term);
  
  $markup = '';
  // Add Author Header
  if ( $term->vid == 3 ) {
    $markup .= taxonomy_term_view($term, 'author_header');
  }
  
  // Content
  $markup .= views_embed_view('taxonomy_page_articles', 'block', $term->tid);
  $build['term_heading'] = array(
    //'#prefix' => '<div class="term-listing-heading">',
    //'#suffix' => '</div>',
    '#markup' => $markup, 
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

/**
 * Returns a Block for skipping ajax.
 */
function nelb_menu_ajax_block($type, $arg1, $arg2 = null, $arg3 = null, $arg4 = null, $arg5 = null) {
  switch($type) {
    case 'grid':
      nelb_menu_ajax_block_grid($type, $arg1, $arg2, $arg3, $arg4, $arg5);
      break;

    case 'node':
      
      break;
  }
}

/**
 *
 */
function nelb_menu_ajax_block_grid($type, $arg1, $arg2, $arg3, $arg4) {
  $params = array();
  if ( $type == 'node' ) {
    $params['term'] = false;
  } else {
    $params['node'] = false;
  }
  if ( !is_null($arg1) ) {
    $params['promote_to'] = $arg1;
  }
  if ( !is_null($arg2) ) {
    $params['place'] = $arg2;
  }
  if ( !is_null($arg3) ) {
    $params['size'] = $arg3;
  }
  if ( !is_null($arg4) ) {
    $params['column'] = $arg4;
  }
  $params['unique'] = true;
  $response = nelb_data_get_blocks_node($params);
}