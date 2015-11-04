<?php

/**
 * Implements hook_preprocess_html().
 */
function nel_preprocess_html(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
  
  // Proccess HTML for Nodes
  nel_preprocess_html_node($variables);
  
  // Proccess HTML for Taxonomy
  nel_preprocess_html_taxonomy($variables);
  
  // Apply Color
  nel_preprocess_html_apply_color($variables);
  
  // Apply Header Background
  nel_preprocess_html_apply_header_background($variables);
  
  // Apply Logo
  nel_preprocess_html_apply_logo($variables);
  
  // Facebook NameSpace
  $variables['more'] = ' xmlns:fb="http://ogp.me/ns/fb#"';
}

/**
 * Preprocess html for Node.
 */
function nel_preprocess_html_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
  
  // Google Class
  nel_preprocess_html_node_google_class($variables, $node);
  
  // Gallery Stuff
  nel_preprocess_html_node_gallery($variables, $node);
  
  // Category Stuff
  nel_preprocess_html_node_category($variables, $node);
}

/**
 *
 */
function nel_preprocess_html_node_google_class(&$variables, $node) {
  $google_class = 'apto-para-adulto';
  if ( isset($node->field_google_class[LANGUAGE_NONE][0]['value']) ) {
    $google_class = $node->field_google_class[LANGUAGE_NONE][0]['value'];
  }
  $variables['attributes_array']['data-google-class'] = $google_class;
}

/**
 *
 */
function nel_preprocess_html_node_gallery(&$variables, $node) {
  $pattern = '/<div\sclass=\"gallery\"><div\sid="field-slideshow-1-wrapper".*?<\/div><\/article>?/msi';
  $page = &$variables['page']['#children'];  
  // 
  $pattern2 = '/<div\sclass="field-slideshow-slide\sfield-slideshow-slide-1[^"]*">.*?<\/a>\s*<\/div>?/msi';
  $page = preg_replace($pattern2, '', $page);
  
  //
  $pattern3 = '/(<ul\sid="field-slideshow-1-pager"[^>]*?>)(<li>.*?<\/li>\s*)/msi';
  $page = preg_replace($pattern3, '$1', $page);
}

/**
 * Helper for nel_preprocess_html_node on Category.
 */
function nel_preprocess_html_node_category(&$variables, $node) {
  if ( isset($node->field_category[LANGUAGE_NONE][0]['tid']) ) {
    // Look for any Category having Term Page.
    $terms_found = array();
    $terms_key = array();
    foreach($node->field_category[LANGUAGE_NONE] as $item) {
      if ( !($term = taxonomy_term_load($item['tid'])) ) {
        continue;
      }
      
      $weight = 0;
      if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
        $terms_found[$term->tid] = $term;
        
        // Look for TV
        if ( $term->tid == 14 ) {
          $weight = 0;
        } // Look for Deportes
        else if ( $term->tid == 154 ) {
          $weight = 1;
        } // Look for Estilos
        else if ( $term->tid == 157 ) {
          $weight = 2;
        } // Look for Portada
        else if ( $term->tid == 9 ) {
          $weight = 9999;
        } else {
          $weight = 10;
        }
        $terms_key[$term->tid] = $weight;
      }
    }
    asort($terms_key);
    
    // There were Any Found?
    if ( !empty($terms_found) ) {
      reset($terms_key);
      $selected = key($terms_key);
      $variables['term_page'] = $terms_found[$selected];
    }
  }
}

/**
 * Preprocess html for Taxonomy.
 */
function nel_preprocess_html_taxonomy(&$variables) {
  if ( !(arg(0) == 'taxonomy' && arg(1) == 'term' && intval(arg(2)) > 0 && $term = taxonomy_term_load(arg(2))) ) {
    return;
  }
    
  if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
    $variables['term_page'] = $term;
    $variables['classes_array'][] = 'term-front-page';
  }
  
}

/**
 * Apply Color class to Body.
 */
function nel_preprocess_html_apply_color(&$variables) {
  if ( isset($variables['term_page']) ) {
    $term = $variables['term_page'];
    
    // Add Class
    if ( isset($term->field_color[LANGUAGE_NONE][0]['value']) ) {
      $term_class = $term->field_color[LANGUAGE_NONE][0]['value'];
      if ( !in_array($term_class, $variables['classes_array']) ) {
        $variables['classes_array'][] = $term_class;
      }
    }
  }
}

/**
 * Apply Header Background class to Body.
 */
function nel_preprocess_html_apply_header_background(&$variables) {
  if ( isset($variables['term_page']) ) {
    $term = $variables['term_page'];
    // Add Class
    if ( isset($term->field_header_background[LANGUAGE_NONE][0]['value']) ) {
      $term_class = $term->field_header_background[LANGUAGE_NONE][0]['value'];
      if ( !in_array($term_class, $variables['classes_array']) ) {
        $variables['classes_array'][] = $term_class;
      }
    }
  }
}

/**
 * Apply Logo class to Body.
 */
function nel_preprocess_html_apply_logo(&$variables) {
  if ( !isset($variables['term_page']) ) {
    return;
  }
  
  $term = $variables['term_page'];
  if ( !isset($term->field_logotipo[LANGUAGE_NONE][0]['uri']) ) {
    return;
  }
  
  $uri = $term->field_logotipo[LANGUAGE_NONE][0]['uri'];
  $ancho = intval($term->field_logo_ancho[LANGUAGE_NONE][0]['value']);
  $alto = intval($term->field_logo_alto[LANGUAGE_NONE][0]['value']);
  
  $image_path = image_style_url('logo', $uri);
  $style = "a.site-logo{";
  $style .= "background-image: url('{$image_path}');";
  $style .= "background-size: {$ancho}px {$alto}px;";
  $style .= "width: {$ancho}px;";
  $style .= "height: {$alto}px;";
  $style .= "}";
  
  // Check for Logo Retina
  if ( isset($term->field_logotipo_retina[LANGUAGE_NONE][0]['uri']) ) {
    $uri = $term->field_logotipo_retina[LANGUAGE_NONE][0]['uri'];
    $image_path = image_style_url('logo', $uri);
    $style .= "@media only screen and (-webkit-min-device-pixel-ratio: 2) {\n";
    $style .= "a.site-logo{";
    $style .= "background-image: url('{$image_path}');";
    $style .= "}";
    $style .= "}";
  }
  
  // Tablet Overrides
  $mheight = 79;
  $mwidth = intval($ancho / $alto * $mheight);
  $style .= "@media only screen and (max-width: 996px) {
    a.site-logo{
      background-size: contain !important;
      width: {$mwidth}px;
      height: {$mheight}px;
    }
  }";
  
  // Mobile Overrides
  $mheight = 57;
  $mwidth = intval($ancho / $alto * $mheight);
  $style .= "@media only screen and (max-width: 748px) {
    a.site-logo{
      width: {$mwidth}px;
      height: {$mheight}px;
    }
  }";
  drupal_add_css($style, array('type' => 'inline', 'media' => 'all', 'group' => CSS_THEME));
}