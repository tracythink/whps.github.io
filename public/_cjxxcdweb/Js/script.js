$(window).load(function(){
	//大神代码
	function animSteam(){
		$('<span>',{
			className:'steam'+Math.floor(Math.random()*2 + 1),
			css:{
				Left	: -10 + Math.floor(Math.random()*20)
			}
		}).appendTo('#rocket').animate({
			left:'-=58',
			bottom:'-=100'
		}, 120,function(){			
			$(this).remove();
			setTimeout(animSteam,10);
		});
	}
	function moveRocket(){
		$('#rocket').animate({'left':'+=100'},5000).delay(1000)
					.animate({'left':'-=100'},5000,function(){
				setTimeout(moveRocket,1000);
		});
	}		
	moveRocket();
	animSteam();
	//我的代码
	//div1
	$('#div1 nav').mouseover(function(){
		$('#div1 p').css('display','block');
	});
	$('#div1 nav').mouseout(function(){
		$('#div1 p').css('display','none');
	});
	var x = ($('#div1 ul li').height()+3) * $('#div1 ul li').length+30;
	$('#div1 div').css({'height':x});
	
	//div2
	var x = ($('#div2 ul li').height()+3) * $('#div1 ul li').length+30;
	$('#div2 div').css({'height':x});
	$('#div2 nav').mouseover(function(){
		$('#div2 p').css('display','block');
	});
	$('#div2 nav').mouseout(function(){
		$('#div2 p').css('display','none');
	});
	
	//div3
	var x = ($('#div3 ul li').height()+3) * $('#div3 ul li').length+30;
	$('#div3 div').css({'height':x});
	$('#div3 nav').mouseover(function(){
		$('#div3 p').css('display','block');
	});
	$('#div3 nav').mouseout(function(){
		$('#div3 p').css('display','none');
	});
	
	//div4
	var x = ($('#div4 ul li').height()+3) * $('#div4 ul li').length+30;
	$('#div4 div').css({'height':x});
	$('#div4 nav').mouseover(function(){
		$('#div4 p').css('display','block');
	});
	$('#div4 nav').mouseout(function(){
		$('#div4 p').css('display','none');
	});
	
	//
	$('#div1').draggable();
	$('#div2').draggable();
	$('#div3').draggable();
	$('#div4').draggable();
	$('#rocket').draggable();
	$('#title').draggable();
	$('#thish2').draggable();
});