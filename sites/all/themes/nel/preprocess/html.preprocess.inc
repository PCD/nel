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