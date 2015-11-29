<?php

	class ResumeSubformHelper{

		public static function doesFormExist($formName){
			$formModel = self::getSubFormVariantModel($formName);
			if(class_exists($formModel)){
				return true;
			}else{
				return false;
			}
		}

		public static function getSubFormVariantModel($formName){
			$formName = preg_replace('/[^a-z0-9]+/i', '', $formName);
			$formModel = "Resume".ucfirst($formName)."Model";
			return $formModel;
		}

		public static function convertDataSetInATwoDimensionalArray($dataSet){
			$newDataset = array();
			foreach($dataSet as $data){
				$newDataset[$data->position][$data->field_name] = $data;
			}
			return $newDataset;
		}

		public static function getProperDate($date){
			$datetime = new DateTime($date);
			return $datetime->format('m/Y');
		}

	}

?>
