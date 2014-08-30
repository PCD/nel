<?php
/**
 * Parse Items.
 */
function nelb_wp_import_parse_file() {
  error_reporting(E_ALL);
  ini_set('display_errors', '1');

  $source_blog = nelb_wp_import_get_blog_source();
  switch($source_blog) {
    case 0:
      $file_name = 'deportes.wordpress.2014-08-29.xml';
      break;

    case 1:
      $file_name = 'estilos.wordpress.2014-08-29.xml';
      break;

    case 2:
      $file_name = 'nayaritenlineamx.wordpress.2014-08-29.xml';
      break;
  }
  
  echo "STARTING IMPORT OF FILE \"{$file_name}\"\n";
  $dumpsdir = dirname(dirname((__FILE__))) . '/dumps/';
  $filepath = $dumpsdir . $file_name;
  
  echo "Reading...";
  $handle = fopen($filepath, 'r');
  if ( !$handle ) {
    echo " Failed.\n";
    exit;
  }
  
  echo " Success!\nStart Parsing\n";
  
  $i = 0;
  $limit = 10000;
  while (($buffer = fgets($handle, 4096)) !== false) {
    $r = nelb_wp_import_parse_file_line($buffer);
    
    // Is Item
    if ( $r == 2 ) {
      nelb_wp_import_parse_file_item($handle, trim($buffer));
    }
    $i++;
    if ( $i == $limit ) {
      //echo "Existing i={$i} and limit={$limit}\n";
      //exit;
    }
  }

  fclose($handle);
}

/**
 *
 */
function nelb_wp_import_parse_file_item(&$handle, $item) {
  $pattern_item_end = '/<\/item>/msi';
  while (($buffer = fgets($handle, 4096)) !== false) {
    $finish = 0;
    $line = trim($buffer);
    if ( preg_match($pattern_item_end, $buffer, $match) ) {
      $finish = 1;
    } else {
      $line = '  ' . $line;
    }
    $item .= "\n" . $line;
    
    if ( $finish == 1 ) {
      break;
    }
  }
  nelb_wp_import_parse_file_line_item($item);
}

/**
 * Parse Line.
 */
function nelb_wp_import_parse_file_line($line) {
  static $i;
  $i = isset($i)?$i+1:1;
  
  $debug = nelb_wp_import_debug();
  
  // Identify Line
  $pattern_author = "/<wp:author>(.*?)<\/wp:author>/msi";
  $pattern_category = "/<wp:category>(.*?)<\/wp:category>/msi";
  $pattern_tag = "/<wp:tag>(.*?)<\/wp:tag>/msi";
  $pattern_menu = "/<wp:term>(.*?)<\/wp:term>/msi";
  $pattern_item = "/<item>/msi";
  
  // Test Author
  if ( preg_match($pattern_author, $line, $match) ) {
    nelb_wp_import_parse_file_line_author($match[1]);
    return 1;
  } else // Test Category
  if ( preg_match($pattern_category, $line, $match) ) {
    nelb_wp_import_parse_file_line_category($match[1]);
    return 1;
  } else // Test Tag
  if ( !$debug && preg_match($pattern_tag, $line, $match) ) {
    nelb_wp_import_parse_file_line_tag($match[1]);
    return 1;
  } else // Test Item
  if ( !$debug && preg_match($pattern_item, $line, $match) ) {
    return 2;
  } else // Test Menu
  if ( !$debug && preg_match($pattern_menu, $line, $match) ) {
    // Ignore
    return 1;
  }
  
  //echo "Couldn't understand this: {$line}";
  return 0;
}

