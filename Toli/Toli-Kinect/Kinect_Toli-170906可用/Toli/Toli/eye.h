//======================================================================
//文件名称：eye.h
//功能概要：眼睛构件头文件
//    定义描述眼睛的结构体.
//    定义初始化函数.
//    定义刷新眼睛位置的函数.
//======================================================================

#ifndef _EYE_H
#define _EYE_H

#include "stdafx.h"
#include "uart.h"
#include "space.h"
#include "draw.h"

//眼睛.
struct Eye_Eye
{
	Space_Point place;          //眼睛位置(毫米).
};


//======================================================================
//函数名称：eye_init
//函数参数：无.
//函数返回：无.
//功能概要：初始化眼睛.
//======================================================================
void eye_init();

//======================================================================
//函数名称：eye_flash
//函数参数：无.
//函数返回：无.
//功能概要：刷新眼睛位置.
//======================================================================
void eye_flash();

#endif