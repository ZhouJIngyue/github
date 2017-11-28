import numpy as np
import re

def train(data):
	#写切分的正则表达式
	regex=re.compile("[\w-]+|[.@#!?]+")  #切分出英文单词以及标点符号
	dicto={} 
	#统计文本中出现各词并归属于各类别的次数
	for oneData in data:
		target=int(oneData[1])
		#构造字典，参考网址http://www.jb51.net/article/31229.htm
		#按正则表达式进行切分
		words=regex.findall(oneData[0])
		#插入字典
		for word in words:
			if not dicto.__contains__(word):
				dicto[word]=[0]*20  #共二十类表情
			dicto[word][target]+=1  #该单词属于该类的次数加1
	#计算出现各词后归属于各类的概率
	model=dicto
	for i in model:
		model[i]=np.array(model[i])
		#Pij=(包含词i且属于类别j的文本条数+1)/(包含词i的文本条数+类别数)
		wordSum=sum(model[i])+20   #包含词i的文本条数+类别数
		model[i]=(model[i]+1)/wordSum
	return model

def use(model,input):
	scores=np.array([1]*20)
	regex=re.compile("[\w-]+|[.@#!?]+")  #切分出英文单词以及标点符号
	#按正则表达式进行切分
	words=regex.findall(input)
	#根据包含的词计算属于各类别的概率
	for word in words:
		if model.__contains__(word):
			scores=scores*model[word]
	scores=scores.tolist()
	return scores.index(max(scores))

	