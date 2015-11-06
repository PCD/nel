<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * Nayarit En Linea theme.
 */

/**
 * Is Real Empty
 */
function nel_is_empty($string) {
  $string = preg_replace('/\s+/msi', '', $string);
  if ( strlen($string) == 0 ) {
    return true;
  }
  return false;
}

/**
 * Overrides Breadcrumb.
 */
function nel_breadcrumb(&$vars) {
  if ( empty($vars['breadcrumb']) ) {
    return '';
  }
  
  $breadcrumb = $vars['breadcrumb'];
  nel_breadcrumb_article($breadcrumb);
  nel_breadcrumb_video($breadcrumb);
  $count = count($breadcrumb);
  if ( $count < 2 ) {
    return '';
  }
  
   // Build output
  $output = "<ul class=\"breadcrumb\">\n";
  
  $items = array();
   // Add items
  foreach($breadcrumb as $i => $crumb) {
    $crumb = str_replace('&lt;br/&gt;', ' ', $crumb);
    $odd = $i%2==0?'even':'odd';
    $order = $i==0?' home':($i==($count-1)?' last':'');
    $class = "item {$odd}{$order}";
    $items[] = "<li class=\"{$class}\">{$crumb}</li>";
  }
  $output .= implode("<li class=\"separator\">&raquo;</li>", $items);

  $output .= "</ul>\n";
  return $output;
}

/**
 * Alters breadcrumb for Article.
 */
function nel_breadcrumb_article(&$breadcrumb) {
  $types = array('article');
  if ( !(arg(0) == 'node' && intval(arg(1)) && is_null(arg(2)) && ($node=node_load(arg(1))) && in_array($node->type, $types)) ) {
    return false;
  }
  
  // Category
  if ( !(isset($node->field_category[LANGUAGE_NONE][0]['tid']) && !empty($node->field_category[LANGUAGE_NONE][0]['tid'])) ) {
    return false;
  }
  
  $tid = $node->field_category[LANGUAGE_NONE][0]['tid'];
  $term = taxonomy_term_load($tid);
  $array = array($term);
  nel_get_breadcrumb_hierarchy($term->tid, $array);
  $new_breadcrumb = array(
    0 => l('Nayarit En Linea', '<front>'), 
  );
  foreach($array as $item) {
    $new_breadcrumb[] = l($item->name, 'taxonomy/term/' . $item->tid);
  }
  $breadcrumb = $new_breadcrumb;
}

/**
 * Nel Make white stuff.
 */
function nel_whitener($string) {
  $string = strip_tags($string);
  $string = str_replace(array('&amp;', '&nbsp;', '&quot;'), array('&', ' ', '"'), $string);
  $string = preg_replace('/\s+/', ' ', $string);
  return trim($string);
}

/**
 * Alters breadcrumb for Video.
 */
function nel_breadcrumb_video(&$breadcrumb) {
  $types = array('video');
  if ( !(arg(0) == 'node' && intval(arg(1)) && is_null(arg(2)) && ($node=node_load(arg(1))) && in_array($node->type, $types)) ) {
    return false;
  }
  
  $new_breadcrumb = array(
    0 => l('Nayarit En Linea', '<front>'), 
    1 => l('TV', 'tv'), 
  );
  $breadcrumb = $new_breadcrumb;
}

function nel_get_breadcrumb_hierarchy($tid, &$array) {
  if ( ($parent_term = nel_get_parent_term($tid)) ) {
    array_unshift($array, $parent_term);
    nel_get_breadcrumb_hierarchy($parent_term->tid, $array);
  }
}

function nel_get_parent_term($tid) {
  static $parent;
  if ( isset($parent[$tid]) ) {
    return $parent[$tid];
  }

  $sql = "SELECT parent FROM {taxonomy_term_hierarchy} WHERE tid = %d";
  $sql = sprintf($sql, $tid);
  $result = db_query($sql);
  if ( ($row=$result->fetchAssoc()) ) {
    if ( ($term = taxonomy_term_load($row['parent'])) ) {
      $parent[$tid] = $term;
      return $term;
    }
  }
  
  $parent[$tid] = false;
  return false;
}

