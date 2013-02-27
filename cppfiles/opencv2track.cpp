
//---------------------------//

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

//----------------------------//

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

//------------------------------//

using namespace std;
using namespace cv;

//Learn about standard templates ... seemed something that i shud have learned a long time back.... 

//-----------------------------//


int main(int argc,char **argv)
		{
		
		int redlow=0;
		int redhigh=0;
		int greenlow=0;
		int greenhigh=0;
		int bluelow=0;
		int bluehigh=0;

              cout<<"Enter the red low"<<"\t";
	      cin>>redlow;
                 
              cout<<"Enter the red high"<<"\t";
	      cin>>redhigh;

              cout<<"Enter the green low"<<"\t";
	      cin>>greenlow;
             	
              cout<<"Enter the green high"<<"\t";
	      cin>>greenhigh;

              cout<<"Enter the blue low"<<"\t";
	      cin>>bluelow;


              cout<<"Enter the blue high"<<"\t";
	      cin>>bluehigh;

		VideoCapture capWebcam(0);
			if(capWebcam.isOpened()==false)
			{
			cout<<"Not a bad idea cameraless motion sensing";
			return(1);
			}

//----------Intialisation---------------------------------------//
		
		Mat matOriginal;	//matrix image used for images in OpenCv
		Mat matProcessed(640,480,CV_8UC1); //gray scale c1 and color c3
		
	 	vector <cv::Vec3f> vecCircles;
		//3 element vector of floats, this will pass by refernece output to HoughCircles()

		vector<cv::Vec3f>::iterator itrCircles;// iteratior for the circle vector


		namedWindow("Original");//camera input
		namedWindow("Processed");//processed webcam
		char charESC=0;
		

//-----------------------------------------------------------//	
		
		while(charESC!=27)
			{
			if(!capWebcam.read(matOriginal))
				{
				cout<<"error nada !! camreo \n";
				break;
				}
		
		inRange(matOriginal,//Input Image.
			Scalar(bluelow,greenlow,redlow),//minimum Filter in BGR standard as in video 0 0 175
			Scalar(bluehigh,greenhigh,redhigh),//maximum Filter in BGR standard as in video 100 100 256
			matProcessed);

		GaussianBlur(matProcessed,//func. input
			     matProcessed,//func. output
			     Size(9,9),//smoothing window
				1.5);	//sigma value ,how much image will be blured
	

		//fill circle vector with all circles in processed image

		HoughCircles(matProcessed,	   //input of the function	
			     vecCircles,	  // output of the function
			     CV_HOUGH_GRADIENT,	  //two pass algorithm.
			     2,		          //acumalator resolution acumm_res_image = image/2 				
			     matProcessed.rows/10,  //min distance in pixel between the centres of detected images
			     100,		  //high treshold of Canny Edge Detector
			      50,		  //low treshold of Canny Edge Detector
			      10,		  //minimum cirlce radius 10
			     400);		  //maximum circle radius 400		  	
			
			
		for(itrCircles=vecCircles.begin();itrCircles!=vecCircles.end();itrCircles++)
		{
		cout<<"x="<<(*itrCircles)[0]
		<<",y="<<(*itrCircles)[1]
		<<",z="<<(*itrCircles)[2]<<"/n";


		int radius =(int)(*itrCircles)[2];

		circle(matOriginal,Point((int)(*itrCircles)[0],(int)(*itrCircles)[1]),3,Scalar(0,255,0),CV_FILLED);

		circle(matOriginal,Point((int)(*itrCircles)[0],(int)(*itrCircles)[1]),radius,Scalar(100,122,49),3);


		

		}	// end for loop

		imshow("Original",matOriginal);
		imshow("Processed",matProcessed);
		charESC=waitKey(10);
	

			
  		}	

	}




