#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 1000       //�����ӱ��С
#define UNIT_MOVE_SIZE 10            //��Ԫ�ƶ����д�С
#define WORD_MOVE_SIZE 4             //�����ƶ����д�С

int wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //�����ӱ�.
vector<int> unitMove[UNIT_MOVE_SIZE];           //��Ԫ�ƶ�����.
int unitMovePointer=0;               //��Ԫ�ƶ�����ָ��.   
int wordMove[WORD_MOVE_SIZE]={0};    //�����ƶ�����.
int wordMovePointer=0;               //�����ƶ�����ָ��.
vector<int> indexList;               //��������.

void seek()
{}

void main()
{
	//wstring a = L"Hello����CSDN";
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
	wifstream win("С˵.txt");
	win.imbue(locale("chs"));
	while(win>>c)
	{	
		wcout<<c;
		ci=c;
		//�����ּ��������ƶ�����.
		wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
		wordMove[wordMovePointer]=ci;
		//��������=�����ƶ����и��ֱ���%WORD_CONNECT_SIZE.
		indexList.clear();
		for(int i=0;i<WORD_MOVE_SIZE;i++)
			indexList.push_back(wordMove[(wordMovePointer+1+i)%WORD_MOVE_SIZE]%WORD_CONNECT_SIZE);
		//Ѱ�ҵ�Ԫ().
		seek();
		//�ڵ�Ԫ�ƶ����ж��׼��뵱ǰ��Ԫ.
	}

	while(true)
	{}
}