<?php
/**
 * Implements hook_process_html.
 */
function nelads_process_html(&$vars) {
  if ( nelads_can_we_show_ads() ) {
    nelads_process_html_google_class($vars, 'apto-para-todo-publico');
    return;
  }
  
  nelads_process_html_google_class($vars, 'apto-para-adulto');
  
  // Delete Ad Article Detail
  //$vars['page'] = preg_replace('/<p><!--#block-inject-1-start-->.*?<!--#block-inject-1-end-->/msi', '', $vars['page']);
  
  // Delete Ad Article Comments
  $vars['page'] = preg_replace('/<!--#nelads-block-4-start-->.*?<!--#nelads-block-4-end-->/msi', '', $vars['page']);
  
  // Delete Ad Article Header
  $vars['page'] = preg_replace('/<!--#nelads-block-5-start-->.*?<!--#nelads-block-5-end-->/msi', '', $vars['page']);
  
  // Delete Ad Related Articles
  $vars['page'] = preg_replace('/<!--#nelads-block-6-start-->.*?<!--#nelads-block-6-end-->/msi', '', $vars['page']);
  
  // Delete Ad Global Header
  $vars['page'] = preg_replace('/<!--#nelads-block-2-start-->.*?<!--#nelads-block-2-end-->/msi', '', $vars['page']);
  
  // Delete Ad Global Sidebar
  $vars['page'] = preg_replace('/<!--#nelads-block-3-start-->.*?<!--#nelads-block-3-end-->/msi', '', $vars['page']);
  
  // Delete Ad Micrositio
  $vars['page'] = preg_replace('/<!--#nelads-block-micrositio-start-->.*?<!--#nelads-block-micrositio-end-->/msi', '', $vars['page']);
  
  // Delete Left Overs
  $pattern = '/<div[^>]*?class="[^"]*?field-collection-item-field-generic-block-banner3[^"]*">\s*<div class="[^"]*? field-name-field-banner-block[^"]*?">\s*<div class="nelads-micrositio-block">\s*?<\/div>\s*?<\/div><\/div>/msi';
  $vars['page'] = preg_replace($pattern, '', $vars['page']);
  
  $pattern = '/<div id="block-nelads-nelads-article-comments"[^>]*?>\s*<div class="block__content">\s*<\/div>\s*<\/div>/msi';
  $vars['page'] = preg_replace($pattern, '', $vars['page']);
}

/**
 * Fill all Double Click blocks with correct Google Class.
 */
function nelads_process_html_google_class(&$vars, $google_class_value) {
  $vars['scripts'] = str_replace('google_class_value', $google_class_value, $vars['scripts']);
}
