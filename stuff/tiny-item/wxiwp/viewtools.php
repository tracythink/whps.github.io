<?php
function get_weixinpress_option(){
    $array_weixinpress_option = array();
    $array_weixinpress_option[WXP_TOKEN] = get_option(WXP_TOKEN);
    $array_weixinpress_option[WXP_WELCOME] = get_option(WXP_WELCOME);
    $array_weixinpress_option[WXP_WELCOME_CMD] = get_option(WXP_WELCOME_CMD);
    $array_weixinpress_option[WXP_HELP] = get_option(WXP_HELP);
    $array_weixinpress_option[WXP_HELP_CMD] = get_option(WXP_HELP_CMD);
    $array_weixinpress_option[WXP_KEYWORD_LENGTH] = get_option(WXP_KEYWORD_LENGTH);
    $array_weixinpress_option[WXP_DEFAULT_ARTICLE_ACCOUNT] = get_option(WXP_DEFAULT_ARTICLE_ACCOUNT);
    $array_weixinpress_option[WXP_NEW_ARTICLE_CMD] = get_option(WXP_NEW_ARTICLE_CMD);
    $array_weixinpress_option[WXP_RAND_ARTICLE_CMD] = get_option(WXP_RAND_ARTICLE_CMD);
    $array_weixinpress_option[WXP_HOT_ARTICLE_CMD] = get_option(WXP_HOT_ARTICLE_CMD);
    $array_weixinpress_option[WXP_CMD_SEPERATOR] = get_option(WXP_CMD_SEPERATOR);
    $array_weixinpress_option[WXP_DEFAULT_THUMB] = get_option(WXP_DEFAULT_THUMB);
   return $array_weixinpress_option;
}

function update_weixinpress_option(){
    if($_POST['action']='保存设置'){
        update_option(WXP_TOKEN, $_POST['wxp-token']);
        update_option(WXP_WELCOME, $_POST['wxp-welcome']);
        update_option(WXP_WELCOME_CMD, $_POST['wxp-welcome-cmd']);
        update_option(WXP_HELP, $_POST['wxp-help']);
        update_option(WXP_HELP_CMD, $_POST['wxp-help-cmd']);
        update_option(WXP_KEYWORD_LENGTH, $_POST['wxp-keyword-length']);
        update_option(WXP_DEFAULT_ARTICLE_ACCOUNT, $_POST['wxp-default-article-account']);
        update_option(WXP_NEW_ARTICLE_CMD, $_POST['wxp-new-article-cmd']);
        update_option(WXP_RAND_ARTICLE_CMD, $_POST['wxp-rand-article-cmd']);
        update_option(WXP_HOT_ARTICLE_CMD, $_POST['wxp-hot-article-cmd']);
        update_option(WXP_CMD_SEPERATOR, $_POST['wxp-cmd-seperator']);
        update_option(WXP_DEFAULT_THUMB, $_POST['wxp-default-thumb']);
    }
    weixinpress_topbarmessage('恭喜，更新配置成功');

}

function weixinpress_topbarmessage($msg) {
     echo '<div class="updated fade" id="message"><p>' . $msg . '</p></div>';
}

function weixinpress_optionpage(){
    include_once('view.php');
}

?>