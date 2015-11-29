<?php

	class ResumeBaseModel{
		public static $attributes;
		
		public function __construct(){

		}
		
		public static function getMapper(){
			$mapper_class_name = str_replace("Model","Mapper",get_called_class());
			$mapper = new $mapper_class_name;
			return $mapper;
		}

		public static function createObject($data){
			$called_class = get_called_class();
			$object = new $called_class;
			foreach($data as $key => $value){
				if(array_key_exists($key,$object::$attributes)){
					if(is_array($value)){
						$object->$key = serialize($value);
					}else{
						$object->$key = $value;
					}
				}
			}
			return $object;
		}

		public function updateFields($data){
			foreach($data as $key => $value){
				if(array_key_exists($key,$this::$attributes)){
					if(is_array($value)){
						$this->$key = serialize($value);
					}else{
						$this->$key = $value;
					}
				}
			}
		}
	
	}

?>
