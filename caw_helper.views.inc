<?php
/**
 * @file
 *
 */

/**
 * [caw_helper_views_data_alter description]
 * @return [type] [description]
 */
function caw_helper_views_data_alter(&$data) {
// views_handler_field_custom
  dpm($data['views']['nothing']);
  $data['views']['nothing']['field']['handler'] = "caw_helper_views_handler_field_custom";
}


/**
 * Implementation of hook_views_data().
 */
function caw_helper_views_data() {


}
