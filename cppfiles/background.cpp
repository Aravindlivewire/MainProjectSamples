#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

using namespace cv;
using namespace std;


const int nmixtures=10;
const bool shadow=false;
const int history =1000;


BackgroundSubtractorMOG2 back_obj(history,nmixtures,shadow);




int main(int argc,char **argv)

	{

Mat original;
Mat background,foreground;

 
VideoCapture cap(0);

    std::vector<std::vector<cv::Point> >contours;

namedWindow("ORIGINAL");

namedWindow("BACKGROUND");

namedWindow("FOREGROUND");

bool con=true;

while(1)
        {
	
	cap>>original;
		
		

	back_obj.operator()(original,foreground);
	
        back_obj.getBackgroundImage(background);



	erode(foreground,foreground,Mat());		
	dilate(foreground,foreground,Mat());		

	findContours(foreground,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	
	drawContours(original,contours,-1,Scalar(255,255,0),4);
	
	imshow("ORIGINAL",original);
	imshow("BACKGROUND",background);
	imshow("FOREGROUND",foreground);


	if(waitKey(10)>=0)
		{
		break;
		}
	}


return 0;
	
}





