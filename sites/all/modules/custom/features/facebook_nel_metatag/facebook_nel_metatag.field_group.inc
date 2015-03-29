<?php
/**
 * @file
 * facebook_nel_metatag.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function facebook_nel_metatag_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_facebook_tags|node|article|form';
  $field_group->group_name = 'group_facebook_tags';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Facebook Tags',
    'weight' => '4',
    'children' => array(
      0 => 'field_facebook_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Facebook Tags',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-facebook-tags field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_facebook_tags|node|article|form'] = $field_group;

  return $export;
}
