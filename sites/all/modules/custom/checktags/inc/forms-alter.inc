<?php
/**
 * Alters Forms Article Node.
 */
function checktags_form_alter(&$form, &$form_state, $form_id) {
  if ( $form_id != 'article_node_form' ) {
    return;
  }
  
  $form['#validate'][] = 'checktags_article_form_validate';
}

/**
 * Validates Some fields sensitive for the Facebook Image.
 */
function checktags_article_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  
  $image_set = false;
  if ( isset($values['field_image'][LANGUAGE_NONE][0]['fid']) && $values['field_image'][LANGUAGE_NONE][0]['fid'] > 0 ) {
    $image_set = true;
  } else if ( isset($values['field_meta_image'][LANGUAGE_NONE][0]['fid']) && $values['field_meta_image'][LANGUAGE_NONE][0]['fid'] > 0 ) {
    $image_set = true;
  } else if ( isset($values['field_video_image'][LANGUAGE_NONE][0]['fid']) && $values['field_video_image'][LANGUAGE_NONE][0]['fid'] > 0 ) {
    $image_set = true;
  } else if ( isset($values['field_facebook_tags'][LANGUAGE_NONE][0]['field_facebook_image'][LANGUAGE_NONE][0]['fid']) && $values['field_facebook_tags'][LANGUAGE_NONE][0]['field_facebook_image'][LANGUAGE_NONE][0]['fid'] > 0 ) {
    $image_set = true;
  }
  
  if ( $image_set == false ) {
    form_set_error('field_meta_image', '<p>No has proporcionado ninguna imagen. Sube al menos una imagen en alguno de los campos marcados en rojo.</p>');
    form_set_error('field_image', '');
    form_set_error('field_video_image', '');
    form_set_error('field_facebook_tags][' . LANGUAGE_NONE . '][0][field_facebook_image', '');
  }
}