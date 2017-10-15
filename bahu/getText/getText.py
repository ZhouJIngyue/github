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
			response = urllib.request.urlopen(request,timeout=10)
			html = response.read()
			html = html.decode('utf-8')
			word = re.findall(u"[\u4E00-\u9FA5]+",html)
			print(word)
		except:
			pass

if __name__ == '__main__':
	path = os.getcwd()
	files = os.listdir(path+'\\url')
	for file in files:
		if os.path.isfile('url\\'+file):
			with open('url\\'+file,'r',encoding = 'utf-8') as kf:
				threads = []
				for line in kf:
					print(line)
					t=getOnePage(line)
					t.start()
					threads.append(t)
				for t in threads:
					t.join()

	print('OK,SIR')