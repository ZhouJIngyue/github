#include "stdafx.h"
#include "eye.h"

Eye_Eye eye_eye;
Eye_Sensor eye_sensor;
extern HANDLE hCom;       //���ھ��.
extern HWND hwnd;         //���ھ��.
extern HBRUSH hbrw;       //�׻�ˢ.
unsigned char Re_buf[11],counter=0;

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
	eye_eye.speed.x=0; eye_eye.speed.y=0; eye_eye.speed.z=0;
	eye_eye.acceleration.x=0; eye_eye.acceleration.y=0; eye_eye.acceleration.z=0;
	//��������ʼ��.
	eye_sensor.acceleration.x=0; eye_sensor.acceleration.y=0; eye_sensor.acceleration.z=0;
	eye_sensor.angle.x=0; eye_sensor.angle.y=0; eye_sensor.angle.z=0;
	//���ڳ�ʼ��.
	uart_init();
}

//======================================================================
//�������ƣ�eye_uart
//������������.
//�������أ���.
//���ܸ�Ҫ���Ӵ������ݻ�ȡ��Ϣ.
//======================================================================
void eye_uart()
{
	char c;
	uart_recvN(&c,1);
	Re_buf[counter]=c;
	if(counter==0&&Re_buf[0]!=0x55) return;      //��0�����ݲ���֡ͷ
	counter++; 
	if(counter==11)               //���յ�11������
	{    
		counter=0;               //���¸�ֵ��׼����һ֡���ݵĽ��� 
		eye_analyze();           //������������.
	}
}

//----------------------�������ڲ�����----------------------------------

//======================================================================
//�������ƣ�eye_analyze
//������������.
//�������أ���.
//���ܸ�Ҫ��������������.
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
		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//��ջ�����.
		break;
	} 
}

//======================================================================
//�������ƣ�eye_calculate
//������������.
//�������أ���.
//���ܸ�Ҫ�������۾��ٶȣ�λ��.
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