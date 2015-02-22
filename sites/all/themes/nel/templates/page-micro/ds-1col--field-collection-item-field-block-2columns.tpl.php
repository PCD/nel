<?php
// Views
$displays = array(
  'one-big-4-small-two-columns' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block', 
        'class' => 'col-1 main-article', 
      ), 
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_1', 
        'class' => 'col-1 other-article', 
      ), 
    ), 
    'class' => 'one-big-4-small-two-columns', 
  ), 
  'two-big-4-small-two-columns' => array(
    'view' => 'taxonomy_articles', 
    'columns' => array(
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_5', 
        'class' => 'two-main-articles', 
      ), 
      array(
        'view' => 'taxonomy_articles', 
        'display_id' => 'block_6', 
        'class' => 'fourth-after-two-main-articles', 
      ), 
    ), 
    'class' => 'two-big-4-small-two-columns', 
  ), 
  'slider-two-columns' => array(
    'view' => 'slider', 
    'columns' => array(
      array(
        'view' => 'slider', 
        'display_id' => 'block_1', 
        'class' => 'slider-two-columns', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
);

// Get Content
$view_output = '';

// Build Output
$style = $field_block_2columns_style[0]['value'];
$tid = $field_categoria_single[0]['tid'];
$term_title = $field_categoria_single[0]['taxonomy_term']->name;
$display = $displays[$style];
foreach($display['columns'] as $i => $column) {
  $j = $i+1;
  $view_output .= "<div class=\"column column-{$j} {$column['class']}\">\n";
  $view_output .= views_embed_view($column['view'], $column['display_id'], $tid);
  $view_output .= "</div>\n";
}


/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> term-<?php print $tid;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <h2 class="block__title"><?php print $term_title;?></h2>
  <div class="article-content ">
    <?php print $view_output;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>