<?php
/**
 * Saves a default record into fbia sync table.
 */
function fbia_sync_save_record($node) {
  if (($record = fbia_sync_load_record($node))) {
    // Update.
    fbia_sync_update_record($node);
  }
  else {
    // Insert.
    fbia_sync_insert_record($node);
  }
}
/**
 * Inserts a default record into fbia sync table.
 */
function fbia_sync_insert_record($node) {
  $data = array(
    'nid' => $node->nid,
    'node_published' => $node->status,
    'sync_enabled' => 0,
  );
  if (isset($node->field_fbia_sync[LANGUAGE_NONE][0]['value'])) {
    $data['sync_enabled'] = $node->field_fbia_sync[LANGUAGE_NONE][0]['value'];
  }
  return drupal_write_record('fbia_sync_article', $data);
}

/**
 * Updates a record to indicates it has to be processed again.
 */
function fbia_sync_update_record($node) {
  $sync_enabled = 0;
  if (isset($node->field_fbia_sync[LANGUAGE_NONE][0]['value'])) {
    $sync_enabled = $node->field_fbia_sync[LANGUAGE_NONE][0]['value'];
  }
  return db_update('fbia_sync_article')
  ->fields(array(
    'sync_status' => 0,
    'node_published' => $node->status,
    'sync_enabled' => $sync_enabled,
  ))
  ->condition('nid', $node->nid)
  ->execute();
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
 * Deletes fbia record.
 */
function fbia_sync_delete_record_by_nid($nid) {
  return db_delete('fbia_sync_article')
  ->condition('nid', $nid)
  ->execute();
}

/**
 * Marks a fbia_sync record as processed but really skipped.
 */
function fbia_sync_mark_record_skipped($node) {
  $updates = array(
    'sync_status' => 1,
    'sync_time' => time(),
  );
  return db_update('fbia_sync_article')
  ->fields($updates)
  ->condition('nid', $node->nid)
  ->execute();
}

/**
 * Marks a fbia_sync record as processed.
 */
function fbia_sync_mark_record($node, $errors = 0, $response = NULL) {
  $updates = array(
    'sync_status' => 1,
    'sync_time' => time(),
    'sync_errors' => $errors,
    'response' => $response,
  );
  if (!empty($response)) {
    $response = serialize($response);
    $updates['response'] = $response;
  }
  return db_update('fbia_sync_article')
  ->fields($updates)
  ->condition('nid', $node->nid)
  ->execute();
}

/**
 * Load fbia item.
 */
function fbia_sync_load_record($node) {
  return db_select('fbia_sync_article', 'f')
  ->fields('f', array('nid'))
  ->condition('nid', $node->nid)
  ->execute()
  ->fetchAssoc();
}


/**
 * Get unprocessed fbia items.
 */
function fbia_sync_get_records($limit = 100, $offset = 0) {
  return db_select('fbia_sync_article', 'f')
  ->fields('f', array('nid', 'sync_enabled', 'node_published'))
  ->condition('sync_status', 0)
  ->range(0, $limit)
  ->execute()
  ->fetchAll();
}

/**
 * Get unprocessed fbia items.
 */
function fbia_sync_fetch($limit = 100, $offset = 0) {
  return db_select('fbia_sync_article', 'f')
  ->fields('f')
  ->orderBy('node_published', 'DESC')
  ->range($offset, $limit)
  ->execute()
  ->fetchAll();
}


