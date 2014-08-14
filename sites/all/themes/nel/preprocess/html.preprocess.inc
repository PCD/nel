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
}

/**
 * Preprocess html for Node.
 */
function nel_preprocess_html_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
  if ( isset($node->field_category[LANGUAGE_NONE][0]['tid']) ) {
    // Look for any Category having Term Page.
    foreach($node->field_category[LANGUAGE_NONE] as $item) {
      if ( !($term = taxonomy_term_load($item['tid'])) ) {
        continue;
      }
      
      if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
        $variables['term_page'] = $term;
        break;
      }
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
  $style .= "background-image: url('{$image_path}') !important;";
  $style .= "background-size: {$ancho}px {$alto}px !important;";
  $style .= "width: {$ancho}px !important;";
  $style .= "height: {$alto}px !important;";
  $style .= "}";
  drupal_add_css($style, array('type' => 'inline', 'media' => 'all', 'group' => CSS_THEME));
}