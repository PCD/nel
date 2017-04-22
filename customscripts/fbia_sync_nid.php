<?php
define('DRUPAL_ROOT', getcwd());
$_SERVER['REMOTE_ADDR'] = "localhost"; // Necessary if running from command line
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
$GLOBALS['base_url'] = 'http://www.nayaritenlinea.mx';
$module_path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'fbia_sync') . '/inc/api.inc';
require_once $module_path;

echo "Type the node id to process: ";
$handle = fopen ("php://stdin","r");
$line = fgets($handle);
$nid = intval(trim($line));
if ($nid < 1) {
  echo "\nAbort.\n\n";
}

echo "\nAbout to process nid = {$nid}\n\n";
fbia_sync_script_process($nid);