#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //�����ӱ��С

void main()
{
	//�������йؼ���.
	vector<string> files;
	string s;
	ifstream ink("E://data//bahu//key//key_word.txt");
	while(ink>>s)
		files.push_back("E://data//bahu//brain//"+s+".txt");
	ink.close();
	//�����ļ�������.
	double **fileRelation;
	fileRelation=new double*[files.size()];
	for(int i=0;i<(int)files.size();i++)
		fileRelation[i]=new double[files.size()];
	//���������ļ��������ӱ�.
	double *sum;
	double ***wordConnect;
	sum=new double[files.size()];
	wordConnect=new double**[files.size()];
	cout<<"���ڶ�ȡ�ļ�.";
	for(int i=0;i<(int)files.size();i++)
	{
		wordConnect[i]=new double*[WORD_CONNECT_SIZE];
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			wordConnect[i][j]=new double[WORD_CONNECT_SIZE];
		}
	}
	//��ȡ�����ļ�.
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
	cout<<"��ȡ�ļ����.";
	//��ÿ���ļ�.
	for(int i=0;i<(int)files.size();i++)
	{
		ofstream out("E://data//bahu//relation//relation.txt",ios::app);
		cout<<i<<endl;
		//�������ļ�
		for(int j=0;j<(int)files.size();j++)
		{
			fileRelation[i][j]=0;
			//if(j<=i) //��ʡȥһ��������.
			//{
			//	out<<fileRelation[i][j]<<" ";
			//	continue;
			//}
			//��һ����Ĳ��.
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
