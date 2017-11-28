import csv
import numpy as np
import random as rd

pastDay=20                 #每则数据包含过去多少天，等同于几维
nextDay=5                  #每则数据结果包含未来几天，等同于最后的建议持股时长
#读入训练数据表
allData=[]
with open('E:\\data\\stoda\\train\\train.csv',newline='') as f:
	reader=csv.reader(f)
	for row in reader:
		allData.append(row)
#构建网络
N=20000       #单次输入数据行数
D=pastDay    #输入维数
K=5          #输出维数
h=1000        #隐藏层节点个数
W=0.01*np.random.randn(D,h)   #隐藏层输入权重
b=np.zeros((1,h))             #隐藏层输入偏置
W2=0.01*np.random.randn(h,K)  #隐藏层输出权重
b2=np.zeros((1,K))            #隐藏层输出偏置
stepSize=1e-0      #梯度下降步长
reg=1e-5           #权重矩阵控制系数，防过拟合

#截取数据
def getData():
	while True:
		useStock=rd.randrange(0,len(allData))                      #随机选股
		startDay=rd.randrange(1,len(allData[0])-pastDay-nextDay)   #随机选日期
		#若该段时间内有数据缺失，丢弃
		if('-1.0' in allData[useStock][startDay:startDay+pastDay+nextDay]):    
			continue
		oneData=[float(allData[useStock][i])/float(allData[useStock][i+1])  \
		for i in range(startDay,startDay+pastDay)]    #前pastDay天涨跌幅作为输入
		oneData.append(float(allData[useStock][startDay+pastDay+nextDay])/ \
		float(allData[useStock][startDay+pastDay]))   #后nextDay天涨跌幅作为输出
		return oneData

#训练，详见http://cs231n.github.io/neural-networks-case-study/
for i in range(10000000):
	#1.获取训练数据
	trainData=[]
	for j in range(N):
		trainData.append(getData())
	trainData=np.array(trainData)
	#从数据中截出输入与输出，前pastDay列为输入，最后一列为输出，详见getData
	X=trainData.T[:len(trainData[0])-1].T
	YData=trainData.T[len(trainData[0])-1:].T
	#对输出分类
	#用分类而不用回归，详见http://cs231n.github.io/neural-networks-2/#losses
	Y=np.zeros(N,dtype='uint8')   #输出，数据类型为无符号整型，取值为0-(K-1)，存放所属类别
	#根据nextDay日后涨跌对输出赋值
	for j in range(len(YData)):
		if YData[j]>1.1:
			Y[j]=4
			continue
		if YData[j]>1.03:
			Y[j]=3
			continue
		if YData[j]>0.97:
			Y[j]=2
			continue
		if YData[j]>0.9:
			Y[j]=1
			continue
		Y[j]=0
	#------------------------------------------------------------------
	#伪造数据，验证网络的基本分类能力
	# for j in range(N):
	# 	a=rd.random()
	# 	for k in range(pastDay):
	# 		if(a<0.2):
	# 			X[j][k]=rd.uniform(0.3,0.5)
	# 			Y[j]=0
	# 			continue
	# 		if(a<0.4):
	# 			X[j][k]=rd.uniform(0.5,0.9)
	# 			Y[j]=1
	# 			continue
	# 		if(a<0.6):
	# 			X[j][k]=rd.uniform(0.9,1.1)
	# 			Y[j]=2
	# 			continue
	# 		if(a<0.8):
	# 			X[j][k]=rd.uniform(1.1,1.3)
	# 			Y[j]=3
	# 			continue
	# 		X[j][k]=rd.uniform(1.3,1.7)
	# 		Y[j]=4
	#------------------------------------------------------------------
	#2.前向传播
	#激活函数为ReLU，详见http://cs231n.github.io/neural-networks-1/#actfun
	hiddenLayer=np.maximum(0,np.dot(X,W)+b)   #计算隐藏层输入
	scores=np.dot(hiddenLayer,W2)+b2          #计算隐藏层输出
	#损失函数使用softmax，详见http://cs231n.github.io/linear-classify/#softmax
	#计算各类别概率
	expScores=np.exp(scores)                                #求指数，为了消除正负号
	probs=expScores/np.sum(expScores,axis=1,keepdims=True)  #计算概率，其实就是归一化，概率和为1
	#计算损失
	correctLogprobs=-np.log(probs[range(N),Y])  #计算预测分布与真实分布的交叉熵，交叉熵定义详见http://colah.github.io/posts/2015-09-Visual-Information/
	dataLoss=np.sum(correctLogprobs)/N          #N个样本预测分布与真实分布的平均交叉熵
	regLoss=0.5*reg*np.sum(W*W)+0.5*reg*np.sum(W2*W2)    #规范化损失，使权重偏好小值，有消除权重取值模糊性，提高泛化性等好处，详见http://cs231n.github.io/linear-classify/#svm
	loss=dataLoss+regLoss                       #总损失为交叉熵与规范化损失两者之和
	#结果展示
	if(i%100==0):
		#输出损失
		print('迭代了%d次：损失为%f'%(i,loss))
		#输出分类准确率
		result=np.argmax(probs,axis=1)
		sameCount=0
		for j in range(N):
			if(result[j]==Y[j]):
				sameCount+=1
		print('准确率为%f'%(sameCount/N))
		#输出预测分布与实际分布
		together=np.vstack((result,Y))
		print(together)
		print('------------------------------------------------------------------------')
	#3.反向传播
	#计算输出结果的梯度
	dScores=probs             #损失correctLogprobs对隐藏层输出的导数，详细推导见http://www.jianshu.com/p/ffa51250ba2e
	dScores[range(N),Y]-=1    #以及http://cs231n.github.io/neural-networks-case-study/#grad
	dScores/=N
	#将梯度反向传播给参数
	#先传播给W2，b2
	dW2=np.dot(hiddenLayer.T,dScores)          #通过链式法则反向传播
	db2=np.sum(dScores,axis=0,keepdims=True)   #详见http://cs231n.github.io/neural-networks-case-study/#grad
	#再传播给隐藏层
	dHidden=np.dot(dScores,W2.T)               #为了求损失correctLogprobs对参数W的导数，继续反向传播
	#通过ReLU函数
	dHidden[hiddenLayer<=0]=0                  #详见http://cs231n.github.io/neural-networks-case-study/#net
	#最后到W，b
	dW=np.dot(X.T,dHidden)
	db=np.sum(dHidden,axis=0,keepdims=True)
	#加上规范化损失的梯度
	dW2+=reg*W2         #0.5*reg*np.sum(W2*W2)对W2求导
	dW+=reg*W
	#进行梯度更新
	W+=-stepSize*dW
	b+=-stepSize*db
	W2+=-stepSize*dW2
	b2+=-stepSize*db2