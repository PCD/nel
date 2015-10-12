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
  
  // Delete Ad Global Header
  $vars['page'] = preg_replace('/<!--#nelads-block-2-start-->.*?<!--#nelads-block-2-end-->/msi', '', $vars['page']);
  
  // Delete Ad Global Sidebar
  $vars['page'] = preg_replace('/<!--#nelads-block-3-start-->.*?<!--#nelads-block-3-end-->/msi', '', $vars['page']);
  
  // Delete Ad Micrositio
  $vars['page'] = preg_replace('/<!--#nelads-block-micrositio-start-->.*?<!--#nelads-block-micrositio-end-->/msi', '', $vars['page']);
}
