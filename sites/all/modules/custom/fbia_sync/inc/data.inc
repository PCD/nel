<?php
/**
 * Get FBI Node.
 */
function fbia_sync_prepare_node($node) {
  $published_date = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'medium', '', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $published_date_r = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'custom', 'r', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $modified_date = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'medium', '', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $modified_date_r = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'custom', 'r', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $main_category = taxonomy_term_load($node->field_main_category[LANGUAGE_NONE][0]['tid']);
  $breadcrumbs = $main_category->name;
  $node_args = array(
    'title' => $node->title,
    'sub_title' => trim(strip_tags($node->field_intro[LANGUAGE_NONE][0]['value'])),
    'published_date' => $published_date,
    'published_date_r' => $published_date_r,
    'modified_date' => $modified_date,
    'modified_date_r' => $modified_date_r,
    'author' => $node->field_author[LANGUAGE_NONE][0]['value'],
    'breadcrumbs' => $breadcrumbs,
    'body' => $node->body[LANGUAGE_NONE][0]['value'],
    'video' => fbia_sync_node_video_to_figure($node),
    'slideshow' => $slideshow,
    'ads' => $ads,
  );

  if (($img = fbia_sync_get_chosen_image($node))) {
    $node_args['image_main'] = $img['src'];
    $node_args['image_main_alt'] = $img['alt'];
  }
  
  if (($slideshow = fbia_sync_get_slideshow_images($node))) {
    $node_args['slideshow'] = $slideshow;
  }
  
  if (($ads = fbia_sync_get_ads())) {
    $node_args['ads'] = $ads;
  }
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
    'width' => 300,
    'height' => 250,
  );
  return $ads;
}

/**
 * Get Slideshow Images.
 */
function fbia_sync_get_slideshow_images($node) {
  $slideshow = array();
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
  
  return $img;
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
 * Get Youtube into Figure.
 */
function fbia_sync_youtube_to_figure($youtube_raw) {
  $pattern = '/v\/(.*)/msi';
  if (!preg_match($pattern, $youtube_raw, $match)) {
    return FALSE;
  }
  
  $youtube_id = $match[1];
  $output = "<figure class=\"op-interactive\">
    <iframe src=\"https://www.youtube.com/embed/{$youtube_id}\"></iframe>
  </figure>";
  return $output;
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
    <iframe src=\"https://player.vimeo.com/video/{$vimeo_id}\"></iframe>
  </figure>";
  return $output;
}
