<?php
/**
 * Implements hook_apachesolr_index_document_build_node().
 */
function nelb_apachesolr_index_document_build_node(ApacheSolrDocument $document, $entity, $entity_type) {
  if ($entity->type == 'article') {
    // Add the start date of the field_research_pubdate field as a sort field to the SOLR index
    // because we cannot use dm_field_research_pubdate (date multiple; must be single) from
    // admin/reports/apachesolr/acquia_search_server_1
    $field_date = field_get_items('node', $entity, 'field_date');
    if (!empty($field_date)) {
      $document->addField('ds_field_date', apachesolr_date_iso(strtotime($field_date[0]['value'])));
    }
  }
}
 
/**
 * Implements hook_apachesolr_query_prepare().
 */
function nelb_apachesolr_query_prepare($query) {
  // Add Publication Date sort to the faculty-research search
    // Add the new field as a sort option
    $query->setAvailableSort('ds_field_date', array(
      'title' => t('Article Date'),
      'default' => 'desc',
    ));
 
    // Sort on our new field
    $query->setSolrSort('ds_field_date', 'desc');
}

/**
 * Implements hook_apachesolr_query_alter().
 */
function nelb_apachesolr_query_alter($query) {
  // Make this field available within template_preprocess_search_result()
  $query->addParam('fl','ds_field_date');
}
