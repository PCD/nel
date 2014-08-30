<?php
/**
 * Import Post.
 */
function nelb_wp_import_post($params) {
  $node = new stdClass();
  $node->type = 'article';
  node_object_prepare($node);
  
  $node->uid = 1;
  if ( !isset($params['title']) || empty($params['title']) ) {
    echo "Skipping Article because Title Missing for params:\n" . print_r($params, true) . "\n\n";
    return;
  }
  $node->title = trim($params['title']);
  $node->language = LANGUAGE_NONE;
  $node->body[LANGUAGE_NONE][0]['value'] = $params['body'];
  $node->body[LANGUAGE_NONE][0]['summary'] = text_summary($params['body']);
  $node->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  $node->created = time();
  $node->status = 1;
  
  // Taxonomies
  $node->field_category[LANGUAGE_NONE] = array();
  foreach($params['category'] as $cat_name) {
    if ( !($term_db = nelb_wp_import_get_category_by_name($cat_name)) ) {
      echo "Couldn't find Term: {$cat_name}.\n\n";
    }
    $node->field_category[LANGUAGE_NONE][] = array('tid' => intval($term_db['tid']));
  }
  
  // Blog Source
  switch($params['source_blog']) {
    case 0:
      $node->field_category[LANGUAGE_NONE][] = array('tid' => 154);
      break;

    case 1:
      $node->field_category[LANGUAGE_NONE][] = array('tid' => 157);
      break;
  }
  
  // TV?
  if ( isset($params['video']) && !empty($params['video']) ) {
    $node->field_category[LANGUAGE_NONE][] = array('tid' => 14);
  }
  
  // Tags
  if ( isset($params['tags']) && !empty($params['tags'])) {
    $node->field_tag[LANGUAGE_NONE] = array();
    foreach($params['tags'] as $tag_name) {
      if ( ($term_db = nelb_wp_import_get_tag_by_name($term_name)) ) {
        $node->field_tag[LANGUAGE_NONE][] = array('tid' => intval($term_db['tid']));
      }
    }
  }
  
  // Author
  if ( isset($params['author']) && !empty($params['author']) ) {
    if ( !($term_db = nelb_wp_import_get_author_by_login($params['author'])) ) {
      echo "Couldn't find the Author.\n\n";
      exit;
    }
    $node->field_author[LANGUAGE_NONE][0]['tid'] = intval($term_db['tid']);
  }
  
  // Source URL
  $node->source_url[LANGUAGE_NONE][0]['url'] = $params['guid'];
  
  // Custom Fields
  $date = strtotime($params['date']);
  $node->field_date[LANGUAGE_NONE][0]['value'] = date('Y-m-d H:m:s', $date);
  $node->field_date[LANGUAGE_NONE][0]['timezone'] = 'America/Mazatlan';
  $node->field_date[LANGUAGE_NONE][0]['timezone_db'] = 'America/Mazatlan';
  $node->field_date[LANGUAGE_NONE][0]['date_type'] = 'datetime';
  
  // Images
  // Search for more pictures assigned to this node.
  nelb_wp_import_images_to_parent($params);
  
  if ( isset($params['image']) && !empty($params['image']) ) {
    // Try to Load them Up
    foreach($params['image'] as $image_item) {
      $image_fid = $image_item['fid'];
      echo "Loading File: {$image_fid}\n";
      $file = file_load($image_fid);
      if ( isset($file->filename) ) {
        $node->field_image[LANGUAGE_NONE][] = (array) $file;
      }
    }
  }
  
  // Video
  if ( isset($params['video']) && !empty($params['video']) ) {
    foreach($params['video'] as $video_url) {
      $node->field_video_source[LANGUAGE_NONE][]['value'] = $video_url;
    }
  }
  
  // Show Author
  if ( isset($params['author_show']) && $params['author'] == 1 ) {
    $node->field_show_author[LANGUAGE_NONE][0]['value'] = 1;
  }
  
  try{
    if ( ($node = node_submit($node)) ) {
      node_save($node);
      nelb_wp_import_post_mark_done($node->nid, $params);
      echo "Article with nid: {$node->nid} saved!\n";
    } else {
      echo "Something happened... Couldn't save the node.\n\n";
      exit;
    }
  } catch (Exception $e) {
    echo "Error Params:\n" . print_r($params, true) . "\n\nat Node Saving:\n" . print_r($node, true) . "\n\nMessage Error:\n" . $e->getMessage() . "\n\n";
    exit;
  }
  return true;
}

/**
 * Search a post by its guid.
 */
function nelb_wp_search_post_by_guid($guid) {
  $sql = "SELECT * FROM {nelb_post} WHERE guid = '%s'";
  $sql = sprintf($sql, $guid);
  $results = db_query($sql);
  return $results->fetchAssoc();
}

/**
 * Search a post by its id.
 */
function nelb_wp_search_post_by_id($id, $blog_source) {
  $sql = "SELECT * FROM {nelb_post} WHERE source_id = %d AND source_blog = %d";
  $sql = sprintf($sql, $id, $blog_source);
  $results = db_query($sql);
  return $results->fetchAssoc();
}

/** 
 *
 */
function nelb_wp_import_post_mark_done($nid, $params) {
  $sql = "INSERT INTO {nelb_post} (source_id, source_blog, guid, nid) VALUES(%d, %d, '%s', %d)";
  $sql = sprintf($sql, $params['id'], $params['source_blog'], $params['guid'], $nid);
  return db_query($sql);
}