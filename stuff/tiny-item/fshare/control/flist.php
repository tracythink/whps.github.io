<?
session_start();
require_once('../model/config.php');
require_once('../model/connectDB.php');
require_once('../model/userop.php');
/*
$_POST['token'] = md5('arstr');
$_POST['time'] = 123154;
$_POST['page'] = 1;
$_SESSION['uinfo'][0] = 6;
*/
if(    $_POST['token'] == md5('arstr') 
	&& $_POST['time'] > 0 
	&& is_int($_POST['time']) 
	&& is_int($_POST['page'])
	&& $_POST['page'] >= 0
   ){
	if( $_SESSION['uinfo'][0] > 0 ){
		gettflist($_SESSION['uinfo'][0], $_POST['time'], $_POST['page']);
	} else {
		echo 1;
	}
} else {
	echo 2;
}

?>