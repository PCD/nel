<?php
//require_once dirname(__DIR__) . '/vendor/autoload.php';
//print dirname(__DIR__);
//exit;

/**
 * Process Node into FBIA.
 */
function fbia_sync_process($node) {
  $node_args = fbia_sync_prepare_node($node);
  $output = theme('fbia-sync--article', $node_args);
}