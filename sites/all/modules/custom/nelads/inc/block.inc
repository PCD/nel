<?php
/**
 * Implements hook_block_info.
 */
function nelads_block_info() {
  $blocks = array();
  /** Double Click **/
  $blocks['dc-article_body'] = array(
    'info' => 'DoubleClick - Article Body', 
  );
  $blocks['dc-sidebar_20'] = array(
    'info' => 'DoubleClick - Sidebar 20', 
  );
  $blocks['dc-sidebar_19'] = array(
    'info' => 'DoubleClick - Sidebar 19', 
  );
  $blocks['dc-sidebar_18'] = array(
    'info' => 'DoubleClick - Sidebar 18', 
  );
  $blocks['dc-sidebar_17'] = array(
    'info' => 'DoubleClick - Sidebar 17', 
  );
  $blocks['dc-sidebar_16'] = array(
    'info' => 'DoubleClick - Sidebar 16', 
  );
  $blocks['dc-sidebar_15'] = array(
    'info' => 'DoubleClick - Sidebar 15', 
  );
  
  /** Micrositio Double Click **/
  $blocks['dc-microsite-19-wide'] = array(
    'info' => 'DoubleClick - Micrositio 19 - Wide', 
  );
  $blocks['dc-microsite-19-half_left'] = array(
    'info' => 'DoubleClick - Micrositio 19 - Half Left', 
  );
  $blocks['dc-microsite-19-half_right'] = array(
    'info' => 'DoubleClick - Micrositio 19 - Half Right', 
  );
  $blocks['dc-microsite-17-wide'] = array(
    'info' => 'DoubleClick - Micrositio 17 - Wide', 
  );
  
  /** Regular **/
  $blocks['nelads-article_detail'] = array(
    'info' => 'Nel Ads - Article Detail', 
  );
  $blocks['nelads-article_comments'] = array(
    'info' => 'Nel Ads - Article Comments', 
  );
  $blocks['nelads-article_header'] = array(
    'info' => 'Nel Ads - Article Header', 
  );
  $blocks['nelads-related_articles'] = array(
    'info' => 'Nel Ads - Related Articles', 
  );
  $blocks['nelads-global_header'] = array(
    'info' => 'Nel Ads - Global Header', 
  );
  $blocks['nelads-global_sidebar'] = array(
    'info' => 'Nel Ads - Global Sidebar', 
  );
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function nelads_block_view($delta = '') {
  $block = array();
  switch($delta) {
    // Double Click
    case 'dc-article_body':
      $block['content'] = nelads_block_view_dc_article_body();
      break;
    
    case 'dc-sidebar_20':
      $block['content'] = nelads_block_view_dc_sidebar_20();
      break;
    
    case 'dc-sidebar_19':
      $block['content'] = nelads_block_view_dc_sidebar_19();
      break;
    
    case 'dc-sidebar_18':
      $block['content'] = nelads_block_view_dc_sidebar_18();
      break;
    
    case 'dc-sidebar_17':
      $block['content'] = nelads_block_view_dc_sidebar_17();
      break;
    
    case 'dc-sidebar_16':
      $block['content'] = nelads_block_view_dc_sidebar_16();
      break;
    
    case 'dc-sidebar_15':
      $block['content'] = nelads_block_view_dc_sidebar_15();
      break;

    // Micrositio Double Click
    case 'dc-microsite-19-wide':
      $block['content'] = nelads_block_view_dc_microsite_19_wide();
      break;

    case 'dc-microsite-19-half_left':
      $block['content'] = nelads_block_view_dc_microsite_19_half_left();
      break;

    case 'dc-microsite-19-half_right':
      $block['content'] = nelads_block_view_dc_microsite_19_half_right();
      break;
    
    case 'dc-microsite-17-wide':
      $block['content'] = nelads_block_view_dc_microsite_17_wide();
      break;
    
    // Adsense
    case 'nelads-article_detail':
      $block['content'] = nelads_block_view_article_detail();
      break;

    case 'nelads-article_comments':
      $block['content'] = nelads_block_view_article_comments();
      break;

    case 'nelads-article_header':
      $block['content'] = nelads_block_view_article_header();
      break;

    case 'nelads-related_articles':
      $block['content'] = nelads_block_view_related_articles();
      break;

    case 'nelads-global_header':
      $block['content'] = nelads_block_view_global_header();
      break;

    case 'nelads-global_sidebar':
      $block['content'] = nelads_block_view_global_sidebar();
      break;

  }
  return $block;
}

/**
 * Returns the nelads-article_detail block.
 */
function nelads_block_view_article_detail() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }

  if ( nelads_ads_count('nelads_block_view_article_detail') > 3 ) {
    return false;
  }
  
  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '3150408355', 
      'ad_format' => 'rectangle', 
    ), 
    /*(object) array(
      'ad_client' => 'ca-pub-5383770617488734', 
      'ad_slot' => '1327010008', 
      'ad_format' => 'rectangle', 
    ),*/ 
  );
  drupal_add_js(array('nelads' => array('ads_article_detail' => $nelads)), 'setting');
  
  return theme('nelads-adslot', array(
    'adslot' => 1, 
    'adsvar' => 'ads_article_detail', 
  ));
}

