
#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"

class database_class
{
  public:
    database_class();
    person_class getList();
    person_class getPerson(person_class person);
    void toString();

  private:
    person_class list[];
};

#endif