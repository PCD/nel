<?php
/**
 * Implements hook_menu.
 */
function fbia_sync_menu() {
  $items = array();
  $items['fbia_sync/login'] = array(
    'page callback' => 'fbia_sync_login',
    'access arguments' => array('FB Login'),
    'file' => 'inc/fb-access.inc',
    'type' => MENU_CALLBACK,
  );
  $items['fbia_sync/callback'] = array(
    'page callback' => 'fbia_sync_callback',
    'access arguments' => array('FB Login'),
    'file' => 'inc/fb-access.inc',
    'type' => MENU_CALLBACK,
  );
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

  return $items;
}

/**
 * Test out nodes against FBIA Sync.
 */
function fbia_sync_test_node($node) {
  fbia_sync_process($node);
}