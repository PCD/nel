<?php
/**
 *
 */
function fbia_sync_iframe_block($node, $index) {
  print $node->field_iframe_block[LANGUAGE_NONE][$index];
  exit;
}
