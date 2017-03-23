<?php
require_once dirname(__DIR__) . '/libs/facebook-instant-articles-sdk/vendor/autoload.php';
use Facebook\InstantArticles\Transformer\Transformer;
use Facebook\InstantArticles\Elements\InstantArticle;
use Facebook\InstantArticles\Elements\Header;
use Facebook\InstantArticles\Elements\Time;
use Facebook\InstantArticles\Elements\Image;
use Facebook\InstantArticles\Elements\Caption;
use Facebook\InstantArticles\Elements\Slideshow;
use Facebook\InstantArticles\Elements\Paragraph;
use Facebook\InstantArticles\Elements\Ad;
use Facebook\InstantArticles\Elements\Interactive;
use Facebook\InstantArticles\Parser\Parser;
use Facebook\InstantArticles\Client\Client;
use Facebook\InstantArticles\Client\Helper;
use Facebook\InstantArticles\Elements\RelatedArticles;
use Facebook\InstantArticles\Elements\RelatedItem;
use Facebook\InstantArticles\Elements\Footer;

/**
 * Process Node into FBIA.
 */
function fbia_sync_process_test($node) {
  /*fbia_sync_mark_record($node);
  return true;*/
  
  $node_args = fbia_sync_prepare_node($node);
  $instant_article = fbia_sync_build_article($node_args);
  print_r($instant_article->render());exit;

  $app_id = variable_get('fbia_sync_APP_ID');
  $app_secret = variable_get('fbia_sync_APP_SECRET');
  $page_id = variable_get('fbia_sync_PAGE_ID');
  $access_token = variable_get('fbia_sync_ACCESS_TOKEN');
  $dev_mode = variable_get('fbia_sync_DEVELOPMENT_MODE', 1);
  $dev_mode = $dev_mode == 1 ? TRUE : FALSE;
  $client = Client::create(
    $app_id,
    $app_secret,
    $access_token,
    $page_id,
    $dev_mode // Use development environment?
  );
  
  try {
    $published_mode = variable_get('fbia_sync_PUBLISHED', 1);
    $published_mode = $published_mode == 1 ? TRUE : FALSE;
    $response = $client->importArticle($instant_article, $published_mode);
    $errors = 0;
  } catch (Exception $e) {
    $msg = 'Could not import the article from nid = ' . $node->nid . ': ' . $e->getMessage();
    watchdog('fbia_sync', $msg, array(), WATCHDOG_ERROR);
    $errors = 1;
  }
  fbia_sync_mark_record($node, $errors, $response);
}

/**
 * Process Node into FBIA.
 */
function fbia_sync_process($node) {
  $node_args = fbia_sync_prepare_node($node);
  

  try {
    $instant_article = fbia_sync_build_article($node_args);
  
    $app_id = variable_get('fbia_sync_APP_ID');
    $app_secret = variable_get('fbia_sync_APP_SECRET');
    $page_id = variable_get('fbia_sync_PAGE_ID');
    $access_token = variable_get('fbia_sync_ACCESS_TOKEN');
    $dev_mode = variable_get('fbia_sync_DEVELOPMENT_MODE', 1);
    $dev_mode = $dev_mode == 1 ? TRUE : FALSE;
    $client = Client::create(
      $app_id,
      $app_secret,
      $access_token,
      $page_id,
      $dev_mode // Use development environment?
    );
  
    $published_mode = variable_get('fbia_sync_PUBLISHED', 1);
    $published_mode = $published_mode == 1 ? TRUE : FALSE;
    $client->importArticle($instant_article, $published_mode);
    $errors = 0;
    $response = array(
      'nid' => $node->nid,
      'node_args' => $node_args,
    );
  } catch (Exception $e) {
    $msg = 'Could not import the article from nid = ' . $node->nid . ': ' . $e->getMessage();
    watchdog('fbia_sync', $msg, array(), WATCHDOG_ERROR);
    $response = array(
      'msg' => $msg,
      'nid' => $node->nid,
      'node_args' => $node_args,
    );
    $errors = 1;
    echo print_r($response, TRUE) . "\n\n";
  }
  fbia_sync_mark_record($node, $errors, $response);
}

/**
 * Builds an Instant Article as DOM based on the node args provided.
 */
