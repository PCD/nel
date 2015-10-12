<?php if ( isset($field_body_type[0]['value']) && $field_body_type[0]['value'] == 100 ):?>
  <?php if ( ($ads_micro = nelads_block_view_micro_page()) ):?>
    <?php print $ads_micro;?>
  <?php endif;?>
<?php else:?>
  <?php print $ds_content; ?>
  <?php if (!empty($drupal_render_children)): ?>
    <?php print $drupal_render_children ?>
  <?php endif; ?>
<?php endif;?>