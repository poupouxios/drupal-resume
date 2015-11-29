<?php

	class ResumeSubformModel extends ResumeBaseModel{
		public static $attributes = array(
			"id" => 0,
			"resume_main_id" => null,
			"form_name" => "",
			"field_name" => "",
			"field_value" => "",
			"position" => 0,
			"created_at" => "NOW()",
			"updated_at" => "NOW()"
		);
	
	}

?>
