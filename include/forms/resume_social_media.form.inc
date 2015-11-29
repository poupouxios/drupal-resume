<?php
	function resume_social_media_form($form, &$form_state,$dataSet){

		if (empty($form_state['num_social_media'])) {
		  $form_state['num_social_media'] = count($dataSet)+1;
		}

	  $form['social_media'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Social Media'),
	    '#collapsible' => TRUE,
	    '#collapsed' => !$form_state['rebuild'],
			'#prefix' => '<div id="social_media-wrapper">',
  		'#suffix' => '</div>',
	  );

		for ($i = 1; $i <= $form_state['num_social_media']; $i++) {

		  $form['social_media'][$i]['name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('Name'),
				'#description' => t('Enter the name of the social media. The page will match
Facebook,Twitter,LinkedIn namings and render the correct logos. If not match found, then
a simple logo will be set'),
		    '#size' => 20,
		    '#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['name'])? $dataSet[$i-1]['name']->field_value: ""
		  );

		  $form['social_media'][$i]['class_name'] = array(
		    '#type' => 'textfield',
		    '#title' => t('CSS Class'),
				'#description' => t('Find from <a href="https://fortawesome.github.io/Font-Awesome/icons/">https://fortawesome.github.io/Font-Awesome/icons/</a> which class you want to use for the icon to appear on the left.'),
		    '#size' => 30,
				'#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['url'])? $dataSet[$i-1]['class_name']->field_value: ""
		  );

		  $form['social_media'][$i]['url'] = array(
		    '#type' => 'textfield',
		    '#title' => t('URL'),
				'#description' => t('Enter the social media url.'),
		    '#size' => 30,
				'#maxlength' => 200,
		    '#required' => FALSE,
				'#default_value' => isset($dataSet[$i-1]) && isset($dataSet[$i-1]['url'])? $dataSet[$i-1]['url']->field_value: ""
		  );

		}

		// Adds "Add another name" button.
		$form['social_media']['add_social_media'] = array(
		  '#type' => 'submit',
		  '#value' => t('Add another social media'),
		  '#submit' => array('resume_add_social_media'),
	    '#limit_validation_errors' => array(array('social_media')),
			'#ajax' => array(
		    'callback' => 'resume_add_more_social_media_callback',
		    'wrapper' => 'social_media-wrapper',
		  ),
		);

		if ($form_state['num_social_media'] > 1) {
		  $form['social_media']['remove_social_media'] = array(
		    '#type' => 'submit',
		    '#value' => t('Remove latest social media'),
		    '#submit' => array('resume_remove_social_media'),
		    // Since we are removing a name, don't validate until later.
		    '#limit_validation_errors' => array(),
				'#ajax' => array(
				  'callback' => 'resume_add_more_social_media_callback',
				  'wrapper' => 'social_media-wrapper',
				),
		  );
		}

		return $form;
	}

	function resume_add_more_social_media_callback($form, $form_state){
		return $form['social_media'];
	}

	function resume_add_social_media($form, &$form_state){
		$form_state['num_social_media']++;
		$form_state['rebuild'] = TRUE;
	}

	function resume_remove_social_media($form, &$form_state){
		if ($form_state['num_social_media'] > 1) {
		  $form_state['num_social_media']--;
		}
		$form_state['rebuild'] = TRUE;
	}

?>

