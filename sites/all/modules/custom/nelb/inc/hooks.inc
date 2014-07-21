<?php
/**
 * Implements hook_node_presave.
 */
function nelb_node_presave($node, $other_info = null) {
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

  $instance = field_info_instance('node', 'body', $node->type);
  $node->body[LANGUAGE_NONE][0]['value'] = $body;
  $node->body[LANGUAGE_NONE][0]['summary'] = text_summary($body);
  $node->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  $node->body[LANGUAGE_NONE][0]['safe_value'] = _text_sanitize($instance, LANGUAGE_NONE, $node->body[$LANGUAGE_NONE][0], 'value'); 
  $node->body[LANGUAGE_NONE][0]['safe_summary'] = _text_sanitize($instance, LANGUAGE_NONE, $node->body[$LANGUAGE_NONE][0], 'summary');
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