#include "stdafx.h"
#include "fstream"
#include "eye.h"

Eye_Eye eye_eye;
extern HWND hwnd;         //窗口句柄.
extern HBRUSH hbrw;       //白画刷.

//======================================================================
//函数名称：eye_init
//函数参数：无.
//函数返回：无.
//功能概要：初始化眼睛.
//======================================================================
void eye_init()
{
	//眼睛初始化.
	eye_eye.place.x=500; eye_eye.place.y=710; eye_eye.place.z=250;
}

//======================================================================
//函数名称：eye_uart
//函数参数：无.
//函数返回：无.
//功能概要：刷新眼睛位置.
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