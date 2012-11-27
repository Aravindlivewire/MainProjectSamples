#include "opencv2/highgui/highgui.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include<opencv2/opencv.hpp>

#include<iostream>

#include<stdio.h>

#include<stdlib.h>


using namespace std;
using namespace cv;


Mat src,src_gray,fore,back;
vector<vector<Point> > contours;
vector <Vec4i> hierarchy;

Mat thresh;


double area=0,areamax=0;
int maxn=0,nc=0;



RNG rng(12345);

/*
const int nmixtures=10;
const bool shadow=false;
const int history =1000;
*/

BackgroundSubtractorMOG back_obj;

int main(int argc,char **argv)

	{


VideoCapture cap(1);

namedWindow("src"); 
//namedWindow("srcgray"); 
//namedWindow("tresh");
	while(1)
		{

	cap>>src;

	back_obj.operator()(src,fore);





	erode(fore,fore,Mat());
	dilate(fore,fore,Mat());



findContours(fore,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));



char txt[]="0";
            txt[0]='0'+contours.size()-1;
            putText(src,txt, cvPoint(30,30), 
    			FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(250,200,250), 1, CV_AA);
  









vector<vector<Point> >hull(contours.size());
	for(int i=0;i<contours.size();i++)
		{	
	convexHull(Mat(contours[i]),hull[i],false);	
		}


	//draw

Mat drawing=Mat::zeros(thresh.size(),CV_8UC3);	

Scalar color_contours=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));

Scalar color_hull=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));

for(int i=0;i<contours.size();i++)
	{
	drawContours(src,contours,i,color_contours,2,8,hierarchy,0,Point());

	drawContours(src,hull,i,color_hull,3,8,hierarchy,0,Point());
	
	}	




	imshow("src",src);
	//imshow("srcgray",src_gray);
	//imshow("tresh",drawing);


	if(waitKey(10)>=0)
		{
		break;
		}

		}


return 0;


	}












