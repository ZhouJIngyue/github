#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //�����ӱ��С
//#define FILE_COUNT 2729             //�ļ�����

//double fileRelation[FILE_COUNT][FILE_COUNT]={0};     //�ļ�������.

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
	//��ÿ���ļ�.

	for(int i=0;i<(int)files.size();i++)
	{
		ofstream out("E://data//bahu//relation//relation.txt",ios::app);
		cout<<i<<endl;
		//������ļ�.
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
		//�������ļ�
		for(int j=0;j<(int)files.size();j++)
		{
			fileRelation[i][j]=0;
			if(j<=i) //��ʡȥһ��������.
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
			//��һ����Ĳ��.
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
