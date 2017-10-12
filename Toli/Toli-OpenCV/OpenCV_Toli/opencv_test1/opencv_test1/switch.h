//======================================================================
//文件名称：switch.h
//功能概要：空间转换构件头文件
//    定义摄像头画面上点信息的结构体.
//    定义转换所需信息的结构体.
//    定义初始化函数.
//    定义将摄像头画面上点信息转化为该点在空间中的位置的函数.
//======================================================================

#ifndef _SWITCH_H
#define _SWITCH_H

#include "space.h"

//摄像头画面上点信息.
struct Switch_Photo
{
	double row;      //点所在行数.
	double col;      //点所在列数.
	double dis;      //点距离摄像头距离.
};

//转换所需信息.
struct Switch_Need
{
	Space_Point o;               //摄像头画面在空间中投射平面的原点.
	Space_Unit_Vector o_x_dir;   //摄像头画面在空间中投射平面的x轴方向.
	Space_Unit_Vector o_y_dir;   //摄像头画面在空间中投射平面的y轴方向.
	double x_ratio;              //空间平面x轴对画面x轴比例（毫米/像素）.
	double y_ratio;              //空间平面y轴对画面y轴比例（毫米/像素）.
	Space_Point c;               //摄像头在空间中的位置.
};

//======================================================================
//函数名称：switch_init
//函数参数：无.
//函数返回：无.
//功能概要：初始化转换所需信息.
//======================================================================
void switch_init();

//======================================================================
//函数名称：switch_switch
//函数参数：sw_photo：摄像头画面上点信息.
//函数返回：该点在空间中的位置.
//功能概要：将摄像头画面上点信息转化为该点在空间中的位置.
//======================================================================
Space_Point switch_switch(Switch_Photo sw_photo);

#endif