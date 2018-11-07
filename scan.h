
#ifndef SCAN_H
#define SCAN_H

#include <iostream>
#include <fstream>
#include <string>
#include "person.h"
#include "database.h"


class scan_class
{
  public:
    scan_class();
    void addtodb(person_class person);
    person_class getPerson(person_class person);
    void deletePerson(person_class person);
    int getx();
    int gety();
    int getxoffset();
    int getyoffset();
    void setx(int);
    void sety(int);
    void setxoffset(int);
    void setyoffset(int);
  
  private:
    int x;
    int y;
    int xoffset;
    int yoffset;
    database_class db;
};

#endif
