<?php
/**
 * Returns the dc-article_header block.
 */
function nelads_block_view_dc_header() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1250, 0], [[900, 90]]).
        addSize([1088, 0], [[728, 90]]).
        addSize([486, 0], [[468, 60]]).
        addSize([338, 0], [[320, 100]]).
        addSize([0, 0], [[234, 60], [180, 150]]).
        build();
        
      googletag.defineSlot('/15651346/Header', [[900, 90], [728, 90], [468, 60], [320, 100], [234, 60], [180, 150]], 'div-gpt-ad-1460578771697-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Header', 
    'div_id' => 'div-gpt-ad-1460578771697-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_20 block.
 */
function nelads_block_view_dc_sidebar_20() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 115], [300, 80]]).
        addSize([733, 0], [[220, 84], [220, 59]]).
        addSize([316, 0], [[300, 250], [300, 115], [300, 80]]).
        addSize([236, 0], [[220, 84], [220, 59]]).
        addSize([216, 0], [[200, 76], [200, 53], [200, 200]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/Sidebar20', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450250971213-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Sidebar20', 
    'div_id' => 'div-gpt-ad-1450250971213-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_19 block.
 */
function nelads_block_view_dc_sidebar_19() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 169]]).
        addSize([733, 0], [[220, 183], [220, 124]]).
        addSize([316, 0], [[300, 250], [300, 169]]).
        addSize([236, 0], [[220, 183], [220, 124]]).
        addSize([216, 0], [[200, 166], [200, 167], [200, 112]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/Sidebar19', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450252638117-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Sidebar19', 
    'div_id' => 'div-gpt-ad-1450252638117-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_18 block.
 */
function nelads_block_view_dc_sidebar_18() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 169]]).
        addSize([733, 0], [[220, 183], [220, 124]]).
        addSize([316, 0], [[300, 250], [300, 169]]).
        addSize([236, 0], [[220, 183], [220, 124]]).
        addSize([216, 0], [[200, 166], [200, 167], [200, 112]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/sidebar18', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450252783279-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/sidebar18', 
    'div_id' => 'div-gpt-ad-1450252783279-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_17 block.
 */
function nelads_block_view_dc_sidebar_17() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 169]]).
        addSize([733, 0], [[220, 183], [220, 124]]).
        addSize([316, 0], [[300, 250], [300, 169]]).
        addSize([236, 0], [[220, 183], [220, 124]]).
        addSize([216, 0], [[200, 166], [200, 167], [200, 112]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/sidebar_17', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450302135505-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/sidebar_17', 
    'div_id' => 'div-gpt-ad-1450302135505-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_16 block.
 */
function nelads_block_view_dc_sidebar_16() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 169]]).
        addSize([733, 0], [[220, 183], [220, 124]]).
        addSize([316, 0], [[300, 250], [300, 169]]).
        addSize([236, 0], [[220, 183], [220, 124]]).
        addSize([216, 0], [[200, 166], [200, 167], [200, 112]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/sidebar_16', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450373545348-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/sidebar_16', 
    'div_id' => 'div-gpt-ad-1450373545348-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-sidebar_15 block.
 */
function nelads_block_view_dc_sidebar_15() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [[300, 250], [300, 169]]).
        addSize([733, 0], [[220, 183], [220, 124]]).
        addSize([316, 0], [[300, 250], [300, 169]]).
        addSize([236, 0], [[220, 183], [220, 124]]).
        addSize([216, 0], [[200, 166], [200, 167], [200, 112]]).
        addSize([0, 0], [180, 150]).
        build();
        
      googletag.defineSlot('/15651346/sidebar_15', [[200, 167], [300, 115], [250, 250], [300, 169], [220, 124], [200, 76], [220, 183], [300, 80], [220, 59], [200, 166], [180, 150], [200, 112], [200, 200], [220, 84], [300, 250], [200, 53]], 'div-gpt-ad-1450373663867-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/sidebar_15', 
    'div_id' => 'div-gpt-ad-1450373663867-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-article_body block.
 */
function nelads_block_view_dc_article_body() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));
  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {
      googletag.defineSlot('/15651346/Article-Body-300x250', [300, 250], 'div-gpt-ad-1446621104256-0').addService(googletag.pubads());
      // Start Custom Criteria
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
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
 * Returns the dc-fbia block.
 */
function nelads_block_view_dc_fbia() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([987, 0], [300, 250]).
        addSize([733, 0], [300, 250]).
        addSize([316, 0], [300, 250]).
        addSize([236, 0], [300, 250]).
        addSize([216, 0], [300, 250]).
        addSize([0, 0], [300, 250]).
        build();
        
      //googletag.defineSlot('/15651346/FB_Instant_300x250', [[300, 250]], 'div-gpt-ad-1489337492379-0').
      googletag.defineSlot('/15651346/Article-Body-300x250', [[300, 250]], 'div-gpt-ad-1489337492379-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    //'group_id' => '15651346/FB_Instant_300x250', 
    'group_id' => '15651346/Article-Body-300x250', 
    'div_id' => 'div-gpt-ad-1489337492379-0', 
    'style' => 'height:250px; width:300px', 
  ));
}

