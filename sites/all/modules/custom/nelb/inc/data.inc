<?php
/**
 * Get Node Blocks and Taxonomy Blocks.
 */
function nelb_data_get_blocks($params) {
  // Place
  $params['place'] = isset($params['place'])?$params['place']:0;
  $params['promote_to'] = isset($params['promote_to'])?$params['promote_to']:0;
  $params['pid'] = isset($params['pid'])?$params['pid']:0;
  
  // Get Node Blocks
  $blocks = nelb_data_get_blocks_node($params);

  if ( $params['promote_to'] == 0 ) {
    // Get Taxonomy Blocks
    $taxonomy_blocks = nelb_data_get_blocks_taxonomy($params);
    $blocks = array_merge($blocks, $taxonomy_blocks);
  }
  
  // Sort Them together.
  $blocks = nelb_data_get_blocks_sorted($blocks);
  
  // Group them.
  $groups = nelb_data_get_blocks_grouped($blocks);
  
  // Add Classes.
  return nelb_data_get_blocks_classify($groups);
}

/**
 * Get Node Blocks.
 */
function nelb_data_get_blocks_node($params) {
  $sql = "SELECT 
    n.nid id, 
    n.title, 
    field_promoted_level_value level, 
    field_promoted_size_value size, 
    field_columna_value 'column', 
    field_show_title_value show_title 

  FROM {node} n \n";
  
  // A que pagina se dirige el block: Homepage o Categoria
  $sql .= sprintf("INNER JOIN {field_data_field_promote_to} pt ON n.nid = pt.entity_id AND n.vid = pt.revision_id AND pt.field_promote_to_value = %d \n", $params['promote_to']);
  
  // Level
  $sql .= "INNER JOIN {field_data_field_promoted_level} l ON n.nid = l.entity_id AND n.vid = l.revision_id \n";
  
  // Place: Contenido Principal o Barra derecha
  $sql .= sprintf("INNER JOIN {field_data_field_promoted_place} pl ON n.nid = pl.entity_id AND n.vid = pl.revision_id AND pl.field_promoted_place_value = %d\n", $params['place']);
  
  // Size
  $sql .= "LEFT JOIN {field_data_field_promoted_size} size ON n.nid = size.entity_id AND n.vid = size.revision_id \n";
  
  // Column
  $sql .= sprintf("LEFT JOIN {field_data_field_columna} c ON n.nid = c.entity_id AND n.vid = c.revision_id \n");
  
  // Show Title
  $sql .= "LEFT JOIN {field_data_field_show_title} t ON n.nid = t.entity_id AND n.vid = t.revision_id \n";
  
  // Where
  $sql .= "WHERE n.type = 'block' AND n.status = 1";
  $results = db_query($sql);
  
  $items = array();
  while(($item = $results->fetchAssoc())) {
    $item['type'] = 'node';
    $item['path'] = 'node/' . $item['id'];
    $items[] = $item;
  }
  
  // Get Rid of Dupps if Random active
  if ( isset($params['random']) && $params['random'] == true ) {
    $items = nelb_data_get_blocks_node_random($items);
  }
  
  return $items;
}

/**
 * Randomize dupp nodes.
 */
function nelb_data_get_blocks_node_random($items) {
  $levels = array();
  foreach($items as $key => $item) {
    $levels[$item['level']]['items'][] = $key;
    $levels[$item['level']]['count'] = isset($levels[$item['level']]['count'])?$levels[$item['level']]['count']+1:1;
  }
  
  // Randomly Choose
  foreach($levels as &$level) {
    if ( $level['count'] > 1 ) {
      $chosen_index = rand(0, ($level['count']-1));
      foreach($level['items'] as $key => $item) {
        if ( $key != $chosen_index ) {
          unset($items[$level['items'][$key]]);
        }
      }
    }
  }
  return $items;
}

/**
 * Get Taxonomy Blocks.
 */
function nelb_data_get_blocks_taxonomy($params) {
  $sql = "SELECT 
    td.tid id, 
    td.name title, 
    field_promoted_level_value level, 
    field_columna_value 'column', 
    field_promoted_place_value place, 
    field_promoted_size_value size, 
    field_promoted_style_value style, 
    field_promoted_style_one_column_value style_one_column, 
    field_promoted_sidebar_style_value style_sidebar 
    
  FROM {taxonomy_term_data} td \n";
  if ( intval($params['pid']) > 0 ) {
    $sql .= sprintf("INNER JOIN {taxonomy_term_hierarchy} h ON td.tid = h.tid AND h.parent = %d\n", $params['pid']);
  }
  
  // Promoted is a Must
  $sql .= "INNER JOIN {field_data_field_promoted} p ON td.tid = p.entity_id AND p.field_promoted_value = 1\n";
  
  // Place: Main or Sidebar
  $sql .= sprintf("INNER JOIN {field_data_field_promoted_place} pl ON td.tid = pl.entity_id AND pl.field_promoted_place_value = %d\n", $params['place']);
  
  // Level
  $sql .= "INNER JOIN {field_data_field_promoted_level} l ON td.tid = l.entity_id \n";
  
  // Promoted Style for Two Columns
  $sql .= "LEFT JOIN {field_data_field_promoted_style} s ON td.tid = s.entity_id \n";
  
  // Promoted Style for One Column
  $sql .= "LEFT JOIN {field_revision_field_promoted_style_one_column} s2 ON td.tid = s2.entity_id \n";
  
  // Promoted Style for Sidebar
  $sql .= "LEFT JOIN {field_revision_field_promoted_sidebar_style} s3 ON td.tid = s3.entity_id \n";
  
  // Size
  $sql .= "LEFT JOIN {field_revision_field_promoted_size} size ON td.tid = size.entity_id \n";
  
  // Column: Left or Right
  $sql .= "LEFT JOIN {field_data_field_columna} c ON td.tid = c.entity_id ";
  
  $results = db_query($sql);
  $items = array();
  while(($item = $results->fetchAssoc())) {
    $item['type'] = 'taxonomy';
    $item['path'] = 'taxonomy/term/' . $item['id'];
    
    // Choose Style
    if ( $item['place'] == 0 ) {
      if ( $item['size'] == 'one-column' ) {
        $item['style'] = $item['style_one_column'];
      }
    } else if ( $item['place'] == 1 ) {
      $item['style'] = $item['style_sidebar'];
    }
    unset($item['style_sidebar']);
    unset($item['style_one_column']);
    $items[] = $item;
  }
  return $items;
}

