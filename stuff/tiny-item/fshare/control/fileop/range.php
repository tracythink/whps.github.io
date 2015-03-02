<?
/*
**
*/
require_once('../../model/config.php');
require_once('../../model/connectDB.php');
require_once('../../model/search.php');
/*
$_POST['longitude'] = 0.255;
$_POST['latitude'] = 0.55;
$_POST['height'] = 0.52;
$_POST['lrange'] = 0.1;
$_POST['hrange'] = 0.1;
*/

if(    is_float($_POST['longitude'])
	&& is_float($_POST['latitude']) 
	&& is_float($_POST['height'])
	&& is_float($_POST['lrange'])
	&& is_float($_POST['hrange']) 
  ){
   echo  	
   sch_range_file( $_POST['longitude'], $_POST['latitude'], $_POST['height'], $_POST['lrange'], $_POST['hrange'] );
}else{
	echo 'para loss';
}
/*
** check data is or not legal
** main todo
*/
function islegal(){
  
}

?>