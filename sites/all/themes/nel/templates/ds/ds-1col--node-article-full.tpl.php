<?php
$node = node_load(arg(1));
if ( !isset($node->field_video[LANGUAGE_NONE][0]['fid']) ) {
  if ( isset($node->field_image[LANGUAGE_NONE][0]['fid']) ) {
    unset($node->field_image[LANGUAGE_NONE][0]);
    sort($node->field_image[LANGUAGE_NONE]);
  }
  
  if ( !empty($node->field_image[LANGUAGE_NONE]) ) {
    $new_gallery = field_view_field('node', $node, 'field_image', 'full');
    $new_gallery = drupal_render($new_gallery);
  } else {
    $new_gallery = '';
  }
  
  // Inject New Gallery
  $pattern = '/<div class="photoswipe-gallery photoswipe-gallery-1">.*?(?:<\/div>){3}/msi';
  $ds_content = preg_replace($pattern, $new_gallery, $ds_content);
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
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
