<?php
/**
 * Inserts a default record into fbia sync table.
 */
function fbia_sync_insert_record($node) {
  $data = array(
    'nid' => $node->nid,
  );
  return drupal_write_record('fbia_sync_article', $data);
}

/**
 * Updates a record to indicates it has to be processed again.
 */
function fbia_sync_update_record($node) {
  $data = array(
    'nid' => $node->nid,
    'sync_status' => 0,
  );
  return drupal_write_record('fbia_sync_article', $data);
}

/**
 * Inserts a default record into fbia sync table.
 */
function fbia_sync_save_record($node, $errors, $response) {
  $response = serialize($response);
  $data = array(
    'nid' => $node->nid,
    'sync_status' => 1,
    'sync_time' => time(),
    'sync_errors' => $errors,
    'response' => $response,
  );
  return drupal_write_record('fbia_sync_article', $data);
}

/**
 * Deletes fbia record.
 */
function fbia_sync_delete_record($node) {
  return db_delete('fbia_sync_article')
  ->condition('nid', $node->nid)
  ->execute();
}

/**
 * Get unprocessed fbia items.
 */
function fbia_sync_get_records($limit = 100) {
  return db_select('fbia_sync_article', 'f')
  ->fields('f', array('nid'))
  ->condition('sync_status', 0)
  ->range(0, $limit)
  ->execute()
  ->fetchAssoc();
}


