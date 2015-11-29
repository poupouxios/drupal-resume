<?php

	class ResumeSubformMapper extends ResumeBaseMapper{
		private $subFormVariant;

		public function __construct(){
			$this->tableName = "resume_subforms";
		}

		public function setSubformVariantModel($subformVariantModel){
			$this->subFormVariant = $subformVariantModel;
			return $this;
		}
		
		public function deleteAllBasedOn($resumeMainId,$formName){
			db_delete($this->tableName)
				->condition("resume_main_id", $resumeMainId)
				->condition("form_name", $formName)
				->execute();
		}

		public function saveSubformVariantData($resumeMainId,$position){
			$model = $this->subFormVariant;
			$fields = array_keys($model::$attributes);
			foreach($fields as $field){
				if(isset($model->$field) && strlen($model->$field) > 0){
					$data = array(
						"resume_main_id" => $resumeMainId,
						"form_name" => get_class($model),
						"field_name" => $field,
						"field_value" => $model->$field,
						"position" => $position
					);
					$subformModel = ResumeSubFormModel::createObject($data);
					$this->setModel($subformModel)->save();
				}
			}		
		}

	}
?>
