<?php
require_once dirname(__DIR__) . '/libs/facebook-instant-articles-sdk/vendor/autoload.php';
/**
 * Implements hook_form.
 */
function fbia_sync_form($form, &$form_state) {
  $form = array();
  $app_id = variable_get('fbia_sync_APP_ID', false);
  $app_secret = variable_get('fbia_sync_APP_SECRET', false);
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
  
  if (($access_token = variable_get('fbia_sync_ACCESS_TOKEN', false)) && !empty($access_token) && !isset($_GET['regenerate'])) {
    $form['fbia_sync_ACCESS_TOKEN'] = array(
      '#type' => 'textarea',
      '#title' => 'Access Token',
      '#required' => TRUE,
      '#default_value' => $access_token,
    );
  }
  else {
    // If we have already app_id and app_secret.
    if ($app_id && $app_secret) {
      // Login or Callback.
      if (!isset($_GET['code'])) {
        $fb = new Facebook\Facebook([
          'app_id' => $app_id,
          'app_secret' => $app_secret,
          'default_graph_version' => 'v2.5',
        ]);
        
        $helper = $fb->getRedirectLoginHelper();
        
        $permissions = ['pages_manage_instant_articles', 'pages_show_list']; // Optional permissions
        $url = url('admin/config/fbia_sync', array('absolute'=>TRUE, 'query' => array('regenerate' => 1)));
        $loginUrl = $helper->getLoginUrl($url, $permissions);
        
        $link = '<a href="' . htmlspecialchars($loginUrl) . '">Log in with Facebook!</a>';
        $form['fbia_link'] = array(
          '#type' => 'markup',
          '#markup' => $link,
        );
      }
      else {
        $fb = new Facebook\Facebook([
          'app_id' => $app_id,
          'app_secret' => $app_secret,
          'default_graph_version' => 'v2.5',
        ]);
        
        $helper = $fb->getRedirectLoginHelper();
        
        try {
          $accessToken = $helper->getAccessToken();
        } catch(Facebook\Exceptions\FacebookResponseException $e) {
          // When Graph returns an error
          echo 'Graph returned an error: ' . $e->getMessage();
          exit;
        } catch(Facebook\Exceptions\FacebookSDKException $e) {
          // When validation fails or other local issues
          echo 'Facebook SDK returned an error: ' . $e->getMessage();
          exit;
        }
        
        if (! isset($accessToken)) {
          if ($helper->getError()) {
            header('HTTP/1.0 401 Unauthorized');
            echo "Error: " . $helper->getError() . "\n";
            echo "Error Code: " . $helper->getErrorCode() . "\n";
            echo "Error Reason: " . $helper->getErrorReason() . "\n";
            echo "Error Description: " . $helper->getErrorDescription() . "\n";
          } else {
            header('HTTP/1.0 400 Bad Request');
            echo 'Bad request';
          }
          exit;
        }
        
        // Logged in
        $oAuth2Client = $fb->getOAuth2Client();
        
        $tokenMetadata = $oAuth2Client->debugToken($accessToken);
        $tokenMetadata->validateAppId($app_id); // Replace {app-id} with your app id
        $tokenMetadata->validateExpiration();
        
        if (! $accessToken->isLongLived()) {
          try {
            $accessToken = $oAuth2Client->getLongLivedAccessToken($accessToken);
          } catch (Facebook\Exceptions\FacebookSDKException $e) {
            echo "<p>Error getting long-lived access token: " . $helper->getMessage() . "</p>\n\n";
            exit;
          }
        }
        
        //$_SESSION['fb_access_token'] = (string) $accessToken;
        variable_set('fbia_sync_ACCESS_TOKEN', $accessToken);
        $form['fbia_sync_ACCESS_TOKEN'] = array(
          '#type' => 'textarea',
          '#title' => 'Access Token',
          '#required' => TRUE,
          '#default_value' => $accessToken,
        );
        drupal_set_message(t('Access Token has been saved.'));
      }
    }
  }
  
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
  if (isset($form_state['values']['fbia_sync_ACCESS_TOKEN'])) {
    variable_set('fbia_sync_ACCESS_TOKEN', $form_state['values']['fbia_sync_ACCESS_TOKEN']);
    //EAAbJJ6uLYqEBAFSNqrc7ZCEnGjnIOT6QQkTTCcBJcZCqyWSG5p1iSMU7JktBEJRBdYm96P3MNOfDMJIHPr0rZCeAVTsTA8dumjc7uwI4K6r7uQMpoK3QcahuZAzPMOF4l8skVspqzJOlc6PTUwGBJn2O2WbEFI4ZD
  }
}




















