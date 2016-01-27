window.onload=function(){
	var but=document.getElementById("pButton");
	but.onclick=preHander;
}
var flag=0;
function BuEnter(obj){
	var bu=document.getElementById("pButton");
	if(obj.keyCode==13){
		bu.click();
		obj.returnValue = false;
	}
}
function preHander(){
	var can=document.getElementById("look");
	var con=can.getContext("2d");
	var selectObj=document.getElementById("shape");
	var index=selectObj.selectedIndex;
	var shape=selectObj[index].value;
	if(shape=="squares"){
		fillBgC(can,con);
		for(var squares=0;squares<20;squares++){
			drawSquare(can,con);
		}
		drawText(can,con);
	    drawBird(can,con);
	}
	else if(shape =="circles"){
		fillBgC(can,con);
		for(var c=0;c<20;c++){
			
			drawCircle(can,con);
		}
		drawText(can,con);
	    drawBird(can,con);
	}
	else if(shape== "love" ){
		 var temp=document.getElementById("Pw");
		 temp.style.display="inline";
		 var pw="0124";
		 if(1 || temp.value == pw){
		 drawLove();
	     setInterval(drawLove,4900);
		 }
		 else {
			 if(temp.value == ""){
			     alert("拜托先输入密码!!");
			 }
		     else{
			 alert("错!!");
			 }
		 }
    }
	else if(shape == "smi" ){
		Smiling();
	}
}
function drawSquare(can,con){
	var w=Math.floor(Math.random()*40);
	var x=Math.floor(Math.random()*can.width);
	var y=Math.floor(Math.random()*can.height);
	var selectObj=document.getElementById("Color");
	var index=selectObj.selectedIndex;
	var bgC=selectObj.options[index].value;
	con.fillStyle=bgC;
	con.fillRect(x,y,w,w);
}
function fillBgC(can,con){
	var selectObj=document.getElementById("bgColor");
	var index=selectObj.selectedIndex;
	var bgC=selectObj.options[index].value;
	con.fillStyle=bgC;
	con.fillRect(0,0,can.width,can.height);
}
function dTor(d){
	return (d*Math.PI)/180;
}
function drawCircle(can,con){
	var r=Math.floor(Math.random()*40);
	var x=Math.floor(Math.random()*can.width);
	var y=Math.floor(Math.random()*can.height);
	con.beginPath();
	con.arc(x,y,r,0,dTor(360),true);
	var selectObj=document.getElementById("Color");
	var index=selectObj.selectedIndex;
	var bgC=selectObj.options[index].value;
	con.fillStyle=bgC;
	con.fill();
}
function Smiling(){
	var can=document.getElementById("look");
	var con=can.getContext("2d");
	fillBgC(can,con);
	con.beginPath();
	con.arc(300,100,90,0,dTor(360),true);
	con.fillStyle="#ffffcc";
	con.fill();
	con.stroke();
	
	con.beginPath();
	con.arc(255,70,15,0,dTor(360),true);
	con.stroke();
	
	con.beginPath();
	con.arc(255,70,10,0,dTor(360),true);
	con.fillStyle="black";
	con.fill();
	con.stroke();
	
	con.beginPath();
	con.arc(345,70,15,0,dTor(360),true);
	con.stroke();
	
	con.beginPath();
	con.arc(345,70,10,0,dTor(360),true);
	con.fillStyle="black";
	con.fill();
	con.stroke();
	
	con.beginPath();
	con.moveTo(300,90);
	con.lineTo(300,120);
	con.stroke();
	
	con.beginPath();
	con.arc(300,100,50,dTor(20),dTor(160),false);
	con.stroke();
}
function drawLove(){
	var can=document.getElementById("look");
	var con=can.getContext("2d");
	var index1=Math.floor(Math.random()*13);
	var index2=Math.floor(Math.random()*6);
	var w=[160,190,240,290,340,390,390,410,430,450,480,510,520];
	var x=w[index1];
	var h=[60,75,90,105,120,135];
	var y=h[index2];
	fillBgC(can,con);
	con.beginPath();
	con.fillStyle="black";
	con.fillRect(0,0,can.width,can.height);
	con.fillStyle="red";
	con.font="italic bold 2em Times,serif";
	con.fillText("zrimxjia@fu",x,y);
	
	con.fillStyle="purple";
	con.font="italic bold 2em Times,serif";
	con.fillText("zrimxjia@fu",can.width-540,can.height-160);
	
	con.fillStyle="#666";
	con.font="italic bold 0.9em Times, serif";
	con.textAlign="right";
	con.fillText("zrimxjia@fu",can.width,can.height-10);
	draw(can,con)
	var tBird = new Image();
	tBird.src="deng.png";
	tBird.onload = function(){
		con.drawImage(tBird,can.width-50,can.height-75,50,50)
	}
}
function drawText(can,con){
	var selectObj = document.getElementById("fgColor");
	var index = selectObj.selectedIndex;
	var fgColor=selectObj[index].value;
	con.fillStyle = fgColor;
	con.font="bold 1.3em Times,serif";
	con.textAlign = "left";
	con.fillText("I saw this tweets!!",20,40);
	
	selectObj=document.getElementById("tweets");
	index=selectObj.selectedIndex;
	var tweet=selectObj[index].value;
	con.font="italic bold 0.9em Times,serif";
	con.fillText(tweet,60,100);
	
	con.font="bold lem Times, serif";
	con.textAlign="right";
	con.fillText("and all I got was this lousy T-shirt",can.width-20,can.height-10);
}
function drawBird(can,con){
	var tBird = new Image();
	tBird.src="twitterBird.png";
	tBird.onload = function(){
		con.drawImage(tBird,20,120,70,70)
	}
}
function draw(can,con){
	var n=Math.floor(Math.random()*7);
	if(n<1){
		n=0.5;
	}
	var index1=Math.floor(Math.random()*15);
	var index2=Math.floor(Math.random()*5);
	var w=[80,130,180,210,240,270,300,330,360,390,420,450,480,510,520];
	var xa=w[index1];
	var h=[70,85,100,115,130];
	var ya=h[index2];
    var pp=Math.PI;
    var m = 0,x,y,rex,rey,xx,yy;
	xx=rex= 5* (16 * Math.pow(Math.sin(m-pp), 3))+xa;
	yy=rey=5*(13 * Math.cos(m-pp) - 5 * Math.cos(2 * m-pp) - 2 * Math.cos(3 * m-pp) - Math.cos(4 *m-pp))+ya;
    setInterval(function(){
     if(m < 50){
			x= n* (16 * Math.pow(Math.sin(m-pp), 3))+xa;
			y=n*(13 * Math.cos(m-pp) - 5 * Math.cos(2 * m-pp) - 2 * Math.cos(3 * m-pp) - Math.cos(4 *m-pp))+ya;
	        con.moveTo(x,y);
	        con.lineTo(x,y+2);
			con.stroke();
	        con.strokeStyle="red";
            m += 0.5;
			if(m==50){	for(m=0;m<100;){
		       xx= n* (16 * Math.pow(Math.sin(m-pp), 3))+xa;
		       yy=n*(13 * Math.cos(m-pp) - 5 * Math.cos(2 * m-pp) - 2 * Math.cos(3 * m-pp) - Math.cos(4 *m-pp))+ya; 
	           con.lineTo(xx,yy);
		       con.stroke();
	           con.strokeStyle="red";
		       m=m+0.5;
		       if(m==100){
	             con.closePath();
                 con.fillStyle="red";
	             con.fill();
		         }
	         }
			  
		   }
	 }
    },50);
}
