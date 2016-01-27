var arr = [
'#logout{width:115px; height:60px; float:right; position:relative; overflow:hidden;}',
'#midcon{background:#FFF; width:700px; height:500px; margin:0 auto; border:1px solid #CCC;position:absolute;margin-top:50px;left:50px;}',
'#nav{height:40px;background-color:#252525; padding-left:26px;}li{float:left; list-style:none;margin-left:20px; position:relative; display:block;font-size:24px;}li a{color:#CCC; text-decoration:none}'
]

var arrjs = [
"$('#logout div').mouseout(function(){ timertimer = setTimeout(function(){ for(var i = 0; i < 3; i++){$('#logout div:eq('+i+')').animate({top:60+i*20+'px'},250); }},800);});",
"for(var ii = 0; ii < 12; ii++){ $('#midcon div:eq('+ii+')').click(indexjq.chSM[ii]);}function (){var ii = 4; if(markClik%2){ $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})$('#midcon div:eq('+ii+')').animate({width:'700px',height:'500px',top:'0',left:'0'});  }else{ $('#midcon div:eq('+ii+')').animate({width:'175px',height:'167px',top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){ $('#midcon div:eq('+ii+')').css({'z-index':'0'});});  }	 markClik++;		},",
"function navSpr0(){   $('#hid').fadeOut(); $('#showCode').text(arr[3]+$('#nav').html()+'\n'+arrjs[3]  ).css({'overflow':'scroll','border-radius':'0'});var high = 3;	var time = 50;	for(var i = 0; i < 4; i++){$('#nav li:eq(0)').animate({top:high+'px'},time+50,function(){ $('#nav li:eq(0)').animate({top:'0px'},time+50);});  high *=-1;}},"
]