function nelb_wp_import_parse_file_line_author($line) {
  $author = array();
  
  // Get Author id
  if ( preg_match('/<wp:author_id>(.*?)<\/wp:author_id>/msi', $line, $match) ) {
    $author['id'] = $match[1];
  }
  
  // Look for existing.
  if ( nelb_wp_import_data_author_save_search_id($author['id']) ) {
    return;
  }
  
  // Get Author Login
  if ( preg_match('/<wp:author_login>(.*?)<\/wp:author_login>/msi', $line, $match) ) {
    $author['login'] = $match[1];
  }
  // Get Author Email
  if ( preg_match('/<wp:author_email>(.*?)<\/wp:author_email>/msi', $line, $match) ) {
    $author['email'] = $match[1];
  }
  // Get Author Display Name
  if ( preg_match('/<wp:author_display_name>(.*?)<\/wp:author_display_name>/msi', $line, $match) ) {
    $author['display_name'] = nelb_wp_import_remove_cdata($match[1]);
  }
  // Get Author First Name
  if ( preg_match('/<wp:author_first_name>(.*?)<\/wp:author_first_name>/msi', $line, $match) ) {
    $author['first_name'] = nelb_wp_import_remove_cdata($match[1]);
  }
  // Get Author Last Name
  if ( preg_match('/<wp:author_last_name>(.*?)<\/wp:author_last_name>/msi', $line, $match) ) {
    $author['last_name'] = nelb_wp_import_remove_cdata($match[1]);
  }
  
  $debug = nelb_wp_import_debug();
  if ( $debug ) {
    print_r($author);
  } else {
    // Register Author
    nelb_wp_import_data_author_save($author);
  }
}

function nelb_wp_import_parse_file_line_category($line) {
  $category = array();
  
  $blog_source = nelb_wp_import_get_blog_source();
  
  // Get Tag id
  if ( preg_match('/<wp:term_id>(.*?)<\/wp:term_id>/msi', $line, $match) ) {
    $category['id'] = intval($match[1]);
  }
  
  // Look for existing.
  if ( nelb_wp_import_data_category_save_search_id($category['id']) ) {
    return;
  }
  
  // Get Tag Name
  if ( preg_match('/<wp:cat_name>(.*?)<\/wp:cat_name>/msi', $line, $match) ) {
    $category['name'] = nelb_wp_import_remove_cdata($match[1]);
  }
  
  $debug = nelb_wp_import_debug();
  if ( $debug ) {
    print_r($category);
  } else {
    // Register Category
    nelb_wp_import_data_category_save($category);
  }
}

function nelb_wp_import_parse_file_line_tag($line) {
  $tag = array();
  // Get Tag id
  if ( preg_match('/<wp:term_id>(.*?)<\/wp:term_id>/msi', $line, $match) ) {
    $tag['id'] = $match[1];
  }
  
  // Get Tag Name
  if ( preg_match('/<wp:tag_name>(.*?)<\/wp:tag_name>/msi', $line, $match) ) {
    $tag['name'] = nelb_wp_import_remove_cdata($match[1]);
  }
  
  // Register Tag
  nelb_wp_import_data_tag_save($tag);
}

function nelb_wp_import_parse_file_line_item($line) {
  // Get Post Type wp:post_type>attachment</wp:post_type>
  if ( preg_match('/<wp:post_type>(.*?)<\/wp:post_type>/msi', $line, $match) ) {
    switch($match[1]) {
      case 'attachment':
        nelb_wp_import_parse_file_line_item_attachment($line);
        break;

      case 'post':
        nelb_wp_import_parse_file_line_item_post($line);
        break;
    }
  } else {
    echo "Couldn't find Post Type on: \n{$line}\n\n";
    exit; 
  }
}

/**
 *
 */
