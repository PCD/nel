<?php
/**
 * Returns the dc-article_body block.
 */
function nelads_block_view_dc_article_body() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));
  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {
      googletag.defineSlot('/15651346/Article-Body-300x250', [300, 250], 'div-gpt-ad-1446621104256-0').addService(googletag.pubads());
      // Start Custom Criteria
      googletag.pubads().setTargeting('google_class','google_class_value');
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

/**
 *
 */
function nelads_block_view_dc_sidebar_20() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1002, 0], [[300, 250], [300, 115], [300, 80]]).
        addSize([748, 0], [[220, 84], [220, 59]]).
        addSize([316, 0], [[300, 250], [300, 115], [300, 80]]).
        addSize([236, 0], [[220, 84], [220, 59]]).
        addSize([216, 0], [[200, 76], [200, 53], [200, 200]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/Sidebar20', [[300, 250], [300, 115], [300, 80], [220, 84], [220, 59], [200, 76], [200, 53], [200, 200]], 'div-gpt-ad-1450250971213-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 102));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Sidebar20', 
    'div_id' => 'div-gpt-ad-1450250971213-0', 
    'style' => '', 
  ));
}