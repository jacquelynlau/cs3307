
#ifndef MOOD_H
#define MOOD_H

#include <vector>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgcodecs.hpp"

class mood_class
{
  public:
    mood_class(std::vector<cv::Rect>, std::vector<cv::Point2f>);
    std::vector<std::string> getMood();
    void setHugLevel(int);
    float getHugLevel();
    bool needHug();
    std::vector<cv::Rect> getSmile();
    std::vector<cv::Rect> getShapes();


  private:
    std::vector<cv::Rect> smile;
    std::vector<cv::Point2f> shapes;
    std::vector<std::string> mood;
    float huglevel;
};

#endif
