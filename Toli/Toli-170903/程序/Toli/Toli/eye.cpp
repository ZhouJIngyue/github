#include "stdafx.h"
#include "eye.h"

Eye_Eye eye_eye;
Eye_Sensor eye_sensor;
extern HANDLE hCom;       //串口句柄.
extern HWND hwnd;         //窗口句柄.
extern HBRUSH hbrw;       //白画刷.
unsigned char Re_buf[11],counter=0;

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
	eye_eye.speed.x=0; eye_eye.speed.y=0; eye_eye.speed.z=0;
	eye_eye.acceleration.x=0; eye_eye.acceleration.y=0; eye_eye.acceleration.z=0;
	//传感器初始化.
	eye_sensor.acceleration.x=0; eye_sensor.acceleration.y=0; eye_sensor.acceleration.z=0;
	eye_sensor.angle.x=0; eye_sensor.angle.y=0; eye_sensor.angle.z=0;
	//串口初始化.
	uart_init();
}

//======================================================================
//函数名称：eye_uart
//函数参数：无.
//函数返回：无.
//功能概要：从串口数据获取信息.
//======================================================================
void eye_uart()
{
	char c;
	uart_recvN(&c,1);
	Re_buf[counter]=c;
	if(counter==0&&Re_buf[0]!=0x55) return;      //第0号数据不是帧头
	counter++; 
	if(counter==11)               //接收到11个数据
	{    
		counter=0;               //重新赋值，准备下一帧数据的接收 
		eye_analyze();           //解析串口数据.
	}
}

//----------------------以下是内部函数----------------------------------

//======================================================================
//函数名称：eye_analyze
//函数参数：无.
//函数返回：无.
//功能概要：解析串口数据.
//======================================================================
void eye_analyze()
{
	switch(Re_buf [1])
	{
	case 0x51:
		eye_sensor.acceleration.x = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*16;
		eye_sensor.acceleration.y = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*16;
		eye_sensor.acceleration.z = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*16;
		break;
	case 0x53:
		eye_sensor.angle.x = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*PI;
		eye_sensor.angle.y = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*PI;
		eye_sensor.angle.z = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*PI;
		eye_calculate();
		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//清空缓冲区.
		break;
	} 
}

//======================================================================
//函数名称：eye_calculate
//函数参数：无.
//函数返回：无.
//功能概要：计算眼睛速度，位置.
//======================================================================
void eye_calculate()
{
	//eye_eye.acceleration.x=0; eye_eye.acceleration.y=0; eye_eye.acceleration.z=0;
	//eye_eye.acceleration.x+=eye_sensor.acceleration.x*cos(eye_sensor.angle.x)*cos(eye_sensor.angle.z)
	//	+eye_sensor.acceleration.y*cos(eye_sensor.angle.x)*sin(eye_sensor.angle.z)
	//	+eye_sensor.acceleration.z*sin(eye_sensor.angle.x)*cos(eye_sensor.angle.y);

	//eye_eye.acceleration.x=eye_sensor.acceleration.x; 
	//eye_eye.acceleration.y=eye_sensor.acceleration.y;
	//eye_eye.speed.x+=eye_sensor.acceleration.x*0.01*G;
	//eye_eye.speed.y+=eye_sensor.acceleration.y*0.01*G;
	//eye_eye.place.x+=eye_eye.speed.x*0.01*1000;
	//eye_eye.place.y+=eye_eye.speed.y*0.01*1000;

	//eye_eye.place.x+=2;
	
	//eye_eye.acceleration.x=eye_sensor.acceleration.x; 
	//eye_eye.acceleration.y=eye_sensor.acceleration.y;
	//eye_eye.speed.x+=eye_sensor.acceleration.x*0.01*G*0.01;
	//eye_eye.speed.y+=eye_sensor.acceleration.y*0.01*G*0.01;
	//eye_eye.place.x+=eye_eye.speed.x*0.01*1000;
	//eye_eye.place.y+=eye_eye.speed.y*0.01*1000;

	eye_eye.acceleration.x=eye_sensor.acceleration.x; 
	eye_eye.acceleration.y=eye_sensor.acceleration.y;
	eye_eye.speed.x=eye_sensor.acceleration.x*0.01*G;
	eye_eye.speed.y=eye_sensor.acceleration.y*0.01*G;
	eye_eye.place.x=eye_eye.speed.x*500+500;
	eye_eye.place.y=eye_eye.speed.y*500+710;

	HDC hdc=GetDC(hwnd);
	RECT rect;
	GetClientRect (hwnd, &rect);
	FillRect(hdc,&rect,hbrw);
	draw_draw(eye_eye.place,hdc);
	ReleaseDC (hwnd, hdc) ;
}