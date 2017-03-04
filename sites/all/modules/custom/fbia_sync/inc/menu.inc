<?php
/**
 * Implements hook_menu.
 */
function fbia_sync_menu() {
  $items = array();
  $items['admin/config/fbia_sync'] = array(
    'title' => 'FBIA',
    'description' => 'Configure Facebook Instant Articles Sync.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('fbia_sync_form'),
    'access arguments' => array('Configure FBIA'),
    'type' => MENU_NORMAL_ITEM,
  );
  return $items;
}
