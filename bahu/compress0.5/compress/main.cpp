#include "iostream"
#include "fstream"
#include "string"
#include "locale"
#include "vector"
using namespace std;

#define WORD_CONNECT_SIZE 100       //�����ӱ��С
#define UNIT_MOVE_SIZE 20            //��Ԫ�ƶ����д�С
#define WORD_MOVE_SIZE 4             //�����ƶ����д�С

double wordConnect[WORD_CONNECT_SIZE][WORD_CONNECT_SIZE]={0};     //�����ӱ�.
vector<int> unitMove[UNIT_MOVE_SIZE];           //��Ԫ�ƶ�����.
int unitMovePointer=0;               //��Ԫ�ƶ�����ָ��.   
int wordMove[WORD_MOVE_SIZE]={0};    //�����ƶ�����.
int wordMovePointer=0;               //�����ƶ�����ָ��.
vector<int> indexList;               //��������.
double chooseResult[WORD_CONNECT_SIZE];         //ѡ��������.           
double connectRowSum[WORD_CONNECT_SIZE]={0};    //�����ӱ����ܺ�.
double connectColSum[WORD_CONNECT_SIZE]={0};    //�����ӱ����ܺ�.

void seek(double oldStrength,int oldCount,int oldMaxNum)
{
	double maxStrength=0;
	int maxNum=-1;
	//1.���ǵ�һ�Σ���������ѡ��������.
	if(oldMaxNum==-1)
	{
		//1.1����ѡ��������.
		for(int i=0;i<WORD_CONNECT_SIZE;i++)
		{
			chooseResult[i]=oldStrength;
			for(int j=0;j<(int)indexList.size();j++)
				chooseResult[i]+=
				(wordConnect[indexList[j]][i]/connectRowSum[indexList[j]])*
				(wordConnect[indexList[j]][i]/connectColSum[i]);
		}
		//1.2����ѡ���������е����ֵ.
		for(int i=0;i<WORD_CONNECT_SIZE;i++)
		{
			if(chooseResult[i]>maxStrength)
			{
				maxStrength=chooseResult[i];
				maxNum=i;
			}
		}
		//1.3��ѡ���������е����ƽ������ǿ��>����ƽ������ǿ��.
		if(maxNum>0&&maxStrength/(oldCount+indexList.size())>oldStrength/oldCount)
		{
			indexList.push_back(maxNum);
			return seek(oldStrength,oldCount,maxNum);
		}
		return;
	}
	//2.���ǵ�һ��.
	double oldChooseResult[WORD_CONNECT_SIZE];   //����ѡ��������.
	//2.1��ʼ������ѡ��������.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
		oldChooseResult[i]=chooseResult[i];
	//2.2����ѡ��������.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		chooseResult[i]=oldChooseResult[i]
		+oldChooseResult[oldMaxNum]+(wordConnect[oldMaxNum][i]/connectRowSum[oldMaxNum])*
			(wordConnect[oldMaxNum][i]/connectColSum[i])-oldStrength;
	}
	//2.3����ѡ���������е����ֵ.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		//�ų����ڵ�Ԫ�ƶ������е�����.
		for(int k=0;k<UNIT_MOVE_SIZE;k++)
			for(int j=0;j<(int)unitMove[k].size();j++)
				if(unitMove[k][j]==i) chooseResult[i]=-1;
		//�ų��������������е�����.
		for(int j=0;j<(int)indexList.size();j++)
			if(indexList[j]==i) chooseResult[i]=-1;
		//����ѡ���������е����ֵ.
		if(chooseResult[i]>maxStrength)
		{
			maxStrength=chooseResult[i];
			maxNum=i;
		}
	}
	//2.4��ѡ���������е����ƽ������ǿ��>����ƽ������ǿ��.
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
	wifstream win("DRŵ����.txt");
	win.imbue(locale("chs"));
	for(int i=0;i<WORD_MOVE_SIZE;i++)
	{
		//��ȡһ���ֲ���ʾ.
		win>>c;
		wcout<<c;
		ci=c;
		//�����ּ��������ƶ�����.
		wordMovePointer=(wordMovePointer+1)%WORD_MOVE_SIZE;
		wordMove[wordMovePointer]=ci;
	}
	//����ֵ�����0����.
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		connectRowSum[i]=1;
		connectColSum[i]=1;
	}
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
		//ͳ�ƹ�������ǿ�ȣ����Ӹ���.
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
		//Ѱ�ҵ�Ԫ.
		seek(oldStrength,oldCount,-1);
		//���õ�Ԫ���뵥Ԫ�ƶ�����.
		unitMovePointer=(unitMovePointer+1)%UNIT_MOVE_SIZE;
		unitMove[unitMovePointer]=indexList;
		//�Ե�Ԫ�ƶ����а��������е�Ԫ������������.
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
	ofstream out("DRŵ����_result.txt");
	for(int i=0;i<WORD_CONNECT_SIZE;i++)
	{
		for(int j=0;j<WORD_CONNECT_SIZE;j++)
		{
			out<<wordConnect[i][j]<<" ";
		}
		out<<endl;
	}
}