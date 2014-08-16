<?php
$category = $field_category[0]['taxonomy_term'];
$category_url = url('taxonomy/term/' . $category->tid);
$ntitle = explode("\n", wordwrap($title, 25, "\n"));
$wtitle = '';
$j = count($ntitle) - 1;
foreach($ntitle as $i => $ntitle_line) {
  $wtitle .= "<span class=\"td-sbig-title\">{$ntitle_line}</span>\n";
  if ( $j != $i ) {
    $wtitle .= "<span class=\"td-sbig-sep\">&nbsp;</span>\n";
  }
}
$image_url = $image_alt = '';
if ( isset($field_video) ) {
  if ( isset($field_video[LANGUAGE_NONE]) ) {
    $field_video = $field_video[LANGUAGE_NONE];
  }
}

if ( isset($field_video[0]['uri']) ) {
  $file_for_view = file_load($field_video[0]['fid']);
  $file_for_view = file_view_file($file_for_view, 'article_slider');
  $image_url = image_style_url('slider', $file_for_view['#path']);
  $image_alt = $file_for_view['#alt'];
} else if ( isset($field_image[0]['uri']) ) {
  $image_url = image_style_url('slider', $field_image[0]['uri']);
  $image_alt = $field_image[0]['alt'];
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

<?php if ($image_url):?>
  <div class="image">
    <a href="<?php print $node_url;?>">
      <img src="<?php print $image_url;?>" alt="<?php print $image_alt;?>" />
    </a>
  </div>
<?php endif;?>
  <div class="info">
    <div class="tagdate">
      <div class="category">
        <a href="<?php print $category_url;?>" typeof="skos:Concept" property="rdfs:label skos:prefLabel" datatype>
          <?php print $category->name;?>
        </a>
      </div>
      <div class="date">
        <span class="date-display-single" property="dc:date" datatype="xsd:dateTime" content="2013-12-17T03:34:58-07:00">
          Dic 17, 2013
        </span>
      </div>
    </div>
    <h3><a href="<?php print $node_url;?>">
      <?php print $wtitle;?>
    </a></h3>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
