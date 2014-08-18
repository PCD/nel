<?php
// Views
$displays = array(
  'one-big-4-small-two-columns' => array(
    'columns' => array(
      array(
        'display_id' => 'block', 
        'class' => 'col-1 main-article', 
      ), 
      array(
        'display_id' => 'block_1', 
        'class' => 'col-1 other-article', 
      ), 
    ), 
    'class' => 'one-big-4-small-two-columns', 
  ), 
  'one-big-4-small-one-column' => array(
    'columns' => array(
      array(
        'display_id' => 'block', 
        'class' => 'col-1 main-article', 
      ), 
      array(
        'display_id' => 'block_1', 
        'class' => 'col-1 other-article', 
      ), 
    ), 
    'class' => 'one-big-4-small-one-column', 
  ), 
  'two-big-4-small-two-columns' => array(
    'columns' => array(
      array(
        'display_id' => 'block_5', 
        'class' => 'two-main-articles', 
      ), 
      array(
        'display_id' => 'block_6', 
        'class' => 'fourth-after-two-main-articles', 
      ), 
    ), 
    'class' => 'two-big-4-small-two-columns', 
  ), 
  'small-carousel' => array(
    'columns' => array(
      array(
        'display_id' => 'block_4', 
        'class' => '', 
      ), 
    ), 
    'class' => 'small-carousel', 
  ), 
  'four-small-inverted-list' => array(
    'columns' => array(
      array(
        'display_id' => 'block_3', 
        'class' => '', 
      ), 
    ), 
    'class' => 'four-small-inverted-list', 
  ), 
  'two-medium-list' => array(
    'columns' => array(
      array(
        'display_id' => 'block_2', 
        'class' => '', 
      ), 
    ), 
    'class' => 'two-medium-list', 
  ), 
);

// Get Content
$view_output = '';
if ( isset($field_promoted_style[LANGUAGE_NONE][0]['value']) && isset($displays[$field_promoted_style[LANGUAGE_NONE][0]['value']]) ) {
  $display = $displays[$field_promoted_style[LANGUAGE_NONE][0]['value']];
  
  // Build Output
  $classes .= ' ' . $display['class'];
  foreach($display['columns'] as $column) {
    $view_output .= "<div class=\"{$column['class']}\">\n";
    $view_output .= views_embed_view('taxonomy_articles', $column['display_id'], $tid);
    $view_output .= "</div>\n";
  }
} else if ( isset($_GET['test']) ) {
  print_r($field_promoted_style[LANGUAGE_NONE][0]['value']);
  exit;
}


/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php print $ds_content; ?>
  <div class="article-content ">
    <?php print $view_output;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>