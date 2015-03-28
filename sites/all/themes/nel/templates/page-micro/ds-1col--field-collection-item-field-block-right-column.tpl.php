<?php
// Views
$displays = array(
  'one-big-4-small-one-column' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block', 
        'display_no_tid_id' => 'block_7', 
        'class' => 'col-1 main-article', 
      ), 
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_1', 
        'display_no_tid_id' => 'block_8', 
        'class' => 'col-1 other-article', 
      ), 
    ), 
    'class' => 'one-big-4-small-one-column', 
  ), 
  'small-carousel' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_4', 
        'display_no_tid_id' => 'block_11', 
        'class' => 'small-carousel', 
      ), 
    ), 
    'class' => 'small-carousel', 
  ), 
  'four-small-inverted-list' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_3', 
        'display_no_tid_id' => 'block_10', 
        'class' => '', 
      ), 
    ), 
    'class' => 'four-small-inverted-list', 
  ), 
  'two-medium-list' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_2', 
        'display_no_tid_id' => 'block_9', 
        'class' => '', 
      ), 
    ), 
    'class' => 'two-medium-list', 
  ), 
);

// Get Content
$view_output = '';

// Build Output
$tid = NULL;
$style = $field_block_right_column_style[0]['value'];
if ( isset($field_categoria_single[0]['taxonomy_term']->name) ) {
  $tid = $field_categoria_single[0]['tid'];
  $term_name = $field_categoria_single[0]['taxonomy_term']->name;
  $title = l($term_name, 'taxonomy/term/' . $tid);
  if ( isset($field_title_hide[0]['value']) && $field_title_hide[0]['value'] == 1 ) {
    $title = NULL;
    $classes .= ' no-title';
  }
} else {
  $classes .= ' no-title';
}

$display = $displays[$style];

$limit = NULL;
if ( isset($field_limit_items[0]['value']) && intval($field_limit_items[0]['value']) > 0 ) {
  $offset = intval($field_limit_items[0]['value']);
}
$offset = NULL;
if ( isset($field_offset_items[0]['value']) && intval($field_offset_items[0]['value']) > 0 ) {
  $offset = intval($field_offset_items[0]['value']);
}
$view_output .= "<div class=\"{$display['class']}\">\n";
foreach($display['columns'] as $i => $column) {
  $j = $i+1;
  $view_output .= "<div class=\"column column-{$j} {$column['class']}\">\n";
  if ( !is_null($tid) ) {
    $view_output .= nel_views_embed_view($column['view'], $column['display_id'], $limit, $offset, $tid);
  } else {
    $view_output .= nel_views_embed_view($column['view'], $column['display_no_tid_id'], $limit, $offset);
  }
  $view_output .= "</div>\n";
}
$view_output .= "</div>\n";


/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> term-<?php print $tid;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (isset($title)):?>
  <h2 class="block__title"><?php print $title;?></h2>
  <?php endif;?>
  
  <div class="article-content ">
    <?php print $view_output;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>