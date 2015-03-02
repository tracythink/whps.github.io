<?
/*
** 
*/

function send_file( $filepath ){
	header('Content-Description: File Transfer');
	header('Content-Type: application/octet-stream');
	header('Content-Disposition: attachment; filename='.basename($filepath) );
	header('Content-Transfer-Encoding: binary');
	header('Expires: 0');
	header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
	header('Pragma: public');
	header('Content-Length: ' . filesize($filepath));
	readfile($filepath);
}
require_once('../../model/config.php');
require_once('../../model/connectDB.php');
require_once('../../model/search.php');
require_once('../../model/fileop.php');

/*
$fid = $_GET['file_id'] = 8;
*/

if( is_int($fid) && $fid != 0 ){
	$r = search_filepath( $fid );
	if( empty($r) ){
		echo '404';
	}else{
		send_file( $r );
	    comp_UDN( $fid, 'down_hot', 1 );
	}
	mysql_close();
}else{
	echo 'para loss';
}
?>