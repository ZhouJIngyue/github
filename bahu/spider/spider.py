#coding=utf-8
import urllib.request
import urllib.parse
from bs4 import BeautifulSoup
import sys
import re
from threading import Thread
import os


class getOnePage(Thread):
    def __init__(self,name):
        super().__init__()
        self.name=name
    def run(self):
	    try:
	        request = urllib.request.Request(self.name)
	        response = urllib.request.urlopen(request,timeout=150)
	        soup = BeautifulSoup(response.read(),"html.parser")
	        urls = soup.find_all(name='a',attrs={'href':re.compile(('.'))})
	        #抓取百度搜索结果中的a标签，其中href是包含了百度的跳转地址
	        for i in urls:
	            if 'www.baidu.com/link?url=' in i['href']:
	                request = urllib.request.Request(i['href'])
	                a = urllib.request.urlopen(request,timeout=15)
	                #对跳转地址进行一次访问，返回访问的url就能得到我们需要抓取的url结果了
	                #if a.status_code == 200:
	                #print a.url
	                with open(line.strip()+'.txt','r') as f:
	                    if a.url not in f.read():
	                        f = open(line.strip()+'.txt','a')
	                        f.write(a.url+'\n')
	                        f.close()
	    except:
	        pass

if __name__ == '__main__':
	key_word = []
	with open('key_word.txt','r') as kf:
		for line in kf:
			print(line.strip())
			if os.path.exists(line.strip()+'.txt'):
				continue
			else:
				threads = []
				f = open(line.strip()+'.txt','w')
				f.close()
				for j in range(0,760,10):
					t=getOnePage('http://www.baidu.com/s?wd='+urllib.parse.quote(line.strip().encode('gbk'))+'&pn='+str(j))
					t.start()
					threads.append(t)
				for t in threads:
					t.join()

	print('OK,SIR')