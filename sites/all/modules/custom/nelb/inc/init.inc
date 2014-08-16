<?php
/**
 * Implements hook_init.
 */
function nelb_init() {
  $q = $_GET['q'];
  
  // Special Cases
  if ( arg(0) == 'node' && arg(2) == 'edit' ) {
    $q = 'node/add/article';
  }
  
  // Switch
  switch($q) {
    case 'admin/blocks':
    case 'admin/categories':
    case 'admin/articles':
    case 'admin/articulos':
      drupal_add_css(drupal_get_path('theme', 'nel') . '/css/typography.css');
      drupal_add_css(drupal_get_path('module', 'nelb') . '/css/nelb-table.css');
      break;

    case 'node/add/article':
      drupal_add_css(drupal_get_path('module', 'nelb') . '/css/nelb-categories.css');
      break;
  }
}