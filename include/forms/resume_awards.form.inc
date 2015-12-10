<?php
	function resume_awards_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_awards'])) {
		  $form_state['num_awards'] = count($dataSet)+1;
		}

	  $form['awards'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('awards'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="awards-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i < $form_state['num_awards']; $i++) {

		  $form['awards'][$i]['title'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Title'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['title'])? $dataSet[$i-1]['title']->field_value: ""
		  );

			$awards_description = isset($dataSet[$i-1]) && isset($dataSet[$i-1]['awards_description']->field_value) ? unserialize($dataSet[$i-1]['awards_description']->field_value) : null;

		  $form['awards'][$i]['awards_description'] = array(
        '#type' => 'text_format',
				'#format'=> isset($awards_description['format']) ? $awards_description['format'] : 'full_html',
		    '#title' => t('Description'),
				'#cols' => 60, 
			  '#rows' => 5,
		    '#required' => FALSE,
				'#default_value' => isset($awards_description['value'])? $awards_description['value']: ""
		  );

			$date_value = isset($dataSet[$i-1]) && isset($dataSet[$i-1]['awards_date'])? $dataSet[$i-1]['awards_date']->field_value: "";
			$start_date = new Datetime($date_value);

		  $form['awards'][$i]['awards_date'] = array(
				'#type' => 'date_select',
				'#title' => t('Date'),
				'#default_value' => strlen($date_value) > 1 ? $start_date->format('Y-m') : "",
				'#date_format' => 'Y-m',
				'#date_label_position' => 'within',
				'#date_year_range' => '0:-60',
				'#required' => TRUE,
		    '#required' => FALSE,
		  );

		}

		// Adds "Add another name" button.
		$form['awards']['add_awards'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add award'),
		  '#submit' => array('resume_add_awards'),
	    '#limit_validation_errors' => array(array('awards')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_awards_callback',
		    'wrapper' => 'awards-wrapper',
		  ),
		);

		if ($form_state['num_awards'] > 1) {
		  $form['awards']['remove_awards'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove last award'),
		    '#submit' => array('resume_remove_awards'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_awards_callback',
				  'wrapper' => 'awards-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_add_more_awards_callback($form, $form_state){
		return $form['awards'];
	}

	function resume_add_awards($form, &$form_state){
		$form_state['num_awards']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_awards($form, &$form_state){
		if ($form_state['num_awards'] > 1) {
		  $form_state['num_awards']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>
