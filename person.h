
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "database.h"
#include "mood.h"

class person_class
{
  public:
    person_class(int iD, std::string sexx, int agee, mood_class moodd, Mat image);
    std::string getsex();
    int getAge();
    mood_class getMood();
    int getID();
    void setAge(int);
    void setMood(mood_class);
    void saveData();
    Mat getImg();
    void setImg(Mat image);

  private:
    int id;
    std::string sex;
    int age;
    mood_class mood;
    Mat img;
};

#endif

