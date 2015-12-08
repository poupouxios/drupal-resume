<?php
	$dataSet = ResumeMainModel::getMapper()->findAll();
	$resumeMainModel = null;
	if(count($dataSet) > 0){
		$resumeMainModel = $dataSet[0];
	}
?>

<div id="resume">
	<div class="row">
		<div class="col-xs-12">
		  <div id="photo-header" class="text-center">
		    <!-- PHOTO (AVATAR) -->
		    <div id="photo">
					<?php if($resumeMainModel): ?>
						<?php $image = file_load($resumeMainModel->image_id);?>
						<?php if($image): ?>
				      <img src="<?= file_create_url($image->uri) ?>" alt="avatar">
						<?php endif; ?>
					<?php endif; ?>
		    </div>
		    <div id="text-header">
					<?php if($resumeMainModel): ?>
						<?php $introduction = unserialize($resumeMainModel->introduction); ?>
			      <?= $introduction['value'] ?>
					<?php endif; ?>
		    </div>
		  </div>
		</div>
	</div>
	<div class="row">
		<div class="col-xs-12 col-sm-12">
		  <div class="box">
				<?php if($resumeMainModel): ?>
					<h2>About Me</h2>
					<?php $aboutMe = unserialize($resumeMainModel->about_me); ?>
		      <?= $aboutMe['value'] ?>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
					<h2>Education</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeEducationModel");
								$educationData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					 ?>
					 <ul class="timeline">
						<?php foreach($educationData as $index => $education): ?>
							<li class="<?= (($index != 0) && ($index % 2 != 0))? "timeline-inverted" : "" ?>">
						    <div class="timeline-badge primary"><a><i class="glyphicon glyphicon-record" rel="tooltip" title="<?= isset($education['education_start_date']) ?  ResumeSubformHelper::getProperDate($education['education_start_date']->field_value) : "" ?>" id=""></i></a></div>
						    <div class="timeline-panel">
						      <div class="timeline-heading">
						        <h3><?= isset($education['title']) ? $education['title']->field_value : "" ?></h3>
										<h5><i class="glyphicon glyphicon-calendar"></i> <?= isset($education['education_start_date']) ?  ResumeSubformHelper::getProperDate($education['education_start_date']->field_value) : "" ?></h5>
						      </div>
						      <div class="timeline-body">
						        <p><?= isset($education['education_description']) ? $education['education_description']->field_value : "" ?></p>
						      </div>
						    </div>
						  </li>
						<?php endforeach; ?>
					</ul>
				<?php endif; ?>				
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
					<h2>Experiences</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeExperiencesModel");
								$experiencesData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<ul class="timeline">
					<?php foreach($experiencesData as $index => $experience): ?>
							<li class="<?= (($index != 0) && ($index % 2 != 0))? "timeline-inverted" : "" ?>">
						    <div class="timeline-badge primary"><a><i class="glyphicon glyphicon-home" rel="tooltip" title="<?= isset($experience['experiences_start_date']) ? ResumeSubformHelper::getProperDate($experience['experiences_start_date']->field_value) : "" ?> <?= isset($experience['experiences_end_date']) ? " - ".ResumeSubformHelper::getProperDate($experience['experiences_end_date']->field_value) : "" ?>"></i></a></div>
						    <div class="timeline-panel">
						      <div class="timeline-heading">
										<h3 class="position"><?= isset($experience['position']) ? $experience['position']->field_value : "" ?></h3>
						        <h4 class="company"><?= isset($experience['company_name']) ? $experience['company_name']->field_value : "" ?></h4>
										<h5><i class="glyphicon glyphicon-calendar"></i> <?= isset($experience['experiences_start_date']) ? ResumeSubformHelper::getProperDate($experience['experiences_start_date']->field_value) : "" ?> <?= isset($experience['experiences_end_date']) ? " - ".ResumeSubformHelper::getProperDate($experience['experiences_end_date']->field_value) : "" ?></h5>
						      </div>
						      <div class="timeline-body">
						        <p><?= isset($experience['position_description']) ? $experience['position_description']->field_value : "" ?></p>
						      </div>
						    </div>
						  </li>
					<?php endforeach; ?>
					</ul>
				<?php endif; ?>				
		  </div>
		  <div class="box clearfix">
		    <h2>Contact</h2>
				<?php if($resumeMainModel && strlen($resumeMainModel->contact_me) > 0): ?>
				  <div class="contact-item">
				    <div class="icon pull-left text-center"><span class="fa fa-phone fa-fw"></span></div>
				    <div class="title only pull-right"><?= $resumeMainModel->contact_me ?></div>
				  </div>
				<?php endif; ?>
				<?php if($resumeMainModel && strlen($resumeMainModel->skype_id) > 0): ?>
				  <div class="contact-item">
				    <div class="icon pull-left text-center"><span class="fa fa-skype fa-fw"></span></div>
				    <div class="title pull-right">Skype</div>
				    <div class="description pull-right"><?= $resumeMainModel->skype_id ?></div>
				  </div>
				<?php endif; ?>
				<?php if($resumeMainModel): ?>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeSocialMediaModel");
								$socialMediaData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<?php foreach($socialMediaData as $socialMedia): ?>
						<div class="contact-item">
						  <div class="icon pull-left text-center"><span class="fa <?= $socialMedia['class_name']->field_value ?> fa-fw"></span></div>
							<div class="title pull-right"><?= $socialMedia['name']->field_value ?></div>
						  <div class="description pull-right"><?= $socialMedia['url']->field_value ?></div>
						</div>
					<?php endforeach; ?>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
				  <h2>Skills</h2>
				  <div class="skills">
						<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeSkillsModel");
									$skillsData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
						?>
						<?php foreach($skillsData as $skill): ?>
					    <div class="item-skills" data-percent="<?= intval($skill['skill_value']->field_value) / 100 ?>"><?= $skill['name']->field_value ?></div>
						<?php endforeach; ?>
				    <div class="skills-legend clearfix">
				      <div class="legend-left legend">Beginner</div>
				      <div class="legend-left legend"><span>Proficient</span></div>
				      <div class="legend-right legend"><span>Expert</span></div>
				      <div class="legend-right legend">Master</div>
				    </div>
					</div>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
				  <h2>Languages</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeLanguagesModel");
								$languageData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
				  <div id="language-skills">
					<?php foreach($languageData as $language): ?>
				    <div class="skill"><?= $language['name']->field_value ?> <div class="icons pull-right"><div style="width: <?= $language['language_level']->field_value ?>%; height: 14px;" class="icons-red"></div></div></div>
					<?php endforeach; ?>
				  </div>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
				  <h2>Hobbies</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeHobbyModel");
								$hobbyData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<?php foreach($hobbyData as $hobby): ?>
				  	<div class="hobby"><?= $hobby['name']->field_value ?></div>
					<?php endforeach; ?>
				<?php endif; ?>
		  </div>
		</div>
	</div>
</div>
