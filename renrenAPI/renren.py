#-*-coding:utf-8-*-

# 人人各种接口

import requests
import json
import re
import random
import time
from pyquery import PyQuery
from encrypt import encryptString
from config import *
from urllib import quote_plus
import os

class RenRen:

    def __init__(self, email=None, pwd=None):
        self.session = requests.Session()
        self.token = {}
        if email and pwd:
            self.login(email, pwd)
    # TODO cookie login will be less icode ?
    def login(self, email, pwd):
        key = self.getEncryptKey()

        if self.getShowCaptcha(email) == 1:
            fn = 'icode.%s.jpg' % os.getpid()
            self.getICode(fn)
            print "Please input the code in file '%s':" % fn
            icode = raw_input().strip()
            os.remove(fn)
        else:
            icode = ''

        data = {
            'email': email,
            'origURL': 'http://www.renren.com/SysHome.do',
            'icode': icode,
            'domain': 'renren.com',
            'key_id': 1,
            'captcha_type': 'web_login',
            'password': encryptString(key['e'], key['n'], pwd) if key['isEncrypt'] else pwd, # 卧槽直接发密码 ?
            'rkey': key['rkey']
        }
        print "login data: %s" % data
        url = 'http://www.renren.com/ajaxLogin/login?1=1&uniqueTimestamp=%f' % random.random()
        r = self.post(url, data)
        result = r.json()
        if result['code']:
            print 'login successfully'
            self.email = email
            r = self.get(result['homeUrl'])
            self.getToken(r.text)
        else:
            print 'login error', r.text

    def getICode(self, fn): # 验证码
        r = self.get("http://icode.renren.com/getcode.do?t=web_login&rnd=%s" % random.random())
        if r.status_code == 200 and r.raw.headers['content-type'] == 'image/jpeg':
            with open(fn, 'wb') as f:
                for chunk in r.iter_content():
                    f.write(chunk)
        else:
            print "get icode failure"

    def getShowCaptcha(self, email=None): # 向服务端请求是否要验证码
        r = self.post('http://www.renren.com/ajax/ShowCaptcha', data={'email': email})
        return r.json()

    def getEncryptKey(self): # 问服务器要公共密钥,每次都不一样来为密码做加密
        r = requests.get('http://login.renren.com/ajax/getEncryptKey')
        return r.json()

    def getToken(self, html=''): # 服务端的和用户共享的 token 确认身份
        rtk = re.compile("requestToken : '(.+)'")
        _rtk = re.compile("_rtk : '(\w+)'")

        if not html:
            r = self.get('http://www.renren.com')
            html = r.text

        self.token = {
            'requestToken': rtk.search(html).group(1),
            '_rtk': _rtk.search(html).group(1)
        }

    def request(self, url, method, data={}):
        if data:
            data.update(self.token)
        if method == 'get':
            return self.session.get(url, data=data)
        elif method == 'post':
            return self.session.post(url, data=data)

    def get(self, url, data={}):
        return self.request(url, 'get', data)

    def post(self, url, data={}):
        return self.request(url, 'post', data)

    def poStatus(self, said='what are you want to say ?'):
        data = {
            'requestToken': self.token['requestToken'],
            '_rtk': self.token['_rtk'],
            'channel': 'renren',
            'content': said
        }
        r= self.post('http://shell.renren.com/493699608/status', data)
        return r
    
    # TODO 未参数化
    # TODO only support one photo upload
    def poPhoto(self, filepath): 
        file = {
            'files[]': open(filepath, 'rb')
        }
        data = {
            'requestToken': self.token['requestToken'],
            '_rtk': self.token['_rtk']
        }
        url = 'http://upload.renren.com/upload.fcgi?pagetype=nphoto&hostid=%d&uploadid=%d' % (493699608, (int(time.time() * 1000)))
        r = self.session.post(url, files=file, data=data)
        rjson = r.json()
        if rjson['code'] == 0:
            photos = [{
                'images': rjson['files'][0]['images'],
                'id': 0,
                'filename': 'renren.png',
                'filesize': 90119,
                "width": 1425,
                "height": 1086,
                "title": "FUCK"
            }]
            data = {
                'async': 'true',
                'album.id': 1114365249,
                'requestToken': self.token['requestToken'],
                '_rtk': self.token['_rtk'],
                'photos': quote_plus(json.dumps(photos)),
                'uploadType': 1,
                'newAlbum': 'false',
                'sourceJson': '{"type":"v7","desc":"人人V7","url":"http://2014.renren.com/v7"}',
                'privacyParams': '{"sourceControl":"99"}',
                'withInfo': '%7B%22wpath%22%3A%5B%5D%7D',
                'noFeed': 'false',
                'coversMainUrl': '',
                'feedDesc': ' '
            }
            r = self.post('http://upload.renren.com/upload/493699608/finish_upload/v1.0', data)
        return r
        

if __name__ == '__main__':
    renren = RenRen(EMAIL, PASSWARD)
    print 'end...'

