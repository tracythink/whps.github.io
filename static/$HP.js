$(function() {
	/* LOGIC FROM HERE START::MAIN */
	var divobjs = $(".incont"), ccobjs = $(".cancel"), zidx = 10, idx;
	var tipobjs = divobjs.children("span"), linkojbs = $("#rbar img");
	var realobjs = $(".real");


	/* Loading things HERE */
	var api = 'https://api.github.com/repos/whps/whps.github.io/issues';
	$.getJSON(api, {sort: "updated"}, function(res){
		var blog = $("#blog");
		for (var i = 0; i < 8; i++) {
			var a = '<a href="'+ res[i].html_url + '"> ' + res[i].title + '</a>';
			var li = '<li class="link">' + a + '</a>';
			blog.append(li);
		}
		var blogurl = "https://github.com/whps/whps.github.io/issues";
		var a = '<a href="'+ "" + '"> ' + "MY BLOG HERE" + '</a>';
		var li = '<li class="link">' + a + '</a>';
		blog.append(li);
	});

	/* INIT : REPOSITION ALL MAIN BLKS */
	if (settings && settings.blks) {
		/* IE don't support forEach, bug to FIX */
		settings.blks.forEach(function(blk, idx) {
			$(divobjs[idx]).css({
				width: blk[0],
				height: blk[1],
				left: blk[2],
				top: blk[3]
			}).fadeIn("slow").children("p").css("opacity", "0.4");
			$(tipobjs[idx]).css({"opacity": "0.5"});
		});
	} else console.log("settings[.blks] UNINIT");


	var mover = function(event) { //mouseover show tips
		var i = divobjs.index(this);
		if (tipobjs[i].className === 'uptips') {
			$(tipobjs[i]).css("height", "auto").stop(true).slideDown(200);
		} else if (tipobjs[i].className === 'coverbg') {
			$(tipobjs[i]).fadeIn(400);
		} else console.log("unkonwn class attr to operation");
	};
	var mleave = function(event) { //disappear when out
		var i = divobjs.index(this), tipobj = $(tipobjs[i]);
		var disappear = function() {
			tipobj.css({"display": "none"});
		}
		if (tipobjs[i].className === 'uptips') {
			tipobj.stop(true).slideUp(200, disappear);
		} else if (tipobjs[i].className === 'coverbg') {
			tipobj.stop(true).fadeOut(400, disappear);
		} else console.log("unkonwn class attr to operation");	
	};
	/* click to expand to the whole show area */
	divobjs.click(function(event) {
		var i = idx = divobjs.index(this), obj = $(divobjs[i]);
		if ($(realobjs[i]).css('display') === 'block') return;
		console.log(i);
		obj.unbind("hover");
		$(tipobjs[i]).css({"display": "none"});
		obj.css({"z-index":(++zidx)}).animate({
			width: "100%",
			height: "100%",
			left: "0%",
			top: "0%"
		}, "fast").children(".cancel").fadeIn();
		$(realobjs[i]).fadeIn();
	}).hover(mover, mleave);


	var esc = function(event) {
		var i = idx = (idx >= 0 ? idx : ccobjs.index(this));
		$(divobjs[i]).animate({
			width: settings.blks[i][0],
			height: settings.blks[i][1],
			left: settings.blks[i][2],
			top: settings.blks[i][3]
		}, "fast", function(){
			$(divobjs[i]).bind("mouseenter", mover).bind("mouseleave", mleave);
		});
		$(ccobjs[i]).fadeOut();
		$(realobjs[i]).css("display", "none");
		event.stopPropagation();
	};
	/* press ESC or click cancel icon back to small view */
	$(document).keyup(function(event) {
		if (event.keyCode === 27 && idx >= 0) esc(event);
	});
	
	ccobjs.click(esc);

	/* link icon hover beauty */
	linkojbs.hover(function() {
		$(this).stop().animate({"opacity": "0.2"});
	}, function() {
		$(this).stop().animate({"opacity": "1"});
	});

	
	$("#posterbtn").preview($("#poster")); // unexcept pheno 2 FIX

});