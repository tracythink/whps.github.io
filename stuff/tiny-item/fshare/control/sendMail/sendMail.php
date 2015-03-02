<?php 
require_once('class.phpmailer.php'); 
 
function sendMail( $recv, $subj, $body, $user ){
    $sendAddress = 'whypass630@163.com';
    $mail= new PHPMailer();  
    $mail->IsSMTP(); 
    $mail->Host = "smtp.163.com";                    //邮件服务器 
    $mail->SMTPDebug = 0; 
    $mail->SMTPAuth = true;                          //使用SMPT验证 
    $mail->Username = $sendAddress;                  //SMTP验证的用户名称 
    $mail->Password = 'a13579724969';  
    $mail->CharSet = "utf-8";                        //设置编码格式
    $mail->Subject = $subj;                          //设置主题
    $mail->SetFrom( $sendAddress, 'Fshare' );        //采用html格式发送邮件 
    $mail->MsgHTML( $body ); 
    $mail->AddAddress( $recv , $user );              //接受者邮件名称 
    
    if(!$mail->Send()){ 
        return $mail->ErrorInfo; 
    } 
    else{ 
        return "SUCCESS"; 
    }
}

/*  test code of function sendMail()

$body = "<a href='http://www.baidu.com'>baidu</a>";
$subj = 'phpmailer';

echo sendMail( 'deng52hmy@gmail.com', $subj, $body, "user" );

*/
?>