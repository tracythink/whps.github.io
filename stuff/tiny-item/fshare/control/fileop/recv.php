<?
session_start();
$dirtree = array(
    'bts' => array( 'torrent' ),
    'vedios' => array( 'bhd', 'avi', 'wmv', 'mp4', '3gp', 'flv', 'rm', 'mov', 'rmvb' ),
    'musics' => array( 'mp3', 'wma', 'acc' ),
    'office' => array( 'pdf', 'doc', 'ppt', 'xls', 'docx', 'pptx', 'xlsx' ),
    'images' => array( 'psd', 'jpg', 'jpeg', 'gif', 'png', 'bmp' ),
    'documents' => array( 'txt', 'c', 'cpp', 'sh', 'php', 'js', 'py', 'go' ),
    'tars' => array( 'zip', 'rar', '7z', 'iso', 'cab' )
    );

$fsize = array(
    0 => 's0to1M', 
    1 => 's1to10M', 
    10 => 's10to20M',
    50 => 's50toxM'
    );
/*
define( 'URL' , 'http://localhost/Dropbox/Fshare/control/fileop/download.php' );
*/
?>

<?
/*
** login check 
*/
/* init */
require_once('../../model/config.php');
require_once('../../model/connectDB.php');
require_once('../../model/fileop.php');
$file_size = 2 * 1024 * 1024;

/*
$_POST['longitude'] = 35.251;
$_POST['latitude'] = 40.25566;
$_POST['isstay'] = 'leave';
$_SEEEION['uid'] = 4;
$_POST['height'] = 30.223;
*/
if (!is_uploaded_file( $_FILES['up_file']['tmp_name'])) {
    echo -1;
    exit;
}

if(    /*is_uploaded_file( $_FILES['up_file']['tmp_name'] )  
    && */is_float($_POST['longitude'])
    && is_float($_POST['latitude'])
    && $_POST['isstay'] 
    && is_float($_POST['height'])
  ){
	if( $_FILES['up_file']['size'] > $file_size ){
        echo 'file size more than max';
        return;
	}
	$file_suffix = get_file_suffix( $_FILES['up_file']['name'] );
    $filehash = md5_file( $_FILES['up_file']['tmp_name'] );
    if( $fid = isuped( $filehash ) ){ 
    	# do nothing
    }else{
    	$adddir = 
        get_dir( strtolower($file_suffix), $_FILES['up_file']['size']/(1024*1024) );

    	add_dir( $_FILES['up_file']['tmp_name'], $adddir, $filehash.'.'.$file_suffix );

    	$fid = 
        add_file( $filehash, $file_suffix, $adddir, $_FILES['up_file']['size'] );

    }
    add_position( 
        $fid, 
        $_SEEEION['uid'], 
        basename($_FILES['up_file']['name']), 
        $_POST['longitude'], 
        $_POST['latitude'],
        $_POST['height'], 
        $_POST['isstay'] 
        );
    mysql_close();
    echo $fid;
}else{
    echo -2;
}
if( $_FILES['up_file']['error'] ){
	echo $_FILES['up_file']['error'];
}
?>

<?

function get_file_suffix( $fn ){
	return substr(strrchr( $fn, '.'), 1);
}

function get_dir( $suffix, $fs ){
    global $fsize; 
    global $dirtree;
    //print_r($fsize);
    if( $suffix ){
        foreach( $dirtree as $k => $v ){
        	if( in_array( $suffix, $v ) ){
        		return $k.'/'.$suffix.'/';
        	}
        }
        foreach ( $fsize as $key => $vl ) {
        	if( $fs <= $key ){
                return 'others'.'/'.$vl.'/';
        	}
        }
        return 'others'.'/'.'s50toxM'.'/';
    }
    return 'documents/others/';
}

?>
