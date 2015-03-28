<?php
// Views
$displays = array(
  'small-carousel-sidebar' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar', 
        'display_id' => 'block', 
        'display_no_tid_id' => 'block_4', 
        'class' => 'small-carousel-sidebar', 
      ), 
    ), 
    'class' => 'one-big-4-small-two-columns', 
  ), 
  'small-carousel-sidebar-one-delay' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar', 
        'display_id' => 'block_1', 
        'display_no_tid_id' => 'block_5', 
        'class' => 'small-carousel-sidebar-one-delay', 
      ), 
    ), 
    'class' => 'two-big-4-small-two-columns', 
  ), 
  'small-carousel-sidebar-two-delay' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar', 
        'display_id' => 'block_2', 
        'display_no_tid_id' => 'block_6', 
        'class' => 'small-carousel-sidebar-two-delay', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'small-carousel-sidebar-three-delay' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar', 
        'display_id' => 'block_2', 
        'display_no_tid_id' => 'block_7', 
        'class' => 'small-carousel-sidebar-three-delay', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'ten-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_9', 
        'display_no_tid_id' => 'block_19', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'nine-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_8', 
        'display_no_tid_id' => 'block_18', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'eight-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_7', 
        'display_no_tid_id' => 'block_17', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'seven-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_6', 
        'display_no_tid_id' => 'block_16', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'six-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_5', 
        'display_no_tid_id' => 'block_15', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'five-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_4', 
        'display_no_tid_id' => 'block_14', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'four-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_3', 
        'display_no_tid_id' => 'block_13', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'three-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_2', 
        'display_no_tid_id' => 'block_12', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'two-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block_1', 
        'display_no_tid_id' => 'block_11', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
  'one-articles-with-picture' => array(
    'columns' => array(
      array(
        'view' => 'taxonomy_articles_sidebar_2', 
        'display_id' => 'block', 
        'display_no_tid_id' => 'block_10', 
        'class' => '', 
      ), 
    ), 
    'class' => 'slider-two-columns', 
  ), 
);
// Get Content
$view_output = '';

// Build Output
$tid = NULL;
$style = $field_sidebar_news_style[0]['value'];
$title = NULL;
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
foreach($display['columns'] as $i => $column) {
  $j = $i+1;
  $view_output .= "<div class=\"{$column['class']}\">\n";
  if ( !is_null($tid) ) {
    $view_output .= views_embed_view($column['view'], $column['display_id'], $tid);
  } else {
    $view_output .= views_embed_view($column['view'], $column['display_no_tid_id']);
  }
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

  <?php if (!is_null($title)):?>
  <h2 class="block__title"><?php print $title;?></h2>
  <?php endif;?>

  <div class="article-content ">
    <?php print $view_output;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>