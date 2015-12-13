<?php

module_load_include('inc', 'resume', 'include/forms/resume_hobbies.form');
module_load_include('inc', 'resume', 'include/forms/resume_education.form');
module_load_include('inc', 'resume', 'include/forms/resume_experiences.form');
module_load_include('inc', 'resume', 'include/forms/resume_skills.form');
module_load_include('inc', 'resume', 'include/forms/resume_social_media.form');
module_load_include('inc', 'resume', 'include/forms/resume_languages.form');
module_load_include('inc', 'resume', 'include/forms/resume_awards.form');

	function resume_main_fields_form($form, &$form_state) {
		global $base_url;
		$form['#tree'] = TRUE;

		$dataModels = ResumeMainModel::getMapper()->findAll();
		$data = null;
		if(count($dataModels) > 0){
			$data = $dataModels[0];
		}

		$form['description'] = array(
		  '#type' => 'item',
		  '#description' => t('Setup below the fields. A page will be generated based on the fields
you set. The URL is <a href="@base_url/resume">@base_url/resume</a>',array("@base_url" => $base_url)),
		);

		$form['header_title'] = array(
        '#title' => 'Header Title',
        '#type' => 'textfield',
        '#required' => TRUE,
				'#default_value' => isset($data->header_title) ? $data->header_title : ""
    );

		$form['resume_image'] = array(
			'#title' => t('Profile Image'),
			'#type' => 'managed_file',
			'#description' => t('Upload a small profile image size of 100x100.'),
			'#upload_location' => 'public://',
			'#default_value' => isset($data->image_id) ? $data->image_id : null
		);

		$introduction = isset($data->introduction) ? unserialize($data->introduction) : null;

		$form['introduction'] = array(
        '#title' => 'Introduction',
        '#description' => 'An introduction for yourself. This will appear below your profile image',
        '#type' => 'text_format',
				'#format'=> isset($introduction['format']) ? $introduction['format'] : 'full_html',
				'#rows' => 5,
				'#cols' => 60,
        '#required' => TRUE,
				'#default_value' => isset($introduction['value'])? $introduction['value'] : ""
    );

		$about_me = isset($data->about_me) ? unserialize($data->about_me) : null;

		$form['about_me'] = array(
        '#title' => 'About me',
        '#description' => 'Describe yourself in few lines',
        '#type' => 'text_format',
				'#format'=>isset($about_me['format']) ? $about_me['format'] : 'full_html',
				'#rows' => 5,
				'#cols' => 60,
        '#required' => TRUE,
				'#default_value' => isset($about_me['value'])? $about_me['value'] : ""
    );

		$form['contact_me'] = array(
        '#title' => 'Contact number',
        '#type' => 'textfield',
        '#required' => FALSE,
				'#default_value' => isset($data->contact_me) ? $data->contact_me : ""
    );

		$form['skype_id'] = array(
        '#title' => 'Skype',
        '#description' => 'Your skype id',
        '#type' => 'textfield',
        '#required' => FALSE,
				'#default_value' => isset($data->skype_id) ? $data->skype_id : ""
    );

		$form = array_merge($form,resume_hobbies_form($form, $form_state,resume_get_dataset("ResumeHobbyModel")));
		$form = array_merge($form,resume_education_form($form, $form_state,resume_get_dataset("ResumeEducationModel")));
		$form = array_merge($form,resume_experiences_form($form, $form_state,resume_get_dataset("ResumeExperiencesModel")));
		$form = array_merge($form,resume_skills_form($form, $form_state,resume_get_dataset("ResumeSkillsModel")));
		$form = array_merge($form,resume_social_media_form($form, $form_state,resume_get_dataset("ResumeSocialMediaModel")));
		$form = array_merge($form,resume_languages_form($form, $form_state,resume_get_dataset("ResumeLanguagesModel")));
		$form = array_merge($form,resume_awards_form($form, $form_state,resume_get_dataset("ResumeAwardsModel")));

		$form['submit_button'] = array(
		  '#type' => 'submit',
		  '#value' => t('Save'),
		);
		
		return $form;
	}

	function resume_get_dataset($formModelName){
		$dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name",$formModelName);
		return ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
	}

	function resume_main_fields_form_submit($form, &$form_state) {

		$file = ImageHelper::handleImageFile($form['resume_image']['#default_value'],
$form_state['values']['resume_image'],"resume","resume_file");

		$dataModels = ResumeMainModel::getMapper()->findAll();

		if(count($dataModels) == 0){
			$resumeMain = ResumeMainModel::createObject($form_state['values']);
			$resumeMain->image_id = isset($file) ? $file->fid : null;
			$resumeMainId = $resumeMain::getMapper()->setModel($resumeMain)->save();
			resume_set_subforms($form_state,$resumeMainId);
	    drupal_set_message("Your profile has been created. Visit the resume front page to view your changes."); 
		}else{
			$resumeMain = $dataModels[0];
			$resumeMain->updateFields($form_state['values']);
			$resumeMain->image_id = isset($file) ? $file->fid : null;
			$resumeMain::getMapper()->setModel($resumeMain)->save();
			resume_set_subforms($form_state,$resumeMain->id);
	    drupal_set_message("Your profile has been updated. Visit the resume front page to view your changes."); 
		}

    return $form;

	}

	function resume_set_subforms($form_state,$resumeMainId){
		foreach($form_state['values'] as $key => $dataSet){
			if(ResumeSubformHelper::doesFormExist($key)){
				$variantModelName = ResumeSubformHelper::getSubFormVariantModel($key);
				ResumeSubformModel::getMapper()->deleteAllBasedOn($resumeMainId,$variantModelName);
				$position = 0;
				foreach($dataSet as $data){
					if(is_array($data)){
						$formModel = $variantModelName::createObject($data);
						ResumeSubformModel::getMapper()->setSubformVariantModel($formModel)->saveSubformVariantData($resumeMainId,$position);
						$position++;
					}
				}
			}
		}
	}

?>