function nelb_wp_import_parse_file_line_item_attachment($line) {
  static $i, $j;
  $item = array();
  
  // Get File GUID
  if ( preg_match('/<guid[^>]*?>(.*?)<\/guid>/msi', $line, $match) ) {
    $guid = $match[1];
    if ( nelb_wp_import_file_search_guid($guid) ) {
      return false;
    }
    
    $item['guid'] = $guid;
  }
  
  // Get Post Id
  if ( preg_match('/<wp:post_id>(.*?)<\/wp:post_id>/msi', $line, $match) ) {
    $item['id'] = $match[1];
  }
  
  // Get Parent Post
  if ( preg_match('/<wp:post_parent>(.*?)<\/wp:post_parent>/msi', $line, $match) ) {
    $item['post_parent'] = $match[1];
  }
  
  // Source Blog
  $blog_selected = nelb_wp_import_get_blog_source();
  $blogs = array(
    0 => 'deportes', 
    1 => 'estilos', 
    2 => 'nayarit', 
  );
  $prefix = 'public://wordpress/' . $blogs[$blog_selected];
  $item['source_blog'] = $blog_selected;
  
  // Get Attachment URL
  if ( preg_match('/<wp:attachment_url>(.*?)<\/wp:attachment_url>/msi', $line, $match) ) {
    $item['attachment_url'] = $match[1];
  }
  
  // Get File Timestamp
  if ( preg_match('/<wp:post_date>(.*?)<\/wp:post_date>/msi', $line, $match) ) {
    $item['timestamp'] = strtotime($match[1]);
  }
  
  // Get Meta Tags
  if ( preg_match_all('/<wp:postmeta>(.*?)<\/wp:postmeta>/msi', $line, $matches) ) {
    foreach($matches[1] as $meta_raw){
      $meta = array();
      
      // Meta Key
      if ( !preg_match('/<wp:meta_key>(.*?)<\/wp:meta_key>/msi', $meta_raw, $meta_match) ) {
        echo "Meta PregMatch Failed: {$meta}\n\n";
        exit;
      }
      $meta['key'] = $meta_match[1];

      // Meta Value
      if ( !preg_match('/<wp:meta_value>(.*?)<\/wp:meta_value>/msi', $meta_raw, $meta_match) ) {
        echo "Meta PregMatch Failed: {$meta}\n\n";
        exit;
      }
      $meta['value'] = nelb_wp_import_remove_cdata($meta_match[1]);
      if ( !empty($meta['value'])) {
        //$item['meta'][] = $meta;
        
        // Process Meta
        switch($meta['key']) {
          case '_wp_attached_file':
          case '_wp_attachment_image_alt':
          case '_wp_attachment_backup_sizes':
          case '_edit_last':
          case '_wpz_original_thumb_url':
          case '_wp_attachment_is_custom_background':
          case '_wp_attachment_context':
          case '_oembed_2cf94967f0ae2b27c663a087ef4dc594'
          case 'Views':
            break;
  
          case '_wp_attachment_metadata':
            $un_value = unserialize($meta['value']);
            $item['uri'] = "{$prefix}/{$un_value['file']}";
            $item['width'] = $un_value['width'];
            $item['height'] = $un_value['height'];
            $item['title'] = check_plain($un_value['image_meta']['title']);
            break;

          default:
            print "Unidentified Key:\n{$meta['key']} and {$meta['value']}\n\n";
            exit;
            break;
        }
      }
    }
  }
  
  // Alt
  if ( preg_match('/<content:encoded>(.*?)<\/content:encoded>/msi', $line, $match) ) {
    $item['alt'] = check_plain(nelb_wp_import_remove_cdata($match[1]));
  }
  
  // Import
  nelb_wp_import_file($item);
}

/**
 *
 */
