<?php
/**
 * Implements hook_node_insert.
 */
function fbia_sync_node_insert($node) {
  // Crear html output.
  $output = theme('fbia-sync--article', array(
    'title' => $node->title,
    'subtitle' => $node->subtitle,
  ))

  // Mandar a API.
}

/**
 * Implements hook_node_update.
 */
function fbia_sync_node_update($node) {
  
}

/**
 * Implements hook_node_delete.
 */
function fbia_sync_node_delete($node) {
  
}

/**
 * Get FBI Node.
 */
function fbia_sync_prepare_node($node) {
  $image_main = fbia_sync_get_chosen_image($node);
  $image_main = file_create_url($node->field_image[LANGUAGE_NONE][0]['uri']);
  $image_main_alt = $node->field_image[LANGUAGE_NONE][0]['alt'];
  $published_date = format_date($node->field_date[LANGUAGE_NONE][0]['value'], 'medium', '', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $published_date_r = format_date($node->field_date[LANGUAGE_NONE][0]['value'], 'custom', 'r', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $modified_date = format_date($node->field_date[LANGUAGE_NONE][0]['value'], 'medium', '', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $modified_date_r = format_date($node->field_date[LANGUAGE_NONE][0]['value'], 'custom', 'r', $node->field_date[LANGUAGE_NONE][0]['timezone']);
  $main_category = taxonomy_term_load($node->field_main_category[LANGUAGE_NONE][0]['tid']);
  $breadcrumbs = $main_category->name;
  $slideshow = array();
  if (count($node->field_image[LANGUAGE_NONE]) > 1) {
    foreach($node->field_image[LANGUAGE_NONE] as $image_item_raw) {
      $image_item = file_create_url($image_item_raw['uri']);
      $image_item_alt = $image_item_raw['alt'];
      $slideshow[] = array(
        'src' => file_create_url($image_item_raw['uri']), 
        'alt' => $image_item_raw['alt'],
      );
    }
  }
  $ads = fbia_sync_get_ads();
  
  $node_args = array(
    'title' => $node->title,
    'sub_title' => $node->field_intro[LANGUAGE_NONE][0]['value'],
    'published_date' => $published_date,
    'published_date_r' => $published_date_r,
    'modified_date' => $modified_date,
    'modified_date_r' => $modified_date_r,
    'author' => $node->field_author[LANGUAGE_NONE][0]['value'],
    'image_main' => $image_main,
    'image_main_alt' => $image_main_alt,
    'breadcrumbs' => $breadcrumbs,
    'body' => $node->body[LANGUAGE_NONE][0]['value'],
    'video' => fbia_sync_node_video_to_figure($node),
    'slideshow' => $slideshow,
    'ads' => $ads,
  );
}

/**
 * Get Ads for Facebook Instant Articles.
 */
function fbia_sync_get_ads() {
  $ad1 = "<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
              new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
              j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
              'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
              })(window,document,'script','dataLayer','GTM-KSC2LWD');</script>
              <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-KSC2LWD"
              height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>"
}
<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
              new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
              j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
              'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
              })(window,document,'script','dataLayer','GTM-KSC2LWD');</script>
              <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-KSC2LWD"
              height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
              
              
/**
 * Get Node chosen Image.
 */
function fbia_sync_get_chosen_image($node) {
  if (fbia_sync_node_video_to_figure($node)) {
    if (isset($node->field_video_image[LANGUAGE_NONE][0]['uri'])) {
      return 
    }
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
function fbia_sync_youtube_to_figure($vimeo_raw) {
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

vimeo://v/206673939