/**
 * Sort Blocks out.
 */
function nelb_data_get_blocks_sorted($blocks) {
  foreach($blocks as $key => $block) {
    $types[$key] = $block['type']=='node'?0:1;
    $levels[$key] = $block['level'];
    $columns[$key] = isset($block['column'])&&intval($block['column'])>0?intval($block['column']):0;
  }
  array_multisort($levels, SORT_DESC, $types, SORT_ASC, $columns, SORT_ASC, $blocks);
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
    $groups[$block['level']]['level'] = $block['level'];
    
    // Initialize Count
    if ( !isset($groups[$block['level']]['types'][$block['type']]['count']) ) {
      $groups[$block['level']]['types'][$block['type']]['count'] = 0;
    }

    // Items
    $groups[$block['level']]['types'][$block['type']]['type'] = $block['type'];
    $groups[$block['level']]['types'][$block['type']]['items'][] = $block;
    
    // Increment
    $groups[$block['level']]['types'][$block['type']]['count']++;
  }
  
  return $groups;
}

/**
 * Classify Group Blocks.
 */
function nelb_data_get_blocks_classify($groups) {
  $group_i = 0;
  $group_t = count($groups);
  foreach($groups as &$group) {
    // Group Specifics
    $group['class'] = nelb_data_get_classes_i($group_i, $group_t, 'group-row group-level-' . $group['level']);
    $group_i++;
    
    // Types
    foreach($group['types'] as &$type) {
      $type['class'] = "type-row type-{$type['type']} count-{$type['count']}";
      $block_i = 0;
      $block_t = $type['count'];
      foreach($type['items'] as &$block) {
        $classes = 'block-item block-' . $block['type'] . '-item';
        if ( $block['type'] == 'taxonomy' ) {
          $classes .= ' ' . $block['style'];
        }
        $block['class'] = nelb_data_get_classes_i($block_i, $block_t, $classes);
        $block_i++;
      }
    }
  }
  
  return $groups;
}

/**
 * Return Classes Acording some Parameters.
 */
function nelb_data_get_classes_i($i, $t, $extra = '') {
  $classes = array();
  if ( !empty($extra) ) {
    $classes[] = $extra;
  }
  if ( $i == 0 ) {
    $classes[] = 'first';
  }
  if ( $i == ($t-1) ) {
    $classes[] = 'last';
  }
  $classes[] = ($i%2==0?'odd':'even');
  return implode(' ', $classes);
}

/**
 *
 */
function nelb_data_get_block_count_per_type($blocks, $type = 'taxonomy') {
  $t = 0;
  foreach($blocks as $block) {
    if ( $block['type'] = $type ) {
      $t++;
    }
  }
  return $t;
}

/**
 * Taxonomy Displays.
 */
function nelb_data_taxonomy_displays() {
  $displays = array(
    // Sidebar area
    'small-carousel-sidebar' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles_sidebar', 
          'display_id' => 'block', 
          'class' => 'small-carousel-sidebar', 
        ), 
      ), 
    ), 
    'small-carousel-sidebar-one-delay' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles_sidebar', 
          'display_id' => 'block_1', 
          'class' => 'small-carousel-sidebar one-delay', 
        ), 
      ), 
    ), 
    'small-carousel-sidebar-two-delay' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles_sidebar', 
          'display_id' => 'block_2', 
          'class' => 'small-carousel-sidebar two-delay', 
        ), 
      ), 
    ), 
    'small-carousel-sidebar-three-delay' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles_sidebar', 
          'display_id' => 'block_3', 
          'class' => 'small-carousel-sidebar three-delay', 
        ), 
      ), 
    ), 
    // Content area
    'one-big-4-small-two-columns' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block', 
          'class' => 'col-1 main-article', 
        ), 
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_1', 
          'class' => 'col-1 other-article', 
        ), 
      ), 
      'class' => 'one-big-4-small-two-columns', 
    ), 
    'one-big-4-small-one-column' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block', 
          'class' => 'col-1 main-article', 
        ), 
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_1', 
          'class' => 'col-1 other-article', 
        ), 
      ), 
      'class' => 'one-big-4-small-one-column', 
    ), 
    'two-big-4-small-two-columns' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_5', 
          'class' => 'two-main-articles', 
        ), 
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_6', 
          'class' => 'fourth-after-two-main-articles', 
        ), 
      ), 
      'class' => 'two-big-4-small-two-columns', 
    ), 
    'small-carousel' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_4', 
          'class' => '', 
        ), 
      ), 
      'class' => 'small-carousel', 
    ), 
    'four-small-inverted-list' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_3', 
          'class' => '', 
        ), 
      ), 
      'class' => 'four-small-inverted-list', 
    ), 
    'two-medium-list' => array(
      'columns' => array(
        array(
          'view' => 'taxonomy_articles', 
          'display_id' => 'block_2', 
          'class' => '', 
        ), 
      ), 
      'class' => 'two-medium-list', 
    ), 
  );
  return $displays;
}