#include "stdafx.h"
#include "space.h"

//======================================================================
//�������ƣ�space_vector_length
//����������s_vector���ռ�������.
//�������أ��ռ���������.
//���ܸ�Ҫ����ռ���������.
//======================================================================
double space_vector_length(Space_Vector s_vector)
{
	return sqrt(s_vector.x*s_vector.x+s_vector.y*s_vector.y+s_vector.z*s_vector.z);
}

//======================================================================
//�������ƣ�space_dot
//����������s_vector1��s_vector2���ռ���������.
//�������أ��ռ����������.
//���ܸ�Ҫ����ռ����������.
//======================================================================
double space_dot(Space_Vector s_vector1, Space_Vector s_vector2)
{
	return s_vector1.x*s_vector2.x+s_vector1.y*s_vector2.y+s_vector1.z*s_vector2.z;
}

//======================================================================
//�������ƣ�space_cross
//����������s_vector1��s_vector2���ռ���������.
//�������أ��ռ����������.
//���ܸ�Ҫ����ռ����������.
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
//�������ƣ�space_point_point_distance
//����������s_point1��s_point2���ռ�������.
//�������أ��ռ����������.
//���ܸ�Ҫ����ռ����������.
//======================================================================
double space_point_point_distance(Space_Point s_point1, Space_Point s_point2)
{
	return sqrt((s_point1.x-s_point2.x)*(s_point1.x-s_point2.x)+
		(s_point1.y-s_point2.y)*(s_point1.y-s_point2.y)+
		(s_point1.z-s_point2.z)*(s_point1.z-s_point2.z));
}

//======================================================================
//�������ƣ�space_point_line_distance
//����������s_point���ռ���һ��.
//    s_line���ռ���һֱ��.
//�������أ��ռ��е㵽ֱ�߾���.
//���ܸ�Ҫ����ռ��е㵽ֱ�߾���.
//======================================================================
double space_point_line_distance(Space_Point s_point, Space_Line s_line)
{
	Space_Vector ab;//ֱ����һ��a���ռ��иõ�b������.
	ab.x=s_point.x-s_line.p1.x;
	ab.y=s_point.y-s_line.p1.y;
	ab.z=s_point.z-s_line.p1.z;
	Space_Vector n;//��ֱ�߷�������.
	n.x=s_line.p2.x-s_line.p1.x;
	n.y=s_line.p2.y-s_line.p1.y;
	n.z=s_line.p2.z-s_line.p1.z;
	double l=space_dot(ab,n)/space_vector_length(n);
	return sqrt(space_vector_length(ab)*space_vector_length(ab)-l*l);
}

//======================================================================
//�������ƣ�space_line_plane_cross
//����������s_line���ռ���һֱ��.
//    s_plane���ռ���һƽ��.
//�������أ��ռ���ֱ����ƽ��Ľ���.
//���ܸ�Ҫ����ռ���ֱ����ƽ��Ľ���.
//======================================================================
Space_Point space_line_plane_cross(Space_Line s_line,Space_Plane s_plane)
{
	Space_Vector l_n;//��ֱ�߷�������.
	l_n.x=s_line.p2.x-s_line.p1.x;
	l_n.y=s_line.p2.y-s_line.p1.y;
	l_n.z=s_line.p2.z-s_line.p1.z;
	double t;//ֱ�߲������̵Ĳ���t.
	t=(s_plane.normal_vector.x*(s_plane.p.x-s_line.p1.x)+
		s_plane.normal_vector.y*(s_plane.p.y-s_line.p1.y)+
		s_plane.normal_vector.z*(s_plane.p.z-s_line.p1.z))/
		(s_plane.normal_vector.x*l_n.x+
		s_plane.normal_vector.y*l_n.y+
		s_plane.normal_vector.z*l_n.z);
	Space_Point p_cross;//��t����������̣��������.
	p_cross.x=s_line.p1.x+l_n.x*t;
	p_cross.y=s_line.p1.y+l_n.y*t;
	p_cross.z=s_line.p1.z+l_n.z*t;
	return p_cross;
}