<?php
/**
 * Implements hook_init.
 */
function nelb_init() {
  switch($_GET['q']) {
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