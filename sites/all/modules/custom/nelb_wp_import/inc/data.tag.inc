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
  $results = db_query($sql, array(), array('target' => 'slave'));
  return $results->fetchAssoc();
}

function nelb_wp_import_get_tag_by_name($name) {
  $sql = "SELECT td.tid, td.vid, td.name, cid.field_tag_id_value tag_id 
  FROM taxonomy_term_data td  
  INNER JOIN field_data_field_tag_id cid ON cid.entity_id = td.tid 
  WHERE td.name = '%s' LIMIT 1";
  $sql = sprintf($sql, $name);
  $results = db_query($sql, array(), array('target' => 'slave'));
  return $results->fetchAssoc();
}
