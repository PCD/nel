<?php
/**
 * Implements hook_theme.
 */
function fbia_sync_theme() {
  return array(
    'fbia-sync--article' => array(
      'variables' => array(
        'url' => NULL,
        'title' => NULL,
        'sub_title' => NULL,
        'published_date' => NULL,
        'published_date_r' => NULL,
        'modified_date' => NULL,
        'modified_date_r' => NULL,
        'author' => NULL,
        'image_main' => NULL,
        'image_main_alt' => NULL,
        'breadcrumbs' => NULL,
        'body' => NULL,
        'video' => NULL,
        'add_2' => NULL,
        'slideshow' => NULL,
        'ads' => NULL,
      ),
      'template' => 'templates/fbia-sync--article',
    ),
    'fbia-sync--double-click' => array(
      'variables' => array(
        'slot_id' => NULL,
        'div_id' => NULL,
      ),
      'template' => 'templates/fbia-sync--double-click',
    ),
  );
}

/**
 * Splits paragraphs out of body.
 */
function fbia_sync_split_paragraphs($body, &$paragraphs, &$iframes) {
  $paragraphs = array();
  $body = str_replace('&nbsp;', ' ', $body);
  $body = preg_replace('/\s+/msi', ' ', $body);
  $pattern = '/<p>(.*?)<\/p>/msi';
  $iframe_pattern = '/(<iframe.*?>.*<\/iframe>)/msi';
  if (preg_match_all($pattern, $body, $matches)) {
    foreach($matches[1] as $i => $paragraph) {
      if (!trim($paragraph)) {
        continue;
      }

      // Detect if iframe in there.
      if (preg_match($iframe_pattern, $paragraph, $match)) {
        $iframe = array('tag' => $match[1]);
        if (preg_match('/src="(.+?)"/msi', $match[1], $src)) {
          $iframe['src'] = $src[1];
          
          // Fix src with http for video providers.
          $iframe['src'] = fbia_sync_fix_video_src($iframe['src']);
        }
        if (preg_match('/height="(.+?)"/msi', $match[1], $height)) {
          $iframe['height'] = (int)$height[1];
        }
        
        if (preg_match('/width="(.+?)"/msi', $match[1], $width)) {
          $iframe['width'] = (int)$width[1];
        }
        
        $iframes[] = $iframe;
      }
      else {
        $paragraphs[] = $paragraph;
      }
    }
  }
  
  return true;
}

/**
 * Fix video source for known providers.
 */
function fbia_sync_fix_video_src($src) {
  if (preg_match('/^\/\/www\.youtube\.com.*/msi', $src, $match)) {
    return 'https:' . $src;
  }
  
  if (preg_match('/^\/\/www\..*/msi', $src, $match)) {
    return 'http:' . $src;
  }
}

/**
 * Get FBI Node.
 */
