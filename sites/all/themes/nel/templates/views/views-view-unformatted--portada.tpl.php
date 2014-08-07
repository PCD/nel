<?php
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
$count = count($rows);
?>
<div class="group-row group-row-<?php print $zebra;?> group-row-<?php print $id;?> total-rows-<?php print $count;?>">
<?php foreach ($rows as $row_id => $row): ?>
  <div<?php if ($classes_array[$row_id]) { print ' class="' . $classes_array[$row_id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
</div>
