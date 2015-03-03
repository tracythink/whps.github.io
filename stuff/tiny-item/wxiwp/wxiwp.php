<?php
/*
Plugin Name: wxiwp
Plugin URI: http://
Description: funcs
Version: 2.0
Author: GHZ
Author URI: http://
*/
// key => name
define('WXP_TOKEN', 'wxp_token');
define('WXP_WELCOME', 'wxp_welcome');
define('WXP_WELCOME_CMD', 'wxp_welcome_cmd');
define('WXP_HELP', 'wxp_help');
define('WXP_HELP_CMD', 'wxp_help_cmd');
define('WXP_KEYWORD_LENGTH', 'wxp_keyword_length');
define('WXP_DEFAULT_ARTICLE_ACCOUNT', 'wxp_default_article_account');
define('WXP_NEW_ARTICLE_CMD', 'wxp_new_article_cmd');
define('WXP_RAND_ARTICLE_CMD', 'wxp_rand_article_cmd');
define('WXP_HOT_ARTICLE_CMD', 'wxp_hot_article_cmd');
define('WXP_CMD_SEPERATOR', 'wxp_cmd_seperator');
define('WXP_DEFAULT_THUMB', 'wxp_default_thumb');
// URL
$siteurl = get_option('siteurl');     
define('WXP_FOLDER', dirname(plugin_basename(__FILE__)));    
define('WXP_URL', $siteurl.'/wp-content/plugins/' . WXP_FOLDER);    
define('WXP_FILE_PATH', dirname(__FILE__));     
define('WXP_DIR_NAME', basename(WXP_FILE_PATH)); 
//定义微信 Token
$wxp_token = get_option(WXP_TOKEN, 'weixin');
define('WEIXIN_TOKEN', $wxp_token);
//定义默认缩略图
$wxp_thumb = get_option(WXP_DEFAULT_THUMB);
if(empty($wxp_thumb)){$wxp_thumb = WXP_URL.'/images/tb5.jpg';}
define('WEIXIN_DEFAULT', $wxp_thumb);

//添加插件的菜单     
add_action('admin_menu','weixinpress_menu');  

function weixinpress_menu() {      
    //下面的这个函数是Wordpress核心函数
    add_menu_page( 
        "wxiwp",
        "wxiwp", 
        8,
        __FILE__,
        "weixinpress_optionpage",   
        WXP_URL."/images/weixin.png"
    );
    //add_submenu_page(__FILE__,'网站列表','网站列表','8','list-site','pro_admin_list_site'); 
}   

/** view **/
include_once('view_tools.php');
/** view **/

/** class **/
include_once('class.php');
/** class **/

add_action('pre_get_posts', 'weixinpress_interface', 4);
function weixinpress_interface($wp_query){
    if(isset($_GET['weixinpress']) ){
        global $weixinpress;
        if(!isset($weixinpress)){
            $weixinpress = new weixinCallback();
            $weixinpress->valid();
            exit;
        }
    }
}


/*
if(!function_exists('get_post_excerpt')){

    function get_post_excerpt($post){
        $post_excerpt = strip_tags($post->post_excerpt); 
        if(!$post_excerpt){
            $post_excerpt = mb_substr(trim(strip_tags($post->post_content)),0,120);
        }
        return $post_excerpt;
    }
}

if(!function_exists('get_post_first_image')){

    function get_post_first_image($post_content){
        preg_match_all('|<img.*?src=[\'"](.*?)[\'"].*?>|i', $post_content, $matches);
        if($matches){
            return $matches[1][0];
        }else{
            return false;
        }
    }
}

if(!function_exists('search_orderby')){

    add_filter('posts_orderby_request', 'search_orderby');
    function search_orderby($orderby = ''){
        global $wpdb,$wp_query;

        $keyword = stripslashes($wp_query->query_vars[s]);

        if($keyword){ 

            $n = !empty($q['exact']) ? '' : '%';

            preg_match_all('/".*?("|$)|((?<=[\r\n\t ",+])|^)[^\r\n\t ",+]+/', $keyword, $matches);
            $search_terms = array_map('_search_terms_tidy', $matches[0]);

            $case_when = "0";

            foreach( (array) $search_terms as $term ){
                $term = esc_sql( like_escape( $term ) );

                $case_when .=" + (CASE WHEN {$wpdb->posts}.post_title LIKE '{$term}' THEN 3 ELSE 0 END) + (CASE WHEN {$wpdb->posts}.post_title LIKE '{$n}{$term}{$n}' THEN 2 ELSE 0 END) + (CASE WHEN {$wpdb->posts}.post_content LIKE '{$n}{$term}{$n}' THEN 1 ELSE 0 END)";
            }

            return "({$case_when}) DESC, {$wpdb->posts}.post_modified DESC";
        }else{
            return $orderby;
        }
    }
}
*/
?>