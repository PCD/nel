<?php
/**
 * Implements hook_permissions.
 */
function fbia_sync_permission() {
  return array(
    'Configure FBIA' => array(
      'title' => 'Configure FBIA',
      'description' => 'Configure FBIA',
    ),
    'Access FBIA' => array(
      'title' => 'Access FBIA',
      'description' => 'Access FBIA',
    ),
    'Test FBIA Sync' => array(
      'title' => 'Test FBIA Sync',
      'description' => 'Test FBIA Sync',
    ),
    'FB Login' => array(
      'title' => 'FB Login',
      'description' => 'FB Login',
    ),
    'Use iFrame for Ads' => array(
      'title' => 'Use iFrame for Ads',
      'description' => 'Use iFrame for Ads',
    ),
  );
}

/**
 *
 */
function fbia_sync_test_access($node, $permission) {
  if ($node->type != 'article') {
    return FALSE;
  }
  
  return user_access($permission);
}
