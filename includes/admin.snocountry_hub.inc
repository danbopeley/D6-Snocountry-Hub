<?php
/**
 * @file admin.snocountry_hub.inc
 * Snocountry Hub Admin Functions
 * Handles all the settings for the snocountry_hub
 * Version: 1.0
 */

/**
 * @name _snocountry_hub_check_install
 * This checks the install when the module is initialized on the admin pages
 * @return bool $error return the error status
*/
/*
function _snocountry_hub_check_install() {
do this someday
} */



/**
 * Main settings form
 */
function _snocountry_hub_main_settings() {
  //Manually Update All Weather
  $form['main'] = array(
    '#type'        => 'fieldset',
    '#group' =>'main',
    '#title'       => t('Sno Country Hub Configuration'),
    '#description' => t('Manually Update All Ski Reports.'),
		'#collapsible' 	=> FALSE,
		'#collapsed' 		=> FALSE,
		'#weight'				=> -50,
    '#group'       => 'main',
  );
	
  $form['main']['snocountry_hub_api_key'] = array(
    '#type' => 'textfield',
     '#group' =>'main',
	  '#title' => t('Sno Country API Key'),
	  '#default_value' => SNOCOUNTRY_HUB_API_KEY,
	  '#size' => 60,
	  '#maxlength' => 128,
	  '#required' => TRUE,
  );
  

  
	$utc_offset = array(
		3 =>'Argentina -3',
		4 =>'Atlantic - 4', 
		5 =>'Eastern - 5', 
		6 =>'Central - 6',
		7 =>'Mountain Standard - 7',
		8 =>'Pacific Standard - 8',
		9 =>'Alaskan Standard - 9'
	);
	$offset_description="The offset selected here, dictates when ski reports are actually requested and stored in database. The intention is to ensure that reports for individual ski areas are updated only once per day. Since most ski areas do not submit reports prior to 5am we instruct the module to begin gather data on cron at 5am in the first timezone of the day that we want the retrieve data for. The offset allows us to select that time zone in UTC";
  $form['main']['snocountry_hub_utc_offset'] = array(
    '#type'          => 'select',
    '#group' =>'main',
    '#title'         => t('UTC Offset'),
    '#description'   => t($offset_description),
    '#multiple'      => FALSE,
    '#options'       => $utc_offset,
    '#default_value' => SNOCOUNTRY_HUB_UTC_OFFSET,
    '#required'      => TRUE,
    '#group'         => 'main',
  );
  
	$resort_states = array(  
		'al' => 'Alabama',
		'ak' => 'Alaska',
		'az' => 'Arizona',
		'ca' => 'California',
		'co' => 'Colorado',
		'ct' => 'Connecticut',
		'ga' => 'Georgia',
		'id' => 'Idaho',
		'il' => 'Illinois',
		'in' => 'Indiana',
		'ia' => 'Iowa',
		'me' => 'Maine',
		'md' => 'Maryland',
		'ma' => 'Massachusetts',
		'mi' => 'Michigan',
		'mn' => 'Minnesota',
		'mo' => 'Missouri',
		'mt' => 'Montana',
		'nv' => 'Nevada',
		'nh' => 'New Hampshire',
		'nj' => 'New Jersey',
		'nm' => 'New Mexico',
		'ny' => 'New York',
		'nc' => 'North Carolina',
		'nd' => 'North Dakota',
		'oh' => 'Ohio',
		'or' => 'Oregon',
		'pa' => 'Pennsylvania',
		'ri' => 'Rhode Island',
		'nc' => 'South Carolina',
		'sd' => 'South Dakota',
		'tn' => 'Tennessee',
		'ut' => 'Utah',
		'vt' => 'Vermont',
		'va' => 'Virginia',
		'wa' => 'Washington',
		'wv' => 'West Virginia',
		'wi' => 'Wisconsin',
		'wy' => 'Wyoming',
		'ab' => 'Alberta', 
		'bc' => 'British Columbia', 
		'lb' => 'Labrador', 
		'mb' => 'Manitoba', 
		'nf' => 'Newfoundland', 
		'ns' => 'Nava Scotia', 
		'on' => 'Ontario', 
		'qc' => 'Quebec', 
		'sk' => 'Saskatchewan'
	);

	
	$selected_states = variable_get('snocountry_hub_resort_states', 'ca');
	
	$states_description="Listed are all the US states and Canadian provinces for which Sno Country provides ski report data. Options selected here will direct this module to gather data for participating ski areas with in the state or province. Sno Country states that it is preferred that report requests specify multiple states in one request, Hence this module will loop all options selected here request data for each individually";
	
  $form['main']['snocountry_hub_resort_states'] = array(
    '#type'          => 'select',
    '#group' 				 =>	'main',
    '#title'         => t('States, Provinces and Countries'),
    '#description'   => t($states_description),
    '#multiple'      => TRUE,
    '#options'       => $resort_states,
    '#default_value' => $selected_states,
    '#required'      => TRUE,
  );
  
  $attributes['class'] = 'update-sno-country';
  $attributes['query'] = drupal_get_destination();
  $items[] = l('Update All Resorts', 'snocountry-hub/update/all', $attributes);
  $form['main']['updatelink'] = array(
   '#group' =>'main',
    '#prefix' => '<p>',
    '#value'   => theme('item_list', $items),
    '#suffix'  => '</p>',
    '#group'   => 'main',
  );
  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return system_settings_form( $form );
}

