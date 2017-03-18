<?php
  
/**
 * Returns a log of all menu items being converted into FB IA.
 */
function fbia_sync_menu_log() {
  $page = 1;
  $offset = 0;
  $limit = 100;
  $results = fbia_sync_fetch($limit, $offset);
  print_r($results);exit;
}
