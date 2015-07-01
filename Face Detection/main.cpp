
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;
 
Mat detectFace(Mat src);
 
int main( )
{


	// Mat src = imread("D:/Image_Project/portrait.jpg", CV_LOAD_IMAGE_COLOR);
	
	 Mat src = imread("D:/Image_Project/por.jpg", CV_LOAD_IMAGE_COLOR);

	// Mat src = imread("D:/Image_Project/123.jpg", CV_LOAD_IMAGE_COLOR);

	 // Mat src = imread("D:/Image_Project/has.png", CV_LOAD_IMAGE_COLOR);

	 // Mat src = imread("D:/Image_Project/rol.png", CV_LOAD_IMAGE_COLOR);

	 // Mat src = imread("D:/Image_Project/ppl.jpg", CV_LOAD_IMAGE_COLOR);

//	  Mat src = imread("D:/Image_Project/boys.jpg", CV_LOAD_IMAGE_COLOR);

	// Mat src = imread("D:/Image_Project/girls.jpg", CV_LOAD_IMAGE_COLOR);

	  //Mat src = imread("D:/Image_Project/portrait.jpg", CV_LOAD_IMAGE_COLOR);

	  Mat gray;

	  imshow("Original pic",src);

	  namedWindow("Original pic", CV_WINDOW_AUTOSIZE);

	  cvtColor(src,gray,CV_BGR2GRAY);

 
 while(1)
 {
          
	 src=detectFace(src);
   
	 imshow( "window1", src );

	 imwrite("D:/Image_Project/FaceDetection.jpg", src);
  // Press 'c' to escape
  if(waitKey(1) == 'c') break;  
 }
 
 waitKey(0);                  
 return 0;
}
 
Mat detectFace(Mat src)
{
	// Load Face cascade (.xml file)
	CascadeClassifier face_cascade( "C:/OpenCv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml" );
 
	//CascadeClassifier eye_cascade( "C:/OpenCv/sources/data/haarcascades/haarcascade_eye.xml" );

	CascadeClassifier eye_cascade( "C:/OpenCv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

	// Detect faces
	std::vector<Rect> faces;



	face_cascade.detectMultiScale( src, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE  , Size(10, 10) );
 
	 // Draw rectangles on the detected faces
	for( int i = 0; i < faces.size(); i++ )
		{
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x,faces[i].y);
			rectangle(src,pt1,pt2,cvScalar(255, 0,255),3,8,0);		

			 
			Mat faceROI = src( faces[i] );
			std::vector<Rect> eyes; 



    //-- In each face, detect eyes
			eye_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(10,10) );

	for(size_t j = 0; j < eyes.size(); j++ )
     {
			Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.15 );
			circle( src, center, radius, cvScalar( 255,0, 255 ), 1, 3, 0 );
	}

	
			

 }
return src;
}

