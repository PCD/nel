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
  $items['node/%node/fbia_sync'] = array(
    'title' => 'FBIA Sync',
    'page callback' => 'fbia_sync_test_node',
    'page arguments' => array(1),
    'access callback' => 'fbia_sync_test_access',
    'access arguments' => array(1, 'Test FBIA Sync'),
    'file' => 'inc/api.inc',
    'weight' => 10,
    'type' => MENU_LOCAL_TASK,
    'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
  );
  $items['fbia_sync/adslot/1'] = array(
    'page callback' => 'fbia_sync_iframe_adslot_1',
    'access arguments' => array('Use iFrame for Ads'),
    'file' => 'inc/ads.inc',
    'type' => MENU_CALLBACK,
  );
  $items['node/%node/iframe-block/%'] = array(
    'page callback' => 'fbia_sync_iframe_block',
    'page arguments' => array(1, 2),
    'access arguments' => array('Use iFrame Block'),
    'file' => 'inc/iframe-block.inc',
    'type' => MENU_CALLBACK,
  );
  $items['admin/fbia_sync'] = array(
    'title' => 'Facebook IA',
    'page callback' => 'fbia_sync_menu_log',
    'access arguments' => array('Configure FBIA'),
    'type' => MENU_CALLBACK,
    'file' => 'inc/menu-log.inc',
  );
  return $items;
}

/**
 * Test out nodes against FBIA Sync.
 */
function fbia_sync_test_node($node) {
  fbia_sync_process_test($node);
}