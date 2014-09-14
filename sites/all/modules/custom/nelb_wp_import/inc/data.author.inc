<?php
/**
 * Saves an author.
 */
function nelb_wp_import_data_author_save($author) {
  // Register One
  echo "New Author {$author['email']} Registered+\n";
  $term = new stdClass();
  $term->name = $author['display_name'];
  $term->vid = 3;
  $term->field_author_id[LANGUAGE_NONE][0]['value'] = $author['id'];
  $term->field_author_email[LANGUAGE_NONE][0]['email'] = strtolower($author['email']);
  $term->field_author_login[LANGUAGE_NONE][0]['value'] = $author['login'];
  taxonomy_term_save($term);
  return true;
}

function nelb_wp_import_data_author_save_search_id($id) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_author_id} WHERE field_author_id_value = %d", 
    $id
  );
  $results = db_query($sql, array(), array('target' => 'slave'));
  return $results->fetchAssoc();
}

function nelb_wp_import_data_author_save_search_email($email) {
  $sql = sprintf("SELECT entity_id FROM {field_data_field_author_email} WHERE field_author_email_email = '%s'", 
    strtolower($email)
  );
  $results = db_query($sql, array(), array('target' => 'slave'));
  return $results->fetchAssoc();
}

function nelb_wp_import_get_author_by_login($login) {
  $sql = "SELECT td.tid, td.vid, td.name, cid.field_author_login_value login 
  FROM taxonomy_term_data td  
  INNER JOIN field_data_field_author_login cid ON cid.entity_id = td.tid 
  WHERE cid.field_author_login_value = '%s' LIMIT 1";
  $sql = sprintf($sql, $login);
  $results = db_query($sql, array(), array('target' => 'slave'));
  return $results->fetchAssoc();
}