function fbia_sync_build_article($node_args) {
  // Header.
  $header = Header::create();
  if (isset($node_args['title'])) {
    $header->withTitle($node_args['title']);
  }
  if (isset($node_args['sub_title'])) {
    $header->withSubTitle($node_args['sub_title']);
  }
  if (isset($node_args['published_date_time'])) {
    $header->withPublishTime(
      Time::create(Time::PUBLISHED)
        ->withDatetime(
          \DateTime::createFromFormat(
            'j-M-Y G:i:s',
            date('j-M-Y G:i:s', $node_args['published_date_time'])
          )
        )
    );
  }
  if (isset($node_args['modified_date_time'])) {
    $header->withModifyTime(
      Time::create(Time::MODIFIED)
        ->withDatetime(
          \DateTime::createFromFormat(
            'j-M-Y G:i:s',
            date('j-M-Y G:i:s', $node_args['modified_date_time'])
        )
      )
    );
  }
  
  // Authors.
  if (isset($node_args['author'])) {
    $author = Author::create()->withName($node_args['author']);
    if (isset($node_args['author_url'])) {
      $author->withURL($node_args['author_url']);
    }
    $header->addAuthor($author);
  }
  
  // Breadcrumbs.
  if (isset($node_args['breadcrumbs'])) {
    $header->withKicker($node_args['breadcrumbs']);
  }
  
  // Ads.
  if (isset($node_args['ads'])) {
    $c = count($node_args['ads']);
    for($i = 0; $i < $c; $i++) {
      $ad_raw = $node_args['ads'][$i];
      $ad = Ad::create();
      $ad->withSource($ad_raw['src']);
      $ad->withWidth($ad_raw['width']);
      $ad->withHeight($ad_raw['height']);
      $ad->enableDefaultForReuse();
      $header->addAd($ad);
    }
  }

  // Main Image - Cover.
  if (isset($node_args['image_main'])) {
    $cover_image = Image::create()->withURL($node_args['image_main']);
    if (isset($node_args['image_main_alt'])) {
      $cover_caption = Caption::create()->appendText($node_args['image_main_alt']);
      $cover_image->withCaption($cover_caption);
    }
      
    $header->withCover($cover_image);
  }

  // Article.
  $article = InstantArticle::create()
    ->withCanonicalUrl($node_args['url'])
    ->withHeader($header);
  
  // Tags.
  $article->addMetaProperty('fb:use_automatic_ad_placement', 'true');
  $article->addMetaProperty('fb:likes_and_comments', 'true');
  $article->addMetaProperty('op:generator', 'facebook-instant-articles-sdk-php');
  $article->addMetaProperty('op:generator:version', '1.0.0');
  $article->addMetaProperty('op:generator:transformer', 'facebook-instant-articles-sdk-php');
  $article->addMetaProperty('op:generator:transformer:version', '1.0.0');
  $article->addMetaProperty('op:markup_version', 'v1.0');
  
  // Body.
  $paragraphs = $iframes = array();
  
  fbia_sync_split_paragraphs($node_args['body'], $paragraphs, $iframes);
  
  foreach($paragraphs as $i => $paragraph) {
    $paragraph_item = Paragraph::create()->appendText(strip_tags($paragraph));
    $article->addChild($paragraph_item);
  }
  
  // Videos.
  if (isset($node_args['video'])) {
    $interactive = Interactive::create()->withSource($node_args['video']['src']);
    if (isset($node_args['video']['width'])) {
      $interactive->withWidth($node_args['video']['width']);
    }
    if (isset($node_args['video']['height'])) {
      $interactive->withHeight($node_args['video']['height']);
    }
    $article->addChild($interactive);
  }
  
  // Iframes.
  foreach($iframes as $iframe) {
    $interactive = Interactive::create()->withSource($iframe['src']);
    if (isset($iframe['width'])) {
      $interactive->withWidth($iframe['width']);
    }
    if (isset($iframe['height'])) {
      $interactive->withHeight($iframe['height']);
    }
    $article->addChild($interactive);
  }
  
  // Slideshow.
  if (isset($node_args['slideshow'])) {
    $slideshow = SlideShow::create();
    foreach($node_args['slideshow'] as $item) {
      $image = Image::create()->withURL($item['src']);
      if (isset($item['alt'])) {
        $image->withCaption($item['alt']);
      }
      $slideshow->addImage($image);
    }
    $article->addChild($slideshow);
  }

  // Analytics.
  if (isset($google_analytics)) {
    $google_analytics = $document->createDocumentFragment();
    $google_analytics->appendXML(
      "<script>
        (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
        (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
        m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
        })(window,document,'script','https://www.google-analytics.com/analytics.js','ga');
      
        ga('create', 'UA-1262614-5', 'auto');
        ga('send', 'pageview');
      
      </script>"
    );
    $analytics = Analytics::create()->withHTML($google_analytics);
    $article->addChild($analytics);
  }
  
  // Footer.
  $footer = Footer::create()
    ->withRelatedArticles(
      RelatedArticles::create()
        ->withTitle('También te puede Interesar')
    );
  
  $article->withFooter($footer);
  
  return $article;
}