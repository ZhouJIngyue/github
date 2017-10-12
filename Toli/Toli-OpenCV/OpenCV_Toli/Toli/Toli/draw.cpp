#include "stdafx.h"
#include "draw.h"

Draw_Thing draw_thing;
Draw_Screen draw_screen;

//======================================================================
//函数名称：draw_init
//函数参数：无.
//函数返回：无.
//功能概要：初始化所画的物体与屏幕.
//======================================================================
void draw_init()
{
	//初始化所画的物体.
	Space_Line l;

	//屏幕对角线.
	//l.p1.x=315; l.p2.x=50;
	//l.p1.y=248; l.p2.y=645;
	//l.p1.z=343; l.p2.z=100;
	//draw_thing.lines.push_back(l);
	//l.p1.x=50; l.p2.x=315;
	//l.p1.y=645; l.p2.y=248;
	//l.p1.z=343; l.p2.z=100;
	//draw_thing.lines.push_back(l);

	//坐标轴.
	l.p1.x=100; l.p2.x=500;
	l.p1.y=0; l.p2.y=0;
	l.p1.z=0; l.p2.z=0;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=0;
	l.p1.y=100; l.p2.y=500;
	l.p1.z=0; l.p2.z=0;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=0;
	l.p1.y=0; l.p2.y=0;
	l.p1.z=100; l.p2.z=500;
	draw_thing.lines.push_back(l);

	//立方体.
	l.p1.x=100; l.p2.x=100;
	l.p1.y=0; l.p2.y=100;
	l.p1.z=0; l.p2.z=0;
	draw_thing.lines.push_back(l);
	l.p1.x=100; l.p2.x=100;
	l.p1.y=0; l.p2.y=0;
	l.p1.z=0; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=0;
	l.p1.y=100; l.p2.y=100;
	l.p1.z=0; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=100;
	l.p1.y=100; l.p2.y=100;
	l.p1.z=0; l.p2.z=0;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=0;
	l.p1.y=0; l.p2.y=100;
	l.p1.z=100; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=100;
	l.p1.y=0; l.p2.y=0;
	l.p1.z=100; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=100; l.p2.x=100;
	l.p1.y=100; l.p2.y=100;
	l.p1.z=0; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=0; l.p2.x=100;
	l.p1.y=100; l.p2.y=100;
	l.p1.z=100; l.p2.z=100;
	draw_thing.lines.push_back(l);
	l.p1.x=100; l.p2.x=100;
	l.p1.y=0; l.p2.y=100;
	l.p1.z=100; l.p2.z=100;
	draw_thing.lines.push_back(l);

	//三角.
	//l.p1.x=100; l.p2.x=0;
	//l.p1.y=0; l.p2.y=100;
	//l.p1.z=0; l.p2.z=0;
	//draw_thing.lines.push_back(l);
	//l.p1.x=0; l.p2.x=0;
	//l.p1.y=100; l.p2.y=0;
	//l.p1.z=0; l.p2.z=100;
	//draw_thing.lines.push_back(l);
	//l.p1.x=0; l.p2.x=100;
	//l.p1.y=0; l.p2.y=0;
	//l.p1.z=100; l.p2.z=0;
	//draw_thing.lines.push_back(l);

	//对角直线.
	l.p1.x=100; l.p2.x=200;
	l.p1.y=100; l.p2.y=200;
	l.p1.z=100; l.p2.z=200;
	draw_thing.lines.push_back(l);

	//初始化屏幕.
	draw_screen.o.x=315; draw_screen.o.y=248; draw_screen.o.z=343;
	draw_screen.x_end.x=50; draw_screen.x_end.y=645; draw_screen.x_end.z=343;
	draw_screen.y_end.x=315; draw_screen.y_end.y=248; draw_screen.y_end.z=100;
	draw_screen.e.x=50; draw_screen.e.y=645; draw_screen.e.z=100;
	draw_screen.x_pixel=1920;
	draw_screen.y_pixel=980;//1225

	draw_screen.x_length=space_point_point_distance(draw_screen.o,draw_screen.x_end);
	draw_screen.y_length=space_point_point_distance(draw_screen.o,draw_screen.y_end);
	draw_screen.up.p1=draw_screen.o; draw_screen.up.p2=draw_screen.x_end;
	draw_screen.down.p1=draw_screen.y_end; draw_screen.down.p2=draw_screen.e;
	draw_screen.left.p1=draw_screen.o; draw_screen.left.p2=draw_screen.y_end;
	draw_screen.right.p1=draw_screen.x_end; draw_screen.right.p2=draw_screen.e;
	draw_screen.plane.p=draw_screen.o;
	Space_Vector a,b;
	a.x=draw_screen.x_end.x-draw_screen.o.x; a.y=draw_screen.x_end.y-draw_screen.o.y; a.z=draw_screen.x_end.z-draw_screen.o.z;
	b.x=draw_screen.y_end.x-draw_screen.o.x; b.y=draw_screen.y_end.y-draw_screen.o.y; b.z=draw_screen.y_end.z-draw_screen.o.z;
	draw_screen.plane.normal_vector=space_cross(a, b);
}

//======================================================================
//函数名称：draw_draw
//函数参数：eye：眼睛在空间中的位置.
//函数返回：无.
//功能概要：根据眼睛的位置绘制物体在屏幕上的投射.
//======================================================================
void draw_draw(Space_Point eye,HDC hdc)
{
	int i,j;
	Space_Line temp_l;
	Space_Point temp_p;
	double to_up,to_down,to_left,to_right;
	int x_pixel,y_pixel;
	for(i=0;i<(int)draw_thing.lines.size();i++)
	{
		//temp_l为眼到物体线段一端的连线.
		temp_l.p1=eye;
		for(j=0;j<2;j++)//对于线段的两个端点.
		{
			if(j==0) temp_l.p2=draw_thing.lines[i].p1;
			if(j==1) temp_l.p2=draw_thing.lines[i].p2;
			//temp_p为temp_l与屏幕所在平面的交点.
			temp_p=space_line_plane_cross(temp_l,draw_screen.plane);
			//计算该交点至屏幕上下边的距离.
			to_up=space_point_line_distance(temp_p,draw_screen.up);
			to_down=space_point_line_distance(temp_p,draw_screen.down);
			to_left=space_point_line_distance(temp_p,draw_screen.left);
			to_right=space_point_line_distance(temp_p,draw_screen.right);
			//判断是否超出屏幕.
			if(to_down>to_up&&to_down>draw_screen.y_length)//向上超出.
				to_up=-to_up;
			if(to_right>to_left&&to_right>draw_screen.x_length)//向左超出.
				to_left=-to_left;
			x_pixel=(int)(to_left*(draw_screen.x_pixel/draw_screen.x_length));
			y_pixel=(int)(to_up*(draw_screen.y_pixel/draw_screen.y_length));
			if(j==0) MoveToEx(hdc,x_pixel,y_pixel,NULL);
			if(j==1) LineTo(hdc,x_pixel,y_pixel);
		}
	}
}