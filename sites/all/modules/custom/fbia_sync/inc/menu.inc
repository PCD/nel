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
    'access arguments' => array('Test FBIA Sync'),
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
  $node_args = fbia_sync_prepare_node($node);
  $output = theme('fbia-sync--article', $node_args);
  print $output;
  exit;
}
