#include "person.h"

person_class :: person_class(int iD, std::string sexx, int agee, mood_class moodd, cv::Mat image) {
  id = iD;
  sex = sexx;
  age = agee;
  mood = moodd;
  img = image;
}

std::string person_class :: getsex() {
  return sex;
}

void person_class :: setSex(std::string sexx) {
  sex = sexx;
}

int person_class :: getAge() {
  return age; 
}

mood_class person_class :: getMood() {
  return mood;
}

int person_class :: getID() {
  return id; 
}

void person_class :: setAge(int agee) {
  age = agee;
}

void person_class :: setMood(mood_class newMood) {
  mood = newMood;
}

Mat person_class :: getImg() {
  return img; 
}

void person_class :: setImg(Mat image) {
  img = image; 
}
}
