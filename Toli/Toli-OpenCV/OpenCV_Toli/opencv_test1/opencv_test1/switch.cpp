#include "switch.h"

Switch_Need switch_Need;

//======================================================================
//函数名称：switch_init
//函数参数：无.
//函数返回：无.
//功能概要：初始化转换所需信息.
//======================================================================
void switch_init()
{
	//Space_Point o;               //摄像头画面在空间中投射平面的原点.
	//Space_Unit_Vector o_x_dir;   //摄像头画面在空间中投射平面的x轴方向.
	//Space_Unit_Vector o_y_dir;   //摄像头画面在空间中投射平面的y轴方向.
	//double x_ratio;              //空间平面x轴对画面x轴比例（毫米/像素）.
	//double y_ratio;              //空间平面y轴对画面y轴比例（毫米/像素）.
	//Space_Point c;               //摄像头在空间中的位置.
	Space_Vector o_x;
	Space_Vector o_y;
	//摄像头画面在空间中投射平面的原点.
	switch_Need.o.x=770;
	switch_Need.o.y=600;
	switch_Need.o.z=410;
	//摄像头画面在空间中投射平面的x轴方向.
	o_x.x=360-switch_Need.o.x;
	o_x.y=635-switch_Need.o.y;
	o_x.z=410-switch_Need.o.z;
	switch_Need.o_x_dir=space_vector_normalize(o_x);
	//摄像头画面在空间中投射平面的y轴方向.
	o_y.x=770-switch_Need.o.x;
	o_y.y=600-switch_Need.o.y;
	o_y.z=90-switch_Need.o.z;
	switch_Need.o_y_dir=space_vector_normalize(o_y);
	//空间平面x轴对画面x轴比例（毫米/像素）.
	switch_Need.x_ratio=sqrt((double)o_x.x*o_x.x
		+o_x.y*o_x.y+o_x.z*o_x.z)/640;
	//空间平面y轴对画面y轴比例（毫米/像素）.
	switch_Need.y_ratio=sqrt((double)o_y.x*o_y.x
		+o_y.y*o_y.y+o_y.z*o_y.z)/480;
	//摄像头在空间中的位置.
	switch_Need.c.x=510;
	switch_Need.c.y=195;
	switch_Need.c.z=260;
}

//======================================================================
//函数名称：switch_switch
//函数参数：sw_photo：摄像头画面上点信息.
//函数返回：该点在空间中的位置.
//功能概要：将摄像头画面上点信息转化为该点在空间中的位置.
//======================================================================
Space_Point switch_switch(Switch_Photo sw_photo)
{
	//计算画面上一点投射在空间平面上的点.
	Space_Point o_x=space_point_to_point(switch_Need.o,
		switch_Need.o_x_dir,switch_Need.x_ratio*sw_photo.col);
	Space_Point o_x_y=space_point_to_point(o_x,
		switch_Need.o_y_dir,switch_Need.y_ratio*sw_photo.row);
	//计算摄像头到空间平面上该点的方向.
	Space_Vector c_to_o_x_y;
	c_to_o_x_y.x=o_x_y.x-switch_Need.c.x;
	c_to_o_x_y.y=o_x_y.y-switch_Need.c.y;
	c_to_o_x_y.z=o_x_y.z-switch_Need.c.z;
	Space_Unit_Vector c_to_o_x_y_unit=space_vector_normalize(c_to_o_x_y);
	//计算目标点.
	Space_Point ans=space_point_to_point(switch_Need.c,
		c_to_o_x_y_unit,sw_photo.dis);
	return ans;
}