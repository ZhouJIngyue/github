import csv
import numpy as np

pastDay=10                 #每则数据包含过去多少天，等同于几维
nextDay=20                 #每则数据结果包含未来几天，等同于最后的建议持股时长
#读入训练数据表
data=[]
with open('E:\\data\\stoda\\train\\train.csv',newline='') as f:
	reader=csv.reader(f)
	for row in reader:
		data.append(row)


# data=data[1:]                 #去掉表头
# data=[d[12] for d in data]    #读取后复权价列
# data=[float(d) for d in data]                  #转浮点型
# for day in range(pastDay,len(data)-nextDay):
# 	#oneTrain=[d/data[day] for d in data[day-pastDay:day]]   #前pastDay天涨跌幅作为输入
# 	oneTrain=[data[i]/data[i+1] for i in range(day-pastDay,day-1)]   #前pastDay天涨跌幅作为输入
# 	oneTrain.append(data[day+nextDay]/data[day])     #后nextDay天涨跌幅作为输出
# 	train.append(oneTrain)
# print(train)