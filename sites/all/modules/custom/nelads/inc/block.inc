<?php
/**
 * Implements hook_block_info.
 */
function nelads_block_info() {
  $blocks = array();
  $blocks['nelads-article_detail'] = array(
    'info' => 'Nel Ads - Article Detail', 
  );
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function nelads_block_view($delta = '') {
  $block = array();
  switch($delta) {
    case 'nelads-article_detail':
      $block['content'] = nelads_block_view_article_detail();
      break;
  }
  return $block;
}

/**
 * Returns the nelads-article_detail block.
 */
function nelads_block_view_article_detail() {
  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '3150408355', 
      'ad_format' => 'rectangle', 
    ), 
    (object) array(
      'ad_client' => 'ca-pub-5383770617488734', 
      'ad_slot' => '1327010008', 
      'ad_format' => 'rectangle', 
    ), 
  );
  drupal_add_js(array('nelads' => array('ads' => $nelads)), 'setting');
  return theme('nelads-article_detail');
}