/**
 * Overrides of the function views_embed_view.
 */
function nel_views_embed_view($name, $display_id = 'default', $limit = null, $offset = null) {
  $args = func_get_args();
  array_shift($args); // remove $name
  if (count($args)) {
    array_shift($args); // remove $display_id
  }
  if (count($args)) {
    array_shift($args); // remove $limit
  }
  if (count($args)) {
    array_shift($args); // remove $offset
  }

  $view = views_get_view($name);
  if (!$view || !$view->access($display_id)) {
    return;
  }
  
  // Set Limit and Offset
  if ( !is_null($limit) && intval($limit) > 0 ) {
    $view->set_items_per_page(intval($limit));
  }
  if ( !is_null($offset) && intval($offset) ) {
    $view->set_offset(intval($offset));
  }

  return $view->preview($display_id, $args);
}

/**
 * Implements hook_theme.
 */
function nel_theme() {
  return array(
    'nel-gamma' => array(
      'arguments' => array(
        'items' => NULL, 
      ), 
      'template' => 'templates/gamma/nel-gamma', 
    ), 
    'nel-gamma-item' => array(
      'arguments' => array(
        'i' => NULL, 
        'title' => NULL, 
        'max_width' => NULL, 
        'max_height' => NULL, 
        'xsmall' => NULL, 
        'small' => NULL, 
        'medium' => NULL, 
        'large' => NULL, 
        'xlarge' => NULL, 
        'xxlarge' => NULL, 
      ), 
      'template' => 'templates/gamma/nel-gamma-item', 
    ), 
  );
}

function nel_html_entity_decode_encode_rss($data) { 
  $array_position = 0; 
  foreach (get_html_translation_table(HTML_ENTITIES) as $key => $value) { 
    //print("<br />key: $key, value: $value <br />\n"); 
    switch ($value) { 
      // These ones we can skip 
      case '&nbsp;': 
        break; 
      case '&gt;': 
      case '&lt;': 
      case '&quot;': 
      case '&apos;': 
      case '&amp;': 
        $entity_custom_from[$array_position] = $key; 
        $entity_custom_to[$array_position] = $value; 
        $array_position++; 
        break; 
      default: 
        $entity_custom_from[$array_position] = $value; 
        $entity_custom_to[$array_position] = $key; 
        $array_position++; 
    } 
  } 
  return str_replace($entity_custom_from, $entity_custom_to, $data); 
} 

/**
 * Implements hook_preprocess_views_view_rss.
 */
function nel_preprocess_views_view_rss(&$vars) {
  drupal_add_http_header('Content-Type', 'text/xml; charset=UTF-8');
  $view = &$vars['view'];
  $style = &$view->style_plugin;

  $style->namespaces['xmlns:media'] = 'http://search.yahoo.com/mrss/';
  $vars['namespaces'] = drupal_attributes($style->namespaces);
}

/**
 * Implements hook_preprocess_views_view_row_rss.
 */
function nel_preprocess_views_view_row_rss(&$vars) {
  // xmlns:media="http://search.yahoo.com/mrss/"
  $view     = &$vars['view'];
  $options  = &$vars['options'];
  $item     = &$vars['row'];

  $vars['title'] = check_plain($item->title);
  
  $vars['link'] = check_url($item->link);
  //$vars['description'] = nel_html_entity_decode_encode_rss(strip_tags($item->description));
  $vars['description'] = check_plain($item->description);
  
  // Add More Stuff
  if ( isset($item->nid) && ($node=node_load($item->nid)) && $node->type == 'article' ) {
    nel_preprocess_views_view_row_rss_node($item, $node);
  }

  $vars['item_elements'] = empty($item->elements) ? '' : format_xml_elements($item->elements);
}

