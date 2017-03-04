<?php
/**
 * Implements hook_permissions.
 */
function fbia_sync_permissions() {
  return array(
    'Configure FBIA' => array(
      'title' => 'Configure FBIA',
      'description' => 'Configure FBIA',
    ),
    'Access FBIA' => array(
      'title' => 'Access FBIA',
      'description' => 'Access FBIA',
    ),
  );
}
