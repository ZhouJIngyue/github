#include "stdafx.h"
#include "space.h"

//======================================================================
//函数名称：space_vector_length
//函数参数：s_vector：空间中向量.
//函数返回：空间向量长度.
//功能概要：求空间向量长度.
//======================================================================
double space_vector_length(Space_Vector s_vector)
{
	return sqrt(s_vector.x*s_vector.x+s_vector.y*s_vector.y+s_vector.z*s_vector.z);
}

//======================================================================
//函数名称：space_dot
//函数参数：s_vector1，s_vector2：空间中两向量.
//函数返回：空间中向量点积.
//功能概要：求空间中向量点积.
//======================================================================
double space_dot(Space_Vector s_vector1, Space_Vector s_vector2)
{
	return s_vector1.x*s_vector2.x+s_vector1.y*s_vector2.y+s_vector1.z*s_vector2.z;
}

//======================================================================
//函数名称：space_cross
//函数参数：s_vector1，s_vector2：空间中两向量.
//函数返回：空间中向量差积.
//功能概要：求空间中向量差积.
//======================================================================
Space_Vector space_cross(Space_Vector s_vector1, Space_Vector s_vector2)
{
	Space_Vector c;
	c.x=s_vector1.y*s_vector2.z-s_vector1.z*s_vector2.y;
	c.y=s_vector1.z*s_vector2.x-s_vector1.x*s_vector2.z;
	c.z=s_vector1.x*s_vector2.y-s_vector1.y*s_vector2.x;
	return c;
}

//======================================================================
//函数名称：space_point_point_distance
//函数参数：s_point1，s_point2：空间中两点.
//函数返回：空间中两点距离.
//功能概要：求空间中两点距离.
//======================================================================
double space_point_point_distance(Space_Point s_point1, Space_Point s_point2)
{
	return sqrt((s_point1.x-s_point2.x)*(s_point1.x-s_point2.x)+
		(s_point1.y-s_point2.y)*(s_point1.y-s_point2.y)+
		(s_point1.z-s_point2.z)*(s_point1.z-s_point2.z));
}

//======================================================================
//函数名称：space_point_line_distance
//函数参数：s_point：空间中一点.
//    s_line：空间中一直线.
//函数返回：空间中点到直线距离.
//功能概要：求空间中点到直线距离.
//======================================================================
double space_point_line_distance(Space_Point s_point, Space_Line s_line)
{
	Space_Vector ab;//直线上一点a到空间中该点b的向量.
	ab.x=s_point.x-s_line.p1.x;
	ab.y=s_point.y-s_line.p1.y;
	ab.z=s_point.z-s_line.p1.z;
	Space_Vector n;//该直线方向向量.
	n.x=s_line.p2.x-s_line.p1.x;
	n.y=s_line.p2.y-s_line.p1.y;
	n.z=s_line.p2.z-s_line.p1.z;
	double l=space_dot(ab,n)/space_vector_length(n);
	return sqrt(space_vector_length(ab)*space_vector_length(ab)-l*l);
}

//======================================================================
//函数名称：space_line_plane_cross
//函数参数：s_line：空间中一直线.
//    s_plane：空间中一平面.
//函数返回：空间中直线与平面的交点.
//功能概要：求空间中直线与平面的交点.
//======================================================================
Space_Point space_line_plane_cross(Space_Line s_line,Space_Plane s_plane)
{
	Space_Vector l_n;//该直线方向向量.
	l_n.x=s_line.p2.x-s_line.p1.x;
	l_n.y=s_line.p2.y-s_line.p1.y;
	l_n.z=s_line.p2.z-s_line.p1.z;
	double t;//直线参数方程的参数t.
	t=(s_plane.normal_vector.x*(s_plane.p.x-s_line.p1.x)+
		s_plane.normal_vector.y*(s_plane.p.y-s_line.p1.y)+
		s_plane.normal_vector.z*(s_plane.p.z-s_line.p1.z))/
		(s_plane.normal_vector.x*l_n.x+
		s_plane.normal_vector.y*l_n.y+
		s_plane.normal_vector.z*l_n.z);
	Space_Point p_cross;//将t带入参数方程，求出交点.
	p_cross.x=s_line.p1.x+l_n.x*t;
	p_cross.y=s_line.p1.y+l_n.y*t;
	p_cross.z=s_line.p1.z+l_n.z*t;
	return p_cross;
}