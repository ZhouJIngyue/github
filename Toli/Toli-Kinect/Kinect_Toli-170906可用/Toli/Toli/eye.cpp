#include "stdafx.h"
#include "fstream"
#include "eye.h"

Eye_Eye eye_eye;
extern HWND hwnd;         //���ھ��.
extern HBRUSH hbrw;       //�׻�ˢ.

//======================================================================
//�������ƣ�eye_init
//������������.
//�������أ���.
//���ܸ�Ҫ����ʼ���۾�.
//======================================================================
void eye_init()
{
	//�۾���ʼ��.
	eye_eye.place.x=500; eye_eye.place.y=710; eye_eye.place.z=250;
}

//======================================================================
//�������ƣ�eye_uart
//������������.
//�������أ���.
//���ܸ�Ҫ��ˢ���۾�λ��.
//======================================================================
void eye_flash()
{
	char filename[] = "..\\..\\aim_point.txt";
	ifstream fin(filename);
	if(fin)
	{
		fin>>eye_eye.place.x>>eye_eye.place.y>>eye_eye.place.z;
		fin.close();
		HDC hdc=GetDC(hwnd);
		RECT rect;
		GetClientRect (hwnd, &rect);
		FillRect(hdc,&rect,hbrw);
		draw_draw(eye_eye.place,hdc);
		ReleaseDC (hwnd, hdc) ;
	}
}