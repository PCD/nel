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
  
  // Category
  nel_preprocess_page_node_category($variables, $node);
  
  // Gallery Stuff
  nel_preprocess_page_node_gallery($variables, $node);
  
  // Facebook Tags
  nel_preprocess_page_node_facebook_tags($variables, $node);
  
  // Preroll Videos.
  if ( $node->type == 'video_preroll' ) {
    drupal_add_js(drupal_get_path('theme', 'nel') . '/js/nel.jwplayer.js');
    drupal_add_js(drupal_get_path('theme', 'nel') . '/js/nel.video-preroll.js');
  }
}

/** 
 * Helper for nel_preprocess_page_node on Gallery.
 */
function nel_preprocess_page_node_gallery(&$variables, $node) {
  if ( $node->type != 'article' ) {
    return;
  }
}

/**
 * Helper for nel_preprocess_page_node on Category.
 */
function nel_preprocess_page_node_category(&$variables, $node) {
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

/**
 * Facbook Tags for Nodes.
 */
function nel_preprocess_page_node_facebook_tags(&$variables, $node) {
  // Prepare Tags
  $fb_tags = array();
  $fb_title = $fb_body = $fb_image = NULL;
  
  // Check for data on Facebook Tags field.
  if ( isset($node->field_facebook_tags[LANGUAGE_NONE][0]['value']) && !empty($node->field_facebook_tags[LANGUAGE_NONE][0]['value'])) {
    $fc_id = $node->field_facebook_tags[LANGUAGE_NONE][0]['value'];
    $fc_items = entity_load('field_collection_item', array($fc_id));
    $fc_item = $fc_items[$fc_id];
    
    // FB Title from Facebook Tags
    if ( isset($fc_item->field_facebook_title[LANGUAGE_NONE][0]['value']) && !nel_is_empty($fc_item->field_facebook_title[LANGUAGE_NONE][0]['value']) ) {
      $fb_title = nel_whitener($fc_item->field_facebook_title[LANGUAGE_NONE][0]['value']);
    }
    
    // FB Body from Facebook Tags
    if ( isset($fc_item->field_facebook_body[LANGUAGE_NONE][0]['value']) && !nel_is_empty($fc_item->field_facebook_body[LANGUAGE_NONE][0]['value']) ) {
      $fb_body = nel_whitener($fc_item->field_facebook_body[LANGUAGE_NONE][0]['value']);
    }
    
    // FB Image from Facebook Tags
    if ( isset($fc_item->field_facebook_image[LANGUAGE_NONE][0]['uri']) && !empty($fc_item->field_facebook_image[LANGUAGE_NONE][0]['uri']) ) {
      $fb_image = image_style_url('facebook_sharing', $fc_item->field_facebook_image[LANGUAGE_NONE][0]['uri']);
    }
  }
  
  // FB Title
  if ( is_null($fb_title) ) {
    if ( isset($node->title) && !nel_is_empty($node->title) ) {
      $fb_title = nel_whitener($node->title);
    } else {
      $fb_title = 'Nayarit En Linea';
    }
  }
  
  // FB Body
  if ( is_null($fb_body) ) {
    if ( isset($node->body[LANGUAGE_NONE][0]['value']) && !nel_is_empty($node->body[LANGUAGE_NONE][0]['value'])) {
      $fb_body = nel_whitener($node->body[LANGUAGE_NONE][0]['value']);
    } else {
      $fb_body = 'El Portal de Nayarit';
    }
  }
  
  // FB Image
  if ( is_null($fb_image) ) {
    if ( isset($node->field_meta_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_meta_image[LANGUAGE_NONE][0]['uri']) ) {
      $fb_image = image_style_url('facebook_sharing', $node->field_meta_image[LANGUAGE_NONE][0]['uri']);
    } else if ( isset($node->field_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_image[LANGUAGE_NONE][0]['uri']) ) {
      $fb_image = image_style_url('facebook_sharing', $node->field_image[LANGUAGE_NONE][0]['uri']);
    } else if ( isset($node->field_video_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_video_image[LANGUAGE_NONE][0]['uri']) ) {
      $fb_image = image_style_url('facebook_sharing', $node->field_video_image[LANGUAGE_NONE][0]['uri']);
    } else {
      $fb_image = 'http://www.nayaritenlinea.mx/sites/all/themes/nel/logo_retina.png';
    }
  }
  
  // Build Tags Array
  $fb_tags['fb_metatag_title'] = array(
    'og:title' => $fb_title, 
  );
  $fb_tags['fb_metatag_description'] = array(
    'og:description' => $fb_body, 
  );
  $fb_tags['fb_metatag_image'] = array(
    'og:image' => $fb_image, 
  );
  $fb_tags['fb_metatag_type'] = array(
    'og:type' => 'article', 
  );
  
  // Execute Tags
  foreach($fb_tags as $fb_key => $fb_tag) {
    $tag_element = array(
      '#tag' => 'meta', 
      '#attributes' => array(), 
    );
    foreach($fb_tag as $fb_tag_key => $fb_tag_value) {
      $tag_element['#attributes']['property'] = $fb_tag_key;
      $tag_element['#attributes']['content'] = $fb_tag_value;
    }
    drupal_add_html_head($tag_element, $fb_key);
  }
}