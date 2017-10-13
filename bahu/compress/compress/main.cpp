#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 1000       //字连接表大小
#define UNIT_MOVE_SIZE 10            //单元移动队列大小
#define WORD_MOVE_SIZE 4             //文字移动队列大小

int wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //字连接表.
vector<int> unitMove[UNIT_MOVE_SIZE];           //单元移动队列.
int unitMovePointer=0;               //单元移动队列指针.   
int wordMove[WORD_MOVE_SIZE]={0};    //文字移动队列.
int wordMovePointer=0;               //文字移动队列指针.
vector<int> indexList;               //索引队列.

void seek()
{}

void main()
{
	//wstring a = L"Hello您好CSDN";
	//wstring r;
	//r = a[0];
	//for (int i = 1; i < a.length(); ++i)
	//{
	//	r += L"/";
	//	r += a[i];
	//}
	wcout.imbue(locale("chs"));
	//wcout<<r;
	wchar_t c;
	int ci;
	wifstream win("小说.txt");
	win.imbue(locale("chs"));
	while(win>>c)
	{	
		wcout<<c;
		ci=c;
		//将该字加入文字移动队列.
		wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
		wordMove[wordMovePointer]=ci;
		//索引队列=文字移动队列各字编码%WORD_CONNECT_SIZE.
		indexList.clear();
		for(int i=0;i<WORD_MOVE_SIZE;i++)
			indexList.push_back(wordMove[(wordMovePointer+1+i)%WORD_MOVE_SIZE]%WORD_CONNECT_SIZE);
		//寻找单元().
		seek();
		//在单元移动队列队首加入当前单元.
	}

	while(true)
	{}
}