<?php
/**
 * Implements hook_block_info.
 */
function nelb_block_info() {
  $blocks = array();
  $blocks['sidebar'] = array(
    'info' => 'NELB Grid Sidebar', 
  );
  $blocks['facebook_script'] = array(
    'info' => 'Facebook Script', 
  );
  $blocks['facebook_comments'] = array(
    'info' => 'Facebook Comments', 
  );
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function nelb_block_view($delta = '') {
  $block = array();
  switch($delta) {
    case 'sidebar':
      $block = nelb_block_view_sidebar();
      break;

    case 'facebook_script':
      $block = nelb_block_view_facebook_script();
      break;

    case 'facebook_comments':
      $block = nelb_block_view_facebook_comments();
      break;
  }
  return $block;
}

/**
 * Grid Sidebar Block.
 */
function nelb_block_view_sidebar() {
  $params = array(
    'place' => 1, 
    'random' => true, 
  );
  
  // Detect if Homepage or Category or Article & Category
  if ( drupal_is_front_page() ) {
    $params['promote_to'] = 0;
  } else if ( arg(0) == 'taxonomy' && arg(1) == 'term' && intval(arg(2)) > 0 ) {
    $params['promote_to'] = 1;
  } else if ( arg(0) == 'node' && intval(arg(1)) > 0 ) {
    $node = node_load(arg(1));
    if ( ($term = nelb_data_get_category_page($node)) ) {
      $params['pid'] = $term->tid;
    }
    $params['promote_to'] = 2;
  }
  
  // Get Block
  $blocks = nelb_data_get_blocks($params);
  return array(
    'content' => nelb_theme_blocks($blocks), 
  );
}

/**
 * Block with Facebook Script.
 */
function nelb_block_view_facebook_script() {
  $output = "<div id=\"fb-root\"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = \"//connect.facebook.net/es_LA/sdk.js#xfbml=1&appId=117628395001698&version=v2.0\";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>\n";
  return array(
    'content' => $output, 
  );
}

/**
 * Block for Facebook Comments
 */
function nelb_block_view_facebook_comments() {
  $url = "http://{$_SERVER['HTTP_HOST']}/{$_GET['q']}";
  $output = "<div class=\"fb-comments\" data-href=\"{$url}\" data-width=\"100%\" data-numposts=\"5\" data-colorscheme=\"light\"></div>\n";
  return array(
    'content' => $output, 
  );
}