function fbia_sync_prepare_node($node) {
  $node_args = array(
    'title' => $node->title,
  );

  // Dates setup.
  if (isset($node->field_date[LANGUAGE_NONE][0]['value'])) {
    $node_args['published_date_time'] = strtotime($node->field_date[LANGUAGE_NONE][0]['value']);
    $node_args['published_date'] = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'medium', '', $node->field_date[LANGUAGE_NONE][0]['timezone']);
    $node_args['published_date_r'] = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'custom', 'r', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  }
  else {
    $node_args['published_date_time'] = $node->created;
    $node_args['published_date'] = format_date($node->created, 'medium');
    $node_args['published_date_r'] = format_date($node->created, 'custom', 'r');
  }

  $node_args['modified_date_time'] = $node->changed;
  $node_args['modified_date'] = format_date($node->changed, 'medium');
  $node_args['modified_date_r'] = format_date($node->changed, 'custom', 'r');

  // Category.
  if (isset($node->field_main_category[LANGUAGE_NONE][0]['tid'])) {
    if (($term = taxonomy_term_load($node->field_main_category[LANGUAGE_NONE][0]['tid']))) {
      $node_args['breadcrumbs'] = $term->name;
    }
  }

  // URL Canonical.
  $url = url('node/' . $node->nid, array('absolute' => TRUE, 'base_url' => 'http://www.nayaritenlinea.mx'));
  if (preg_match('/(.*?)\?.*/', $url, $match)) {
    $node_args['url'] = $match[1];
  }

  // Intro.
  if (isset($node->field_intro[LANGUAGE_NONE][0]['value'])) {
    $node_args['sub_title'] = trim(strip_tags($node->field_intro[LANGUAGE_NONE][0]['value']));
  }

  // Author.
  if (isset($node->field_author[LANGUAGE_NONE][0]['value'])) {
    if (($term = taxonomy_term_load($node->field_author[LANGUAGE_NONE][0]['tid']))) {
      $node_args['author'] = $term->name;
      $node_args['author_url'] = url('taxonomy/term/' . $term->tid, array('absolute' => TRUE, 'base_url' => 'http://www.nayaritenlinea.mx'));
    }
  }

  // Body.
  if (isset($node->body[LANGUAGE_NONE][0]['value'])) {
    $node_args['body'] = $node->body[LANGUAGE_NONE][0]['value'];
  }

  // Video.
  if (isset($node->field_video[LANGUAGE_NONE][0]['uri'])) {
    if (($video = fbia_sync_node_video_data($node))) {
      $node_args['video'] = $video;
    }
  }

  // Slideshow.
  if (($slideshow = fbia_sync_get_slideshow_images($node))) {
    $node_args['slideshow'] = $slideshow;
  }

  // Main image.
  if (($img = fbia_sync_get_chosen_image($node))) {
    $node_args['image_main'] = $img['src'];
    $node_args['image_main_alt'] = $img['alt'];
  }

  // Embed blocks.
  if (isset($node->field_iframe_block[LANGUAGE_NONE][0]['value'])) {
    $i = 0;
    foreach($node->field_iframe_block[LANGUAGE_NONE] as $index => $item) {
      if (!($paragraph = paragraphs_item_load($item['value']))) {
        continue;
      }
      
      $url = url('node/' . $node->nid . '/iframe-block/' . ($index+1), array('absolute' => TRUE));
      if (preg_match('/(.*?)\?.*/', $url, $match)) {
        $url = $match[1];
      }
      
      $iframe_block = array(
        'src' => $url,
      );
      
      if (isset($paragraph->field_embed_width[LANGUAGE_NONE][0]['value'])) {
        $iframe_block['width'] = intval($paragraph->field_embed_width[LANGUAGE_NONE][0]['value']);
      }
      if (isset($paragraph->field_embed_height[LANGUAGE_NONE][0]['value'])) {
        $iframe_block['height'] = intval($paragraph->field_embed_height[LANGUAGE_NONE][0]['value']);
      }
      $node_args['iframe_block'][$i] = $iframe_block;
      $i++;
    }
  }

  // Ads.
  $node_args['ads'][] = array(
    'src' => url('fbia_sync/adslot/1', array('absolute' => TRUE, 'base_url' => 'http://www.nayaritenlinea.mx')),
    'width' => 300,
    'height' => 300,
  );
  $node_args['ads'][] = array(
    'src' => 'https://www.facebook.com/adnw_request?placement=1910022079210145_1915486201997066&adtype=banner300x250',
    'width' => 300,
    'height' => 250,
  );
  $node_args['ads'][] = array(
    'src' => 'https://www.facebook.com/adnw_request?placement=1910022079210145_1915486258663727&adtype=banner300x250',
    'width' => 300,
    'height' => 250,
  );
  $node_args['ads'][] = array(
    'src' => 'https://www.facebook.com/adnw_request?placement=1910022079210145_1915486281997058&adtype=banner320x50',
    'width' => 320,
    'height' => 50,
  );

  return $node_args;
}

/**
 * Get Ads for Facebook Instant Articles.
 */
function fbia_sync_get_ads() {
  $ads = array();
  $ad1 = theme('fbia-sync--double-click', array(
    'slot_id' => '15651346/FB_Instant_300x250',
    'div_id' => 'div-gpt-ad-1488668257116-0',
  ));
  $ads[] = array(
    'code' => $ad1,
    'width' => (int) 300,
    'height' => (int) 250,
  );
  return $ads;
}

/**
 * Get Slideshow Images.
 */
function fbia_sync_get_slideshow_images($node) {
  $slideshow = array();

  if (!isset($node->field_image[LANGUAGE_NONE][0]['uri'])) {
    return $slideshow;
  }
  $count = count($node->field_image[LANGUAGE_NONE]);
  if ($count > 1) {
    for($i=1; $i<$count; $i++) {
      $image_item_raw = $node->field_image[LANGUAGE_NONE][$i];
      $image_item = file_create_url($image_item_raw['uri']);
      $image_item_alt = $image_item_raw['alt'];
      $slideshow_item = array(
        'src' => file_create_url($image_item_raw['uri']), 
      );
      if (!empty($image_item_raw['alt'])) {
        $slideshow_item['alt'] = $image_item_raw['alt'];
      }
      $slideshow[] = $slideshow_item;
    }
  }
  return $slideshow;
}
              
/**
 * Get Node chosen Image.
 */
