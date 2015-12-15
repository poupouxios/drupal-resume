<?php
	
	class ResumeBaseMapper{
		protected $tableName;
		protected $model;

		public function __construct(){

		}

		public function setModel($model){
			$this->model = $model;
			return $this;
		}
	
		public function findAll(){
			$dataSet = db_select($this->tableName,"a")->fields("a")->execute()->fetchAll(PDO::FETCH_ASSOC);
			$called_class = str_replace("Mapper","Model",get_called_class());
			$dataModels = array();
			foreach($dataSet as $data){
				$dataModels[] = $called_class::createObject($data);
			}
			return $dataModels;
		}

		public function findAllBy($field,$value,$sortField = "",$order = "ASC"){
			$query = db_select($this->tableName,"a");
			$query->fields("a")
						->condition($field,$value);
			if(strlen($sortField) > 1){
				$query->orderBy($sortField,$order);
			}
			$dataSet = $query->execute()->fetchAll(PDO::FETCH_ASSOC);
			$called_class = str_replace("Mapper","Model",get_called_class());
			$dataModels = array();
			foreach($dataSet as $data){
				$dataModels[] = $called_class::createObject($data);
			}
			return $dataModels;
		}

		public function save(){
			if(isset($this->model->id)){
				$this->update();
				return $this->model->id;
			}else{
				return $this->insert();
			}
		}

		public function insert(){
			$this->model->created_at = date("Y-m-d H:i:s");
			$this->model->updated_at = date("Y-m-d H:i:s");
		  return db_insert($this->tableName)->fields((array)$this->model)->execute();
		}

		public function update(){
			$this->model->updated_at = date("Y-m-d H:i:s");
			db_update($this->tableName)->fields((array)$this->model)->condition("id",$this->model->id)
			->execute();
		}

	}
?>
