<?php
/**
 * Renders the first ad slot.
 */
function fbia_sync_iframe_adslot_1() {
  $candidato_class = '';
  if (isset($_GET['nid']) && intval($_GET['nid']) > 0 && ($node = node_load(intval($_GET['nid']))) && $node->type == 'article') {
    if (isset($node->field_candidato[LANGUAGE_NONE][0]['tid']) && ($term = taxonomy_term_load($node->field_candidato[LANGUAGE_NONE][0]['tid']))) {
      $candidato_class = $term->name;
    }
  }
  $ad1 = theme('fbia-sync--double-click', array(
    'slot_id' => '15651346/FB_Instant_300x250',
    'div_id' => 'div-gpt-ad-1488668257116-0',
    'candidato_class' => $candidato_class,
  ));
  return $ad1;
}
