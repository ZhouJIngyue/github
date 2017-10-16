#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //字连接表大小
#define UNIT_MOVE_SIZE 20            //单元移动队列大小
#define WORD_MOVE_SIZE 4             //文字移动队列大小

double wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //字连接表.
vector<int> unitMove[UNIT_MOVE_SIZE];           //单元移动队列.
int unitMovePointer=0;               //单元移动队列指针.   
int wordMove[WORD_MOVE_SIZE]={0};    //文字移动队列.
int wordMovePointer=0;               //文字移动队列指针.
vector<int> indexList;               //索引队列.
double chooseResult[WORD_CONNECT_SIZE];         //选择结果队列.           
double connectRowSum[WORD_CONNECT_SIZE]={0};    //字连接表行总和.
double connectColSum[WORD_CONNECT_SIZE]={0};    //字连接表列总和.

void seek(double oldStrength,int oldCount,int oldMaxNum)
{
	double maxStrength=0;
	int maxNum=-1;
	//1.若是第一次，计算整个选择结果队列.
	if(oldMaxNum==-1)
	{
		//1.1计算选择结果队列.
		for(int i=0;i<WORD_CONNECT_SIZE;i++)
		{
			chooseResult[i]=oldStrength;
			for(int j=0;j<(int)indexList.size();j++)
				chooseResult[i]+=
				(wordConnect[indexList[j]][i]/connectRowSum[indexList[j]])*
				(wordConnect[indexList[j]][i]/connectColSum[i]);
		}
		//1.2计算选择结果队列中的最大值.
		for(int i=0;i<WORD_CONNECT_SIZE;i++)
		{
			if(chooseResult[i]>maxStrength)
			{
				maxStrength=chooseResult[i];
				maxNum=i;
			}
		}
		//1.3若选择结果队列中的最大平均连接强度>固有平均连接强度.
		if(maxNum>0&&maxStrength/(oldCount+indexList.size())>oldStrength/oldCount)
		{
			indexList.push_back(maxNum);
			return seek(oldStrength,oldCount,maxNum);
		}
		return;
	}
	//2.不是第一次.
	double oldChooseResult[WORD_CONNECT_SIZE];   //固有选择结果队列.
	//2.1初始化固有选择结果队列.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
		oldChooseResult[i]=chooseResult[i];
	//2.2计算选择结果队列.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		chooseResult[i]=oldChooseResult[i]
		+oldChooseResult[oldMaxNum]+(wordConnect[oldMaxNum][i]/connectRowSum[oldMaxNum])*
			(wordConnect[oldMaxNum][i]/connectColSum[i])-oldStrength;
	}
	//2.3计算选择结果队列中的最大值.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		//排除已在单元移动队列中的数据.
		for(int k=0;k<UNIT_MOVE_SIZE;k++)
			for(int j=0;j<(int)unitMove[k].size();j++)
				if(unitMove[k][j]==i) chooseResult[i]=-1;
		//排除已在索引队列中的数据.
		for(int j=0;j<(int)indexList.size();j++)
			if(indexList[j]==i) chooseResult[i]=-1;
		//计算选择结果队列中的最大值.
		if(chooseResult[i]>maxStrength)
		{
			maxStrength=chooseResult[i];
			maxNum=i;
		}
	}
	//2.4若选择结果队列中的最大平均连接强度>固有平均连接强度.
	if(maxStrength/(oldCount+indexList.size()*2+1)>
		oldChooseResult[oldMaxNum]/(oldCount+indexList.size()))
	{
		indexList.push_back(maxNum);
		cout<<maxNum<<" ";
		return seek(oldChooseResult[oldMaxNum],oldCount+indexList.size()-1,maxNum);
	}
	cout<<endl;
}

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
	wifstream win("DR诺力股.txt");
	win.imbue(locale("chs"));
	for(int i=0;i<WORD_MOVE_SIZE;i++)
	{
		//读取一个字并显示.
		win>>c;
		wcout<<c;
		ci=c;
		//将该字加入文字移动队列.
		wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
		wordMove[wordMovePointer]=ci;
	}
	//赋初值避免除0错误.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		connectRowSum[i]=1;
		connectColSum[i]=1;
	}
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
		//统计固有连接强度，连接个数.
		double oldStrength=0;
		int oldCount=0;
		for(int i=0;i<(int)indexList.size();i++)
		{
			for(int j=i+1;j<(int)indexList.size();j++)
			{
				oldStrength+=(wordConnect[indexList[i]][indexList[j]]/connectRowSum[indexList[i]])*
					(wordConnect[indexList[i]][indexList[j]]/connectColSum[indexList[j]]);
				oldCount++;
			}
		}
		//寻找单元.
		seek(oldStrength,oldCount,-1);
		//将该单元加入单元移动队列.
		unitMovePointer=(unitMovePointer+1)%UNIT_MOVE_SIZE;
		unitMove[unitMovePointer]=indexList;
		//对单元移动队列包含的所有单元建立后向连接.
		for(int i=0;i<UNIT_MOVE_SIZE;i++)
		{
			vector<int> oneUnit=unitMove[(unitMovePointer+1+i)%UNIT_MOVE_SIZE];
			for(int j=0;j<(int)oneUnit.size();j++)
				for(int k=0;k<(int)indexList.size();k++)
				{
					wordConnect[oneUnit[j]][indexList[k]]++;
					connectRowSum[j]++;
					connectColSum[k]++;
				}
		}
	}
	ofstream out("DR诺力股_result.txt");
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			out<<wordConnect[i][j]<<" ";
		}
		out<<endl;
	}
}