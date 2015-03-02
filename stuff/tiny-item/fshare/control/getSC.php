<?php

session_start();

require_once('createRN.php');

if( $_GET['pwd'] == md5('arstr')  ){
	$_SESSION['safecode'] = createRandNum( 5 );
    echo $_SESSION['safecode'];
}

?>