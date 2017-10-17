#include "iostream"
#include "io.h"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 600       //�����ӱ��С
#define WORD_MOVE_SIZE 30           //�����ƶ����д�С

double wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //�����ӱ�.
int wordMove[WORD_MOVE_SIZE]={0};    //�����ƶ�����.
int wordMovePointer=0;               //�����ƶ�����ָ��.

void getAllFiles(string path, vector<string>& files)
{
	//�ļ����  
	long hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
	string p;  //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("//").append(fileinfo.name));//�����ļ�������
					getAllFiles(p.assign(path).append("//").append(fileinfo.name), files);//�ݹ鵱ǰ�ļ���
				}
			}
			else    //�ļ�����
			{
				files.push_back(p.assign(path).append("//").append(fileinfo.name));//�ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}

void main()
{
	vector<string> files;
	getAllFiles("E://data//bahu//text",files);
	for(int i=0;i<(int)files.size();i++)
	{
		cout<<files[i]<<endl;
		wcout.imbue(locale("chs"));
		wchar_t c;
		int ci;
		wifstream win(files[i]);
		win.imbue(locale("chs"));
		//��ʼ�������ƶ�����.
		for(int j=0;j<WORD_MOVE_SIZE;j++)
		{
			//��ȡһ���ֲ���ʾ.
			win>>c;
			wcout<<c;
			ci=c;
			//�����ּ��������ƶ�����.
			wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
			wordMove[wordMovePointer]=ci;
		}
		cout<<endl;
		//��ȡ�ļ���������.
		while(win>>c)
		{	
			//wcout<<c;
			ci=c;
			//�����ּ��������ƶ�����.
			wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
			wordMove[wordMovePointer]=ci;
			//�������ƶ����а��������е�Ԫ������������.
			for(int j=0;j<WORD_MOVE_SIZE;j++)
			{
				wordConnect[wordMove[wordMovePointer+j+1]%WORD_CONNECT_SIZE]
				[wordMove[wordMovePointer]%WORD_CONNECT_SIZE]++;
			}
		}
		ofstream out("E://data//bahu//brain//"+files[i].substr(files[i].rfind('/')));
		for(int k=0;k<WORD_CONNECT_SIZE;k++)
		{
			for(int j=0;j<WORD_CONNECT_SIZE;j++)
			{
				out<<wordConnect[k][j]<<" ";
			}
			out<<endl;
		}
	}
}