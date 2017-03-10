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
  $parser = new Parser();
  $instant_article = $parser->parse($html);
  print_r($instant_article);
  exit;
  
  $app_id = variable_get('fbia_sync_APP_ID');
  $app_secret = variable_get('fbia_sync_APP_SECRET');
  $page_id = variable_get('fbia_sync_PAGE_ID');
  $access_token = variable_get('fbia_sync_ACCESS_TOKEN');
  $client = Client::create(
    $app_id,
    $app_secret,
    $access_token,
    $page_id,
    TRUE // Use development environment?
  );
  
  try {
    $client->importArticle($instant_article, FALSE);
  } catch (Exception $e) {
    echo 'Could not import the article: '.$e->getMessage();
  }
  exit;
}