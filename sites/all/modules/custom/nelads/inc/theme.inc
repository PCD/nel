<?php
/**
 * Implements hook_theme.
 */
function nelads_theme() {
  return array(
    'nelads-adslot' => array(
      'arguments' => array(
        'adslot' => 1, 
        'adsvar' => 'ads_article_detail', 
        'wrapper_class' => FALSE, 
      ), 
      'template' => 'templates/nelads-adslot', 
    ), 
  );
}
