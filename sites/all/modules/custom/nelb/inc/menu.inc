<?php
/**
 * Implements hook_menu.
 */
function nelb_menu() {
  $items = array();
  $items['portada'] = array(
    'page callback' => 'nelb_menu_home', 
    'access arguments' => array(TRUE),
    'type' => MENU_CALLBACK, 
  );
  return $items;
}

/**
 * Callback for HomePage.
 */
function nelb_menu_home() {
  // Get Node Blocks and Taxonomy Blocks for HomePage.
  $params = array();
  $blocks = nelb_data_get_blocks($params);
  return nelb_theme_blocks($blocks);
}