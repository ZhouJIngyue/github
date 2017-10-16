#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //字连接表大小

void main()
{
	//读入所有关键字.
	vector<string> files;
	string s;
	ifstream ink("E://data//bahu//key//key_word.txt");
	while(ink>>s)
		files.push_back("E://data//bahu//brain//"+s+".txt");
	ink.close();
	//建立文件关联表.
	double **fileRelation;
	fileRelation=new double*[files.size()];
	for(int i=0;i<(int)files.size();i++)
		fileRelation[i]=new double[files.size()];
	//创建所有文件文字连接表.
	double *sum;
	double ***wordConnect;
	sum=new double[files.size()];
	wordConnect=new double**[files.size()];
	cout<<"正在读取文件.";
	for(int i=0;i<(int)files.size();i++)
	{
		wordConnect[i]=new double*[WORD_CONNECT_SIZE];
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			wordConnect[i][j]=new double[WORD_CONNECT_SIZE];
		}
	}
	//读取所有文件.
	for(int i=0;i<(int)files.size();i++)
	{
		cout<<i<<" ";
		ifstream in(files[i]);
		sum[i]=0;
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			for(int k=0;k<WORD_CONNECT_SIZE;k++)
			{
				in>>wordConnect[i][j][k];
				sum[i]+=wordConnect[i][j][k];
			}
		}
		in.close();
	}
	cout<<"读取文件完毕.";
	//对每个文件.
	for(int i=0;i<(int)files.size();i++)
	{
		ofstream out("E://data//bahu//relation//relation.txt",ios::app);
		cout<<i<<endl;
		//对所有文件
		for(int j=0;j<(int)files.size();j++)
		{
			fileRelation[i][j]=0;
			//if(j<=i) //可省去一半运算量.
			//{
			//	out<<fileRelation[i][j]<<" ";
			//	continue;
			//}
			//归一化后的差方和.
			for(int m=0;m<WORD_CONNECT_SIZE;m++)
			{
				for(int k=0;k<WORD_CONNECT_SIZE;k++)
				{
					fileRelation[i][j]+=
						(wordConnect[i][m][k]/sum[i]-wordConnect[j][m][k]/sum[j])*
						(wordConnect[i][m][k]/sum[i]-wordConnect[j][m][k]/sum[j]);
				}
			}
			out<<fileRelation[i][j]<<" ";
		}
		out<<endl;
		out.close();
	}
}
