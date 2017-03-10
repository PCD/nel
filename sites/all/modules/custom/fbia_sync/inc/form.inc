<?php
/**
 * Implements hook_form.
 */
function fbia_sync_form($form, &$form_state) {
  $form = array();
  $form['fbia_sync_APP_ID'] = array(
    '#type' => 'textfield',
    '#title' => 'APP ID',
    '#required' => TRUE,
    '#default_value' => variable_get('fbia_sync_APP_ID', ''),
  );
  $form['fbia_sync_APP_SECRET'] = array(
    '#type' => 'textfield',
    '#title' => 'APP SECRET',
    '#required' => TRUE,
    '#default_value' => variable_get('fbia_sync_APP_SECRET', ''),
  );
  $form['fbia_sync_PAGE_ID'] = array(
    '#type' => 'textfield',
    '#title' => 'PAGE ID',
    '#required' => TRUE,
    '#default_value' => variable_get('fbia_sync_PAGE_ID', ''),
  );
  
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );
  return $form;
}

/**
 * Process fbia_sync_form submission.
 */
function fbia_sync_form_submit(&$form, &$form_state) {
  variable_set('fbia_sync_APP_ID', $form_state['values']['fbia_sync_APP_ID']);
  variable_set('fbia_sync_APP_SECRET', $form_state['values']['fbia_sync_APP_SECRET']);
  variable_set('fbia_sync_PAGE_ID', $form_state['values']['fbia_sync_PAGE_ID']);
}
