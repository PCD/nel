<?php
  $tid = intval($fields['tid']->content);
  $term = taxonomy_term_load($tid);
  if ( ($parents = taxonomy_get_parents($tid)) ) {
    $parent = array_shift($parents);
  }
  if ( isset($term->field_feed_logo[LANGUAGE_NONE][0]['fid']) ) {
    $image_url = image_style_url('feed_logo', $term->field_feed_logo[LANGUAGE_NONE][0]['uri']);
    $dimensions = array(
      'width' => $term->field_feed_logo[LANGUAGE_NONE][0]['width'],
      'height' => $term->field_feed_logo[LANGUAGE_NONE][0]['height'],
    );
    image_style_transform_dimensions('feed_logo', $dimensions);
    $image_width = $dimensions['width'];
    $image_height = $dimensions['height'];
    $image_type = $term->field_feed_logo[LANGUAGE_NONE][0]['filemime'];
  }
?>
  <title><?php print check_plain($term->name);?></title>
    <guid><?php print url('taxonomy/term/' . $term->tid, array('absolute'=>true));?></guid>
    <link><?php print url('taxonomy/term/' . $term->tid . '/feed', array('absolute'=>true));?></link>
<?php if (isset($parent)):?>
    <source url="<?php print url('taxonomy/term/' . $parent->tid, array('absolute'=>TRUE));?>"><?php print check_plain($parent->name);?></source>
<?php endif;?>
<?php if (isset($image_url)):?>
    <media:content url="<?php print $image_url;?>" width="<?php print $image_width;?>" height="<?php print $image_height;?>" type="<?php print $image_type;?>" />
<?php endif; ?>
