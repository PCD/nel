<?php
/**
 * Implements hook_preprocess_node.
 */
function nel_process_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
  
  // Gallery Stuff
  nel_process_node_gallery($variables, $node);
}

/** 
 * Helper for nel_process_page_node on Gallery.
 */
function nel_process_node_gallery(&$variables, $node) {
  if ( $node->type != 'article' ) {
    return;
  }
  
  if ( !isset($node->field_image[LANGUAGE_NONE][0]['uri']) ) {
    return;
  }
  
  if ( count($node->field_image[LANGUAGE_NONE]) < 2 ) {
    return;
  }
  
  
  // Create Gamma Gallery
  $tpath = drupal_get_path('theme', 'nel') . '/js';
  drupal_add_js("{$tpath}/masonry/masonry.pkgd.min.js");
  drupal_add_js("{$tpath}/imagesloaded/imagesloaded.pkgd.min.js");
  drupal_add_js("{$tpath}/masonry-nel.js");
		
  $items = '';
  $max_width = 1300;
  $max_height = 1700;
  foreach($node->field_image[LANGUAGE_NONE] as $i => $image) {
    if ( !empty($image['title']) ) {
      $title = check_plain($image['title']);
    } else {
      $title = check_plain($node->title);
    }
    
    $params = array();
    $params['i'] = $i;
    $params['title'] = $title;
    $params['max_width'] = $max_width;
    $params['max_height'] = $max_height;
    $params['xsmall'] = image_style_url('gamma_xsmall', $image['uri']);
    $params['small'] = image_style_url('gamma_small', $image['uri']);
    $params['medium'] = image_style_url('gamma_medium', $image['uri']);
    $params['large'] = image_style_url('gamma_large', $image['uri']);
    $params['xlarge'] = image_style_url('gamma_xlarge', $image['uri']);
    $params['xxlarge'] = image_style_url('gamma_xxlarge', $image['uri']);
    
    $items .= theme('nel-gamma-item', $params);
  }
  
  $output = theme('nel-gamma', array('items' => $items));
  $variables['gamma_gallery'] = $output;
}
