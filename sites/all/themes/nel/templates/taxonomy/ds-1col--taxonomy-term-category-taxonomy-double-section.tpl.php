<?php
// First One
$two_main_article = views_embed_view('taxonomy_articles','block_5', $tid);
$fourth_articles = views_embed_view('taxonomy_articles','block_6', $tid);

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
  <div class="article-content">
    <?php print $two_main_article;?>
    <?php print $fourth_articles;?>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>