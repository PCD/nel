<?php
/**
 * Implements hook_node_view.
 */
function nelads_node_view($node, $view_mode, $langcode) {
  if ( $node->type == 'article' ) {
    if ( !(isset($node->field_google_class[LANGUAGE_NONE][0]['value']) && $node->field_google_class[LANGUAGE_NONE][0]['value'] == 'apto-para-todo-publico') ) {
      nelads_can_we_show_ads(true);
    }
  }
}
