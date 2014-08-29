<?php
// First One
$first_article = views_embed_view('taxonomy_articles','block', $tid);
$fourth_articles = views_embed_view('taxonomy_articles','block_1', $tid);

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
    <div class="col-1 main-article">
      <?php print $first_article;?>
    </div>
    <div class="col-1 other-article">
      <?php print $fourth_articles;?>
    </div>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>