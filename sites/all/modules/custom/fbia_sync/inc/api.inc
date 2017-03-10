<?php
require_once dirname(__DIR__) . '/libs/facebook-instant-articles-sdk/vendor/autoload.php';
use Facebook\InstantArticles\Transformer\Transformer;
use Facebook\InstantArticles\Parser\Parser;
use Facebook\InstantArticles\Client\Client;
use Facebook\InstantArticles\Client\Helper;

/**
 * Process Node into FBIA.
 */
function fbia_sync_process($node) {
  $node_args = fbia_sync_prepare_node($node);
  $html = theme('fbia-sync--article', $node_args);
  
  libxml_use_internal_errors(true);
  $document = new \DOMDocument();
  $document->loadHTML($html);
  libxml_use_internal_errors(false);
  $parser = new Parser();
  //$instant_article = $parser->parse($document);
  
  /*$client = Client::create(
    'APP_ID',
    'APP_SECRET',
    'ACCESS_TOKEN',
    'PAGE_ID',
    TRUE // Use development environment?
  );*/
  $userAccessToken = 'USER_ACCESS_TOKEN';

  // Instantiate a client helper
  $app_id = variable_get('fbia_sync_APP_ID');
  $app_secret = variable_get('fbia_sync_APP_SECRET');
  $helper = Helper::create(
    $app_id,
    $app_secret
  );
  /*$pagesAndTokens = $helper->getPagesAndTokens($userAccessToken)->all();
  foreach ($pagesAndTokens as $pageAndToken) {
    echo 'Page ID: ' . $pageAndToken->getField('id');
    echo 'Page name: ' . $pageAndToken->getField('name');
    echo 'Page access token: ' . $pageAndToken->getField('access_token');
  }
  exit;
  
  /*
  
  // Instantiate an API client
  $client = Client::create(
    'APP_ID',
    'APP_SECRET',
    'ACCESS_TOKEN',
    'PAGE_ID',
    TRUE // Use development environment?
  );
  
  // Import the article
  try {
    $client->importArticle($article, $take_live);
  } catch (Exception $e) {
    echo 'Could not import the article: '.$e->getMessage();
  }
  */
}