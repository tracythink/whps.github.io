<?php
session_start();
/*
* reg post this interface
* "better check" means ( backgtage do this job )
* paras:
  safecode ( better check ), 
  username ( better check 字母开头,允许5-16字节,允许字母数字下划线 ), 
  pwd      ( must be secret by md5 ), 
  email    ( better check )  
  # impotant point COOKIE PHPSESSID #
*/
require_once('../model/config.php');  
require_once('../model/connectDB.php');
//require_once('sendMail/sendMail.php');
require_once('createRN.php');
/*
$_POST['username'] = 'deng630';
$_POST['pwd'] = md5('13579724969');
$_POST['email'] = '1095786568@qq.com';
*/

if( ($_POST['safecode'] != $_SESSION['safecode']) || empty($_SESSION['safecode'])  ){
    echo 8387;
    return;
}

if( $_POST['username'] && $_POST['pwd'] && $_POST['email'] ){
	$un = $_POST['username'];
	$email = $_POST['email'];
	$pwd = $_POST['pwd'];
	if( !preg_match('/^[a-zA-Z][a-zA-Z0-9_]{4,15}$/', $un) ){
        echo 1;//字母开头,允许5-16字节,允许字母数字下划线
        return; 
    }
    if( !preg_match('/\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/', $email) ){
        echo 2;// ilegal email
        return;
    }
    $ur = uniqueACT( $email );
    if( $ur === 0 ){
        echo 3;// reged
        return;  
	}else if( $ur === 2 ){
		echo 6887; // database wrong
		return;
	}
    //reg( $un, $pwd, $email );
    createUser($un, $pwd, $email);
    echo 0;
}else{
	echo 7873; // no info
}

function uniqueACT( $desc ){

     $sql = "SELECT id FROM userinfo WHERE email = '$desc'";
     $r = mysql_query($sql);
     if( $r === FALSE ){
     	 return 2;
     }
     if( mysql_fetch_row( $r ) === FALSE ){
     	 return 1;
     }
     return 0;
}
/*
function reg( $un, $pwd , $email ){
    createUser( $un, $pwd, $email );
    $_SESSION['mailCheck'] = createRandNum( 6 );
    $body = '感谢注册 Fshare 您的验证码如下:'.$_SESSION['mailCheck'];
    echo sendMail( $email, 'Fshare注册验证' , $body , $un );
}
*/
function createUser( $un, $pwd, $email ){
    $pwd = md5($pwd);
    $timestamp = time();
    $sql = "INSERT INTO userinfo (id,name,pwd,email,state,createtime) VALUES (0,'$un','$pwd','$email',0,$timestamp)";
    if( mysql_query($sql) === FALSE ){
    	echo "database err";
    }
}

mysql_close();

?>