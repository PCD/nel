<?php
/**
 * Implements hook_url_outbound_alter.
 */
function nelb_url_outbound_alter(&$path, &$options, $original_path) {
  return;
  // Instead of pointing to user/[uid]/edit, point to user/me/edit.
  if (preg_match('|^node/([0-9]*)(/.*)?|', $path, $matches)) {
    if ( ($node = node_load($matches[1])) ) {
      $options['query']['vid'] = $node->vid;
    }
  }
}

/**
 * Implements hook_node_presave.
 */
function nelb_node_presave($node, $other_info = null) {
  // Joomla Import
  nelb_node_presave_joomla($node, $other_info);
}

/**
 * URL Alter at hook_node_presave for Articles.
 */
function nelb_node_presave_article($node) {
  if ( $node->type == 'article' ) {
    return;
  }
}

/**
 * Implements hook_node_insert.
 */
function nelb_node_insert($node) {
  if ( $node->type != 'article' ) {
    return;
  }
  
  if ( ($term = nelb_data_get_category_page($node)) ) {
    nelb_pathauto_node_update_alias($node, 'insert');
  
    // Check for Date
    if ( !isset($node->field_date[LANGUAGE_NONE][0]['value']) ) {
      $node->field_date[LANGUAGE_NONE][0] = array(
        'value' => date('Y-m-d H:i:s', $node->created), 
        'timezone' => 'America/Mazatlan', 
        'timezone_db' => 'America/Mazatlan', 
        'date_type' => 'datetime', 
      );
    }
  }
}

/**
 * Implements hook_node_update.
 */
function nelb_node_update($node) {
  if ( $node->type != 'article' ) {
    return;
  }
  
  if ( ($term = nelb_data_get_category_page($node)) ) {
    nelb_pathauto_node_update_alias($node, 'update');
  
    // Check for Date
    if ( !isset($node->field_date[LANGUAGE_NONE][0]['value']) ) {
      $node->field_date[LANGUAGE_NONE][0] = array(
        'value' => date('Y-m-d H:i:s', $node->created), 
        'timezone' => 'America/Mazatlan', 
        'timezone_db' => 'America/Mazatlan', 
        'date_type' => 'datetime', 
      );
    }
  }
}

/**
 * hook_node_presave for importing joomla.
 */
function nelb_node_presave_joomla($node, $other_info = null) {
  // Joomla Import
  if ( !(isset($node->joomla) && $node->joomla == 1) ) {
    return;
  }
  // Language
  $node->language = LANGUAGE_NONE;
  
  // User
  global $user;
  $node->uid = $user->uid;
  
  // Picture Out of Body.
  nelb_extract_pictures_from_body($node);
  
  // Date
  $node->field_date[LANGUAGE_NONE][0]['value'] = date('Y-m-d H:i:s', $node->created);
  $node->field_date[LANGUAGE_NONE][0]['timezone'] = 'America/Mazatlan';
  $node->field_date[LANGUAGE_NONE][0]['timezone_db'] = 'America/Mazatlan';
  $node->field_date[LANGUAGE_NONE][0]['date_type'] = 'datetime';
  
  // Terms
  if ( isset($node->other_info['tid']) ) {
    $tid = $node->other_info['tid'];
    
    // Look for Autor
    if ( ($autor_tid = nelb_get_autor_tid($tid)) ) {
      $node->field_author[LANGUAGE_NONE][0]['tid'] = $autor_tid;
    }
    
    // Look for Category
    if ( ($category_tid = nelb_get_category_tid($tid)) ) {
      $node->field_category[LANGUAGE_NONE][0]['tid'] = $category_tid;
    }
  }
}

/**
 * Gets Pictures out of the Body Field.
 */
function nelb_extract_pictures_from_body(&$node) {
  // Get Picture Out
  $body = $node->body[LANGUAGE_NONE][0]['value'];
  if ( preg_match_all('/<img [^>]*>/msi', $body, $matches) ) {
    foreach($matches[0] as $key => $img) {
      nelb_extract_pictures_from_body_item($node, $key, $img);
    }
  }
  $body = preg_replace('/<img [^>]*/msi', '', $body);
  
  // Replace Youtube Video
  $body = nelb_extract_pictures_from_body_youtube($body);

  // Replace Vimeo Video
  $body = nelb_extract_pictures_from_body_vimeo($body);
  
  // Replace Audio Player
  $body = nelb_extract_pictures_from_body_audio($body);

  $instance = field_info_instance('node', 'body', $node->type);
  $node->body[LANGUAGE_NONE][0]['value'] = $body;
  $node->body[LANGUAGE_NONE][0]['summary'] = text_summary($body);
  $node->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  $node->body[LANGUAGE_NONE][0]['safe_value'] = _text_sanitize($instance, LANGUAGE_NONE, $node->body[$LANGUAGE_NONE][0], 'value'); 
  $node->body[LANGUAGE_NONE][0]['safe_summary'] = _text_sanitize($instance, LANGUAGE_NONE, $node->body[$LANGUAGE_NONE][0], 'summary');
}

/**
 * Youtube player
 */
function nelb_extract_pictures_from_body_youtube($body) {
  $pattern = '/\{youtube\}([^\}]*)\{\/youtube\}/msi';
  $replace = '<iframe allowfullscreen="" frameborder="0" height="350" src="//www.youtube.com/embed/${1}" width="630"></iframe>';
  return preg_replace($pattern, $replace, $body);
}

/**
 * Vimeo player
 */
function nelb_extract_pictures_from_body_vimeo($body) {
  $pattern = '/\{vimeo\}([^\}]*)\{\/vimeo\}/msi';
  $replace = '<iframe src="//player.vimeo.com/video/${1}?title=0&amp;byline=0&amp;portrait=0" width="630" height="354" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>';
  return preg_replace($pattern, $replace, $body);
}

/**
 * Audio player
 */
function nelb_extract_pictures_from_body_audio($body) {
  $pattern = '/\{audio\}mp3\/([^\}]*)\{\/audio\}/msi';
  $replace = '<audio id="player2" src="/sites/default/files/mp3/${1}" type="audio/mp3" controls="controls"></audio>';
  return preg_replace($pattern, $replace, $body);
}

/**
 * Gets a picture out of the Body Field item.
 */
function nelb_extract_pictures_from_body_item(&$node, $key, $img) {
  static $i;
  $i = isset($i)?$i+1:1;
  
  $img_path = $img_alt = '';
  // Get Picture Alt
  if ( preg_match('/alt="([^"]*)"/msi', $img, $matches) ) {
    $img_alt = $matches[1];
  }
  
  global $user;
  // Get Picture Path
  if ( preg_match('/src="\/sites\/default\/filesimages\/([^"]*)"/msi', $img, $matches) ) {
    $file_path = '/Users/cristian100/Sites/archivo_nel/html/images/' . $matches[1];
    if ( !file_exists($file_path) ) {
      return false;
    }
    $file = (object) array(
      'uid' => $user->uid, 
      'uri' => $file_path, 
      'filename' => pathinfo($file_path, PATHINFO_BASENAME), 
      'filepath' => $file_path, 
      'filemime' => file_get_mimetype($file_path), 
      'filesize' => filesize($file_path), 
      'alt' => $img_alt, 
      'status' => FILE_STATUS_PERMANENT, 
      'display' => 1, 
    );
    $destination = file_build_uri("joomla/{$file->filename}");
    $file = file_copy($file, $destination, FILE_EXISTS_RENAME);
    $node->field_image[LANGUAGE_NONE][$key] = (array) $file;
  }
}