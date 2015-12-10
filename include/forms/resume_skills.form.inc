<?php
	function resume_skills_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_skills'])) {
		  $form_state['num_skills'] = count($dataSet)+1;
		}

	  $form['skills'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('skills'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="skills-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i < $form_state['num_skills']; $i++) {

		  $form['skills'][$i]['name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Name'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['name'])? $dataSet[$i-1]['name']->field_value: ""
		  );

		  $form['skills'][$i]['skill_value'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Value'),
				'#description' => t('Enter value between 0 and 100'),
		    '#size' => 10,
				'#maxlength' => 4,
		    '#required' => FALSE,
				'#element_validate' => array('resume_skills_skill_value_validate'),
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['skill_value'])? $dataSet[$i-1]['skill_value']->field_value: ""
		  );

		}

		// Adds "Add another name" button.
		$form['skills']['add_skills'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add another skill'),
		  '#submit' => array('resume_add_skills'),
	    '#limit_validation_errors' => array(array('skills')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_skills_callback',
		    'wrapper' => 'skills-wrapper',
		  ),
		);

		if ($form_state['num_skills'] > 1) {
		  $form['skills']['remove_skills'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove latest skill'),
		    '#submit' => array('resume_remove_skills'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_skills_callback',
				  'wrapper' => 'skills-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_skills_skill_value_validate($element, $form_state){
		if(strlen($element['#value']) == 0){
			return;
		}
		if(!is_numeric($element['#value'])){
			form_error($element, t('You must enter a number between 0 and 100'));	
		}else{
			$skill_value = floatval($element['#value']);
			if($skill_value < 0 || $skill_value > 100){
				form_error($element, t('The value #skill_value is not between the 0 and 100 range',array('#skill_value' => $skill_value)));	
			}		
		}
	}

	function resume_add_more_skills_callback($form, $form_state){
		return $form['skills'];
	}

	function resume_add_skills($form, &$form_state){
		$form_state['num_skills']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_skills($form, &$form_state){
		if ($form_state['num_skills'] > 1) {
		  $form_state['num_skills']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>

