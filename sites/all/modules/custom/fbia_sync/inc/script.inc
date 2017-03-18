<?php
/**
 * Script that process pending items from FB IA.
 */
function fbia_sync_script_process() {
  $start = time();
  echo "**************************************\n";
  echo "*  FB Instant Articles Sync Process  *\n";
  echo "**************************************\n\n";
  while(($nids = fbia_sync_get_records())) {
    $count = count($nids);
    echo "1.- Got {$count} items, lets process them.\n\n";
    echo "2.- Process the {$count} items:\n";
    foreach($nids as $item) {
      echo " >> Processing Item {$item->nid}...";
      if (($node = node_load($item->nid))) {
        if ($item->sync_enabled == 1 && $item->node_published == 1) {
          fbia_sync_process($node);
          echo " Done!\n";
        }
        else {
          print fbia_sync_mark_record_skipped($node);
          echo " Skipped!\n";
        }
      }
    }
    echo "\n3.- Finished {$count} items.\n\n";
  }
  
  $seconds = time() - $start;
  $time_spent = fbia_sync_get_human_time($seconds);
  
  echo "**************************************\n";
  echo "*  Finished in {$time_spent}   *\n";
  echo "**************************************\n\n";
}

/**
 * Resets all fbia sync records.
 */
function fbia_sync_reset_all() {
  $start = time();
  echo "**************************************\n";
  echo "*  FB Instant Articles Reset ALL  *\n";
  echo "**************************************\n\n";
  
  db_query('UPDATE fbia_sync_article SET sync_status = 0');
  
  $seconds = time() - $start;
  $time_spent = fbia_sync_get_human_time($seconds);
  
  echo "**************************************\n";
  echo "*  Finished in {$time_spent}   *\n";
  echo "**************************************\n\n";
}

/**
 * Convert time from seconds to human.
 */
function fbia_sync_get_human_time($seconds) {
  $minutes = intval($seconds / 60);
  $seconds = $seconds % 60;
  $seconds = number_format($seconds);
  $minutes = number_format($minutes);
  return "{$minutes}m {$seconds}s";
}