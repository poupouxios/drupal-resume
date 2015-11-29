<?php
	function resume_education_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_education'])) {
		  $form_state['num_education'] = count($dataSet)+1;
		}

	  $form['education'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Education'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="education-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i <= $form_state['num_education']; $i++) {

		  $form['education'][$i]['title'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Title'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['title'])? $dataSet[$i-1]['title']->field_value: ""
		  );

		  $form['education'][$i]['education_description'] = array(
		    '#type' => 'textarea',
		    '#title' => t('Description'),
				'#cols' => 60, 
			  '#rows' => 5,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['education_description'])? $dataSet[$i-1]['education_description']->field_value: ""
		  );

			$date_value = isset($dataSet[$i-1]) && isset($dataSet[$i-1]['education_start_date'])? $dataSet[$i-1]['education_start_date']->field_value: "";
			$start_date = new Datetime($date_value);

		  $form['education'][$i]['education_start_date'] = array(
				'#type' => 'date_select',
				'#title' => t('Started on'),
				'#default_value' => strlen($date_value) > 1 ? $start_date->format('Y-m') : "",
				'#date_format' => 'Y-m',
				'#date_label_position' => 'within',
				'#date_year_range' => '0:-60',
				'#required' => TRUE,
				'#description' => t('Enter the date you started the education. 
The end date will be a start date of another education'),
		    '#required' => FALSE,
		  );

		}

		// Adds "Add another name" button.
		$form['education']['add_education'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add another education'),
		  '#submit' => array('resume_add_education'),
	    '#limit_validation_errors' => array(array('education')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_education_callback',
		    'wrapper' => 'education-wrapper',
		  ),
		);

		if ($form_state['num_education'] > 1) {
		  $form['education']['remove_education'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove latest education'),
		    '#submit' => array('resume_remove_education'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_education_callback',
				  'wrapper' => 'education-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_add_more_education_callback($form, $form_state){
		return $form['education'];
	}

	function resume_add_education($form, &$form_state){
		$form_state['num_education']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_education($form, &$form_state){
		if ($form_state['num_education'] > 1) {
		  $form_state['num_education']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>
