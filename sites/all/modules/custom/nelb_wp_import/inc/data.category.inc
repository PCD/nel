<?php
/**
 * Saves an author.
 */
function nelb_wp_import_data_category_save($category) {
  // Look for existing.
  if ( nelb_wp_import_data_category_save_search_id($category['id']) ) {
    return;
  }
  
  // Register One
  echo "New Category {$category['name']} Registered+\n";
  $term = new stdClass();
  $term->name = $category['name'];
  $term->vid = 2;
  $term->field_category_id[LANGUAGE_NONE][0]['value'] = $category['id'];  
  taxonomy_term_save($term);
  return true;
}

function nelb_wp_import_data_category_save_search_id($id) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_category_id} WHERE field_category_id_value = %d", 
    $id
  );
  $results = db_query($sql);
  return $results->fetchAssoc();
}
