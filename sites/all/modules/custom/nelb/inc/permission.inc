<?php
/**
 * Implements hook_permission.
 */
function nelb_permission() {
  return array(
    'access nelb pages' => array(
      'title' => 'access nelb pages', 
      'description' => 'access nelb pages', 
    ), 
  );
}
