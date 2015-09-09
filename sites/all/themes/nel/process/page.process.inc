<?php
/**
 * Implements hook_process_page().
 */
function nel_process_page(&$variables) {
  // Proccess HTML for Nodes
  //nel_process_page_node($variables);
}

/**
 * Implements hook_process_page for Node.
 */
function nel_process_page_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
}