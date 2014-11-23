<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * Nayarit En Linea theme.
 */


/**
 * Overrides Breadcrumb.
 */
function nel_breadcrumb(&$vars) {
  if ( empty($vars['breadcrumb']) ) {
    return '';
  }
  
  $breadcrumb = $vars['breadcrumb'];
  nel_breadcrumb_article($breadcrumb);
  $count = count($breadcrumb);
  
   // Build output
  $output = "<ul class=\"breadcrumb\">\n";
  
  $items = array();
   // Add items
  foreach($breadcrumb as $i => $crumb) {
    $crumb = str_replace('&lt;br/&gt;', ' ', $crumb);
    $odd = $i%2==0?'even':'odd';
    $order = $i==0?' home':($i==($count-1)?' last':'');
    $class = "item {$odd}{$order}";
    $items[] = "<li class=\"{$class}\">{$crumb}</li>";
  }
  $output .= implode("<li class=\"separator\">&raquo;</li>", $items);

  $output .= "</ul>\n";
  return $output;
}

/**
 * Alters breadcrumb.
 */
function nel_breadcrumb_article(&$breadcrumb) {
  $types = array('article', 'video');
  if ( !(arg(0) == 'node' && intval(arg(1)) && is_null(arg(2)) && ($node=node_load(arg(1))) && in_array($node->type, $types)) ) {
    return false;
  }
  
  // Category
  if ( !(isset($node->field_category[LANGUAGE_NONE][0]['tid']) && !empty($node->field_category[LANGUAGE_NONE][0]['tid'])) ) {
    return false;
  }
  
  $tid = $node->field_category[LANGUAGE_NONE][0]['tid'];
  $term = taxonomy_term_load($tid);
  $array = array($term);
  nel_get_breadcrumb_hierarchy($term->tid, $array);
  $new_breadcrumb = array(
    0 => l('Nayarit En Linea', '<front>'), 
  );
  foreach($array as $item) {
    $new_breadcrumb[] = l($item->name, 'taxonomy/term/' . $item->tid);
  }
  $breadcrumb = $new_breadcrumb;
}

function nel_get_breadcrumb_hierarchy($tid, &$array) {
  if ( ($parent_term = nel_get_parent_term($tid)) ) {
    array_unshift($array, $parent_term);
    nel_get_breadcrumb_hierarchy($parent_term->tid, $array);
  }
}

function nel_get_parent_term($tid) {
  static $parent;
  if ( isset($parent[$tid]) ) {
    return $parent[$tid];
  }

  $sql = "SELECT parent FROM {taxonomy_term_hierarchy} WHERE tid = %d";
  $sql = sprintf($sql, $tid);
  $result = db_query($sql);
  if ( ($row=$result->fetchAssoc()) ) {
    if ( ($term = taxonomy_term_load($row['parent'])) ) {
      $parent[$tid] = $term;
      return $term;
    }
  }
  
  $parent[$tid] = false;
  return false;
}