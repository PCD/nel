<?php
/**
 * Implements hook_preprocess_field.
 */
function nel_preprocess_field(&$variables) {
  $element = $variables['element'];
  if ( $element['#field_type'] == 'field_collection' && $element['#field_name'] == 'field_banner_block' ) {
    $fcid = $element['#items'][0]['value'];
    $fcitems = field_collection_item_load_multiple(array($fcid));
    $fc = $fcitems[$fcid];

    if ( $fc->field_body_type[LANGUAGE_NONE][0]['value'] == 100 ) {
      $variables['classes_array'][] = 'adsense-micrositio-block';
      $variables['element']['classes_array'][] = 'adsense-micrositio-block';
      //print_r(array_keys($variables));exit;
    }

  }
}