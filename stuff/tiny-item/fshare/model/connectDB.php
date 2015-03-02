<?

function connectDB(){
       $con = mysql_connect(HOST,USER,PWD);
       mysql_select_db(DB,$con);
       mysql_query("set names 'utf8'");
}

connectDB();

?>