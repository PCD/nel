<?php
$node = $elements['#entity']->hostEntity();
$data_preview = image_style_url('teaser', $node->field_video_image[LANGUAGE_NONE][0]['uri']);
$data_preroll = $field_preroll_url[0]['url'];
$data_video = $field_video_url[0]['url'];
$data_plugin = base_path() . drupal_get_path('theme', 'nel') . '/js/nel.jwplayerlist.js';
/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  
  <div id="preroll-player" data-plugin="<?php print $data_plugin;?>" data-preview="<?php print $data_preview;?>" data-preroll="<?php print $data_preroll;?>" data-video="<?php print $data_video;?>"></div>
  
  
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
