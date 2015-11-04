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
  
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));
  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {
      googletag.defineSlot('/15651346/Article-Body-300x250', [300, 250], 'div-gpt-ad-1446621104256-0').addService(googletag.pubads());
      // Start Custom Criteria
      googletag.pubads().setTargeting('google_class','{$google_class}');
      // End Custom Criteria
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Article-Body-300x250', 
    'div_id' => 'div-gpt-ad-1446621104256-0', 
    'style' => 'height:250px; width:300px;', 
  ));
}
