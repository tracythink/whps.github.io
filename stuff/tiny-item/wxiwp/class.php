<?php
class weixinCallback
{
    private $items = '';
    private $articleCount = 0;
    private $keyword = '';
    private $arg = '';

    public function valid()
    {
        if(isset($_GET['debug'])){
            $this->keyword = $_GET['t'];
            $this->responseMsg();
        }

        $echoStr = $_GET['echostr'];

        //valid signature , option
        if($this->checkSignature() || 1){
            echo $echoStr;
            $this->responseMsg();
            
            exit;
        }
    }

    public function responseMsg()
    {
        //get post data, May be due to the different environments
        $postStr = $GLOBALS['HTTP_RAW_POST_DATA'];

        $array_weixinpress_option = get_weixinpress_option();
        $array_weixinpress_welcome_cmd = explode(' ', $array_weixinpress_option[WXP_WELCOME_CMD]);
        $array_weixinpress_help_cmd = explode(' ', $array_weixinpress_option[WXP_HELP_CMD]);
        $array_weixinpress_new_cmd = explode(' ', $array_weixinpress_option[WXP_NEW_ARTICLE_CMD]);
        $array_weixinpress_rand_cmd = explode(' ', $array_weixinpress_option[WXP_RAND_ARTICLE_CMD]);
        $array_weixinpress_hot_cmd = explode(' ', $array_weixinpress_option[WXP_HOT_ARTICLE_CMD]);
        $wxp_keyword_length = $array_weixinpress_option[WXP_KEYWORD_LENGTH];
        $wxp_cmd_seperator = $array_weixinpress_option[WXP_CMD_SEPERATOR];

        //extract post data
        if (isset($_GET['debug']) || !empty($postStr)){    
            if(!isset($_GET['debug'])){
                $postObj = simplexml_load_string($postStr, 'SimpleXMLElement', LIBXML_NOCDATA);
                $fromUsername = $postObj->FromUserName;
                $toUsername = $postObj->ToUserName;
                $msgType = strtolower(trim($postObj->MsgType));
                if($msgType == 'event'){
                    $keywords = strtolower(trim($postObj->Event));
                }else{
                    $keywords = strtolower(trim($postObj->Content));
                }

                //add by HQ
                $keywordArray = explode($wxp_cmd_seperator, $keywords, 2);
                if(is_array($keywordArray)){
                    $this->keyword = $keywordArray[0];
                    $this->arg = $keywordArray[1];
                } else {
                    $this->keyword = $keywordArray;
                }


            }

            $time = time();
            $textTpl = '<xml>
                        <ToUserName><![CDATA[%s]]></ToUserName>
                        <FromUserName><![CDATA[%s]]></FromUserName>
                        <CreateTime>%d</CreateTime>
                        <MsgType><![CDATA[text]]></MsgType>
                        <Content><![CDATA[%s]]></Content>
                        <FuncFlag>0</FuncFlag>
                        </xml>';     
            $picTpl = ' <xml>
                        <ToUserName><![CDATA[%s]]></ToUserName>
                        <FromUserName><![CDATA[%s]]></FromUserName>
                        <CreateTime>%d</CreateTime>
                        <MsgType><![CDATA[news]]></MsgType>
                        <Content><![CDATA[]]></Content>
                        <ArticleCount>%d</ArticleCount>
                        <Articles>
                        %s
                        </Articles>
                        <FuncFlag>1</FuncFlag>
                        </xml>';
            /*            
            if($this->arg=='古侯子'){
                $fromUsername = 'o4hGYjlfXp2tkPnqVCIiqudQHsnU';
                $textMsg = '<xml>
                        <ToUserName><![CDATA['.$fromUsername.']]></ToUserName>
                        <FromUserName><![CDATA['.$toUsername.']]></FromUserName>
                        <CreateTime>'.$time.'</CreateTime>
                        <MsgType><![CDATA[text]]></MsgType>
                        <Content><![CDATA['.$this->keyword.']]></Content>
                        <FuncFlag>0</FuncFlag>
                        </xml>'; 
                echo $textMsg;
                exit;
            }
            */
            $weixin_custom_keywords = apply_filters('weixin_custom_keywords',array());

            if(in_array($this->keyword, $weixin_custom_keywords)){
                do_action('weinxinpress',$this->keyword,$textTpl, $picTpl);
            //}elseif($this->keyword == 'hi' || $this->keyword == 'hello'  || $this->keyword == '好'  || $this->keyword == '您好'  || $this->keyword == '你好' || $this->keyword == 'subscribe' ){
            }elseif(in_array($this->keyword, $array_weixinpress_welcome_cmd) || $this->keyword == 'subscribe' ){
                // welcome
                $weixin_welcome = $array_weixinpress_option[WXP_WELCOME];
                $weixin_welcome = apply_filters('weixin_welcome',$weixin_welcome);
                echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_welcome);
            }elseif(in_array($this->keyword, $array_weixinpress_help_cmd) ){
                // give help at the same time
                $weixin_help = $array_weixinpress_option[WXP_HELP];
                $weixin_help = apply_filters('weixin_help',$weixin_help);
                echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_help);
            }elseif(in_array($this->keyword, $array_weixinpress_new_cmd)){
                $this->query('new');
                if($this->articleCount == 0){
                        $weixin_not_found = "抱歉，最新文章显示错误，请重试一下 :-) ";
                        $weixin_not_found = apply_filters('weixin_not_found', $weixin_not_found, $this->keyword);
                        echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_not_found);
                    }else{
                        echo sprintf($picTpl, $fromUsername, $toUsername, $time, $this->articleCount,$this->items);
                }
            }elseif(in_array($this->keyword, $array_weixinpress_rand_cmd)){
                $this->query('rand');
                if($this->articleCount == 0){
                        $weixin_not_found = "抱歉，随机文章显示错误，请重试一下 :-) ";
                        $weixin_not_found = apply_filters('weixin_not_found', $weixin_not_found, $this->keyword);
                        echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_not_found);
                    }else{
                        echo sprintf($picTpl, $fromUsername, $toUsername, $time, $this->articleCount,$this->items);
                }
            }elseif(in_array($this->keyword, $array_weixinpress_hot_cmd)){
                $this->query('hot');
                if($this->articleCount == 0){
                        $weixin_not_found = "抱歉，随机文章显示错误，请重试一下 :-) ";
                        $weixin_not_found = apply_filters('weixin_not_found', $weixin_not_found, $this->keyword);
                        echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_not_found);
                    }else{
                        echo sprintf($picTpl, $fromUsername, $toUsername, $time, $this->articleCount,$this->items);
                }
            }else {
                /*
                $keyword_length = mb_strwidth(preg_replace('/[\x00-\x7F]/','',$this->keyword),'utf-8')+str_word_count($this->keyword)*2;

                $weixin_keyword_allow_length = $wxp_keyword_length;
                $weixin_keyword_allow_length = apply_filters('weixin_keyword_allow_length',$weixin_keyword_allow_length);
        
                if($keyword_length > $weixin_keyword_allow_length){
                    $weixin_keyword_too_long = '输入的关键字太长，换个稍短的关键字试下？';
                    $weixin_keyword_too_long = apply_filters('weixin_keywords_too_long',$weixin_keyword_too_long);
                    echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_keyword_too_long);
                }elseif( !empty( $this->keyword )){
                */
                    $this->query();
                    if($this->articleCount == 0){
                        $weixin_not_found = "抱歉，没有找到与【{$this->keyword}】相关的文章，换个关键字，可能就有结果了哦 :-) ";
                        $weixin_not_found = apply_filters('weixin_not_found', $weixin_not_found, $this->keyword);
                        echo sprintf($textTpl, $fromUsername, $toUsername, $time, $weixin_not_found);
                    }else{
                        echo sprintf($picTpl, $fromUsername, $toUsername, $time, $this->articleCount,$this->items);
                    }
                //}
            }
        }else {
            echo "";
            exit;
        }
    }

    private function query($queryArg = NULL){
        global $wp_query;

        $queryKeyword = $this->keyword;

        $weixin_count = get_option(WXP_DEFAULT_ARTICLE_ACCOUNT);
        
        if(!empty($this->arg) && preg_match("/^\d*$/",$this->arg)) { // if the arg is a number or not, is_numeric($fgid)
            $weixin_count = $this->arg;
        } else {
            $queryKeyword = $this->keyword.' '.$this->arg;
            $this->keyword = $this->keyword.'@'.$this->arg;
        }
        


        $weixin_count = apply_filters('weixin_count',$weixin_count);

        switch ($queryArg) {
            case 'new':
                $weixin_query_array = array('showposts' => $weixin_count , 'post_status' => 'publish' );
                break;
            case 'rand':
                $weixin_query_array = array('orderby' => 'rand', 'posts_per_page' => $weixin_count , 'post_status' => 'publish' );
                break;
             case 'hot':
                $weixin_query_array = array('orderby' => 'meta_value_num', 'meta_key'=>'views', 'order'=>'DESC', 'posts_per_page' => $weixin_count , 'post_status' => 'publish' );
                break;
            default:
                $weixin_query_array = array('s' => $queryKeyword, 'posts_per_page' => $weixin_count , 'post_status' => 'publish' );
                break;
        }

        
        $weixin_query_array = apply_filters('weixin_query',$weixin_query_array);

        $wp_query->query($weixin_query_array);

        if(have_posts()){
            while (have_posts()) {
                the_post();

                global $post;

                $title =get_the_title(); 
                $excerpt = 'excpt';//get_post_excerpt($post);

                $thumbnail_id = get_post_thumbnail_id($post->ID);
                if($thumbnail_id ){
                    $thumb = wp_get_attachment_image_src($thumbnail_id, 'thumbnail');
                    $thumb = $thumb[0];
                }else{
                    $thumb = 'thumb';//get_post_first_image($post->post_content);
                }

                if(!$thumb && WEIXIN_DEFAULT){
                    $thumb = WEIXIN_DEFAULT;
                }

                $link = get_permalink();

                $items = $items . $this->get_item($title, $excerpt, $thumb, $link);

            }
        }

        $this->articleCount = count($wp_query->posts);
        if($this->articleCount > $weixin_count) $this->articleCount = $weixin_count;

        $this->items = $items;
    }

    public function get_item($title, $description, $picUrl, $url){
        //if(!$description) $description = $title;

        return
        '
        <item>
            <Title><![CDATA['.$title.']]></Title>
            <Discription><![CDATA['.$description.']]></Discription>
            <PicUrl><![CDATA['.$picUrl.']]></PicUrl>
            <Url><![CDATA['.$url.']]></Url>
        </item>
        ';
    }

    private function checkSignature()
    {
        $signature = $_GET["signature"];
        $timestamp = $_GET["timestamp"];
        $nonce = $_GET["nonce"];
                
        $weixin_token = apply_filters('weixin_token',WEIXIN_TOKEN);
        if(isset($_GET['debug'])){
            echo "\n".'WEIXIN_TOKEN：'.$weixin_token;
        }
        $tmpArr = array($weixin_token, $timestamp, $nonce);
        sort($tmpArr, SORT_STRING);
        $tmpStr = implode( $tmpArr );
        $tmpStr = sha1( $tmpStr );
        
        if( $tmpStr == $signature ){
            return true;
        }else{
            return false;
        }
    }
}
?>