function nelb_wp_import_parse_file_line_item_post($line) {
  //print_r($line);
  $item = array(
    'type' => 'post', 
    'author_show' => false, 
  );
  
  $blog_selected = nelb_wp_import_get_blog_source();
  $blogs = array(
    0 => 'deportes', 
    1 => 'estilos', 
    2 => 'nayarit', 
  );
  $item['source_blog'] = $blog_selected;
  
  // Get Post Id
  if ( preg_match('/<wp:post_id>(.*?)<\/wp:post_id>/msi', $line, $match) ) {
    $item['id'] = $match[1];
  }
  
  if ( nelb_wp_search_post_by_id($item['id'], $item['source_blog']) ) {
    return false;
  }
  
  // Get Post GUID
  if ( preg_match('/<guid[^>]*?>(.*?)<\/guid>/msi', $line, $match) ) {
    $item['guid'] = $match[1];
  }
  
  // Get Post Title
  if ( preg_match('/<title>(.*?)<\/title>/msi', $line, $match) ) {
    $item['title'] = trim($match[1]);
  }
  
  // Get Created Date
  if ( preg_match('/<pubDate>(.*?)<\/pubDate>/msi', $line, $match) ) {
    $item['created'] = $match[1];
  }
  
  // Get Publish Date
  if ( preg_match('/<wp:post_date>(.*?)<\/wp:post_date>/msi', $line, $match) ) {
    $item['date'] = $match[1];
  }
  
  // Get Post Body
  if ( preg_match('/<content:encoded>(.*?)<\/content:encoded>/msi', $line, $match) ) {
    $item['body'] = nelb_wp_import_remove_cdata($match[1]);
  }
  
  // Get Post Status
  if ( preg_match('/<wp:status>(.*?)<\/wp:status>/msi', $line, $match) ) {
    $item['status'] = $match[1];
  }
  
  // Get Author
  if ( preg_match('/<dc:creator>(.*?)<\/dc:creator>/msi', $line, $match) ) {
    $item['author'] = nelb_wp_import_remove_cdata($match[1]);
  }
  
  // Get Tags
  if ( preg_match_all('/<category[^>]*>(.*?)<\/category>/msi', $line, $matches) ) {
    $item['tags'] = $item['category'] = array();
    foreach($matches[0] as $key => $match_item) {
      $parsed_item = array(
        'name' => nelb_wp_import_remove_cdata($matches[1][$key]), 
      );
      // Find Domain
      if ( !preg_match('/domain="([^"]*)"/msi', $match_item, $match) ) {
        echo "Couldn't find a type for the category: {$match_item}\n";
        exit;
      }
      
      $parsed_item['type'] = $match[1];
      switch($parsed_item['type']) {
        case 'category':
          $item['category'][] = $parsed_item['name'];
          break;

        case 'post_tag':
          $item['tags'][] = $parsed_item['name'];
          break;

        case 'post_format':
          break;

        default:
          echo "Unidentified Category: \n{$line}\n\n";
          exit;
          break;
      }
    }
  }
  
  // Get Meta Tags
  if ( preg_match_all('/<wp:postmeta>(.*?)<\/wp:postmeta>/msi', $line, $matches) ) {
    foreach($matches[1] as $meta_raw){
      $meta = array();
      
      // Meta Key
      if ( !preg_match('/<wp:meta_key>(.*?)<\/wp:meta_key>/msi', $meta_raw, $meta_match) ) {
        echo "Meta PregMatch Failed: {$meta}\n\n";
        exit;
      }
      $meta['key'] = $meta_match[1];

      // Meta Value
      if ( !preg_match('/<wp:meta_value>(.*?)<\/wp:meta_value>/msi', $meta_raw, $meta_match) ) {
        echo "Meta PregMatch Failed: {$meta}\n\n";
        exit;
      }
      $meta['value'] = nelb_wp_import_remove_cdata($meta_match[1]);
      if ( !empty($meta['value'])) {
        //$item['meta'][] = $meta;
        
        // Process Meta
        switch($meta['key']) {
          case 'td_post_video':
            $video = unserialize($meta['value']);
            $item['video'][] = $video['td_video'];
            break;
  
          // To Ignore
          case '_edit_last':
          case 'pinterest_url':
          case 'wordpress_connect_custom_fields_like_button_enable':  
          case 'wordpress_connect_custom_fields_like_button_position':  
          case 'wordpress_connect_custom_fields_comments_enabled':  
          case 'wordpress_connect_custom_fields_comments_position':  
            break;
  
          // To Analyze
          case '_thumbnail_id':
            $image = nelb_wp_import_file_search_id(trim($meta['value']), $item['source_blog']);
            $item['image'][] = $image;
            break;
  
          default:
            //print "Unidentified Key:\n{$meta['key']}\n\n";
            //exit;
            break;
        }
      }
    }
  }
  
  // Import
  nelb_wp_import_post($item);
}

function nelb_wp_import_remove_cdata($string) {
  if ( preg_match('/<!\[CDATA\[([^\]]*?)\]\]>/msi', $string, $match) ) {
    return $match[1];
  }
  return $string;
}

function nelb_wp_import_get_blog_source() {
  return 1;
}

function nelb_wp_import_debug() {
  return false;
}