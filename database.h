
#ifndef DATABASE_H
#define DATABASE_H

#include <opencv2/opencv.hpp>
#include "person.h"
#include <iostream>
#include <fstream>

class database_class
{
  public:
    std::vector<person_class> getList();
    person_class getPerson(person_class person);
    void toString();
    void saveData(person_class person);

  private:
    std::vector<person_class> list;
};

#endif
