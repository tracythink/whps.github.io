<?php
if(isset($_POST['action'])){
    if($_POST['action']=='��������'){
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
            <h2>wxiwp����</h2>
        </div>
        
        <div class="wxp-option-main">
            <form name="wxp-options" method="post" action="">
                <table cellpadding="0" cellspacing="0">
                    <tr>
                        <td class="right"><label>΢��TOKEN��</label></td>
                        <td class="left">
                            <input type="text" name="wxp-token" value="<?php echo $array_weixinpress_option[WXP_TOKEN]; ?>"/>
                            <span class="wxp-notes">��д����΢�Žӿڵ�TOKEN����΢�ź�̨����һ��</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>��ӭ��Ϣ��</label></td>
                        <td class="left">
                            <textarea name="wxp-welcome"><?php echo $array_weixinpress_option[WXP_WELCOME]; ?></textarea>
                            <span class="wxp-notes">��д�����û�����ʱ���͵Ļ�ӭ��Ϣ</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>��ӭ���</label></td>
                        <td class="left">
                            <input type="text" name="wxp-welcome-cmd" value="<?php echo $array_weixinpress_option[WXP_WELCOME_CMD]; ?>"/>
                            <span class="wxp-notes">��д�����û���ѯ�ʺ���Ϣ��������硰hi��������á�</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>������Ϣ��</label></td>
                        <td class="left">
                            <textarea name="wxp-help"><?php echo $array_weixinpress_option[WXP_HELP]; ?></textarea>
                            <span class="wxp-notes">��д�����û�Ѱ�����ʱ�İ�����Ϣ</span>
                        </td>
                    </tr>
                     <tr>
                        <td class="right"><label>�������</label></td>
                        <td class="left">
                            <input type="text" name="wxp-help-cmd" value="<?php echo $array_weixinpress_option[WXP_HELP_CMD]; ?>"/>
                            <span class="wxp-notes">��д�����û�Ѱ�����ʱ������硰����������help�����ֶ������м��ÿո����</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>�ؼ��ֳ��ȣ�</label></td>
                        <td class="left">
                            <input type="text" name="wxp-keyword-length" value="<?php echo $array_weixinpress_option[WXP_KEYWORD_LENGTH]; ?>"/>
                            <span class="wxp-notes">��д�û�����Ĺؼ��ֳ������ƣ�ע�⣺���������ֳ���Ϊ2������Ӣ���ַ������ֳ���Ϊ1�����硰ʱ�����������Ϊ8����weixin��������6</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>Ĭ����������</label></td>
                        <td class="left">
                            <input type="text" name="wxp-default-article-account" value="<?php echo $array_weixinpress_option[WXP_DEFAULT_ARTICLE_ACCOUNT]; ?>"/>
                            <span class="wxp-notes">��дĬ�Ϸ��ص�������Ŀ�����û���������ָ���ָ��������Ŀʱ���ص�������Ŀ�������Ϊ10</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>�����������</label></td>
                        <td class="left">
                            <input type="text" name="wxp-new-article-cmd" value="<?php echo $array_weixinpress_option[WXP_NEW_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">��д�û���ѯ�������µ�����ֶ������м��ÿո����</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>����������</label></td>
                        <td class="left">
                            <input type="text" name="wxp-rand-article-cmd" value="<?php echo $array_weixinpress_option[WXP_RAND_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">��д�û���ѯ������µ����֧�ֶ������м��ÿո����</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>�����������</label></td>
                        <td class="left">
                            <input type="text" name="wxp-hot-article-cmd" value="<?php echo $array_weixinpress_option[WXP_HOT_ARTICLE_CMD]; ?>"/>
                            <span class="wxp-notes">��д�û���ѯ������µ�����ֶ������м��ÿո����</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>����ָ�����</label></td>
                        <td class="left">
                            <input type="text" name="wxp-cmd-seperator" value="<?php echo $array_weixinpress_option[WXP_CMD_SEPERATOR]; ?>"/>
                            <span class="wxp-notes">��д����ָ�������֧��ʹ�����ơ��ؼ�@6����������С�@��Ϊ����ָ��������������Ϊ���ص������������Ϊ10</span>
                        </td>
                    </tr>
                    <tr>
                        <td class="right"><label>Ĭ������ͼ��ַ��</label></td>
                        <td class="left">
                            <input type="text" name="wxp-default-thumb" value="<?php echo $array_weixinpress_option[WXP_DEFAULT_THUMB]; ?>"/>
                            <span class="wxp-notes">��дĬ������ͼ��ַ����������û��ͼƬʱ��ʹ�øõ�ַ�����ͼƬ</span>
                        </td>
                    </tr>
                    <tr>
                        <td colspan="2" class="wxp-center wxp-btn-box">
                            <input type="submit" class="wxp-submit-btn" name="action" value="��������"/>
                        </td>
                    </tr>
                </table>
            </form>
        </div>
        <!--
        <div class="wxp-option-sidebar">
            <div class="sidebar-box">
                <h3>����Weixinpress</h3>
                <a href="http://www.houqun.net" target="_blank">�ź��Ӳ���</a>
                <a href="http://www.houqun.net/articles/roll-out-weixinpress-plugin-for-wordpress.html" target="_blank">�鿴�����ҳ</a>
                <a href="http://www.houqun.net/articles/roll-out-weixinpress-plugin-for-wordpress.html" target="_blank">������BUG</a>
                <a href="http://me.alipay.com/houqun" target="_blank">���������</a>
            </div>
        </div>
        -->
    </div>