/**
 *
 */
function nel_preprocess_views_view_row_rss_node(&$item, $node) {
  // Get pictures Together
  if ( ($pictures = nelb_row_rss_node_get_pictures($node)) ) {
    foreach($pictures as $picture) {
      // Type
      $media_type = $picture['filemime'];
      
      // Source
      $source_url = file_create_url($picture['uri']);
      $source_width = $picture['width'];
      $source_height = $picture['height'];
      
      // Medium
      $medium_url = image_style_url('rss_medium', $picture['uri']);
      $medium_dimensions = array(
        'width' => $picture['width'],
        'height' => $picture['height'],
      );
      image_style_transform_dimensions('rss_medium', $medium_dimensions);
      $medium_width = $medium_dimensions['width'];
      $medium_height = $medium_dimensions['height'];
      
      // Thumbnail
      $thumbnail_url = image_style_url('rss_thumbnail', $picture['uri']);
      $thumbnail_dimensions = array(
        'width' => $picture['width'],
        'height' => $picture['height'],
      );
      image_style_transform_dimensions('rss_thumbnail', $thumbnail_dimensions);
      $thumbnail_width = $thumbnail_dimensions['width'];
      $thumbnail_height = $thumbnail_dimensions['height'];
      
      $item->elements[] = array(
        'key' => 'media:group', 
        'value' => array(
          // Source
          array(
            'key' => 'media:content', 
            'attributes' => array(
              'url' => $source_url, 
              'type' => $media_type, 
              'width' => $source_width, 
              'height' => $source_height, 
            ), 
          ), 
          // Mediano
          array(
            'key' => 'media:content', 
            'attributes' => array(
              'url' => $medium_url, 
              'type' => $media_type, 
              'width' => $medium_width, 
              'height' => $medium_height, 
            ), 
          ), 
          // Thumbnail
          array(
            'key' => 'media:content', 
            'attributes' => array(
              'url' => $thumbnail_url, 
              'type' => $media_type, 
              'width' => $thumbnail_width, 
              'height' => $thumbnail_height, 
            ), 
          ), 
        ), 
      );
    }
  }
  
  if ( isset($node->field_video[LANGUAGE_NONE][0]['uri']) ) {
    $video = $node->field_video[LANGUAGE_NONE][0];
    switch($video['filemime']) {
      case 'video/vimeo':
        if ( preg_match('/v\/(.*)/', $video['uri'], $match) ) {
          $url = 'https://player.vimeo.com/video/' . $match[1];
          $item->elements[] = array(
            'key' => 'media:content', 
            'value' => array(
              array(
                'key' => 'media:player', 
                'attributes' => array(
                  'url' => $url, 
                ), 
              ), 
              array(
                'key' => 'media:title', 
                'value' => check_plain($node->title), 
              ), 
            ), 
          );
        }
        break;

      case 'video/youtube':
        if ( preg_match('/v\/(.*)/', $video['uri'], $match) ) {
          $url = "https://www.youtube.com/v/{$match[1]}?version=3";
          $url_tmb = "https://i4.ytimg.com/vi/{$match[1]}/hqdefault.jpg";
          $item->elements[] = array(
            'key' => 'media:group', 
            'value' => array(
              array(
                'key' => 'media:title', 
                'value' => check_plain($node->title), 
              ), 
              array(
                'key' => 'media:content', 
                'attributes' => array(
                  'url' => $url, 
                  'type' => 'application/x-shockwave-flash', 
                  'width' => '640', 
                  'height' => '390', 
                ), 
              ),  
              array(
                'key' => 'media:thumbnail', 
                'attributes' => array(
                  'url' => $url_tmb, 
                  'width' => '480', 
                  'height' => '360', 
                ), 
              ), 
            ), 
          );
        }
        break;
    }
  }
}































