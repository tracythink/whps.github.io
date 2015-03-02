<?

function login( $em, $pw ){
	$pw = md5($pw);
	$opt = 'id,name,email,createtime';
	$sql = "SELECT $opt FROM userinfo WHERE email = '$em' AND pwd = '$pw' LIMIT 1";
	if($r = mysql_query($sql)){
    	$s = mysql_fetch_row($r);
    	if( empty($s) ){ 
    		echo 1;
    		exit;
    	}
    	$_SESSION['uinfo'] = $s;
    	echo json_encode($s);
	} else {
		echo 2;
	} 
}

function gettflist($id, $t, $page){
	if( $page == 0 ){ 
		$pid = 0;
	}else{
		$page = $page * 10;
		$opt = 'pid,fid,filename,createtime';
		$from = "SELECT pid FROM pstinfo WHERE uid = $id AND createtime >= $t LIMIT $page";
		$sql1 = "SELECT MAX(pid) FROM ($from) AS tmp";
		if($r = mysql_query($sql1)){
    		$s = mysql_fetch_row($r);
    		if( empty($s[0]) ){ 
    			echo 3;
    			exit;
    		}
    		$pid = $s[0];
		} else {
			echo 4;
			exit;
		}
    }
	if( !isset($pid) ){ 
		echo 5;
		exit;
	}
	$opt = 'pid, fid, filename, createtime';
	$sql2 = "SELECT  $opt 
			 FROM pstinfo 
			 WHERE uid = $id AND createtime >= $t AND pid > $pid 
			 order by createtime LIMIT 10";
	$arr = array();
	if($r = mysql_query($sql2)){
    	while( $s = mysql_fetch_array($r, MYSQL_ASSOC) ){
    		array_push($arr, $s);
    	}
    	if( empty($arr) ){
    		echo 6;
    		exit;
    	}
    	echo json_encode($arr);
	} else {
		echo $sql2;
		echo mysql_error();
		echo 7;
	} 
}

?>