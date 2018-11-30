
// header files

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/face/facemark.hpp"
//#include "mood.h"
//#include "person.h"
#include <iostream>

using namespace std;
using namespace cv;

void facialRecognition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale );

int main( int argc, char** argv)
{

  CascadeClassifier cascade, nestedCascade;
  Mat edges, image,song, dst;
  double scale=1;

  // load classifiers
  nestedCascade.load( "haarcascade_eye_tree_eyeglasses.xml" ) ;
  cascade.load( "haarcascade_frontalcatface.xml" ) ;

  if(argc > 1){
    try {
      song = imread(argv[1]);
      resize(song, dst, Size(540, 960));
      facialRecognition(dst, cascade, nestedCascade, scale);
    }
    catch(const bad_alloc&){
      perror("file not found");
    }
  }
  else{
    VideoCapture capture(0);
    namedWindow("display", WINDOW_AUTOSIZE);
    if(capture.isOpened())
    {
      for(;;)
      {
        Mat frame;
        capture >> frame;
        imshow("display", frame);
        char c = (char)waitKey(10);

        if (c == 27 || c == 'c' || c == 'C' ){
          Mat frame1 = frame.clone();
          facialRecognition(frame1, cascade, nestedCascade, scale);
          break;
        }
      }
    }
  }
  return 0;
}

// Commented out all the drawing for faces except the rectangle
// All the points from each classifier model are stored within vector<Rect> objs
// pass objs to the mood class which can extrapolate the persons mood and then save that person and
// perform image analysis 
void facialRecognition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale)
{

  vector<Rect> faces, faces2;
vector<Rect> smile;

  Ptr<face::Facemark> facemark = face::createFacemarkKazemi();
  Mat gray, smallImg;
  double fx = 1 / scale;

  CascadeClassifier smileCascade;
  smileCascade.load( "haarcascade_smile.xml");

  try{

    // trained model
    facemark->loadModel("face_landmark_model.dat");
  }
  catch(const bad_alloc&){
    perror("bad alloc here");
  }
  cout << "model loaded successfully\n";

  cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
  resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
  equalizeHist( smallImg, smallImg );

  // Detect faces of different sizes using cascade classifier

  cascade.detectMultiScale( smallImg, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

  // circles around eyes and glasses

  for ( size_t i = 0; i < faces.size(); i++ )

  {

    Rect r = faces[i];
    Mat roi;
    vector<Rect> objs;
    Point center;
    Scalar color = Scalar(255, 0, 0); 
    int radius;
    double aspect_ratio = (double)r.width/r.height;

    if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )

    {
      center.x = cvRound((r.x + r.width*0.5)*scale);
      center.y = cvRound((r.y + r.height*0.5)*scale);
      radius = cvRound((r.width + r.height)*0.25*scale);
      //circle( img, center, radius, color, 3, 8, 0 );
    }

    else

      rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
          cvPoint(cvRound((r.x + r.width-1)*scale),
            cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);

    if( nestedCascade.empty() )

      continue;

    roi = smallImg( r );

    // Detection of eyes int the input image

    nestedCascade.detectMultiScale( roi, objs, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    // Draw circles around eyes
    smileCascade.detectMultiScale(roi, smile, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
  }

  vector< vector<Point2f> > shapes;

  if (facemark->fit(img, faces, shapes))
  {

    for (size_t n = 0; n < faces.size(); n++)
    {
      rectangle(img,faces[n], Scalar(255,0,0));
    }
  }

  // create mood object with points for smile and face landmarks
  //mood_class mood(smile, shapes);
  //person_class person(0, "male", 0, mood, img);


      namedWindow ("Display window", WINDOW_AUTOSIZE);
      imshow( "Display window", img );
      waitKey(0);
      }
