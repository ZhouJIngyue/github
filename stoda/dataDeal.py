import csv
import numpy as np

#从上证指数表中读取时间列
date=[]
with open('E:\\data\\stoda\\index\\sh000001.csv',newline='') as f:
	reader=csv.reader(f)
	for row in reader:
		date.append(row)
date=date[1:]                 #去掉表头
date=[d[1] for d in date]     #读取时间列
date=date[1678:4093]          #选取指定时间列
allData=[]

dateData,data=[],[]           #按指定时间列排列好的数据，原始数据
with open('E:\\data\\stoda\\original\\sh600519.csv',newline='') as f:
	reader=csv.reader(f)
	for row in reader:
		data.append(row)
data=data[1:]                 #去掉表头
oriDate=[d[1] for d in data]     #读取时间列
oriData=[d[12] for d in data]    #读取后复权价列
for i in range(len(date)):
	dateData.append(-1.0)
for i in range(len(date)):
	if date[i] in oriDate:
		dateData[i]=float(oriData[oriDate.index(date[i])])
allData.append(dateData)
print(allData)

# j=0
# for i in range(0,len(date)):
# 	while j<len(data):
# 		if data[j][0]==date[i]:break
# 	if 


# import csv

# pastDay=10                 #每则数据包含过去多少天，等同于几维
# nextDay=20                 #每则数据结果包含未来几天，等同于最后的建议持股时长
# data,train=[],[]
# with open('E:\\data\\stoda\\original\\sh600519.csv',newline='') as f:
# 	reader=csv.reader(f)
# 	for row in reader:
# 		data.append(row)
# data=data[1:]                 #去掉表头
# data=[d[12] for d in data]    #读取后复权价列
# data=[float(d) for d in data]                  #转浮点型
# for day in range(pastDay,len(data)-nextDay):
# 	#oneTrain=[d/data[day] for d in data[day-pastDay:day]]   #前pastDay天涨跌幅作为输入
# 	oneTrain=[data[i]/data[i+1] for i in range(day-pastDay,day-1)]   #前pastDay天涨跌幅作为输入
# 	oneTrain.append(data[day+nextDay]/data[day])     #后nextDay天涨跌幅作为输出
# 	train.append(oneTrain)
# print(train)