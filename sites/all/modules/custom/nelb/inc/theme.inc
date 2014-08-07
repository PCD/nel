<?php
/**
 * Themes out an array of nodes and taxonomy blocks.
 */
function nelb_theme_blocks($groups) {
  $output = "<div id=\"blocks-grid\">\n";
  foreach($groups as $blocks) {
    $block_output = '';
    foreach($blocks as $block) {
      if ( $block['type'] == 'taxonomy' ) {
        $block_output .= nelb_theme_blocks_item($block);
      }
    }
    $output .= theme('nelb-block-taxonomy-group', array(
      'class' => 'group-row', 
      'content' => $block_output, 
    ));
  }
  $output .= "</div>\n";
  return $output;
}

/**
 * Themes out a single block.
 */
function nelb_theme_blocks_item($block) {
  $output = '';
  $display = nelb_data_taxonomy_display_get_by_id($block['style']);

  // Build Output
  foreach($display['columns'] as $column) {
    $output .= nelb_theme_blocks_item_tpl($column, $block, $display);
  }
  
  // Add Wrapper
  $link = l($block['title'], $block['path']);
  return theme('nelb-block-taxonomy', array(
    'class' => $display['class'], 
    'title' => $link, 
    'content' => $output, 
  ));
}

/**
 *
 */
function nelb_theme_blocks_item_tpl($column, $block, $display) {
  $content = views_embed_view('taxonomy_articles', $column['display_id'], $block['id']);
  return theme('nelb-block-taxonomy-item', array(
    'class' => $column['class'], 
    'content' => $content, 
  ));
}

/**
 * Implements hook_theme.
 */
function nelb_theme() {
  return array(
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