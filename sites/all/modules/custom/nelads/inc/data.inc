<?php
/**
 * Identify if the current page can show ads or not.
 */
function nelads_can_we_show_ads($disable = false) {
  return true;
  static $disable_ads;
  if ( isset($disable_ads) ) {
    return false;
  }
  
  if ( $disable == true ) {
    $disable_ads = 'disabled';
    return false;
  }
  
  return true;
}