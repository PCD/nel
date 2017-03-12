<?php
/**
 * Implements hook_node_insert.
 */
function fbia_sync_node_insert($node) {
  if ($node->type != 'article') {
    return;
  }
  
  // Insert record for further processing.
  fbia_sync_save_record($node);
  
  //$output = fbia_sync_prepare_node($node);
  
  // Mandar a API.
}

/**
 * Implements hook_node_update.
 */
function fbia_sync_node_update($node) {
  if ($node->type != 'article') {
    return;
  }
  
  // Mark record to be processed again.
  fbia_sync_save_record($node);
}

/**
 * Implements hook_node_delete.
 */
function fbia_sync_node_delete($node) {
  if ($node->type != 'article') {
    return;
  }
  
  fbia_sync_delete_record($node);
}
