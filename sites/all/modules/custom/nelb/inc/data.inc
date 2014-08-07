<?php
/**
 * Get Node Blocks and Taxonomy Blocks.
 */
function nelb_data_get_blocks($params) {
  // Place
  $params['place'] = isset($params['place'])?$params['place']:0;
  $params['pid'] = isset($params['pid'])?$params['pid']:0;
  
  // Get Node Blocks
  $node_blocks = nelb_data_get_blocks_node($params['place']);

  // Get Taxonomy Blocks
  $taxonomy_blocks = nelb_data_get_blocks_taxonomy($params['place'], $params['pid']);
  
  // Sort Them together.
  $blocks = nelb_data_get_blocks_sorted($node_blocks, $taxonomy_blocks);
  
  // Group them.
  return nelb_data_get_blocks_grouped($blocks);
}

/**
 * Get Node Blocks.
 */
function nelb_data_get_blocks_node($place = 0) {
  $sql = "SELECT n.nid id, n.title, field_promoted_level_value level, field_columna_value 'column' 
  FROM {node} n 
  INNER JOIN {field_data_field_promoted} p ON n.nid = p.entity_id AND n.vid = p.revision_id AND p.field_promoted_value = 1\n";
  $sql .= sprintf("INNER JOIN {field_data_field_promoted_place} pl ON n.nid = pl.entity_id AND n.vid = pl.revision_id AND pl.field_promoted_place_value = %d\n", $place);
  $sql .= "INNER JOIN {field_data_field_promoted_level} l ON n.nid = l.entity_id AND n.vid = l.revision_id 
  LEFT JOIN {field_data_field_columna} c ON n.nid = c.entity_id AND n.vid = c.revision_id 
  WHERE n.status = 1";
  $results = db_query($sql);
  $items = array();
  while(($item = $results->fetchAssoc())) {
    $item['type'] = 'node';
    $item['path'] = 'node/' . $item['id'];
    $items[] = $item;
  }
  return $items;
}

/**
 * Get Taxonomy Blocks.
 */
function nelb_data_get_blocks_taxonomy($place = 0, $pid = 0) {
  $sql = "SELECT td.tid id, td.name title, field_promoted_level_value level, field_columna_value 'column', field_promoted_style_value style 
  FROM {taxonomy_term_data} td \n";
  if ( intval($pid) > 0 ) {
    $sql .= sprintf("INNER JOIN {taxonomy_term_hierarchy} h ON td.tid = h.tid AND h.parent = %d\n", $pid);
  }
  $sql .= "INNER JOIN {field_data_field_promoted} p ON td.tid = p.entity_id AND p.field_promoted_value = 1\n";
  $sql .= sprintf("INNER JOIN {field_data_field_promoted_place} pl ON td.tid = pl.entity_id AND pl.field_promoted_place_value = %d\n", $place);
  $sql .= "INNER JOIN {field_data_field_promoted_level} l ON td.tid = l.entity_id 
  INNER JOIN {field_data_field_promoted_style} s ON td.tid = s.entity_id 
  LEFT JOIN {field_data_field_columna} c ON td.tid = c.entity_id ";
  $results = db_query($sql);
  $items = array();
  while(($item = $results->fetchAssoc())) {
    $item['type'] = 'taxonomy';
    $item['path'] = 'taxonomy/term/' . $item['id'];
    $items[] = $item;
  }
  return $items;
}

/**
 * Sort Blocks out.
 */
function nelb_data_get_blocks_sorted($node_blocks, $taxonomy_blocks) {
  $blocks = array_merge($node_blocks, $taxonomy_blocks);
  foreach($blocks as $key => $block) {
    $levels[$key] = $block['level'];
    $columns[$key] = isset($block['column'])&&intval($block['column'])>0?intval($block['column']):0;
  }
  array_multisort($levels, SORT_DESC, $columns, SORT_ASC, $blocks);
  return $blocks;
}

/**
 * Get Taxonomy Display by ID.
 */
function nelb_data_taxonomy_display_get_by_id($display_id) {
  $displays = nelb_data_taxonomy_displays();
  if ( isset($displays[$display_id]) ) {
    return $displays[$display_id];
  }
  return false;
}

/**
 * Groups Blocks in Rows.
 */
function nelb_data_get_blocks_grouped($blocks) {
  $groups = array();
  foreach($blocks as $block) {
    $groups[$block['level']][] = $block;
  }
  return $groups;
}

/**
 * Taxonomy Displays.
 */
function nelb_data_taxonomy_displays() {
  $displays = array(
    'one-big-4-small-two-columns' => array(
      'columns' => array(
        array(
          'display_id' => 'block', 
          'class' => 'col-1 main-article', 
        ), 
        array(
          'display_id' => 'block_1', 
          'class' => 'col-1 other-article', 
        ), 
      ), 
      'class' => 'one-big-4-small-two-columns', 
    ), 
    'one-big-4-small-one-column' => array(
      'columns' => array(
        array(
          'display_id' => 'block', 
          'class' => 'col-1 main-article', 
        ), 
        array(
          'display_id' => 'block_1', 
          'class' => 'col-1 other-article', 
        ), 
      ), 
      'class' => 'one-big-4-small-one-column', 
    ), 
    'two-big-4-small-two-columns' => array(
      'columns' => array(
        array(
          'display_id' => 'block_5', 
          'class' => 'two-main-articles', 
        ), 
        array(
          'display_id' => 'block_6', 
          'class' => 'fourth-after-two-main-articles', 
        ), 
      ), 
      'class' => 'two-big-4-small-two-columns', 
    ), 
    'small-carousel' => array(
      'columns' => array(
        array(
          'display_id' => 'block_4', 
          'class' => '', 
        ), 
      ), 
      'class' => 'small-carousel', 
    ), 
    'four-small-inverted-list' => array(
      'columns' => array(
        array(
          'display_id' => 'block_3', 
          'class' => '', 
        ), 
      ), 
      'class' => 'four-small-inverted-list', 
    ), 
    'two-medium-list' => array(
      'columns' => array(
        array(
          'display_id' => 'block_2', 
          'class' => '', 
        ), 
      ), 
      'class' => 'two-medium-list', 
    ), 
  );
  return $displays;
}