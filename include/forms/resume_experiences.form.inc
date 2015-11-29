<?php
	function resume_experiences_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_experiences'])) {
		  $form_state['num_experiences'] = count($dataSet)+1;
		}

	  $form['experiences'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('experiences'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="experiences-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i <= $form_state['num_experiences']; $i++) {

		  $form['experiences'][$i]['company_name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Company name'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['company_name'])? $dataSet[$i-1]['company_name']->field_value: ""
		  );

		  $form['experiences'][$i]['position'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Position'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['position'])? $dataSet[$i-1]['position']->field_value: ""
		  );

		  $form['experiences'][$i]['position_description'] = array(
		    '#type' => 'textarea',
		    '#title' => t('Description of position'),
				'#cols' => 60, 
			  '#rows' => 5,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['position_description'])? $dataSet[$i-1]['position_description']->field_value: ""
		  );

			$date_value = isset($dataSet[$i-1]) && isset($dataSet[$i-1]['experiences_start_date'])? $dataSet[$i-1]['experiences_start_date']->field_value: "";
			$start_date = new Datetime($date_value);

		  $form['experiences'][$i]['experiences_start_date'] = array(
				'#type' => 'date_select',
				'#title' => t('Started on'),
				'#default_value' => strlen($date_value) > 1 ? $start_date->format('Y-m') : "",
				'#date_format' => 'Y-m',
				'#date_label_position' => 'within',
				'#date_year_range' => '0:-60',
				'#required' => FALSE,
		  );

			$date_value = isset($dataSet[$i-1]) && isset($dataSet[$i-1]['experiences_end_date'])? $dataSet[$i-1]['experiences_end_date']->field_value: "";
			$end_date = new Datetime($date_value);

		  $form['experiences'][$i]['experiences_end_date'] = array(
				'#type' => 'date_select',
				'#title' => t('Finished on'),
				'#default_value' => strlen($date_value) > 1 ? $end_date->format('Y-m') : "",
				'#date_format' => 'Y-m',
				'#date_label_position' => 'within',
				'#date_year_range' => '0:-60',
				'#required' => FALSE,
		  );

		}

		// Adds "Add another name" button.
		$form['experiences']['add_experiences'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add another experience'),
		  '#submit' => array('resume_add_experiences'),
	    '#limit_validation_errors' => array(array('experiences')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_experiences_callback',
		    'wrapper' => 'experiences-wrapper',
		  ),
		);

		if ($form_state['num_experiences'] > 1) {
		  $form['experiences']['remove_experiences'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove latest experience'),
		    '#submit' => array('resume_remove_experiences'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_experiences_callback',
				  'wrapper' => 'experiences-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_add_more_experiences_callback($form, $form_state){
		return $form['experiences'];
	}

	function resume_add_experiences($form, &$form_state){
		$form_state['num_experiences']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_experiences($form, &$form_state){
		if ($form_state['num_experiences'] > 1) {
		  $form_state['num_experiences']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>
