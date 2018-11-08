
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "database.h"
#include "mood.h"

class person_class
{
  public:
    person_class();
    std::string getsex();
    int getAge();
    mood_class getMood();
    void setAge(int);
    void setMood(mood_class);
    void saveData();

  private:
    int id;
    std::string sex;
    int age;
    mood_class mood;
};

#endif

