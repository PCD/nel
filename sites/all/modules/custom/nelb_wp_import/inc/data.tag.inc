<?php
/**
 * Saves an author.
 */
function nelb_wp_import_data_tag_save($tag) {
  // Look for existing.
  if ( nelb_wp_import_data_tag_save_search_id($tag['id']) ) {
    return;
  }
  
  // Register One
  echo "New Tag {$tag['name']} Registered+\n";
  $term = new stdClass();
  $term->name = $tag['name'];
  $term->vid = 24;
  $term->field_tag_id[LANGUAGE_NONE][0]['value'] = $tag['id'];  
  taxonomy_term_save($term);
  return true;
}

function nelb_wp_import_data_tag_save_search_id($id) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_tag_id} WHERE field_tag_id_value = %d", 
    $id
  );
  $results = db_query($sql);
  return $results->fetchAssoc();
}
