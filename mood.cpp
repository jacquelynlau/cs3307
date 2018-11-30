#include "mood.h"

mood_class::mood_class(std::vector<cv::Rect> this_smile, std::vector<cv::Point2f> this_shapes){
  smile = this_smile;
  shapes = this_shapes;
  huglevel = 0;
}

std::vector<std::string> mood_class::getMood(){
  return mood;
}

void mood_class::setHugLevel(int level){
  huglevel = level;
}

float mood_class::getHugLevel(){
  return huglevel;
}

bool mood_class::needHug(){
  if (huglevel < 50){
    return true;
  }
  return false;
}

std::vector<cv::Rect> mood_class::getSmile(){
  return smile;
}

std::vector<cv::Point2f> mood_class::getShapes(){
  return shapes;
}

