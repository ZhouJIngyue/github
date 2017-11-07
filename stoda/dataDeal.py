import csv
import numpy as np
import os

#从上证指数表中读取时间列
date=[]
with open('E:\\data\\stoda\\index\\sh000001.csv',newline='') as f:
	reader=csv.reader(f)
	for row in reader:
		date.append(row)
date=date[1:]                 #去掉表头
date=[d[1] for d in date]     #读取时间列
date=date[1678:4093]          #选取指定时间列

rootDir='E:\\data\\stoda\\original'
for parent,dirNames,fileNames in os.walk(rootDir):
	for fileName in fileNames:
		dateData,data=[],[]           #按指定时间列排列好的数据，原始数据
		with open(os.path.join(parent,fileName),newline='') as f:
			reader=csv.reader(f)
			for row in reader:
				data.append(row)
		data=data[1:]                 #去掉表头
		oriDate=[d[1] for d in data]     #读取时间列
		oriData=[d[12] for d in data]    #读取后复权价列
		dateData.append(data[0][0])      #写入股票代码
		print(dateData)
		for i in range(len(date)):
			dateData.append(-1.0)        #初始化为全-1
		for i in range(len(date)):
			if date[i] in oriDate:       #将后复权价填入各交易日时间
				dateData[i+1]=float(oriData[oriDate.index(date[i])])
		with open('E:\\data\\stoda\\train\\train.csv','a',newline='') as dataCsv:
			writer=csv.writer(dataCsv)
			writer.writerow(dateData)
