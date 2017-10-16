#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //字连接表大小
//#define FILE_COUNT 2729             //文件个数

//double fileRelation[FILE_COUNT][FILE_COUNT]={0};     //文件关联表.

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
	//对每个文件.

	for(int i=0;i<(int)files.size();i++)
	{
		ofstream out("E://data//bahu//relation//relation.txt",ios::app);
		cout<<i<<endl;
		//读入该文件.
		ifstream inb(files[i]);
		double sum1=0;
		double wordConnect1[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE];
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			for(int k=0;k<WORD_CONNECT_SIZE;k++)
			{
				inb>>wordConnect1[j][k];
				sum1+=wordConnect1[j][k];
			}
		}
		inb.close();
		//对所有文件
		for(int j=0;j<(int)files.size();j++)
		{
			fileRelation[i][j]=0;
			if(j<=i) //可省去一半运算量.
			{
				out<<fileRelation[i][j]<<" ";
				continue;
			}
			cout<<j<<" ";
			ifstream inb2(files[j]);
			double sum2=0;
			double wordConnect2[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE];
			for(int m=0;m<WORD_CONNECT_SIZE;m++)
			{
				for(int k=0;k<WORD_CONNECT_SIZE;k++)
				{
					inb2>>wordConnect2[m][k];
					sum2+=wordConnect2[m][k];
				}
			}
			inb2.close();
			//归一化后的差方和.
			for(int m=0;m<WORD_CONNECT_SIZE;m++)
			{
				for(int k=0;k<WORD_CONNECT_SIZE;k++)
				{
					fileRelation[i][j]+=
						(wordConnect1[m][k]/sum1-wordConnect2[m][k]/sum2)*
						(wordConnect1[m][k]/sum1-wordConnect2[m][k]/sum2);
				}
			}
			out<<fileRelation[i][j]<<" ";
		}
		cout<<endl;
		out<<endl;
		out.close();
	}
}
