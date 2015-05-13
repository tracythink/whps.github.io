/* 050915 by WHPS :) Happy Codeing
** settings 4 $HP such =>
** > bg-colors 
** > kinds of block size(width. height) */

var settings = window.settings || {};

settings.bgcolors = [
	"#099",    // sunshine blue
	"#e6423d"  // warm pink
];

settings.blks =[
	["40%", "50%", "0%", "0%"],
	["30%", "25%", "40%", "0%"],
	["30%", "25%", "40%", "25%"],
    ["30%", "50%", "70%", "0%"],
    ["30%", "50%", "0%", "50%"],
    ["40%", "50%", "30%", "50%"],
    ["30%", "25%", "70%", "50%"],
	["30%", "25%", "70%", "75%"],
];

// Array.forEach bug to FIX

/* that function default click 
   the big pic to close :) */ 
$.fn.preview = function($obj) {
	$(this).click(function(event) {
		$obj.css("z-index", "1024").fadeIn();
	});
	$obj.click(function(event){
		$obj.fadeOut();
	});
};

if (!Array.prototype.forEach)  {  
    Array.prototype.forEach = function(fun) {  
        var len = this.length;
        if (typeof fun != "function") throw new TypeError();
        var thisp = arguments[1];  
        for (var i = 0; i < len; i++) {
            if (i in this) fun.call(thisp, this[i], i, this);
        }
    };
}
