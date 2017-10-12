#include "stdafx.h"
#include "uart.h"

HANDLE hCom; //���ھ��.

//======================================================================
//�������ƣ�uart_init
//������������.
//�������أ���.
//���ܸ�Ҫ�����ڳ�ʼ��.
//======================================================================
void uart_init()
{
	hCom = CreateFileA("COM4",//COM3��
		GENERIC_READ|GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		0, //ͬ����ʽ
		NULL);

	SetupComm(hCom,1024,1024); //���뻺����������������Ĵ�С����1024

	COMMTIMEOUTS TimeOuts;
	GetCommTimeouts(hCom, &TimeOuts);
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 115200; //������Ϊ115200
	dcb.ByteSize = 8; //ÿ���ֽ���8λ
	dcb.Parity = NOPARITY; //����żУ��λ
	dcb.StopBits = ONESTOPBIT; //һ��ֹͣλ
	SetCommState(hCom, &dcb);

	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);//��ջ�����.
}

//======================================================================
//�������ƣ�uart_recvN
//����������str���������ݴ���׵�ַ.
//    length���������ݳ���.
//�������أ���.
//���ܸ�Ҫ�����ڽ�������.
//======================================================================
void uart_recvN(char *str,int length)
{
	ReadFile(hCom,str,length,NULL,NULL);
}
