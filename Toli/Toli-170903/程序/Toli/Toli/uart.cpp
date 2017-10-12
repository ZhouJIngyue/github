#include "stdafx.h"
#include "uart.h"

HANDLE hCom; //串口句柄.

//======================================================================
//函数名称：uart_init
//函数参数：无.
//函数返回：无.
//功能概要：串口初始化.
//======================================================================
void uart_init()
{
	hCom = CreateFileA("COM4",//COM3口
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		0, //同步方式
		NULL);

	SetupComm(hCom,1024,1024); //输入缓冲区和输出缓冲区的大小都是1024

	COMMTIMEOUTS TimeOuts;
	GetCommTimeouts(hCom, &TimeOuts);
	//设定读超时
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 115200; //波特率为115200
	dcb.ByteSize = 8; //每个字节有8位
	dcb.Parity = NOPARITY; //无奇偶校验位
	dcb.StopBits = ONESTOPBIT; //一个停止位
	SetCommState(hCom, &dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//清空缓冲区.
}

//======================================================================
//函数名称：uart_recvN
//函数参数：str：接收数据存放首地址.
//    length：接收数据长度.
//函数返回：无.
//功能概要：串口接收数据.
//======================================================================
void uart_recvN(char *str,int length)
{
	ReadFile(hCom,str,length,NULL,NULL);
}
