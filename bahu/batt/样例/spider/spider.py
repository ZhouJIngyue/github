# import urllib.parse
# import urllib.request

# # params  CategoryId=808 CategoryType=SiteHome ItemListActionName=PostList PageIndex=3 ParentCategoryId=0 TotalPostCount=4000
# def getHtml(url,values):
#     user_agent='Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.82 Safari/537.36'
#     headers = {'User-Agent':user_agent}
#     data = urllib.parse.urlencode(values)
#     response_result = urllib.request.urlopen(url+'?'+data).read()
#     html = response_result.decode('utf-8')
#     return html

# #获取数据
# def requestCnblogs(index):
#     print('请求数据')
#     url = 'http://www.cnblogs.com/mvc/AggSite/PostList.aspx'
#     value= {
#          'CategoryId':808,
#          'CategoryType' : 'SiteHome',
#          'ItemListActionName' :'PostList',
#          'PageIndex' : index,
#          'ParentCategoryId' : 0,
#         'TotalPostCount' : 4000
#     }
#     result = getHtml(url,value)
#     return result

# print(requestCnblogs(0))



#coding=utf-8
import urllib.request
import urllib.parse
from bs4 import BeautifulSoup
import sys
import re

with open('data.txt','a') as f:
    key_word = []
    with open('key_word.txt','r') as kf:
        for line in kf:
            request = urllib.request.Request('http://www.baidu.com/s?wd='+urllib.parse.quote(line.strip().encode('gbk')))
            response = urllib.request.urlopen(request)
            soup = BeautifulSoup(response.read(),"html.parser")
            data = [re.sub(u'<[\d\D]*?>',' ',str(item)) for item in soup.select('div.result h3.t > a')]
            for item in data:
                f.writelines(''.join(item.strip().split())+'\n')