<?php
/**
 * Returns the dc-article_body block.
 */
function nelads_block_view_dc_article_body() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }
  
  $google_class = 'apto-para-adulto';
  if ( isset($node->field_google_class[LANGUAGE_NONE][0]['value']) ) {
    $google_class = $node->field_google_class[LANGUAGE_NONE][0]['value'];
  }
  
  drupal_add_js(array('neladsdc' => array('google_class' => $google_class)), 'setting');
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js');
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-article_body.js');
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Article-Body-300x250', 
    'div_id' => 'div-gpt-ad-1446621104256-0', 
    'style' => 'height:250px; width:300px;', 
  ));
}
