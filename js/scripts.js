
(function ($) {
	var callback = function(){
		$('.item-skills').each(function(){
			newWidth = $(this).parent().width() * $(this).data('percent');
			$(this).width(0);
		  $(this).animate({
		      width: newWidth,
		  }, 1000);
		});
		$('.icons-red').each(function(){
			height = $(this).height();
		  $(this).animate({
		      height: 14,
		  }, 2000);
		});

		var my_posts = $("[rel=tooltip]");
		var size = $(window).width();

		for(i=0;i<my_posts.length;i++){
			the_post = $(my_posts[i]);

			if(the_post.hasClass('invert') && size >=767 ){
				the_post.tooltip({ placement: 'left'});
				the_post.css("cursor","pointer");
			}else{
				the_post.tooltip({ placement: 'rigth'});
				the_post.css("cursor","pointer");
			}
		}

	};
	$(document).ready(callback);

	var resize;
	window.onresize = function() {
		clearTimeout(resize);
		resize = setTimeout(function(){
			callback();
		}, 100);
	};
})(jQuery);
