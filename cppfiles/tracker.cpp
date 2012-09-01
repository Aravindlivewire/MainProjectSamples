#include <cv.h>
#include <highgui.h>

//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV){        
       IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
       cvInRangeS(imgHSV, cvScalar(6,42,29), cvScalar(40,125,223), imgThresh); 
       return imgThresh;
} 
 
int main(){
      CvCapture* capture =0;       

      capture = cvCaptureFromCAM(1);
      if(!capture){
            printf("Capture failure\n");
            return -1;
      }
      
      IplImage* frame=0;
      cvNamedWindow("Video");      
      cvNamedWindow("Ball");


      //iterate through each frames of the video      
      while(true){

            frame = cvQueryFrame(capture);            
            if(!frame) break;

            frame=cvCloneImage(frame); 
            cvSmooth(frame, frame, CV_GAUSSIAN,3,3); //smooth the original image using Gaussian kernel

            IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3); 
            cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV
            IplImage* imgThresh = GetThresholdedImage(imgHSV);
          
            cvSmooth(imgThresh, imgThresh, CV_GAUSSIAN,3,3); //smooth the binary image using Gaussian kernel
            
            cvShowImage("Ball", imgThresh);            
            cvShowImage("Video", frame);
            
            //Clean up used images
            cvReleaseImage(&imgHSV);
            cvReleaseImage(&imgThresh);            
            cvReleaseImage(&frame);

            //Wait 50mS
            int c = cvWaitKey(10);
            //If 'ESC' is pressed, break the loop
            if((char)c==27 ) break;      
      }

      cvDestroyAllWindows() ;
      cvReleaseCapture(&capture);     

      return 0;
}

