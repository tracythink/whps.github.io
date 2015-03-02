<?
/*
** only path , name info
*/

define( 'RLTVDIR', '../../' );
define( 'ROOTDIR', 'X7HB3EOuZ7P89mSk3/' );

function search_filepath( $fid ){
    $sql = "SELECT path,hashid,type FROM fileinfo WHERE  fid = $fid";
	$r = mysql_fetch_row( mysql_query($sql) );
	if( empty($r) ){
		return 0;
	}
	return RLTVDIR.ROOTDIR.$r[0].$r[1].'.'.$r[2];
}
/*
** file detail info
*/
function sch_range_file( $longi, $lati, $het, $lrange, $hrange ){
    $lomax = $longi + $lrange;
    $lomin = $longi - $lrange;
    $lamax = $lati + $lrange;
    $lamin = $lati - $lrange;
    $hmax = $het + $hrange;
    $hmin = $het - $hrange;

    $option = "userinfo.name, pstinfo.fid, pstinfo.uid, pstinfo.filename";
    $oncdt = "userinfo.id = pstinfo.uid";
    $whcdt = "     (pstinfo.longitude BETWEEN $lomin AND $lomax) 
               AND ( pstinfo.latitude BETWEEN $lamin AND $lamax ) 
               AND ( pstinfo.height BETWEEN $hmin AND $hmax ) 
             ";
    $sql = "SELECT $option FROM pstinfo LEFT JOIN userinfo ON( $oncdt ) WHERE ( $whcdt ) LIMIT 10";
    
    $rarr = array();
    $res = mysql_query( $sql );
    while( $row = mysql_fetch_array( $res, MYSQL_ASSOC ) ){
    	array_push( $rarr, $row );
    }
    return json_encode($rarr);
}
?>