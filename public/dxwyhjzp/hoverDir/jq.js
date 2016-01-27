             
			var timer;
			
			
			indexjq.loseThreediv = function(){
				
				
				
				timer = setTimeout(function(){
					
					        $('#logout div').mouseover(function(){ 
								clearTimeout(timer);	
							 })
							 
					        thistimer();
							
					},800);
				
				
				 
				 function thistimer(){
					 
				        for(var i = 0; i < 3; i++){
					
					       $('#logout div:eq('+i+')').animate({top:60+i*20+'px'},250);
					        
				        }			
				 }
			}	
			
			indexjq.getThreediv = function(){
				$('#hid').fadeOut();
				$('#showCode').text(arr[0]+$('#logout').html()+'\n'+arrjs[0]
				).css({'overflow':'scroll','border-radius':'0'});
				clearTimeout(timertimer);
				for(var i = 0; i < 3; i++){
					
					$('#logout div:eq('+i+')').animate({top:'10px'},300);
					
				}
			}			
			
			indexjq.getWordShow = function(){//显示文字

				var time = 0;
				
				for(var j = 0; j < $('#top h1').length; j++){
					$('#top h1:eq('+j+')').fadeIn(500 + time,function(){
						
						});
					time += 1000;
					}
					
				time = 2000;
				
			    for(var j = 0; j < $('#bot h1').length; j++){
					$('#bot h1:eq('+j+')').fadeIn(500 + time,function(){
						            setTimeout(function(){
									$('#top').animate({top:'-320px'},500);
				                    $('#bot').animate({bottom:'-320px'},500,function(){
									$('header').css('display','none');
									//for(var i = )
									
									});},2500);
						});
					time += 1000-j*100;
					}
				}
				
			indexjq.spring = [//函数数组
			function navSpr0(){
				    $('#hid').fadeOut();
				    $('#showCode').text(arr[3]+$('#nav').html()+'\n'+arrjs[3]
				    ).css({'overflow':'scroll','border-radius':'0'});
					var high = 3;
					var time = 50;
					for(var i = 0; i < 4; i++){
						$('#nav li:eq(0)').animate({top:high+'px'},time+50,function(){
                            $('#nav li:eq(0)').animate({top:'0px'},time+50);
							});
						high *=-1;
						}
					},
					
			function navSpr1(){
				    $('#hid').fadeOut();
				    $('#showCode').text(arr[3]+$('#nav').html()+'\n'+arrjs[3]
				    ).css({'overflow':'scroll','border-radius':'0'});
					var high = 3;
					var time = 50;
					for(var i = 0; i < 4; i++){
						$('#nav li:eq(1)').animate({top:high+'px'},time+50,function(){
                            $('#nav li:eq(1)').animate({top:'0px'},time+50);
							});
						high *=-1;
						}
					},
					
			function navSpr2(){
				    $('#hid').fadeOut();
				    $('#showCode').text(arr[3]+$('#nav').html()+'\n'+arrjs[3]
				    ).css({'overflow':'scroll','border-radius':'0'});
					var high = 3;
					var time = 50;
					for(var i = 0; i < 4; i++){
						$('#nav li:eq(2)').animate({top:high+'px'},time+50,function(){
                            $('#nav li:eq(2)').animate({top:'0px'},time+50);
							});
						high *=-1;
						}
					},
					
			function navSpr3(){
				    $('#hid').fadeOut();
				    $('#showCode').text(arr[3]+$('#nav').html()+'\n'+arrjs[3]
				    ).css({'overflow':'scroll','border-radius':'0'});
					var high = 3;
					var time = 50;
					for(var i = 0; i < 4; i++){
						$('#nav li:eq(3)').animate({top:high+'px'},time+50,function(){
                            $('#nav li:eq(3)').animate({top:'0px'},time+50);
							});
						high *=-1;
						}
					}
			]
			
			
			indexjq.chSM = [
			function (){
				  var ii = 0;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						  $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					  
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 1;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 2;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 3;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 4;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 5;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 6;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 7;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 8;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 9;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 10;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				},
				function (){
				  var ii = 11;
				  if(markClik%2){
					  
					  $('#midcon div:eq('+ii+')').css({'z-index':'1','opacity':'0.98'})
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'700px',height:'500px',top:'0',left:'0'});
					  
					  }
				  
				  else{
					  
				      $('#midcon div:eq('+ii+')')
					  .animate({width:'175px',height:'167px',
					  top:parseInt(ii/4)*167+'px',left:(ii%4)*175+'px'},function(){
						   $('#midcon div:eq('+ii+')').css({'z-index':'0'});
						  });
					 
					  }
				 markClik++;	  
				}
			]