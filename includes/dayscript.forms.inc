<?php

/**
 * @file
 * This is the file that containing only forms
 */

/*
 * Implements hook_form().
 */
function dayscript_form($form, &$form_state) {

	module_load_include('inc', 'dayscript', 'includes/dayscript.functions');
	$getArrayDate = _get_array_date();


	// need to validate the form ajax and js level 
	$form['#attached']['js'] = array(
		array(
			'type'  => 'file',
			'data' => drupal_get_path('module', 'dayscript') . '/js/after_ajax.js',
		),
	);
	// // need to load js validator form 
	$form['#attached']['js'] = array(
		array(
			'type'  => 'file',
			'data' => drupal_get_path('module', 'dayscript') . '/js/jquery.validate.js',
		),
	);
	$form['username'] = array(
		'#type' => 'textfield',
		'#title' => t('Name'),
		'#attributes'=> array('Placeholder' => t('Enter your Username')),
		'#size' => 60,
		'#maxlength' => 60,
		'#required' => TRUE,
	);
	$form['identification'] = array(
		'#type' => 'textfield',
		'#title' => t('Identificaction'),
		'#attributes'=> array('Placeholder' => t("Enter your Identification")),
		'#size' => 60,
		'#maxlength' => 60,
		'#required' => TRUE,
	);
	$form['date'] = array(
		'#type' => 'date',
		'#title' => t('Born date'),
		'#description' => t('You can select your born date displaying each list'),
        '#required' => TRUE,
	);
	$form['work'] = array(
		'#type' => 'select',
		'#title' => t('Work'),
		'#options' => $getArrayDate,
		'#required' => TRUE,
	);
	$form['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('ENVIAR'),
  	);

	return $form;
}

/**
 * Implements hook_form_validate().
 */
function dayscript_form_validate($form, &$form_state) {

	module_load_include('inc', 'dayscript', 'includes/dayscript.functions');

	// get values from dayscript_form 
	$identification = $form_state['values']['identification'];
	$name           = $form_state['values']['username'];
	$month 			= $form_state['values']['date']['month'];
	$day 			= $form_state['values']['date']['day'];
	$year 			= $form_state['values']['date']['year'];
	$date 			= $day.'-'.$month.'-'.$year;
	$work 			= $form_state['values']['work'];

	$validateAlphanumeric = _validate_alphanumeric_string($name);
	$validateNumeric = _validate_numeric($identification, $error_message);

	$validate = TRUE;

	if (!$validateAlphanumeric == TRUE) {
		form_set_error($name, t('The name field only accepts alphanumeric characters'));
		$validate = FALSE;
	}
	if (!$validateNumeric == TRUE) {
		form_set_error($identification, t($error_message));
		$validate = FALSE;
	}

	if ($validate == FALSE) {
			watchdog('Dayscript', "There are inconsistencies filling out the form", NULL, WATCHDOG_ERROR);
	}
}

/**
 * Implements hook_form_submit().
 */
function dayscript_form_submit($form, &$form_state) {

	$identification = $form_state['values']['identification'];
	$name           = $form_state['values']['username'];
	$month 			= $form_state['values']['date']['month'];
	$day 			= $form_state['values']['date']['day'];
	$year 			= $form_state['values']['date']['year'];
	$date 			= $day.'-'.$month.'-'.$year;
	$work 			= $form_state['values']['work'];

	$state = ($work == 0) ? 1 : 0;
	$setNameWork = _get_name_work($work);

	$nid = db_insert('example_users') -> fields(
    	array(
			'name'           => $name,
			'identification' => $identification,
			'date'           => $date,
			'work'           => $setNameWork,
			'state'          => $state,
    	)
  	)-> execute();  

	if ($nid) {
		$getIdUser = get_id_user($identification);

		watchdog('Dayscript', "successful registration, UID = ".$getIdUser.', user = '.$name, NULL, WATCHDOG_INFO);
		drupal_set_message(t('Congratulation, you are signed to DayScript'));
		drupal_goto('<front>');

		return TRUE;
	} 
}