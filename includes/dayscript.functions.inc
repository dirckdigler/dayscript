<?php

/**
 * @file
 * This is the file that provides a custom functions to work perfectly all module
 */

/**
* Verify if the field name is a valid format.
*
* @param $name
*	A string containing a name.
* @return
*	TRUE if the name is in a valid format.
*/
function _validate_alphanumeric_string($name) {

	if (preg_match('/^[a-zA-Z]+[a-zA-Z0-9._]+$/', $name)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
* Verify if the identification is numeric and input max 10 digits of the given values.
*
* @param $value
*	A integer containing an identification.
* @param $error_message
* 	A string parameter by reference that show the error message
* @return
*	TRUE if the identification is in a valid format.
*/
function _validate_numeric($value, &$error_message) {

	$error_messege = '';
	$validate = TRUE;
	$response = is_numeric($value);
  	$len = strlen($value);

	if (!$response == TRUE) {
		$error_message = 'The field identification field accepts only numeric characters';
		$validate = FALSE;
	}
	if ($len > 10) {
		$error_message = 'The field identification accept only 10 digits maximum';
		$validate = FALSE;
	}
	if ($len < 4) {
		$error_message = 'The field identification accept minimum 4 digits';
		$validate = FALSE;
	}
	if ($validate) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * 
* Asociative array with kind of jobs values.
*
* @return
*	Asociative Array.
*/
function _get_array_date() {

	$date_array = array(
		0 => 'Administrator',
		1 => 'Webmaster',
		2 => 'Development',
	);

	return $date_array;
}

/**
*
* @param $work
*   A string containing kind of work.
*
* @return
*	the work selected from the dayscript_form.
*/
function _get_name_work($work) {

	$work_array = _get_array_date();

	foreach ($work_array as $key => $value) {
		return $work_array[$work];
	}
}

/**
*
* @param $identification
*   A integer containing an identification
*
* @return
*	the User ID registered in database
*/
function get_id_user($identification) {

	$result = db_query('SELECT uid FROM {example_users} WHERE identification = :identification',
	array(':identification' => $identification))->fetchObject();

	return $result->uid;
}

/**
*
*  Valid identification already exists in DB and its return is based on ajax
* 
* @return
*	JSON Format containig TRUE or FALSE depending if exis the User ID in database
*/
function _retrieve_identification_validate() {

    $identification = $_POST['identification'];

	$result = db_query('SELECT uid FROM {example_users} WHERE identification = :identification',
	array(':identification' => $identification));
	$exist = $result->rowCount();

	if ($exist) {
        return drupal_json_output(array('response' => FALSE));
	}		
	return drupal_json_output(array('response' => TRUE));
}    



