<?php

/**
 * Implements hook_preprocess_page().
 */
function nel_preprocess_page(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
  
  // Proccess HTML for Nodes
  nel_preprocess_page_node($variables);
  
  // Proccess HTML for Taxonomy
  nel_preprocess_page_taxonomy($variables);
  
  // Apply Logo
  nel_preprocess_page_apply_logo($variables);
  
  // Add Search Button
  nel_preprocess_page_search($variables);
}

/**
 * Preprocess page for Node.
 */
function nel_preprocess_page_node(&$variables) {
  if ( !(arg(0) == 'node' && intval(arg(1)) > 0 && ($node = node_load(arg(1)))) ) {
    return;
  }
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
 * Preprocess page for Taxonomy.
 */
function nel_preprocess_page_taxonomy(&$variables) {
  if ( !(arg(0) == 'taxonomy' && arg(1) == 'term' && intval(arg(2)) > 0 && $term = taxonomy_term_load(arg(2))) ) {
    return;
  }
    
  if ( isset($term->field_taxonomy_page[LANGUAGE_NONE][0]['value']) && $term->field_taxonomy_page[LANGUAGE_NONE][0]['value'] == 1 ) {
    $variables['term_page'] = $term;
  }
  
}

/**
 * Apply Logo class to Body.
 */
function nel_preprocess_page_apply_logo(&$variables) {
  if ( !isset($variables['term_page']) ) {
    return;
  }
  
  $term = $variables['term_page'];
  $url = url("taxonomy/term/{$term->tid}");
  $variables['front_page'] = $url;
}

/**
 * Preprocess Page for Search.
 */
function nel_preprocess_page_search(&$variables) {
  $search_block = &$variables['page']['navigation']['search_form'];
  $search_block['#prefix'] = "<div id=\"search-area\"><a class=\"cta\" href=\"#\">Buscar</a>\n";
  $search_block['#suffix'] = "</div>\n";
}