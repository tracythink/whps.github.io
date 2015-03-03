<?php
if(isset($_POST['action'])){
    if($_POST['action']=='保存设置'){
        update_weixinpress_option();
    }
}
$array_weixinpress_option = get_weixinpress_option();
?>
<style type="text/css">
        h2{
            height:36px;
            line-height: 36px;
        }
        label{
            display: inline-block;
            font-weight: bold;
        }
        textarea{
            width:450px;
            height:80px;
        }
        input{
            width: 450px;
            height: 30px;
        }
        table{
            border: 0px solid #ececec;
        }
        tr{
            margin: 20px 0px;
        }
        .right{
            vertical-align: top;
            padding-top: 10px;
            width:100px;
            text-align: right;
        }
        .left{
            width: 500px;
            padding-left:50px;
            text-align: left;
        }
        .wxp-logo{
            background: url(<?php echo WXP_URL; ?>/images/weixin-big.png) 0px 0px no-repeat;
            background-size: 36px 36px;
            height: 36px;
            width: 36px;
            float: left;
        }
        .wxp-notes{
            margin: 10px 0px 30px 0px;
            display: inline-block;
            width: 450px;
        }
        .wxp-submit-btn{
            height: 30px;
            width: 150px;
            background-color: #21759b;
            font-weight: bold;
            color: #ffffff;
            font-family: "Microsoft YaHei";
        }
        .wxp-center{
            text-align: center;
        }
        .wxp-btn-box{
            margin: 15px 0px;
        }
        .wxp-option-main{
            margin: 5px 0px;
            width: 650px;
            float:left;
        }
        .wxp-option-sidebar{
            width: 100px;
            float:left;
        }
        .sidebar-box{
            border:1px solid #dfdfdf;
            width:200px;
            border-radius: 3px;
            box-shadow: inset 0 1px 0 #fff;
            background-color: #f5f5f5;
        }
        .sidebar-box h3{
            font-size: 15px;
            font-weight: bold;
            padding: 7px 10px;
            margin: 0;
            line-height: 1;
            background-color: #f1f1f1;
            border-bottom-color: #dfdfdf;
            text-shadow: #fff 0 1px 0;
            box-shadow: 0 1px 0 #fff;
        }
        .sidebar-box a{
            padding: 4px;
            display: block;
            padding-left: 25px;
            text-decoration: none;
            border: none;
        }


    </style>

    <div class="wxp-option-container">
        <div class="wxp-header">
            <div class="wxp-logo"></div>
            <h2>wxiwp设置</h2>
        </div>
        
        <div class="wxp-option-main">
            <form name="wxp-options" method="post" action="">
                <table cellpadding="0" cellspacing="0">
                    <tr>
                        <td class="right"><label>微信TOKEN：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-token" value="<?php echo $array_weixinpress_option[WXP_TOKEN]; ?>"/>
                            <span class="wxp-notes">填写用于微信接口的TOKEN，与微信后台设置一致</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>欢迎信息：</label></td>
                        <td class="left">
                            <textarea name="wxp-welcome"><?php echo $array_weixinpress_option[WXP_WELCOME]; ?></textarea>
                            <span class="wxp-notes">填写用于用户订阅时发送的欢迎信息</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>欢迎命令：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-welcome-cmd" value="<?php echo $array_weixinpress_option[WXP_WELCOME_CMD]; ?>"/>
                            <span class="wxp-notes">填写用于用户查询问候信息的命令，例如“hi”，“你好”</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>帮助信息：</label></td>
                        <td class="left">
                            <textarea name="wxp-help"><?php echo $array_weixinpress_option[WXP_HELP]; ?></textarea>
                            <span class="wxp-notes">填写用于用户寻求帮助时的帮助信息</span>
                        </td>
                    </tr>
                     <tr>
                        <td class="right"><label>帮助命令：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-help-cmd" value="<?php echo $array_weixinpress_option[WXP_HELP_CMD]; ?>"/>
                            <span class="wxp-notes">填写用于用户寻求帮助时命令，例如“帮助”、“help”，持多个命令，中间用空格隔开</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>关键字长度：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-keyword-length" value="<?php echo $array_weixinpress_option[WXP_KEYWORD_LENGTH]; ?>"/>
                            <span class="wxp-notes">填写用户输入的关键字长度限制，注意：单个中文字长度为2，单个英文字符或数字长度为1，例如“时间管理”长度填为8，“weixin”长度是6</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>默认文章数：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-default-article-account" value="<?php echo $array_weixinpress_option[WXP_DEFAULT_ARTICLE_ACCOUNT]; ?>"/>
                            <span class="wxp-notes">填写默认返回的文章数目，即用户不用命令分隔符指定返回数目时返回的文章数目，最大数为10</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>最新文章命令：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-new-article-cmd" value="<?php echo $array_weixinpress_option[WXP_NEW_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">填写用户查询最新文章的命令，持多个命令，中间用空格隔开</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>随机文章命令：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-rand-article-cmd" value="<?php echo $array_weixinpress_option[WXP_RAND_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">填写用户查询随机文章的命令，支持多个命令，中间用空格隔开</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>热门文章命令：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-hot-article-cmd" value="<?php echo $array_weixinpress_option[WXP_HOT_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">填写用户查询随机文章的命令，持多个命令，中间用空格隔开</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>命令分隔符：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-cmd-seperator" value="<?php echo $array_weixinpress_option[WXP_CMD_SEPERATOR]; ?>"/>
                            <span class="wxp-notes">填写命令分隔符，即支持使用类似“关键@6”的命令，其中“@”为命令分隔符，后面的数字为返回的文章数，最大为10</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>默认缩略图地址：</label></td>
                        <td class="left">
                            <input type="text" name="wxp-default-thumb" value="<?php echo $array_weixinpress_option[WXP_DEFAULT_THUMB]; ?>"/>
                            <span class="wxp-notes">填写默认缩略图地址，当文章中没有图片时，使用该地址代表的图片</span>
                        </td>
                    </tr>
                    <tr>
                        <td colspan="2" class="wxp-center wxp-btn-box">
                            <input type="submit" class="wxp-submit-btn" name="action" value="保存设置"/>
                        </td>
                    </tr>
                </table>
            </form>
        </div>
        <!--
        <div class="wxp-option-sidebar">
            <div class="sidebar-box">
                <h3>关于Weixinpress</h3>
                <a href="http://www.houqun.net" target="_blank">古侯子博客</a>
                <a href="http://www.houqun.net/articles/roll-out-weixinpress-plugin-for-wordpress.html" target="_blank">查看插件主页</a>
                <a href="http://www.houqun.net/articles/roll-out-weixinpress-plugin-for-wordpress.html" target="_blank">报告插件BUG</a>
                <a href="http://me.alipay.com/houqun" target="_blank">赞助本插件</a>
            </div>
        </div>
        -->
    </div>