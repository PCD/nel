<?php
/**
 * Implements hook_init.
 */
function nelb_init() {
  $q = $_GET['q'];
  
  // Special Cases
  if ( arg(0) == 'node' && arg(2) == 'edit' ) {
    $q = 'node/add/article';
  } else if ( arg(0) == 'search' && arg(1) == 'site' ) {
    $q = 'buscador';
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
      drupal_add_js(drupal_get_path('module', 'nelb') . '/js/nelb-main-category.js');
      break;

    case 'buscador':
      $keywords = arg(2);
      drupal_set_title('Buscar: ' . arg(2));
      break;
  }
}