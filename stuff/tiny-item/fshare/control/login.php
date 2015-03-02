<?
session_start();
require_once('../model/config.php');
require_once('../model/connectDB.php');
require_once('../model/userop.php');
/*
$_POST['pwd'] = md5('13579724969');
$_POST['email'] = '1095786568@qq.com';
$POST['token'] = md5('arstr');
*/
if($_POST['email'] && $_POST['pwd'] && $POST['token'] == md5('arstr')){
    if( !preg_match('/\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/', $_POST['email']) ){
        echo 1;// ilegal email
        return;
    }
	login($_POST['email'], $_POST['pwd']);
} else {
	echo 7873;
}

?>