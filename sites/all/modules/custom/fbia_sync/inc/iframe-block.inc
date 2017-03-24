<?php
/**
 *
 */
function fbia_sync_iframe_block($node, $index) {
  $index--; 
  print $node->field_iframe_block[LANGUAGE_NONE][$index]['value'];
  exit;
}
