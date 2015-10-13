<?php
/**
 * Identify if the current page can show ads or not.
 */
function nelads_can_we_show_ads($disable = false) {
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

/**
 * Increases and return the total of adsense block shown already in the current page.
 */
function nelads_ads_count($calling = '') {
  static $ads_count;
  $ads_count = isset($ads_count)?$ads_count+1:1;
  
  return $ads_count;
}

/**
 * Returns an Adsense Slot for Micrositio.
 */
function nelads_get_microsite_ad_slot() {
  static $ads_count;
  $ads_count = isset($ads_count)?$ads_count+1:1;
  
  switch($ads_count) {
    case 1:
      return array(
        (object) array(
          'ad_client' => 'ca-pub-6659210167862789', 
          'ad_slot' => '1213539958', 
          'ad_format' => '', 
          'ad_number' => 1, 
        ), 
        /*(object) array(
          'ad_client' => 'ca-pub-5383770617488734', 
          'ad_slot' => '7222962809', 
          'ad_format' => '', 
          'ad_number' => 1, 
        ),*/ 
      );
      break;

    case 2:
      return array(
        (object) array(
          'ad_client' => 'ca-pub-6659210167862789', 
          'ad_slot' => '2690273151', 
          'ad_format' => '', 
          'ad_number' => 2, 
        ), 
        /*(object) array(
          'ad_client' => 'ca-pub-5383770617488734', 
          'ad_slot' => '8699696002', 
          'ad_format' => '', 
          'ad_number' => 2, 
        ),*/ 
      );
      break;

    case 3:
      return array(
        (object) array(
          'ad_client' => 'ca-pub-6659210167862789', 
          'ad_slot' => '4167006356', 
          'ad_format' => '', 
          'ad_number' => 3, 
        ), 
        /*(object) array(
          'ad_client' => 'ca-pub-5383770617488734', 
          'ad_slot' => '1176429201', 
          'ad_format' => '', 
          'ad_number' => 3, 
        ),*/ 
      );
      break;
  }
  
  return false;
}
