import random as rd
import train as tr

#读入数据
inputsFile=open('E:\\data\\semeval2018\\data\\tweetUS.txt.text','r',encoding='UTF-8')
targetsFile=open('E:\\data\\semeval2018\\data\\tweetUS.txt.labels','r',encoding='UTF-8')
inputs=inputsFile.readlines()
targets=targetsFile.readlines()
#为使测试方便，截取一部分数据
# inputs=inputs[:100]
# targets=targets[:100]
#合并输入输出
allData=[]
for i in range(len(inputs)):
	allData.append([inputs[i],targets[i]])
#切分数据为训练集与测试集
allDatasize=len(allData)
trainSize=allDatasize/5*4
testSize=allDatasize-trainSize
trains=[]
tests=[]
while len(allData)>trainSize:
	i=rd.randrange(0,len(allData))
	tests.append(allData[i])
	allData.pop(i)
trains=allData
#训练模型
model=tr.train(trains)
print('训练完成.')
#评估模型
rightCount=0
for i in range(len(tests)):
	result=tr.use(model,tests[i][0])
	#print(result,int(tests[i][1]))
	if result==int(tests[i][1]):
		rightCount+=1
accuracy=rightCount/len(tests)
print(len(tests))
print(accuracy)