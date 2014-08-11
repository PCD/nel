<?php
/**
 * Implements hook_block_info.
 */
function nelb_block_info() {
  $blocks = array();
  $blocks['sidebar'] = array(
    'info' => 'NELB Grid Sidebar', 
  );
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function nelb_block_view($delta = '') {
  $block = array();
  switch($delta) {
    case 'sidebar':
      $block = nelb_block_view_sidebar();
      break;
  }
  return $block;
}

/**
 * Grid Sidebar Block.
 */
function nelb_block_view_sidebar() {
  $params = array(
    'place' => 1, 
    'random' => true, 
  );
  $blocks = nelb_data_get_blocks($params);
  return array(
    'content' => nelb_theme_blocks($blocks), 
  );
}