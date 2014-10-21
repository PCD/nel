<?php
/**
 * Implements hook_apachesolr_query_alter().
 */
function nelb_search_apachesolr_query_alter(DrupalSolrQueryInterface $query) {
  $query->addParam('bf', array('freshness' =>
    'recip(abs(ms(NOW/HOUR,dm_field_date)),3.16e-11,1,.1)'
  ));
  $query->addParam('fl', 'timestamp');
  $query->setSolrsort('timestamp', 'desc');
}


function nelb_apachesolr_query_prepare($query) {
 // Add a sort on date.
 $query->setAvailableSort('timestamp', array(
   'title' => t('Date'),
   'default' => 'asc',
 ));
}