
/*-----------------------*/
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
/*-----------------------*/


//open CV standard libraries.
/*-----------------------*/
#include "cv.h"
#include "highgui.h"
/*------------------------*/


int HueLowervalue=0;
int SaturationLowervalue=0;
int ValueLowervalue=0;


int HueUppervalue=180;
int SaturationUppervalue=256;
int ValueUppervalue=256;

//using namespace cv;


IplImage* HsvToBinaryConverter(IplImage* HSVImage)
	{

	IplImage* BinaryImage=cvCreateImage(cvGetSize(HSVImage),IPL_DEPTH_8U,1);
	cvInRangeS(HSVImage,cvScalar(HueLowervalue,SaturationLowervalue,ValueLowervalue),cvScalar(HueUppervalue,SaturationUppervalue,ValueUppervalue),BinaryImage);
	
	return BinaryImage;
	}



void Create_Windows_and_Trackbars()
	{

	cvNamedWindow("Original",0);
	cvNamedWindow("Processed",0);

	cvCreateTrackbar("Lower-Hue","Processed",&HueLowervalue,180,NULL);
	cvCreateTrackbar("Upper-Hue","Processed",&HueUppervalue,180,NULL);


	cvCreateTrackbar("Lower-Sat","Processed",&SaturationLowervalue,256,NULL);
	cvCreateTrackbar("Upper-Sat","Processed",&SaturationUppervalue,256,NULL);


	cvCreateTrackbar("Lower-Value","Processed",&ValueLowervalue,256,NULL);
	cvCreateTrackbar("Upper-Value","Processed",&ValueUppervalue,256,NULL);

	}





int main(int argc,char ** argv)

	{
  
        IplImage* originalframe=0;
 

	Create_Windows_and_Trackbars();


	while(1)
		{
		
		originalframe=cvLoadImage(argv[1]); 
 
		IplImage* HSVImage=cvCreateImage((cvGetSize(originalframe)),
		IPL_DEPTH_8U,3);
		
	        cvSmooth(originalframe,originalframe,CV_GAUSSIAN,9,9);

		cvCvtColor(originalframe,HSVImage,CV_BGR2HSV);
		
		IplImage *BinaryImage=HsvToBinaryConverter(HSVImage);

		cvShowImage("Processed",BinaryImage);
		cvShowImage("Original",originalframe);
               
                

		cvReleaseImage(&originalframe);
		cvReleaseImage(&BinaryImage);
		cvReleaseImage(&HSVImage);


		char c=cvWaitKey(10);
		if(c==27) 
		 	break;

		}


	cvDestroyAllWindows();
//	cvReleaseCapture(&cam);

	return 0;

     }
