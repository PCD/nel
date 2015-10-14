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
  
  // Delete Ad Article Comments
  $vars['page'] = preg_replace('/<!--#nelads-block-4-start-->.*?<!--#nelads-block-4-end-->/msi', '', $vars['page']);
  
  // Delete Ad Article Header
  $vars['page'] = preg_replace('/<!--#nelads-block-5-start-->.*?<!--#nelads-block-5-end-->/msi', '', $vars['page']);
  
  // Delete Ad Global Header
  $vars['page'] = preg_replace('/<!--#nelads-block-2-start-->.*?<!--#nelads-block-2-end-->/msi', '', $vars['page']);
  
  // Delete Ad Global Sidebar
  $vars['page'] = preg_replace('/<!--#nelads-block-3-start-->.*?<!--#nelads-block-3-end-->/msi', '', $vars['page']);
  
  // Delete Ad Micrositio
  $vars['page'] = preg_replace('/<!--#nelads-block-micrositio-start-->.*?<!--#nelads-block-micrositio-end-->/msi', '', $vars['page']);
}
