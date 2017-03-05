<?php 
/**
 * Add fbia wrapper.
 */
require __DIR__ . '/vendor/autoload.php';

/**
 * Instantiate an API client.
 * 
 * @param fbia_sync_APP_ID = fb app id
 * @param fbia_sync_APP_SECRET = fb app secred code
 * @param fbia_sync_ACCESS_TOKEN = Access token to the page
 * @param fbia_sync_PAGE_ID = Facebook page id
 *
 * @return $ia_client object.
 */
function fbia_sync_client_init() {
  use Facebook\InstantArticles\Client\Client;
  if (variable_get('fbia_sync_APP_ID')) {
    $fia_credentials['APP_ID'] = variable_get('fbia_sync_APP_ID');
  } else {
    return;
  }
  if (variable_get('fbia_sync_APP_SECRET')) {
    $fia_credentials['APP_SECRET'] = variable_get('fbia_sync_APP_SECRET');
  } else {
    return;
  }
  if (variable_get('fbia_sync_ACCESS_TOKEN')) {
    $fia_credentials['ACCESS_TOKEN'] = variable_get('fbia_sync_ACCESS_TOKEN');
  } else {
    return;
  }
  if (variable_get('fbia_sync_PAGE_ID')) {
    $fia_credentials['PAGE_ID'] = variable_get('fbia_sync_PAGE_ID');
  } else {
    return;
  }
  $ia_client = Client::create($fia_credentials);
  return $ia_client;
}

/**
 * Create instant article 
 * 
 * Variables:
 * @param html = html to convert to object.
 *  
 * $iarticle object
 *
 */
function fbia_sync_create_instant_article($html=NULL) {
  use Facebook\InstantArticles\Transformer\Transformer;
  if (!isset($html)) {
    return 'Error html not valid';
  }
  $transformer = new Transformer();
  $rules = file_get_contents(__DIR__ .'/vendor/facebook/facebook-instant-articles-sdk-php/tests/Facebook/InstantArticles/Transformer/custom-html-rules.json', true);
  $transformer->loadRules($rules);
  $document = new \DOMDocument();
  $document->loadHTML($html);
  $iarticle = InstantArticle::create();
  $transformer->transform($iarticle, $document);
  $warnings = $transformer->getWarnings();

  return $iarticle;
}

/**
 * Push Instant article to facebook
 */
function fbia_sync_push_article($iarticle){
  if (!is_object($iarticle)) {
    return 'Instant article is not valid';
  }
  $ia_client = fbia_sync_client_init();
  if (is_object($ia_client)) {
    try {
      $ia_client->importArticle($my_article);
    } catch (Exception $e) {
        echo 'Could not import the article: '.$e->getMessage();
    }
  } else {
    return 'Error loading Client '.$ia_client;
  }
}

/**
 * Delete Instant article of facebook.
 *
 * @param $iarticle article object.
 */
function fbia_sync_delete_article($iarticle) {
  if (!is_object($iarticle)) {
    return 'Instant article is not valid';
  }
  $ia_client = fbia_sync_client_init();
  $iarticle_object = fbia_sync_load_iarticle($iarticle);
  if (is_object($ia_client)) {
    try {
      $ia_client->importArticle($my_article);
    } catch (Exception $e) {
        echo 'Could not import the article: '.$e->getMessage();
    }
  } else {
    return 'Error loading Client '.$ia_client;
  }
}

/**
 * Load Instant article
 *
 * @params 
 */
function fbia_sync_load_iarticle($iarticle) {
  
}
