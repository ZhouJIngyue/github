#include <Kinect.h>
#include <Kinect.face.h>
//#include <d2d1.h>
//#include <Shlobj.h>
#include <iostream>
#include "fstream"

//#pragma comment (lib, "d2d1.lib")
using namespace std;

//指明需要哪些面部数据.
static const DWORD c_FaceFrameFeatures = 
	FaceFrameFeatures::FaceFrameFeatures_BoundingBoxInColorSpace
	| FaceFrameFeatures::FaceFrameFeatures_PointsInInfraredSpace;

IBodyFrameReader*      m_pBodyFrameReader;

HRESULT UpdateBodyData(IBody** ppBodies)
{
	HRESULT hr = E_FAIL;

	if (m_pBodyFrameReader != nullptr)
	{
		IBodyFrame* pBodyFrame = nullptr;
		hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);
		if (SUCCEEDED(hr))
		{
			hr = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, ppBodies);
		}
		if (pBodyFrame != nullptr)
		{
			pBodyFrame->Release();
			pBodyFrame = nullptr;
		}   
	}

	return hr;
}

int main(void)
{
	// 多次取平均.
	int avgTime = 4;
	float xAll=0;
	float yAll=0;
	float zAll=0;
	//读图像使用.
	HRESULT hr;
	IKinectSensor * mySensor = nullptr;
	hr = GetDefaultKinectSensor(&mySensor);
	if (FAILED(hr))
	{
		return hr;
	}
	mySensor->Open();

	//面部识别使用.
	IFaceFrameSource*	   m_pFaceFrameSources[BODY_COUNT];
	IFaceFrameReader*	   m_pFaceFrameReaders[BODY_COUNT];
	IFaceFrame* pFaceFrame = nullptr;
	BOOLEAN bFaceTracked;
	IFaceFrameResult* pFaceFrameResult;
	PointF facePoints[FacePointType::FacePointType_Count];
	IBodyFrameSource* pBodyFrameSource;
	//for (int i = 0; i < BODY_COUNT; i++)
	//{
	//	m_pFaceFrameSources[i] = nullptr;
	//	m_pFaceFrameReaders[i] = nullptr;
	//}
	mySensor->get_BodyFrameSource(&pBodyFrameSource);
	pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
	for (int i = 0; i < BODY_COUNT; i++)
	{
		// create the face frame source by specifying the required face frame features
		hr = CreateFaceFrameSource(mySensor, 0, c_FaceFrameFeatures, &m_pFaceFrameSources[i]);
		// open the corresponding reader
		hr = m_pFaceFrameSources[i]->OpenReader(&m_pFaceFrameReaders[i]);			
	}
	facePoints[0].X=100;
	facePoints[0].Y=100;

	IBody* ppBodies[BODY_COUNT]={0};
	bool bHaveBodyData;



	IDepthFrameSource    * mySource = nullptr;
	mySensor->get_DepthFrameSource(&mySource);

	int    height = 0, width = 0;
	IFrameDescription    * myDescription = nullptr;
	mySource->get_FrameDescription(&myDescription);
	myDescription->get_Height(&height);
	myDescription->get_Width(&width);
	myDescription->Release();

	IDepthFrameReader    * myReader = nullptr;        
	mySource->OpenReader(&myReader);

	UINT    size = 0;
	UINT16    * buffer = nullptr;
	ICoordinateMapper * pCoordinateMapper;
	mySensor->get_CoordinateMapper(&pCoordinateMapper);
	CameraSpacePoint *cameraSpacePoint= 0;

	int    times = 10000000;
	IDepthFrame    * myFrame = nullptr;
	while (times)
	{
		//面部检测.
		bHaveBodyData = SUCCEEDED( UpdateBodyData(ppBodies) );
		for (int i = 0; i < BODY_COUNT; i++)
		{
			//Sleep(10);
			hr = m_pFaceFrameReaders[i]->AcquireLatestFrame(&pFaceFrame);
			bFaceTracked = false;
			if (SUCCEEDED(hr) && nullptr != pFaceFrame)
			{
				hr = pFaceFrame->get_IsTrackingIdValid(&bFaceTracked);
			}
			if (SUCCEEDED(hr))
			{
				if (bFaceTracked)
				{
					pFaceFrameResult = nullptr;

					hr = pFaceFrame->get_FaceFrameResult(&pFaceFrameResult);

					// need to verify if pFaceFrameResult contains data before trying to access it
					if (SUCCEEDED(hr) && pFaceFrameResult != nullptr)
					{			
						hr = pFaceFrameResult->GetFacePointsInInfraredSpace(FacePointType::FacePointType_Count, facePoints);
					}
					//清除
					if (pFaceFrameResult != nullptr)
					{
						pFaceFrameResult->Release();
						pFaceFrameResult = nullptr;
					}
				}
				else 
				{	
					// face tracking is not valid - attempt to fix the issue
					// a valid body is required to perform this step
					if (bHaveBodyData)
					{
						// check if the corresponding body is tracked 
						// if this is true then update the face frame source to track this body
						IBody* pBody = ppBodies[i];
						if (pBody != nullptr)
						{
							BOOLEAN bTracked = false;
							hr = pBody->get_IsTracked(&bTracked);

							UINT64 bodyTId;
							if (SUCCEEDED(hr) && bTracked)
							{
								// get the tracking ID of this body
								hr = pBody->get_TrackingId(&bodyTId);
								if (SUCCEEDED(hr))
								{
									// update the face frame source with the tracking ID
									m_pFaceFrameSources[i]->put_TrackingId(bodyTId);
								}
							}
						}
					}
				}
			}
		}
		if (myReader->AcquireLatestFrame(&myFrame) == S_OK)
		{
			//获取面部相机坐标
			myFrame->AccessUnderlyingBuffer(&size,&buffer);
			if(cameraSpacePoint== 0) cameraSpacePoint=new CameraSpacePoint[size];
			pCoordinateMapper->MapDepthFrameToCameraSpace(size,buffer,size,cameraSpacePoint);
			myFrame->Release();
			//if(times%avgTime==0)
			//{
			//	xAll/=avgTime;
			//	yAll/=avgTime;
			//	zAll/=avgTime;
			//	cout << facePoints[0].X << "\t";
			//	cout << facePoints[0].Y << "\t";
			//	//cout << buffer[width * ((int)facePoints[0].Y) + (int)facePoints[0].X] << "\t";
			//	cout << xAll<< "\t";
			//	cout << yAll<< "\t";
			//	cout << zAll<< endl;


			//	char filename[] = "..\\..\\aim_point.txt";
			//	ofstream fout(filename);
			//	fout<<900-xAll*1000<<" "<<330+zAll*1000<<" "<<220+yAll*1000 <<endl;
			//	fout.close();
			//	xAll=0;
			//	yAll=0;
			//	zAll=0;
			//}
			//else
			//{
			//	xAll+=cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].X;
			//	yAll+=cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].Y;
			//	zAll+=cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].Z;
			//}

			if(!_finite(xAll))xAll=0;
			if(!_finite(yAll))yAll=0;
			if(!_finite(zAll))zAll=0;
			xAll=xAll/avgTime*(avgTime-1)+cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].X/avgTime;
			yAll=yAll/avgTime*(avgTime-1)+cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].Y/avgTime;
			zAll=zAll/avgTime*(avgTime-1)+cameraSpacePoint[width * ((int)facePoints[0].Y) + (int)facePoints[0].X].Z/avgTime;
			cout << facePoints[0].X << "\t";
			cout << facePoints[0].Y << "\t";
			//cout << buffer[width * ((int)facePoints[0].Y) + (int)facePoints[0].X] << "\t";
			cout << xAll<< "\t";
			cout << yAll<< "\t";
			cout << zAll<< endl;

			char filename[] = "..\\..\\aim_point.txt";
			ofstream fout(filename);
			fout<<900-xAll*1000<<" "<<330+zAll*1000<<" "<<220+yAll*1000 <<endl;
			fout.close();
			times--;
		}
	}
	myReader->Release();
	mySource->Release();
	mySensor->Close();
	mySensor->Release();

	//---------------------------------------------------------------------------

	//ICoordinateMapper * pCoordinateMapper;
	//mySensor->get_CoordinateMapper(&pCoordinateMapper);
	//pCoordinateMapper->MapDepthFrameToCameraSpace(count,kinect.depthFramData,count, PointCloud);


	//IDepthFrameSource    * mySource = nullptr;
	//mySensor->get_DepthFrameSource(&mySource);

	//int    height = 0, width = 0;
	//IFrameDescription    * myDescription = nullptr;
	//mySource->get_FrameDescription(&myDescription);
	//myDescription->get_Height(&height);
	//myDescription->get_Width(&width);
	//myDescription->Release();

	//IDepthFrameReader    * myReader = nullptr;        
	//mySource->OpenReader(&myReader);

	//int    times = 100;
	//IDepthFrame    * myFrame = nullptr;
	//while (times)
	//    if (myReader->AcquireLatestFrame(&myFrame) == S_OK)
	//    {
	//        UINT    size = 0;
	//        UINT16    * buffer = nullptr;
	//        myFrame->AccessUnderlyingBuffer(&size,&buffer);
	//        cout << buffer[width * (height / 2) + width / 2] << endl;
	//        times--;
	//        myFrame->Release();
	//    }
	//myReader->Release();
	//mySource->Release();
	//mySensor->Close();
	//mySensor->Release();

	return    0;
}