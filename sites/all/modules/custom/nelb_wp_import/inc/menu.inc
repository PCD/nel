<?php
/**
 *
 */
function nelb_wp_import_menu() {
  $items = array();
  $items['admin/nelb/import'] = array(
    'page callback' => 'nelb_wp_import_menu_callback', 
    'access arguments' => array('access nelb pages'),
    'type' => MENU_CALLBACK, 
  );
  return $items;
}

/**
 *
 */
function nelb_wp_import_menu_callback() {
  nelb_wp_import_parse_file();
}