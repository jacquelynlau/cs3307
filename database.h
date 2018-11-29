
#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"

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
