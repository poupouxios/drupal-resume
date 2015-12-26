<?php

	class ResumeMainModel extends ResumeBaseModel{
		public static $attributes = array(
			"id" => 0,
			"header_title" => "",
			"image_id" => null,
			"cv_file_id" => null,
			"about_me" => "",
			"introduction" => "",
			"contact_me" => "",
			"skype_id" => "",
			"created_at" => "NOW()",
			"updated_at" => "NOW()"
		);

	}

?>