function _snocountry_hub_main_settings_submit($form_id, &$form_state) {
  $update_message = t('Your Sno Country Hub settings have been saved.');
  drupal_set_message($update_message);
}



function _snocountry_hub_resort_settings() {
	
		$resort_states = array(  
		'al' => 'Alabama',
		'ak' => 'Alaska',
		'az' => 'Arizona',
		'ca' => 'California',
		'co' => 'Colorado',
		'ct' => 'Connecticut',
		'ga' => 'Georgia',
		'id' => 'Idaho',
		'il' => 'Illinois',
		'in' => 'Indiana',
		'ia' => 'Iowa',
		'me' => 'Maine',
		'md' => 'Maryland',
		'ma' => 'Massachusetts',
		'mi' => 'Michigan',
		'mn' => 'Minnesota',
		'mo' => 'Missouri',
		'mt' => 'Montana',
		'nv' => 'Nevada',
		'nh' => 'New Hampshire',
		'nj' => 'New Jersey',
		'nm' => 'New Mexico',
		'ny' => 'New York',
		'nc' => 'North Carolina',
		'nd' => 'North Dakota',
		'oh' => 'Ohio',
		'or' => 'Oregon',
		'pa' => 'Pennsylvania',
		'ri' => 'Rhode Island',
		'nc' => 'South Carolina',
		'sd' => 'South Dakota',
		'tn' => 'Tennessee',
		'ut' => 'Utah',
		'vt' => 'Vermont',
		'va' => 'Virginia',
		'wa' => 'Washington',
		'wv' => 'West Virginia',
		'wi' => 'Wisconsin',
		'wy' => 'Wyoming',
		'ab' => 'Alberta', 
		'bc' => 'British Columbia', 
		'lb' => 'Labrador', 
		'mb' => 'Manitoba', 
		'nf' => 'Newfoundland', 
		'ns' => 'Nava Scotia', 
		'on' => 'Ontario', 
		'qc' => 'Quebec', 
		'sk' => 'Saskatchewan'
	);
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
  
  

/*
$get_resorts = db_query("SELECT sc.rid, sc.resortName, sc.state, sc.ts
FROM {snocountry_hub_reports} sc
INNER JOIN
    (
    	SELECT rid, state, MAX(ts) AS MaxDateTime
    	FROM {snocountry_hub_reports}
    	GROUP BY rid
    ) groupedsc ON sc.rid = groupedsc.rid AND sc.ts = groupedsc.MaxDateTime");

*/
	$get_resorts = db_query("SELECT DISTINCT rid, resortName, state FROM {snocountry_hub_reports} ORDER BY state ASC, resortName ASC");

		$prevstate ='';
		
	while ($r = db_fetch_array($get_resorts)) {
		$curstate = $r['state'];
		
		if($prevstate != $curstate){
			if($prevstate != ''){
				
					$header = array(
						array('data' => t('Resort ID'), 'field' => 'rid'),
				  	array('data' => t('Resort '), 'field' => 'resortName'),
				  	array('data' => t('State'), 'field' => 'state'),
				  	array('data' => t('Report Timestamp '), 'field' => 'ts'),
				  	array('data' => t('Last Updated '), 'field' => 'reportDateTime'),
				  	//array('data' => t('Hashed ID'), 'field' => 'rmd5')
				  	array('data' => t('Tools'), 'field' => 'operations')
					);
				
				  $form['resort_settings'][$prevstate]['snocountry_hub_resort_list'] = array(
   				'#value' => theme('table', $header, $rows),
  				);
  				
  				unset($header);
  				unset($rows);
				
			}
			
			$statefull = $resort_states[strtolower($curstate)];
			$form['resort_settings'][$curstate] = array(
		  '#type' => 'fieldset',
		  '#title' => t($curstate.' - ('.$statefull.')'),
		  '#collapsible' => TRUE,
		  '#collapsed' => TRUE,
			);	
		}
		
		$lastupdate = _snocountry_hub_validate_lastupdate($r['rid']);

		$rid = $r['rid'];
		$state = $r['state'];
		$md5r = md5($rid);
		$ts =  date('n-d-y h:i:s A',$r['ts']);
		$r['ts'] = $lastupdate['ts'];
		$r['reportDateTime'] = $lastupdate['rdt'];
		$resortname = strtolower(str_replace(' ','',$r['resortName']));
		 $linkattributes['target'] = '_blank';
		 
		$linkattributes = array(
    'attributes' => array(
      'target' => '_blank'
    ));
		$r['operations'] = 'View on '. l('Snocountry','http://snocountry.com/index.php/resort-page/'.strtolower($state).'/'.$resortname,$linkattributes).' - '.l('Local','http://ski.bluetent.com/snocountry-hub/get-report/'.$rid.'/4/xml',$linkattributes);
		
		$updateattributes['query'] = drupal_get_destination();
		
		$r['operations'] .= '<br />'.l('Manual Update','snocountry-hub/manual-update/'.$rid,$updateattributes);
  	//$r['rmd5'] = $md5r;
  	$rows[] = $r;
  	
  	
  	
  	$prevstate = $curstate;
  	
	}

  $form['resort_settings'][$prevstate]['snocountry_hub_resort_list'] = array(
		'#value' => theme('table', $header, $rows),
	);

  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return $form;
}

//Submit Current Settings Form
function _snocountry_hub_resort_settings_submit($form_id, &$form_state) {
  $update_message = t('Your Sno Country Hub settings have been saved.');
  drupal_set_message($update_message);
}