/**
 * Returns the nelads-article_comments block.
 */
function nelads_block_view_article_comments() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }

  if ( nelads_ads_count('nelads_block_view_article_comments') > 3 ) {
    return false;
  }
  
  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '3604943158', 
      'ad_format' => '', 
    ), 
  );
  drupal_add_js(array('nelads' => array('ads_article_comments' => $nelads)), 'setting');
  
  return theme('nelads-adslot', array(
    'adslot' => 4, 
    'adsvar' => 'ads_article_comments', 
  ));
}

/**
 * Returns the nelads-article_header block.
 */
function nelads_block_view_article_header() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }
  
  if ( nelads_ads_count('nelads_block_view_article_header') > 3 ) {
    return false;
  }

  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '9313399557', 
      'ad_format' => '', 
    ), 
  );
  drupal_add_js(array('nelads' => array('ads_article_header' => $nelads)), 'setting');
  return theme('nelads-adslot', array(
    'adslot' => 5, 
    'adsvar' => 'ads_article_header', 
  ));
}

/**
 * Returns the nelads-related_articles block.
 */
function nelads_block_view_related_articles() {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }
  
  /*if ( nelads_ads_count('nelads_block_view_related_articles') > 3 ) {
    return false;
  }*/

  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '1208586358', 
      'ad_format' => 'autorelaxed', 
    ), 
  );
  drupal_add_js(array('nelads' => array('ads_related_articles' => $nelads)), 'setting');
  return theme('nelads-adslot', array(
    'adslot' => 6, 
    'adsvar' => 'ads_related_articles', 
  ));
}

/**
 * Returns the nelads-global_header block.
 */
function nelads_block_view_global_header() {
  if ( (arg(0) == 'node' && intval(arg(1)) > 0 && is_null(arg(2)) && ($node=node_load(arg(1))) && $node->type == 'article') ) {
    return false;
  }
  
  if ( nelads_ads_count('nelads_block_view_global_header') > 3 ) {
    return false;
  }

  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '3634759556', 
      'ad_format' => '', 
    ), 
    /*(object) array(
      'ad_client' => 'ca-pub-5383770617488734', 
      'ad_slot' => '3824648002', 
      'ad_format' => '', 
    ),*/ 
  );
  drupal_add_js(array('nelads' => array('ads_global_header' => $nelads)), 'setting');
  return theme('nelads-adslot', array(
    'adslot' => 2, 
    'adsvar' => 'ads_global_header', 
  ));
}

/**
 * Returns the nelads-global_sidebar block.
 */
function nelads_block_view_global_sidebar() {
  if ( nelads_ads_count('nelads_block_view_global_sidebar') > 3 ) {
    return false;
  }
  
  $nelads = array(
    (object) array(
      'ad_client' => 'ca-pub-6659210167862789', 
      'ad_slot' => '2060294754', 
      'ad_format' => 'rectangle', 
    ), 
    /*(object) array(
      'ad_client' => 'ca-pub-5383770617488734', 
      'ad_slot' => '1089677603', 
      'ad_format' => 'rectangle', 
    ),*/ 
  );
  drupal_add_js(array('nelads' => array('ads_global_sidebar' => $nelads)), 'setting');
  return theme('nelads-adslot', array(
    'adslot' => 3, 
    'adsvar' => 'ads_global_sidebar', 
  ));
}

/**
 * Returns the nelads-global_sidebar block.
 */
function nelads_block_view_micro_page() {
  if ( nelads_ads_count('nelads_block_view_micro_page') > 3 ) {
    return false;
  }
  
  if ( !($nelads = nelads_get_microsite_ad_slot()) ) {
    return false;
  }
  
  $id_ad = 'ads_micrositio_' . $nelads[0]->ad_number;
  drupal_add_js(array('nelads' => array($id_ad => $nelads)), 'setting');
  return theme('nelads-adslot', array(
    'adslot' => 'micrositio', 
    'adsvar' => $id_ad, 
    'wrapper_class' => 'nelads-micrositio-block', 
  ));
}






