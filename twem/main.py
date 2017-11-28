import re
import operator as op
import matplotlib.pyplot as plt

#读文件
text=open('E:\\data\\semeval2018\\data\\tweetUS.txt.text','r',encoding='UTF-8')
lines=text.readlines()
#写切分的正则表达式
#regex=re.compile("(?x) (?: [\w-]+ | [\x80-\xff]{3} )") 
regex=re.compile("[\w-]+|[.@#!?]+")
dicto={} 
#处理文件内容
#i=0
for line in lines:
	#构造字典，参考网址http://www.jb51.net/article/31229.htm
	#按正则表达式进行切分
	#i+=1
	#if i>100:
	#	break
	words=regex.findall(line)
	#插入字典
	for word in words:
		if dicto.__contains__(word):
			dicto[word]+=1
		else:
			dicto[word]=1
dicto=sorted(dicto.items(),key=op.itemgetter(1),reverse=True)
y=[]
for dic in dicto:
	y.append(dic[1])
x=range(len(y))
plt.plot(x,y)
plt.show()