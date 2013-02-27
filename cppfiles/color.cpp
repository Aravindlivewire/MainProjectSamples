#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
   
  
 
 vector<vector<Point> > contours;
 vector <Vec4i> hierarchy;
  Mat mask(Mat src,Mat hsv,Mat bw)
  {int i;
   cvtColor(src, hsv, CV_BGR2HSV);
   inRange(hsv, Scalar(5, 40, 11), Scalar(37, 133, 159), bw);
   findContours(bw.clone(), ::contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
   
     double area=0,areamax=0;
                int contour_index=0;

                for( i=0;i< ::contours.size();i++)
                        {
                        area=contourArea(contours[i]);
                        if(area>areamax)
                                {
                                areamax=area;
                                contour_index=i;
                                }

                        }


   Mat dst = Mat::zeros(src.size(), src.type());
  //   drawContours(dst,contours,contour_index,Scalar::all(0),2,8,hierarchy,0,Point());
    drawContours(dst, contours, contour_index, Scalar::all(255), CV_FILLED);
   



   return dst&src;
  }

  Mat erode_dilate(Mat masked,int op)
  {
   if (op==1)
   erode(masked,masked,Mat()); 
   else if(op==2)   
   dilate(masked,masked,Mat()); 
   else 
   {erode(masked,masked,Mat());dilate(masked,masked,Mat());}
   return masked;
  }
int main()
{

 Mat src,hsv,bw;
         VideoCapture cap(0);
 	namedWindow("src");   

while(1)
 {  
      cap>>src;
     Mat masked=mask(src,hsv,bw);
      erode_dilate(masked,2);
  


    imshow("src", src);
    imshow("dst", masked);
   if( waitKey(10)>=0)
     break;
  }	
   return 0;
}

