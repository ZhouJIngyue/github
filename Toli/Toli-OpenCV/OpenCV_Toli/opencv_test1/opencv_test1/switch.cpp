#include "switch.h"

Switch_Need switch_Need;

//======================================================================
//�������ƣ�switch_init
//������������.
//�������أ���.
//���ܸ�Ҫ����ʼ��ת��������Ϣ.
//======================================================================
void switch_init()
{
	//Space_Point o;               //����ͷ�����ڿռ���Ͷ��ƽ���ԭ��.
	//Space_Unit_Vector o_x_dir;   //����ͷ�����ڿռ���Ͷ��ƽ���x�᷽��.
	//Space_Unit_Vector o_y_dir;   //����ͷ�����ڿռ���Ͷ��ƽ���y�᷽��.
	//double x_ratio;              //�ռ�ƽ��x��Ի���x�����������/���أ�.
	//double y_ratio;              //�ռ�ƽ��y��Ի���y�����������/���أ�.
	//Space_Point c;               //����ͷ�ڿռ��е�λ��.
	Space_Vector o_x;
	Space_Vector o_y;
	//����ͷ�����ڿռ���Ͷ��ƽ���ԭ��.
	switch_Need.o.x=770;
	switch_Need.o.y=600;
	switch_Need.o.z=410;
	//����ͷ�����ڿռ���Ͷ��ƽ���x�᷽��.
	o_x.x=360-switch_Need.o.x;
	o_x.y=635-switch_Need.o.y;
	o_x.z=410-switch_Need.o.z;
	switch_Need.o_x_dir=space_vector_normalize(o_x);
	//����ͷ�����ڿռ���Ͷ��ƽ���y�᷽��.
	o_y.x=770-switch_Need.o.x;
	o_y.y=600-switch_Need.o.y;
	o_y.z=90-switch_Need.o.z;
	switch_Need.o_y_dir=space_vector_normalize(o_y);
	//�ռ�ƽ��x��Ի���x�����������/���أ�.
	switch_Need.x_ratio=sqrt((double)o_x.x*o_x.x
		+o_x.y*o_x.y+o_x.z*o_x.z)/640;
	//�ռ�ƽ��y��Ի���y�����������/���أ�.
	switch_Need.y_ratio=sqrt((double)o_y.x*o_y.x
		+o_y.y*o_y.y+o_y.z*o_y.z)/480;
	//����ͷ�ڿռ��е�λ��.
	switch_Need.c.x=510;
	switch_Need.c.y=195;
	switch_Need.c.z=260;
}

//======================================================================
//�������ƣ�switch_switch
//����������sw_photo������ͷ�����ϵ���Ϣ.
//�������أ��õ��ڿռ��е�λ��.
//���ܸ�Ҫ��������ͷ�����ϵ���Ϣת��Ϊ�õ��ڿռ��е�λ��.
//======================================================================
Space_Point switch_switch(Switch_Photo sw_photo)
{
	//���㻭����һ��Ͷ���ڿռ�ƽ���ϵĵ�.
	Space_Point o_x=space_point_to_point(switch_Need.o,
		switch_Need.o_x_dir,switch_Need.x_ratio*sw_photo.col);
	Space_Point o_x_y=space_point_to_point(o_x,
		switch_Need.o_y_dir,switch_Need.y_ratio*sw_photo.row);
	//��������ͷ���ռ�ƽ���ϸõ�ķ���.
	Space_Vector c_to_o_x_y;
	c_to_o_x_y.x=o_x_y.x-switch_Need.c.x;
	c_to_o_x_y.y=o_x_y.y-switch_Need.c.y;
	c_to_o_x_y.z=o_x_y.z-switch_Need.c.z;
	Space_Unit_Vector c_to_o_x_y_unit=space_vector_normalize(c_to_o_x_y);
	//����Ŀ���.
	Space_Point ans=space_point_to_point(switch_Need.c,
		c_to_o_x_y_unit,sw_photo.dis);
	return ans;
}