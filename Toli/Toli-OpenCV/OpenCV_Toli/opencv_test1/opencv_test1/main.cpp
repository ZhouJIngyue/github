#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  

#include "space.h"
#include "switch.h"
#include "iostream"
#include "fstream"

using namespace cv;  
using namespace std;  


int main()  
{  

	VideoCapture cap(0);  
	if(!cap.isOpened())  
	{  
		return -1;  
	}  
	Mat frame;  
	//Mat edges;  
	vector<Mat> channels;  //三色通道.
	Mat deal;
	Mat deal2;
	int fre=0;
	int sum;
	int ball_col;
	int ball_row;
	int channels2 = deal2.channels();
	int nRows = deal2.rows;
	int nCols = deal2.cols * channels2;
	int area;
	int area_old;
	int ball_radius;
	Switch_Photo switch_Photo;
	Space_Point aim_point;
	uchar* p;
	//半径到距离换算公式.
	double r2d[400];
	for(int i=0;i<18;i++)
	{
		r2d[i]=2600-i*100;
	}
	for(int i=18;i<20;i++)
	{
		r2d[i]=800-(i-18)*50;
	}
	for(int i=20;i<23;i++)
	{
		r2d[i]=700-(i-20)*30;
	}
	for(int i=23;i<28;i++)
	{
		r2d[i]=600-(i-23)*20;
	}
	for(int i=28;i<36;i++)
	{
		r2d[i]=500-(i-28)*12.5;
	}
	for(int i=36;i<51;i++)
	{
		r2d[i]=400-(i-37)*6.67;
	}
	for(int i=51;i<71;i++)
	{
		r2d[i]=300-(i-51)*5;
	}
	for(int i=71;i<100;i++)
	{
		r2d[i]=200-(i-71)*2;
	}
	for(int i=100;i<400;i++)
	{
		r2d[i]=0;
	}

	switch_init();

	bool stop = false;  
	while(!stop)  
	{  
		cap>>frame;  
		flip(frame,frame,1);
		//cvtColor(frame, edges, CV_BGR2GRAY);  
		//GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);  
		//Canny(edges, edges, 0, 30, 3);  
		//imshow("当前视频",edges);
		split(frame,channels);
		//addWeighted( channels.at(2), 1, channels.at(1), -1.5, 0.0,deal);
		//addWeighted( deal, 1, channels.at(0), 0.5, 0.0,deal);
		addWeighted( channels.at(2), 1, channels.at(0), -0.9, 0.0,deal);
		addWeighted( deal, 1, channels.at(1), -0.4, 0.0,deal);
		threshold(deal,deal2,60,255,THRESH_BINARY);

		if(fre>0)
		{
			CV_Assert(deal2.depth() == CV_8U);
			p = deal2.data;
			channels2 = deal2.channels();
			nRows = deal2.rows;
			nCols = deal2.cols * channels2;
			int *col_all=new int[deal2.cols];
			int *row_all=new int[deal2.rows];
			//col_all,row_all初始化.
			for(int i=0;i<deal2.cols;i++)
			{
				col_all[i]=0;
			}
			for(int i=0;i<deal2.rows;i++)
			{
				row_all[i]=0;
			}
			//col_all,row_all赋值.
			for(int i = 0; i < nRows; i++)
			{
				for (int j = 0; j < nCols; j+=channels2)
				{
					col_all[j/channels2]+=p[i*nCols+j];
					row_all[i]+=p[i*nCols+j];
				}
			}
			//col_all取中值点.
			sum=0;
			for(int i=0;i<deal2.cols;i++)
			{
				sum+=col_all[i];
			}
			sum/=2;
			for(int i=0;i<deal2.cols;i++)
			{
				sum-=col_all[i];
				if(sum<0)
				{
					ball_col=i;
					break;
				}
			}
			//row_all取中值点.
			sum=0;
			for(int i=0;i<deal2.rows;i++)
			{
				sum+=row_all[i];
			}
			sum/=2;
			for(int i=0;i<deal2.rows;i++)
			{
				sum-=row_all[i];
				if(sum<0)
				{
					ball_row=i;
					break;
				}
			}
			//for(int i=0;i<deal2.cols;i++)
			//{
			//	cout<<all[i]/deal2.rows<<" ";
			//}
			//cout<<endl;
			fre=0;
		}
		fre++;

		//计算球的半径.
		ball_radius=5;
		area=0;
		area_old=-1;
		p = deal2.data;
		//从球心一圈一圈向外加，到没有增长时结束迭代，迭代次数即为圆半径.
		while(area!=area_old)
		{
			if(ball_row-ball_radius<0||ball_row+ball_radius>=deal2.rows) break;
			if(ball_col-ball_radius<0||ball_col+ball_radius>=deal2.cols) break;
			area_old=area;
			for(int i=0;i<ball_radius*2;i+=2)
			{
				area+=p[(ball_row+ball_radius-i)*nCols+(ball_col-ball_radius)*channels2];
				area+=p[(ball_row+ball_radius-i)*nCols+(ball_col+ball_radius)*channels2];
				area+=p[(ball_row+ball_radius)*nCols+(ball_col+ball_radius-i)*channels2];
				area+=p[(ball_row-ball_radius)*nCols+(ball_col+ball_radius-i)*channels2];
			}
			ball_radius++;
			//界限超出.
		}

		switch_Photo.col=ball_col;
		switch_Photo.row=ball_row;
		switch_Photo.dis=r2d[ball_radius];
		aim_point=switch_switch(switch_Photo);

		//cout<<"横坐标为："<<ball_col<<"\t纵坐标为："<<ball_row<<"\t半径为："<<ball_radius<<endl;
		cout<<"x："<<aim_point.x<<"\ty："<<aim_point.y<<"\tz："<<aim_point.z<<endl;
		char filename[] = "..\\..\\aim_point.txt";
		ofstream fout(filename);
		fout<<aim_point.x<<" "<<aim_point.y<<" "<<aim_point.z<<endl;
		fout.close();

		//在原图中标记.
		p = channels.at(0).data;
		for(int i = 0; i < nRows; i++)
		{
			for (int j = 0; j < nCols; j+=channels2)
			{
				if(i>ball_row-10&&i<ball_row+10||j/channels2>ball_col-10&&j/channels2<ball_col+10)
					p[i*nCols+j]=0;
			}
		}
		////显示圆半径.
		//stringstream stream;  
		//stream<<ball_radius;  
		//putText(channels.at(0),stream.str(),cvPoint(ball_col+11,ball_row-11),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),3);
		//显示距离.
		stringstream stream;  
		stream<<r2d[ball_radius];  
		putText(channels.at(0),stream.str(),cvPoint(ball_col+11,ball_row-11),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(255,255,255),3);

		//显示.
		//imshow("当前视频",frame);  
		imshow("当前视频b",channels.at(0));  
		//imshow("当前视频g",channels.at(1));  
		//imshow("当前视频r",channels.at(2));  
		//imshow("处理后的",deal); 
		imshow("阈值化的",deal2); 
		if(waitKey(30) >=0)  
			stop = true;  
	}  
	return 0;  
}  