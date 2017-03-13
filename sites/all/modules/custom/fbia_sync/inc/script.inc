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
  $end = time();
  $seconds = $end - $start;
  $minutes = intval($seconds / 60);
  $seconds = $seconds % 60;
  $seconds = number_format($seconds);
  $minutes = number_format($minutes);
  $time_spent = "{$minutes}m {$seconds}s";
  
  echo "**************************************\n";
  echo "*  Finished in {$time_spent}   *\n";
  echo "**************************************\n\n";
}
