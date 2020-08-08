<?php
	$dataSet = ResumeMainModel::getMapper()->findAll();
	$resumeMainModel = null;
	if(count($dataSet) > 0){
		$resumeMainModel = $dataSet[0];
	}
?>
<div class="row">
	<div class="col-sm-12">
		<h1 class="resume-header-title">
		<?php if($resumeMainModel): ?>
			<?= $resumeMainModel->header_title ?>
		<?php endif; ?>
		</h1>
	</div>
	<?php if($resumeMainModel): ?>
		<?php if($resumeMainModel->cv_file_id): ?>
			<?php $cvFile = file_load($resumeMainModel->cv_file_id);?>
			<?php if($cvFile): ?>
				<div class="col-sm-12 my-cv">
					<a class="btn btn-info" href="<?= file_create_url($cvFile->uri) ?>" title="Download my CV"><span class="glyphicon glyphicon-download-alt"></span>  Download my CV</a>
				</div>
			<?php endif; ?>
		<?php endif;?>
	<?php endif; ?>
</div>
<div id="resume">
	<div class="row">
		<div class="col-xs-12">
		  <div id="photo-header" class="text-center">
		    <!-- PHOTO (AVATAR) -->
		    <div id="photo">
					<?php if($resumeMainModel): ?>
						<?php if($resumeMainModel->image_id): ?>
							<?php $image = file_load($resumeMainModel->image_id);?>
							<?php if($image): ?>
						    <img src="<?= file_create_url($image->uri) ?>" alt="avatar">
							<?php endif; ?>
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
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeSocialMediaModel","position");
								$socialMediaData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<?php foreach($socialMediaData as $socialMedia): ?>
						<div class="contact-item">
						  <div class="icon pull-left text-center"><span class="fa <?= $socialMedia['class_name']->field_value ?> fa-fw"></span></div>
							<div class="title pull-right"><?= $socialMedia['name']->field_value ?></div>
						  <div class="description pull-right"><?= filter_var($socialMedia['url']->field_value,FILTER_VALIDATE_URL) === FALSE ? $socialMedia['url']->field_value : "<a href='".$socialMedia['url']->field_value."'>".$socialMedia['url']->field_value."</a>" ?></div>
						</div>
					<?php endforeach; ?>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
					<h2>Experiences</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeExperiencesModel","field_value",'desc');
								$experiencesData = array_reverse(ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet));
                                usort($experiencesData,['ResumeSubformMapper','sortByExperienceStartDate']);
					?>
					<ul class="timeline">
					<?php foreach($experiencesData as $index => $experience): ?>
							<li class="<?= (($index != 0) && ($index % 2 != 0))? "timeline-inverted" : "" ?>">
						    <div class="timeline-badge primary"><a><i class="glyphicon glyphicon-home" rel="tooltip" title="<?= isset($experience['experiences_start_date']) ? ResumeSubformHelper::getProperDate($experience['experiences_start_date']->field_value) : "" ?> <?= isset($experience['experiences_end_date']) ? " - ".ResumeSubformHelper::getProperDate($experience['experiences_end_date']->field_value) : " - Current" ?>"></i></a></div>
						    <div class="timeline-panel">
						      <div class="timeline-heading">
										<h3 class="position"><?= isset($experience['position']) ? $experience['position']->field_value : "" ?></h3>
						        <h4 class="company"><?= isset($experience['company_name']) ? $experience['company_name']->field_value : "" ?></h4>
										<h5><i class="glyphicon glyphicon-calendar"></i> <?= isset($experience['experiences_start_date']) ? ResumeSubformHelper::getProperDate($experience['experiences_start_date']->field_value) : "" ?> <?= isset($experience['experiences_end_date']) ? " - ".ResumeSubformHelper::getProperDate($experience['experiences_end_date']->field_value) : " - Current" ?></h5>
						      </div>
						      <div class="timeline-body">
						        <p><?php
												$description = isset($experience['position_description']) ? unserialize($experience['position_description']->field_value) : null;
												if($description){
													echo $description['value'];
												}
											?>
										</p>
						      </div>
						    </div>
						  </li>
					<?php endforeach; ?>
					</ul>
				<?php endif; ?>
		  </div>
		  <div class="box clearfix">
				<?php if($resumeMainModel): ?>
					<h2>Education</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeEducationModel","position");
								$educationData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					 ?>
					 <ul class="timeline">
						<?php foreach($educationData as $index => $education): ?>
							<li class="<?= (($index != 0) && ($index % 2 != 0))? "timeline-inverted" : "" ?>">
						    <div class="timeline-badge primary"><a><i class="glyphicon glyphicon-record" rel="tooltip" title="<?= isset($education['education_start_date']) ?  ResumeSubformHelper::getProperDate($education['education_start_date']->field_value) : "" ?> <?= isset($education['education_end_date']) ? " - ".ResumeSubformHelper::getProperDate($education['education_end_date']->field_value) : "" ?>" id=""></i></a></div>
						    <div class="timeline-panel">
						      <div class="timeline-heading">
						        <h3><?= isset($education['title']) ? $education['title']->field_value : "" ?></h3>
										<h5><i class="glyphicon glyphicon-calendar"></i> <?= isset($education['education_start_date']) ?  ResumeSubformHelper::getProperDate($education['education_start_date']->field_value) : "" ?> <?= isset($education['education_end_date']) ? " - ".ResumeSubformHelper::getProperDate($education['education_end_date']->field_value) : "" ?></h5>
						      </div>
						      <div class="timeline-body">
						        <p><?php
												$description = isset($education['education_description']) ? unserialize($education['education_description']->field_value) : null;
												if($description){
													echo $description['value'];
												}
											?>
										</p>
						      </div>
						    </div>
						  </li>
						<?php endforeach; ?>
					</ul>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
				  <h2>Skills</h2>
				  <div class="skills">
						<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeSkillsModel","position");
									$skillsData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
									$sortedSkills = [];
									foreach($skillsData as $skill){
										$skill_value = intval($skill['skill_value']->field_value);
										$sortedSkills[$skill_value][] = $skill;
									}
									krsort($sortedSkills);
						?>
						<?php foreach($sortedSkills as $skill_value => $skills): ?>
							<?php foreach($skills as $skill): ?>
							   <div class="item-skills" data-percent="<?= intval($skill_value) / 100 ?>"><?= $skill['name']->field_value ?></div>
							<?php endforeach; ?>
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
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeLanguagesModel","position");
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
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeHobbyModel","position");
								$hobbyData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<?php foreach($hobbyData as $hobby): ?>
				  	<div class="hobby"><?= $hobby['name']->field_value ?></div>
					<?php endforeach; ?>
				<?php endif; ?>
		  </div>
		  <div class="box">
				<?php if($resumeMainModel): ?>
				  <h2>Awards</h2>
					<?php $dataSet = ResumeSubformModel::getMapper()->findAllBy("form_name","ResumeAwardsModel","position");
								$awardsData = ResumeSubformHelper::convertDataSetInATwoDimensionalArray($dataSet);
					?>
					<?php foreach($awardsData as $award): ?>
						<div class="award">
							<h3><?= $award['title']->field_value ?></h3>
							<h5><i class="glyphicon glyphicon-calendar"></i> <?= isset($award['awards_date']) ?  ResumeSubformHelper::getProperDate($award['awards_date']->field_value) : "" ?></h5>
							<div class="award-description">
								<?php
									$description = isset($award['awards_description']) ? unserialize($award['awards_description']->field_value) : null;
									if($description){
										echo $description['value'];
									}
								?>
							</div>
						</div>
					<?php endforeach; ?>
				<?php endif; ?>
		  </div>
		</div>
	</div>
</div>
