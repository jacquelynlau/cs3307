
// Include required header files from OpenCV directory 
#include "opencv2/objdetect.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "opencv2/imgcodecs.hpp"
#include "opencv2/face/facemark.hpp"
#include <iostream> 

using namespace std; 
using namespace cv; 

// Function for Face Detection 
void facialRecognition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale ); 
string cascadeName, nestedCascadeName; 

int main( int argc, char** argv ) 
{ 

  Mat frame, image, song, dst; 

  if(argc > 0){
    try {

      song = imread(argv[1]);
    }
    catch(const bad_alloc&){
      perror("file not found");
    }}
  else{
    song = imread("song.jpg");
  }

  resize(song, dst, Size(540,960));


  // PreDefined trained XML classifiers with facial features 
  CascadeClassifier cascade, nestedCascade;
  double scale=1; 

  //load classifiers 
  nestedCascade.load( "haarcascade_eye_tree_eyeglasses.xml" ) ; 
  cascade.load( "haarcascade_frontalcatface.xml" ) ; 

  facialRecognition(dst, cascade, nestedCascade, scale);

  return 0; 
} 

void facialRecognition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale) 
{ 
  vector<Rect> faces, faces2; 
  Mat gray, smallImg; 
  Ptr<face::Facemark> facemark = face::createFacemarkKazemi();
  perror("no error");
  try{

    // trained model
    facemark->loadModel("face_landmark_model.dat");
  }
  catch(const bad_alloc&){
    perror("bad alloc here");
  }
  cout << "Loaded facemark model" << endl;

  cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale 
  double fx = 1 / scale; 

  // grayscale
  resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT ); 
  equalizeHist( smallImg, smallImg ); 

  // Detect faces of different sizes using cascade classifier 
  cascade.detectMultiScale( smallImg, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) ); 

  // circles around eyes and glasses
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
    } 
  } 

  vector< vector<Point2f> > shapes;

  if (facemark->fit(img, faces, shapes))
  {
    for (size_t n = 0; n < faces.size(); n++)
    {
      rectangle(img,faces[n], Scalar(255,0,0));
    }
    for(unsigned long n=0; n <faces.size(); n++){
      for(unsigned long k=0; k < shapes[n].size(); k++)
      {
        circle(img, shapes[n][k], 5, Scalar(0,0,255), FILLED);
      }
    }
  }

  namedWindow ("Display window", WINDOW_AUTOSIZE);
  imshow( "Display window", img ); 
  //wait for key before exit
  waitKey(0);
} 

