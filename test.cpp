// CPP program to detects face in a video 

// Include required header files from OpenCV directory 
#include "opencv2/objdetect.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "opencv2/imgcodecs.hpp"
#include <iostream> 

using namespace std; 
using namespace cv; 

// Function for Face Detection 
void detectAndDraw( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, CascadeClassifier& nestedCascade2, double scale ); 
string cascadeName, nestedCascadeName; 

int main( int argc, const char** argv ) 
{ 
  // declares matrixs 
  // for now using static images, will try and upgrade to video capture later on.
	Mat frame, image, song, dst; 
  song = imread("song.jpg");
  resize(song, dst, Size(540,960));
  

	// PreDefined trained XML classifiers with facial features 
	CascadeClassifier cascade, nestedCascade, nestedCascade2; 
	double scale=1; 

  //load classifiers 
  nestedCascade2.load("haarcascade_frontalface_default.xml");
	nestedCascade.load( "haarcascade_eye_tree_eyeglasses.xml" ) ; 
	cascade.load( "haarcascade_frontalcatface.xml" ) ; 

  detectAndDraw(dst, cascade, nestedCascade, nestedCascade2, scale);

return 0; 
} 

void detectAndDraw( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, CascadeClassifier& nestedCascade2, double scale) 
{ 
	vector<Rect> faces, faces2; 
	Mat gray, smallImg; 

	cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale 
	double fx = 1 / scale; 

	// Resize the Grayscale Image 
	resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR ); 
	equalizeHist( smallImg, smallImg ); 

	// Detect faces of different sizes using cascade classifier 
	cascade.detectMultiScale( smallImg, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 

	// Draw circles around the faces 
	for ( size_t i = 0; i < faces.size(); i++ ) 
	{ 
		Rect r = faces[i]; 
		Mat smallImgROI; 
		vector<Rect> nestedObjects; 
		Point center; 
		Scalar color = Scalar(255, 0, 0); // Color for Drawing tool 
		int radius; 

		double aspect_ratio = (double)r.width/r.height; 
		if( 0.75 < aspect_ratio && aspect_ratio < 1.3 ) 
		{ 
			center.x = cvRound((r.x + r.width*0.5)*scale); 
			center.y = cvRound((r.y + r.height*0.5)*scale); 
			radius = cvRound((r.width + r.height)*0.25*scale); 
			circle( img, center, radius, color, 3, 8, 0 ); 
		} 
		else
			rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)), 
					cvPoint(cvRound((r.x + r.width-1)*scale), 
					cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0); 
		if( nestedCascade.empty() ) 
			continue; 
		smallImgROI = smallImg( r ); 
		
		// Detection of eyes int the input image 
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2, 
										0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 
		
		// Draw circles around eyes 
		for ( size_t j = 0; j < nestedObjects.size(); j++ ) 
		{ 
			Rect nr = nestedObjects[j]; 
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale); 
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale); 
			radius = cvRound((nr.width + nr.height)*0.25*scale); 
			circle( img, center, radius, color, 3, 8, 0 ); 
			
		// Detection of face
		nestedCascade2.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2, 
										0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 
		
		for ( size_t k = 0; k < nestedObjects.size(); k++ ) 
		{ 
			Rect nr = nestedObjects[k]; 
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale); 
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale); 
			radius = cvRound((nr.width + nr.height)*0.25*scale); 
			circle( img, center, radius, color, 3, 8, 0 ); 
		} 
} 
	} 

	// Show Processed Image with detected faces 
  namedWindow ("Display window", WINDOW_AUTOSIZE);
	imshow( "Display window", img ); 
  // wait for key before exit
  waitKey(0);
} 

