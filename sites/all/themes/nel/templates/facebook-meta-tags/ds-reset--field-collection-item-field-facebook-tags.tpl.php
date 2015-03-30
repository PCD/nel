<?php
$node = $field_collection_item->hostEntity();

// Prepare Tags
$fb_tags = array();
$fb_title = $fb_body = $fb_image = NULL;

// FB Title Tag
if ( isset($field_facebook_title[0]['safe_value']) && !nel_is_empty($field_facebook_title[0]['safe_value']) ) {
  $fb_title = $field_facebook_title[0]['safe_value'];
} else if ( isset($node->title) && !nel_is_empty($node->title) ) {
  $fb_title = check_plain($node->title);
} else {
  $fb_title = 'Nayarit En Linea';
}
$fb_tags['fb_metatag_title'] = array(
  'og:title' => $fb_title, 
);

// FB Description Tag
if ( isset($field_facebook_body[0]['safe_value']) && !nel_is_empty($field_facebook_body[0]['safe_value']) ) {
  $fb_body = $field_facebook_body[0]['safe_value'];
} else if ( isset($node->body[LANGUAGE_NONE][0]['safe_value']) && !nel_is_empty($node->body[LANGUAGE_NONE][0]['safe_value'])) {
  $fb_body = $node->body[LANGUAGE_NONE][0]['safe_value'];
} else {
  $fb_body = 'El Portal de Nayarit';
}
$fb_tags['fb_metatag_description'] = array(
  'og:description' => $fb_body, 
);

// FB Image Tag
if ( isset($field_facebook_image[0]['uri']) && !empty($field_facebook_image[0]['uri']) ) {
  $fb_image = image_style_url('facebook_sharing', $field_facebook_image[0]['uri']);
} else if ( isset($node->field_meta_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_meta_image[LANGUAGE_NONE][0]['uri']) ) {
  $fb_image = image_style_url('facebook_sharing', $node->field_meta_image[LANGUAGE_NONE][0]['uri']);
} else if ( isset($node->field_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_image[LANGUAGE_NONE][0]['uri']) ) {
  $fb_image = image_style_url('facebook_sharing', $node->field_image[LANGUAGE_NONE][0]['uri']);
} else if ( isset($node->field_video_image[LANGUAGE_NONE][0]['uri']) && !empty($node->field_video_image[LANGUAGE_NONE][0]['uri']) ) {
  $fb_image = image_style_url('facebook_sharing', $node->field_video_image[LANGUAGE_NONE][0]['uri']);
} else {
  $fb_image = 'http://www.nayaritenlinea.mx/sites/all/themes/nel/logo_retina.png';
}
$fb_tags['fb_metatag_image'] = array(
  'og:image' => $fb_image, 
);

// FB Type Tag
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