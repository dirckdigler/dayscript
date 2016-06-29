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
	// need to load js validator form 
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


