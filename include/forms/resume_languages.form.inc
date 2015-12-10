<?php
	function resume_languages_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_languages'])) {
		  $form_state['num_languages'] = count($dataSet)+1;
		}

	  $form['languages'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Languages'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="languages-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i < $form_state['num_languages']; $i++) {

		  $form['languages'][$i]['name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Name'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['name'])? $dataSet[$i-1]['name']->field_value: ""
		  );

		  $form['languages'][$i]['language_level'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Language Level'),
				'#description' => t('Enter a value between 0 and 100 to indicate how fluent you speak the specific language'),
		    '#size' => 10,
				'#maxlength' => 3,
		    '#required' => FALSE,
				'#element_validate' => array('resume_languages_language_level_validate'),
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['language_level'])? $dataSet[$i-1]['language_level']->field_value: ""
		  );

		}

		$form['languages']['add_languages'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add language'),
		  '#submit' => array('resume_add_languages'),
	    '#limit_validation_errors' => array(array('languages')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_languages_callback',
		    'wrapper' => 'languages-wrapper',
		  ),
		);

		if ($form_state['num_languages'] > 1) {
		  $form['languages']['remove_languages'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove last language'),
		    '#submit' => array('resume_remove_languages'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_languages_callback',
				  'wrapper' => 'languages-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_languages_language_level_validate($element, $form_state){
		if(strlen($element['#value']) == 0){
			return;
		}
		if(!is_numeric($element['#value'])){
			form_error($element, t('You must enter a number between 0 and 100'));	
		}else{
			$language_level = floatval($element['#value']);
			if($language_level < 0 || $language_level > 100){
				form_error($element, t('The value #language_level is not between the 0 and 100 range',array('#language_level' => $language_level)));	
			}		
		}
	}

	function resume_add_more_languages_callback($form, $form_state){
		return $form['languages'];
	}

	function resume_add_languages($form, &$form_state){
		$form_state['num_languages']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_languages($form, &$form_state){
		if ($form_state['num_languages'] > 1) {
		  $form_state['num_languages']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>

