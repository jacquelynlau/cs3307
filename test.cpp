
// header files
#include "/usr/local/include/opencv4/opencv2/objdetect.hpp"
#include "/usr/local/include/opencv4/opencv2/highgui.hpp"
#include "/usr/local/include/opencv4/opencv2/imgproc.hpp"
#include "/usr/local/include/opencv4/opencv2/imgcodecs.hpp"
#include "/usr/local/include/opencv4/opencv2/face/facemark.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void facialRecognition( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale );
string cascadeName, nestedCascadeName;

int main( int argc, char** argv )
{

  CascadeClassifier cascade, nestedCascade;
  Mat image, song, dst;
  double scale=1.1;

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
  double fx = 1 / scale;

  perror("no error");
  try{

    // trained model
    facemark->loadModel("face_landmark_model.dat");
  }
  catch(const bad_alloc&){
    perror("bad alloc here");
  }
  cout << "Loaded model successfully" << endl;

  cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale

  // grayscale
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
    roi = smallImg( r );

    // Detection of eyes int the input image
    nestedCascade.detectMultiScale( roi, objs, 1.1, 2,
        0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    // Draw circles around eyes
    for ( size_t j = 0; j < objs.size(); j++ )
    {
      Rect nr = objs[j];
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
  waitKey(0);
}
