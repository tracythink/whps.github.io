<?
$staystt = array('stay','leave');
define( 'RLTVDIR', '../../' );
define( 'ROOTDIR', 'X7HB3EOuZ7P89mSk3/' );
/*
** if file existed return fid
*/
function isuped( $hi ){
	$sql = "SELECT fid FROM fileinfo where hashid = '$hi'";
	$r = mysql_fetch_row( mysql_query($sql) );
    return $r[0];
}

/*
**  
*/
function add_position( $fid, $uid, $fname, $longitude, $latitude, $height, $isstay ){
	/* add up times && existnum*/
	global $staystt;
	if( !in_array($isstay, $staystt) ) $isstay = 'leave';
	if( empty($uid) ) $uid = 0;
	$time = time();
	$option = ' pid, fid, uid, filename, longitude, latitude, height, isstay, createtime ';
	$data = " 0, $fid, $uid, '$fname', $longitude, $latitude, $height, '$isstay',  $time ";
	$sql = "INSERT INTO pstinfo ( $option ) VALUES ( $data )";
	mysql_query( $sql );
	comp_UDN( $fid, 'up_hot', 1 );
	comp_UDN( $fid, 'existnum', 1 );
}
/*
**
*/
function add_dir( $src, $path, $fn ){
	if ( !is_dir( RLTVDIR.ROOTDIR.$path ) ) mkdir( RLTVDIR.ROOTDIR.$path );
    move_uploaded_file( $src, RLTVDIR.ROOTDIR.$path.$fn );
}
/*
**
*/
function add_file( $filehash, $type, $path, $fs ){
	$time = time();
    $option = " fid,hashid,type,path,size,existnum,up_hot,down_hot,createtime";
    $data =  "0, '$filehash', '$type', '$path', $fs, 0, 0, 0, $time ";
    $sql = 'INSERT INTO fileinfo ('.$option.') VALUES ( '.$data.' )';
    //echo $sql;
    mysql_query($sql);
    //echo mysql_error();
    return mysql_insert_id();
}
/*
**
*/
function comp_UDN( $fid, $col, $op ){
   $sql =  " UPDATE fileinfo SET $col = $col + $op WHERE fid = $fid";
   mysql_query($sql);
}
/*
**
*/

/*
**
*/

?>