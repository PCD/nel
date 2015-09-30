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
  return theme('nelads-article_detail');
}
