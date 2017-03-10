<?php
require_once dirname(__DIR__) . '/libs/facebook-instant-articles-sdk/vendor/autoload.php';
function fbia_sync_login() {
  $fb = new Facebook\Facebook([
    'app_id' => variable_get('fbia_sync_APP_ID'),
    'app_secret' => variable_get('fbia_sync_APP_SECRET'),
    'default_graph_version' => 'v2.5',
  ]);
  
  $helper = $fb->getRedirectLoginHelper();
  
  $permissions = ['manage_pages']; // Optional permissions
  $url = url('fbia_sync/callback', array('absolute'=>TRUE));
  $loginUrl = $helper->getLoginUrl($url, $permissions);
  
  return '<a href="' . htmlspecialchars($loginUrl) . '">Log in with Facebook!</a>';
}