<div 
<?php if(isset($did) && !is_null($did)):?>id="<?php print $did;?>"<?php endif;?>
<?php if(isset($class) && !is_null($class)):?>class="<?php print $class;?>"<?php endif;?>
 >
  <?php if (isset($title) && !is_null($title)):?>
  <h2 class="block__title"><?php print $title;?></h2>
  <?php endif;?>
  <?php if (isset($class_content) && !is_null($class_content)):?>
  <div class="<?php print $class_content;?>">
  <?php endif;?>
    <?php print $content;?>
  <?php if (isset($class_content) && !is_null($class_content)):?>
  </div>
  <?php endif;?>
</div>
