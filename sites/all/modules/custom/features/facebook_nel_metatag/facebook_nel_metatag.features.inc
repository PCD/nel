<?php
/**
 * @file
 * facebook_nel_metatag.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function facebook_nel_metatag_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function facebook_nel_metatag_image_default_styles() {
  $styles = array();

  // Exported image style: facebook_sharing.
  $styles['facebook_sharing'] = array(
    'label' => 'Facebook Sharing (600px)',
    'effects' => array(
      24 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 600,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
