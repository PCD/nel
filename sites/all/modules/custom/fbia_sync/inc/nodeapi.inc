<?php
/**
 * Implements hook_node_insert.
 */
function fbia_sync_node_insert($node) {
  // Crear html output.
  $output = fbia_sync_prepare_node($node);
  
  print_r($output);
  exit;
  
  // Mandar a API.
}

/**
 * Implements hook_node_update.
 */
function fbia_sync_node_update($node) {
  
}

/**
 * Implements hook_node_delete.
 */
function fbia_sync_node_delete($node) {
  
}
