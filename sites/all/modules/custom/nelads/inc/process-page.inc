<?php
/**
 * Implements hook_process_html.
 */
function nelads_process_html(&$vars) {
  if ( nelads_can_we_show_ads() ) {
    return;
  }
  
  // Delete Ad Article Detail
  $vars['page'] = preg_replace('/<p><!--#block-inject-1-start-->.*?<!--#block-inject-1-end-->/msi', '', $vars['page']);
}