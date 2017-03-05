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