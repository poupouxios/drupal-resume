<?php

	class ImageHelper{
		
		public static function handleImageFile($formValue,$formStateValue,$moduleName,$fieldName){
			$file = null;

			if (isset($formStateValue) && $formStateValue) {
				if (isset($formValue) && $formValue != $formStateValue) {
				  $file = self::removeImageFile($formValue, $moduleName,$fieldName);
					$file = self::addImageFile($formStateValue,$moduleName,$fieldName);
				}
				else {
					$file = self::addImageFile($formStateValue,$moduleName,$fieldName);
				}
			}else{
				$file = self::removeImageFile($formValue, $moduleName,$fieldName);
			}
			return $file;
		}

		private static function removeImageFile($imageFileId,$moduleName,$fieldName){
			$file = $imageFileId ? file_load($imageFileId) : FALSE;
			if ($file) {
				file_usage_delete($file, $moduleName, $fieldName, $file->fid);
				file_delete($file);
			}
			return $file;
		}

		private static function addImageFile($imageFileId,$moduleName,$fieldName){
		 /* if our file is already in use, then we don't need to re-do this and increase the count */
			$count = db_query('SELECT `count` FROM {file_usage} WHERE fid=:fid', array('fid' => $imageFileId))->fetchField();
			$file = file_load($imageFileId);
			if (empty($count)) {
				$file->status = FILE_STATUS_PERMANENT;
				file_save($file);
				file_usage_add($file, $moduleName, $fieldName, $imageFileId);
			}
			return $file;
		}

		
	}
