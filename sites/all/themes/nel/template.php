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