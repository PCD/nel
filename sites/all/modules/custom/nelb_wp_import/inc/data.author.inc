<?php
/**
 * Saves an author.
 */
function nelb_wp_import_data_author_save($author) {
  // Look for existing.
  if ( nelb_wp_import_data_author_save_search_id($author['id']) ) {
    return;
  }
  
  // Register One
  echo "New Author {$author['email']} Registered+\n";
  $term = new stdClass();
  $term->name = $author['display_name'];
  $term->vid = 3;
  $term->field_author_id[LANGUAGE_NONE][0]['value'] = $author['id'];
  $term->field_author_email[LANGUAGE_NONE][0]['email'] = strtolower($author['email']);
  taxonomy_term_save($term);
  return true;
}

function nelb_wp_import_data_author_save_search_id($id) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_author_id} WHERE field_author_id_value = %d", 
    $id
  );
  $results = db_query($sql);
  return $results->fetchAssoc();
}

function nelb_wp_import_data_author_save_search_email($email) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_author_email} WHERE field_author_email_email = '%s'", 
    strtolower($email)
  );
  $results = db_query($sql);
  return $results->fetchAssoc();
}