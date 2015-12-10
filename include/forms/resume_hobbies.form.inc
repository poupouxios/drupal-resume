<?php

	function resume_hobbies_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_hobbies'])) {
		  $form_state['num_hobbies'] = count($dataSet)+1;
		}

	  $form['hobby'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Hobbies'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="hobby-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i < $form_state['num_hobbies']; $i++) {

		  $form['hobby'][$i]['name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Hobby name'),
		    '#description' => t("Enter your hobby."),
		    '#size' => 20,
		    '#maxlength' => 100,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['name'])? $dataSet[$i-1]['name']->field_value: ""
		  );
		}

		// Adds "Add another name" button.
		$form['hobby']['add_hobby'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add hobby'),
		  '#submit' => array('resume_add_hobby'),
	    '#limit_validation_errors' => array(array('hobby')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_hobbies_callback',
		    'wrapper' => 'hobby-wrapper',
		  ),
		);

		if ($form_state['num_hobbies'] > 1) {
		  $form['hobby']['remove_hobby'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove last hobby'),
		    '#submit' => array('resume_remove_hobby'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_hobbies_callback',
				  'wrapper' => 'hobby-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_add_more_hobbies_callback($form, $form_state){
		return $form['hobby'];
	}

	function resume_add_hobby($form, &$form_state){
		$form_state['num_hobbies']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_hobby($form, &$form_state){
		if ($form_state['num_hobbies'] > 1) {
		  $form_state['num_hobbies']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>