function fbia_sync_get_chosen_image($node) {
  $img = array();
  if (fbia_sync_node_video_to_figure($node)) {
    if (isset($node->field_video_image[LANGUAGE_NONE][0]['uri'])) {
      $img['src'] = file_create_url($node->field_video_image[LANGUAGE_NONE][0]['uri']);
      $img['alt'] = $node->field_video_image[LANGUAGE_NONE][0]['alt'];
      return $img;
    }
  }
  
  if (isset($node->field_image[LANGUAGE_NONE][0]['uri'])) {
    $img['src'] = file_create_url($node->field_image[LANGUAGE_NONE][0]['uri']);
    $img['alt'] = $node->field_image[LANGUAGE_NONE][0]['alt'];
  }
  
  if (isset($node->field_meta_image[LANGUAGE_NONE][0]['uri'])) {
    $img['src'] = file_create_url($node->field_meta_image[LANGUAGE_NONE][0]['uri']);
    $img['alt'] = $node->field_meta_image[LANGUAGE_NONE][0]['alt'];
  }
  
  return $img;
}

/**
 * Get Node Video data.
 */
function fbia_sync_node_video_data($node) {
  if (!isset($node->field_video[LANGUAGE_NONE][0])) {
    return FALSE;
  }
  
  $video_url = $node->field_video[LANGUAGE_NONE][0]['uri'];

  // Is youtube?
  $pattern = '/youtube:/msi';
  if (preg_match($pattern, $video_url, $match)) {
    return fbia_sync_youtube_data($video_url);
  }
  
  // Is Vimeo?
  $pattern = '/vimeo:/msi';
  if (preg_match($pattern, $video_url, $match)) {
    return fbia_sync_vimeo_data($video_url);
  }
}

/**
 * Get Node Video to Figure.
 */
function fbia_sync_node_video_to_figure($node) {
  if (!isset($node->field_video[LANGUAGE_NONE][0])) {
    return FALSE;
  }
  
  $video_url = $node->field_video[LANGUAGE_NONE][0]['uri'];

  // Is youtube?
  $pattern = '/youtube:/msi';
  if (preg_match($pattern, $video_url, $match)) {
    return fbia_sync_youtube_to_figure($video_url);
  }
  
  // Is Vimeo?
  $pattern = '/vimeo:/msi';
  if (preg_match($pattern, $video_url, $match)) {
    return fbia_sync_vimeo_to_figure($video_url);
  }
}

/**
 * Get Youtube data.
 */
function fbia_sync_youtube_data($youtube_raw) {
  $pattern = '/v\/(.*)/msi';
  if (!preg_match($pattern, $youtube_raw, $match)) {
    return FALSE;
  }
  
  $youtube_id = $match[1];
  $src = "https://www.youtube.com/embed/{$youtube_id}";
  $code = "<iframe src=\"{$src}\" width=\"560\" height=\"315\"></iframe>";
  return array(
    'code' => $code,
    'src' => $src,
    'width' => 560,
    'height' => 315,
  );
}

/**
 * Get Youtube into Figure.
 */
function fbia_sync_youtube_to_figure($youtube_raw) {
  $pattern = '/v\/(.*)/msi';
  if (!preg_match($pattern, $youtube_raw, $match)) {
    return FALSE;
  }
  
  $youtube_id = $match[1];
  $output = "<figure class=\"op-interactive\">
    <iframe src=\"https://www.youtube.com/embed/{$youtube_id}\" width=\"560\" height=\"315\"></iframe>
  </figure>";
  return $output;
}

/**
 * Get Youtube data.
 */
function fbia_sync_vimeo_data($vimeo_raw) {
  $pattern = '/v\/(.*)/msi';

  if (!preg_match($pattern, $vimeo_raw, $match)) {
    return FALSE;
  }
  
  $vimeo_id = $match[1];
  $src = "https://player.vimeo.com/video/{$vimeo_id}";
  $code = "<iframe src=\"{$src}\" width=\"560\" height=\"315\"></iframe>";
  return array(
    'code' => $code,
    'src' => $src,
    'width' => 560,
    'height' => 315,
  );
}


/**
 * Get Youtube into Figure.
 */
function fbia_sync_vimeo_to_figure($vimeo_raw) {
  $pattern = '/v\/(.*)/msi';

  if (!preg_match($pattern, $vimeo_raw, $match)) {
    return FALSE;
  }
  
  $vimeo_id = $match[1];
  $output = "<figure class=\"op-interactive\">
    <iframe src=\"https://player.vimeo.com/video/{$vimeo_id}\" width=\"560\" height=\"315\"></iframe>
  </figure>";
  return $output;
}
