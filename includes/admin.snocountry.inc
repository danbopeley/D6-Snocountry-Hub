<?php
/**
 * @file admin.noaa.inc
 * NOAA Weather Admin Functions
 * Handles all the settings for the NOAA Weather Module
 * Version: 1.0
 */

/**
 * @name _snocountry_hub_check_install
 * This checks the install when the module is initialized on the admin pages
 * @return bool $error return the error status

function _snocountry_hub_check_install() {
  $settings_link = l(' Click here for NOAA Weather settings', 'admin/settings/noaaweather');
  $error         = FALSE;
  //Current weather station
  if (variable_get('snocountry_hub_current_weather_station_default', 'INIT') == 'INIT') {
    $MSG = t( 'You have not entered a current condition weather station, please select a station from the NOAA Weather Station List.');
    drupal_set_message($MSG, 'error', FALSE);
    $error = TRUE;
  }
  //Current Location
  if (is_null(variable_get('snocountry_hub_current_location_name_default', NULL))) {
    $MSG = t( 'You have not named your current location.');
    drupal_set_message($MSG, 'error', FALSE);
    $error = TRUE;
  }
  //Radar station
  if (variable_get('snocountry_hub_radar_station_default', 'INIT') == 'INIT') {
    $MSG = t( 'You have not entered a radar station, please select a station from the NOAA Radar Station List.');
    drupal_set_message($MSG, 'error', FALSE);
    $error = TRUE;
  }
  //Module Link
  if ($error == TRUE) {
    $MSG = t( '!link', array('!link' => $settings_link) );
    drupal_set_message($MSG, 'error', FALSE);
  }
} */
/**
 * Main settings form
 */
function _snocountry_hub_main_settings() {
  //Manually Update All Weather
  $form['main'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Sno Country Hub manual Update'),
    '#description' => t('Manually Update All Ski Reports.'),
		'#collapsible' 	=> FALSE,
		'#collapsed' 		=> FALSE,
		'#weight'				=> -50,
    '#group'       => 'main',
  );

  //Update NOAA Weather, this should flag an error when we first start the module.
  $attributes['class'] = 'update-sno-country';
  $attributes['query'] = drupal_get_destination();
  $items[] = l('Update All Weather', 'admin/settings/noaaweather/update/all', $attributes);
  $form['main']['updatelink'] = array(
    '#prefix' => '<p>',
    '#value'   => theme('item_list', $items),
    '#suffix'  => '</p>',
    '#group'   => 'main',
  );
  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return $form;
}

function _snocountry_hub_resort_settings() {
  //Form Settings @todo = what is this for?
  $form['resort_settings'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Resort List'),
    '#description' => t('List of all resorts currently reporting conditions'),
		'#collapsible' => FALSE,
		'#collapsed' 	 => FALSE,
		'#weight'			 => -50,
    '#group'       => 'main_settings',
  );
  
  
	$get_resorts = db_query("SELECT DISTINCT rid, resortName, state FROM {snocountry_hub_reports} ORDER BY state ASC, resortName ASC");
	$header = array(
  array('data' => t('Resort ID'), 'field' => 'rid'),
  array('data' => t('Resort '), 'field' => 'resortName'),
  array('data' => t('State'), 'field' => 'state'),
		);

	while ($r = db_fetch_array($get_resorts)) {
  	$rows[] = $r;
	}
	print theme('table', $header, $rows);
	


  $form['resort_settings']['snocountry_hub_resort_list'] = array(
   '#value' => theme('table', $header, $rows),
  );

  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return system_settings_form( $form );
}

//Submit Current Settings Form
function _snocountry_hub_resort_settings_submit($form_id, &$form_state) {
  $update_message = t('Your NOAA Weather current condition settings have been saved.');
  drupal_set_message($update_message);
}