/**
 * Returns the dc-microsite_19-wide block.
 */
function nelads_block_view_dc_microsite_19_wide() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1093, 0], [[728, 92]]).
        addSize([1002, 0], [[642, 82]]).
        addSize([748, 0], [[473, 60]]).
        addSize([0, 0], [[300, 38]]).
        build();
        
      googletag.defineSlot('/15651346/Microsite19Wide', [[728, 92], [642, 82], [473, 60], [343, 91], [300, 80], [300, 38], [226, 60]], 'div-gpt-ad-1450427370456-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Microsite19Wide', 
    'div_id' => 'div-gpt-ad-1450427370456-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-microsite_19-half_left block.
 */
function nelads_block_view_dc_microsite_19_half_left() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1093, 0], [[343, 91]]).
        addSize([1002, 0], [[300, 80]]).
        addSize([748, 0], [[226, 60]]).
        addSize([0, 0], [[300, 80]]).
        build();
        
      googletag.defineSlot('/15651346/Microsite19HalfLeft', [[728, 92], [642, 82], [473, 60], [343, 91], [300, 80], [300, 38], [226, 60]], 'div-gpt-ad-1450427490112-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Microsite19HalfLeft', 
    'div_id' => 'div-gpt-ad-1450427490112-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-microsite_19-half_right block.
 */
function nelads_block_view_dc_microsite_19_half_right() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1093, 0], [[343, 91]]).
        addSize([1002, 0], [[300, 80]]).
        addSize([748, 0], [[226, 60]]).
        addSize([0, 0], [[300, 80]]).
        build();
        
      googletag.defineSlot('/15651346/Microsite19HalfRight', [[728, 92], [642, 82], [473, 60], [343, 91], [300, 80], [300, 38], [226, 60]], 'div-gpt-ad-1450427550452-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Microsite19HalfRight', 
    'div_id' => 'div-gpt-ad-1450427550452-0', 
    'style' => '', 
  ));
}

/**
 * Returns the dc-microsite_17-wide block.
 */
function nelads_block_view_dc_microsite_17_wide() {
  drupal_add_js(drupal_get_path('module', 'nelads') . '/js/nelads-dc-general.js', array('weight'=>100));

  static $i;
  $i = isset($i)?$i+1:1;
  if ( $i == 1 ) {
    $js = "googletag.cmd.push(function() {

      var mapping = googletag.sizeMapping().
        addSize([1093, 0], [[728, 92]]).
        addSize([1002, 0], [[642, 82]]).
        addSize([748, 0], [[473, 60]]).
        addSize([0, 0], [[300, 38]]).
        build();
        
        googletag.defineSlot('/15651346/Microsite17Wide', [[728, 92], [642, 82], [473, 60], [343, 91], [300, 80], [300, 38], [226, 60]], 'div-gpt-ad-1450486677457-0').
      defineSizeMapping(mapping).
      setCollapseEmptyDiv(true).
      addService(googletag.pubads());
      googletag.pubads().setTargeting('google_class','google_class_value');
      googletag.pubads().setTargeting('candidato_class','candidato_class_value');
      googletag.pubads().enableSingleRequest();
      googletag.enableServices();
    });";
    drupal_add_js($js, array('type'=>'inline', 'scope'=>'header', 'weight' => 101));
  }
  
  return theme('nelads-dcslot', array(
    'group_id' => '15651346/Microsite17Wide', 
    'div_id' => 'div-gpt-ad-1450486677457-0', 
    'style' => '', 
  ));
}













