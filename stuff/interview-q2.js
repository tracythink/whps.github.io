/* 今天在咖啡馆都有点懵，思路完全不对
 * 下面这道题的思路实际上要打印对角线上的一串【下标之差/之和】是有规律的
 * 譬如差为这样的变化规律 3, 2, 1, 0, -1, -2, -3 
 * 这样的话做一个 0 至 2*length-1 的遍历
 * 只需要检查下标差是否为给定值 且 下标合法 则 打印出来 */

var a = [
	[1, 2, 3, 4], 
	[5, 6, 7, 8], 
	[9, 7, 1, 2], 
	[3, 4, 5, 6]
];

// O(n*n)
function printMatrix(m) {

	var length = m.length;
	
	for (var i = 0, n = length - 1; i < 2*length - 1; i++, n--) {
		
		for (var j = 0; j < length; j++) {
			var idx = n + j; // 同一对角线方向下标之差为同一值 idx - j == n
			if (idx > -1 && idx < length) console.log(m[j][idx]);
		}
	}
}

//printMatrix(a);

/* 这个题目的关键在于掐头加尾就得到下一个需要比较的值，
 * 做一个 length - n 次的遍历存最小值就好 */
// O(n)
function continueNMin(a, n) {
	var min = 0, tmp, length = a.length - n;
	
	for (var i = 0; i < n; i++) {
		min += a[i];
	}
	
	tmp = min;
	
	for (var i = 1; i < length; i++) {
		tmp = tmp - a[i-1] + a[i+n-1] ;
		if (tmp < min) min = tmp;
	}
	
	return min;
}

//console.log(continueNMin([1, 4, 4, 4, -5, -3, -4, 5], 4) === -8);
