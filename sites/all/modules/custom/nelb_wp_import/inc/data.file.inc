<?php
/**
 * Look for Existing Files.
 */
function nelb_wp_import_file_search_guid($guid) {
  $sql = sprintf("SELECT source_id FROM {nelb_file} WHERE guid = '%s'", $guid);
  $results = db_query($sql);
  if ( ($row=$results->fetchAssoc())) {
    //echo "Found, skipping file.\n";
    return $row['source_id'];
  }
  return false;
}

/**
 * Imports file.
 */
function nelb_wp_import_file($params) {
  echo "Importing File: {$params['attachment_url']}... ";
  $url = $params['attachment_url'];
  $uri = $params['uri'];
  $extra_fields = array();
  $extra_fields['field_source_guid'][LANGUAGE_NONE][0]['value'] = $params['guid'];
  $extra_fields['field_source_id'][LANGUAGE_NONE][0]['value'] = $params['id'];
  $extra_fields['field_source_blog'][LANGUAGE_NONE][0]['value'] = $params['source_blog'];
  
  if ( ($file = nelb_wp_import_download_external_file($url, $uri, FILE_EXISTS_REPLACE, TRUE, $extra_fields)) ) {
    nelb_wp_import_file_mark_done($file, $params);
    echo "Done.\n";
  } else {
    echo "Failed on file: " . print_r($file) . "\nparams: " . print_r($params, true) . ".\n";
    exit;
  }
}

/** 
 *
 */
function nelb_wp_import_file_mark_done($file, $params) {
  $sql = "INSERT INTO {nelb_file} (source_id, source_blog, guid, fid) VALUES(%d, %d, '%s', %d)";
  $sql = sprintf($sql, $params['id'], $params['source_blog'], $params['guid'], $file['fid']);
  return db_query($sql);
}

/**
 *
 * param string $url
 *    Full url to file to download
 * param string $uri
 *    Drupal uri of where to save file public://archive/test.pdf
 * param int $save_mode
 *    File save mode from drupal core, ex FILE_EXISTS_REPLACE
 */
function nelb_wp_import_download_external_file($url, $uri, $save_mode = FILE_EXISTS_RENAME, $manage_file = TRUE, $extra_fields = array()) {
  $url_info = parse_url($url);
  $url_path_info = pathinfo($url_info['path']);

  //This helps with filenames with spaces
  $url = $url_info['scheme'] . '://' . $url_info['host'] . $url_path_info['dirname'] . '/' . rawurlencode($url_path_info['basename']);

  //Need to remove the filename from the uri
  $uri_target = file_uri_target($uri);
  $uri_scheme = file_uri_scheme($uri);
  $uri_path_info = pathinfo($uri_target);
  $directory = file_stream_wrapper_uri_normalize($uri_scheme . "://" . $uri_path_info['dirname']);
  
  if(file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    $options = array(
      'timeout' => 120, 
    );
    $drupal_result = drupal_http_request($url, $options);
    if(!empty($drupal_result->data)) {
      $path = file_stream_wrapper_uri_normalize($uri);
      if($manage_file) {
        if ( !($new_file = nelb_wp_import_file_save_data($drupal_result->data, $path, $save_mode, $extra_fields)) ) {
          echo "Aqui fallo";
        }
      } else {
        echo "aqui voy";
        exit;
        return file_unmanaged_save_data($drupal_result->data, $path, $save_mode);
      }
    } else {
      echo "Error downloading file, no data recieved for " . $url;
      return FALSE;
    }

    $new_file->display = 1;
    return (array)$new_file;
  } else {
    echo "Aqui FALLO\n";
    exit;
    return false;
  }
}

/**
 * File Save Data Nelb Version.
 */
function nelb_wp_import_file_save_data($data, $destination = NULL, $replace = FILE_EXISTS_RENAME, $extra_fields = array()) {
  global $user;

  if (empty($destination)) {
    $destination = file_default_scheme() . '://';
  }
  if (!file_valid_uri($destination)) {
    watchdog('file', 'The data could not be saved because the destination %destination is invalid. This may be caused by improper use of nelb_wp_import_file_save_data() or a missing stream wrapper.', array('%destination' => $destination));
    drupal_set_message(t('The data could not be saved, because the destination is invalid. More information is available in the system log.'), 'error');
    return FALSE;
  }

  if ($uri = file_unmanaged_save_data($data, $destination, $replace)) {
    // Create a file object.
    $file = new stdClass();
    $file->fid = NULL;
    $file->uri = $uri;
    $file->filename = drupal_basename($uri);
    $file->filemime = file_get_mimetype($file->uri);
    $file->uid = $user->uid;
    $file->status = FILE_STATUS_PERMANENT;
    // If we are replacing an existing file re-use its database record.
    if ($replace == FILE_EXISTS_REPLACE) {
      $existing_files = file_load_multiple(array(), array('uri' => $uri));
      if (count($existing_files)) {
        $existing = reset($existing_files);
        $file->fid = $existing->fid;
        $file->filename = $existing->filename;
      }
    }
    // If we are renaming around an existing file (rather than a directory),
    // use its basename for the filename.
    elseif ($replace == FILE_EXISTS_RENAME && is_file($destination)) {
      $file->filename = drupal_basename($destination);
    }
    
    // Fields
    if ( !empty($extra_fields) ) {
      foreach($extra_fields as $key => $extra_field) {
        $file->$key = $extra_field;
      }
    }

    return file_save($file);
  }
  return FALSE;
}