<?php
if ( isset($_GET['vtest']) ) {
  print_r(get_defined_vars());
  exit;
}
$videos = views_embed_view('lo_mas_visto','block_2', $tid);

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> term-<?php print $tid;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php print $ds_content; ?>
  <div class="article-content">
    <?php print $videos;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
