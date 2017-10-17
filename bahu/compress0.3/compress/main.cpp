#include "iostream"
#include "io.h"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 600       //字连接表大小
#define WORD_MOVE_SIZE 30           //文字移动队列大小

double wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //字连接表.
int wordMove[WORD_MOVE_SIZE]={0};    //文字移动队列.
int wordMovePointer=0;               //文字移动队列指针.

void getAllFiles(string path, vector<string>& files)
{
	//文件句柄  
	long hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //判断是否为文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("//").append(fileinfo.name));//保存文件夹名字
					getAllFiles(p.assign(path).append("//").append(fileinfo.name), files);//递归当前文件夹
				}
			}
			else    //文件处理
			{
				files.push_back(p.assign(path).append("//").append(fileinfo.name));//文件名
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
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
		//初始化文字移动队列.
		for(int j=0;j<WORD_MOVE_SIZE;j++)
		{
			//读取一个字并显示.
			win>>c;
			wcout<<c;
			ci=c;
			//将该字加入文字移动队列.
			wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
			wordMove[wordMovePointer]=ci;
		}
		cout<<endl;
		//读取文件中所有字.
		while(win>>c)
		{	
			//wcout<<c;
			ci=c;
			//将该字加入文字移动队列.
			wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
			wordMove[wordMovePointer]=ci;
			//对文字移动队列包含的所有单元建立后向连接.
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