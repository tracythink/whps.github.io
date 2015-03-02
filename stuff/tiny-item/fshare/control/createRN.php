<?php
/*
* create safe code
* save as session 
*/

function createRandNum( $leg ){
	$strarr = array(
		"qwerop567asdfWEvbnm",
    	"QRTtYUIOPAS4DFGHM54",
    	"yuihjklCVBNzr34xc58",
    	"01g23e234JK45eLZX89"
    );
	$sc = "";
    for( $i = 0; $i < $leg; $i++ ){
        $v = $strarr[ $i % 4 ];
    	$sc .= $v[mt_rand( 0, strlen($v)-1 )];
    }
    return $sc;
}
/* ex 
echo createRandNum( 8 );
*/

?>