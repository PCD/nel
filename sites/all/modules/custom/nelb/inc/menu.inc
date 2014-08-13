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
function nelb_menu_alter() {
  
}

/**
 * Callback for HomePage.
 */
function nelb_menu_home() {
  // Get Node Blocks and Taxonomy Blocks for HomePage.
  $params = array(
    'random' => TRUE, 
  );
  $blocks = nelb_data_get_blocks($params);
  return nelb_theme_blocks($blocks);
}