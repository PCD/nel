<?php
/**
 *
 */
function fbia_sync_iframe_block($node, $delta) {
  $output = '';
  if (intval($delta) < 1) {
    print $output;
    exit;
  }
  
  $delta = intval($delta) - 1;
  if (!isset($node->field_iframe_block[LANGUAGE_NONE][$delta]['value'])) {
    print $output;
    exit;
  }
  $field = field_get_items('node', $node, 'field_iframe_block');
  $output = field_view_value('node', $node, 'field_iframe_block', $field[$delta]);
  $output = render($output);
  print "<html><head><style>.twitter-tweet{margin: 0 !important;}</style></head><body style=\"margin:0;padding:0;\">{$output}</body></html>";
  exit;
}
