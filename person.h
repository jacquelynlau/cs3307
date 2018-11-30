
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <opencv2/opencv.hpp>
#include "database.h"
#include "mood.h"

class person_class
{
  public:
    person_class(int, std::string, int, mood_class, cv::Mat);
    std::string getsex();
    void setSex(std::string);
    int getAge();
    mood_class getMood();
    int getID();
    void setAge(int);
    void setMood(mood_class);
    cv::Mat getImg();
    void setImg(cv::Mat);

  private:
    int id;
    std::string sex;
    int age;
    mood_class mood;
    cv::Mat img;
};

#endif

