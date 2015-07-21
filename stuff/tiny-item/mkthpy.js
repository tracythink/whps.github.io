/* 5.4.2014 --- by WHPS @ :) >> util tools 
 * point => this, new, prototype, argumets
 * JavaScript is a dangerous language
 * basic type prototype is common struct */

/***** for Debug *****/
var echo = console.log;

(function() {

	function addfunc(obj, name, func) {
		if (typeof obj[name] !== 'function') {
			obj[name] = func;
		}
		/* if already set the func, ign */
	}

	/* set which obj point to be the __proto__ 
	 * suit all obj except array cause length*/
	addfunc(Object, 'beget', function(o) {
		var F = function() {};
		F.prototype = o;
		return new F();
	});


	/* we can do this cause: all the objs have a hide __proto__
 	 * point a constructor.prototype $ set common struct like =>
 	 ************************************************************
 	 >	cons.prototype.common_struct =  value;
 	 ************************************************************
	 * when function-obj created, code will be like =>
	 ************************************************************
	 >	this.prototype = {constructor: this}; 
 	 ************************************************************/
	addfunc(Function.prototype, 'method', function(name, func) {
		if (!this.prototype[name]) {
			this.prototype[name] = func;
		}
		return this;
	});

	Number.method('integer', function() {
		return Math[this < 0 ? 'ceiling' : 'floor'](this);
	});

	String.method('tirm', function() {
		return this.replace(/^\s+|\s+$/g, '');
	});

	Function.method('curry', function() {
		var slice = Array.prototype.slice,
			args = slice.apply(arguments),
			that = this;
		return function() {
			var __args = slice.apply(arguments);
			return that.apply(null, args.concat(__args));
		}
	});
	/* is inherits good ? not good! */
	Function.method('inherits', function(Parent) {
		this.prototype = new Parent();
		return this;
	});
	
	Object.method('isarray', function(value) {
		/* poorly this only recognize in the same window */
		/* return value && 
			typeof value === 'object' && 
			value.constructor === Array; */
		return value && 				// first must be a real value
			typeof value === 'object' &&		// for obj, array, null will be true
			typeof value.length === 'number' &&     // length is a number? array always true
			typeof value.splice === 'function' &&   // has a splice func? array always true
			!(value.propertyIsEnumerable('length'));// but array.length is UnEnum
	});
	/* init only can be value-type */
	Array.dim = function(dim, init) {
		var a = [];
		for (var i = 0; i < dim; i++) {
			a[i] = init;
		}
		return a;
	};

	Array.matrix = function(m,n, init) {
		var mat = [];
		for (var i = 0; i < m; i++) {
			mat[i] = Array.dim(n, 0);
		}
		return mat;
	}
	/* END INIT ENV, SETTINGS ... */
})();

/****************************
 *** HOW TO USE INHERITS ****
 ****************************
var Car = function(name) {
	this.name = name || "Car";
	this.print = function() {
		echo(this.name);
	};
};

var Bench = (function(name) {
	this.name = name || "Bench";
}).inherits(Car);

var bench = new Bench("WHPS");
bench.print(); 
*******************************/

/******************************
 * HOW TO WRITE A CONSTRUCTOR *
 ******************************
 var constructor = function(spec, my) {
	var that, other_private_var;
	my = my || {};
	
	my.interfaces = ...;
	my.public_prototypes = ...;

	that = new a obj by your way(maybe: new, beget, {} ...);
	that.interfaces = ...;
	that.public_prototypes = ...;

	return that;
 }
 *******************************/
