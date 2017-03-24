<?php
define('DRUPAL_ROOT', getcwd());
$_SERVER['REMOTE_ADDR'] = "localhost"; // Necessary if running from command line
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
$GLOBALS['base_url'] = 'http://www.nayaritenlinea.mx';
$module_path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'fbia_sync') . '/inc/api.inc';
require_once $module_path;
fbia_sync_reset_all_with_errors();

