<?php
/**
 * Themes out an array of nodes and taxonomy blocks.
 */
function nelb_theme_blocks($groups) {
  $output = '';
  foreach($groups as $group) {
    $output .= nelb_theme_blocks_group($group);
  }
  
  return theme('nelb-block', array(
    'class' => 'nelb-grid', 
    'content' => $output, 
  ));
}

/**
 * Themes out a Block group array.
 */
function nelb_theme_blocks_group($group) {
  $output = '';
  foreach($group['types'] as $type) {
    $output .= nelb_theme_blocks_type($type);
  }
  
  return theme('nelb-block', array(
    'class' => $group['class'], 
    'content' => $output, 
  ));
}

/**
 * Themes out a Block type array.
 */
function nelb_theme_blocks_type($type) {
  $output = '';
  foreach($type['items'] as $item) {
    $output .= nelb_theme_blocks_type_item($item);
  }

  return theme('nelb-block', array(
    'class' => $type['class'], 
    'content' => $output, 
  ));
}

function nelb_theme_blocks_type_item($item) {
  switch($item['type']) {
    case 'node':
      return nelb_theme_blocks_type_item_node($item);
      break;

    case 'taxonomy':
      return nelb_theme_blocks_type_item_taxonomy($item);
      break;
  }
  return '';
}

/**
 * Themes out a Node Block Item.
 */
function nelb_theme_blocks_type_item_node($item) {
  $node = node_load($item['id']);
  $view = node_view($node, 'teaser');
  $content = drupal_render($view);
  $title = $item['show_title']==1?check_plain($item['title']):NULL;
  $class_content = $item['show_title']==1?'article-content':NULL;
  return theme('nelb-block', array(
    'class' => $item['class'], 
    'title' => $title, 
    'content' => $content, 
    'class_content' => $class_content, 
  ));
}

/**
 * Themes out a Taxonomy Block Item.
 */
function nelb_theme_blocks_type_item_taxonomy($item) {
  $title = l($item['title'], $item['path']);
  $display = nelb_data_taxonomy_display_get_by_id($item['style']);
  
  // Build Output
  $content = '';
  foreach($display['columns'] as $column) {
    $content .= nelb_theme_blocks_type_item_taxonomy_style($column, $item, $display);
  }
  
  return theme('nelb-block', array(
    'class' => $item['class'], 
    'class_content' => 'article-content', 
    'content' => $content, 
    'title' => $title, 
  ));
}

/**
 * Embeds a View for Taxonomy Style.
 */
function nelb_theme_blocks_type_item_taxonomy_style($column, $block, $display) {
  $content = views_embed_view('taxonomy_articles', $column['display_id'], $block['id']);
  
  return theme('nelb-block', array(
    'class' => $column['class'], 
    'content' => $content, 
  ));
}

/**
 * Implements hook_theme.
 */
function nelb_theme() {
  return array(
    'nelb-block' => array(
      'arguments' => array(
        'content' => NULL, 
        'class' => NULL, 
        'class_content' => NULL, 
        'title' => NULL, 
      ), 
      'template' => 'themes/grid/nelb-block', 
    ), 
    'nelb-block-taxonomy-group' => array(
      'arguments' => array(
        'class' => NULL, 
        'content' => NULL, 
      ), 
      'template' => 'themes/taxonomy/nelb-block-taxonomy-group', 
    ), 
    'nelb-block-taxonomy' => array(
      'arguments' => array(
        'class' => NULL, 
        'title' => NULL, 
        'content' => NULL, 
      ), 
      'template' => 'themes/taxonomy/nelb-block-taxonomy', 
    ), 
    'nelb-block-taxonomy-item' => array(
      'arguments' => array(
        'class' => NULL, 
        'content' => NULL, 
      ), 
      'template' => 'themes/taxonomy/nelb-block-taxonomy-item', 
    ), 
  );
}