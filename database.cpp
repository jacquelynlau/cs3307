#include "database.h"

database_class :: database_class(std::vector<person_class> a) {
	list = a;
}

std::vector<person_class> database_class :: getList() {
	return list;
}

person_class database_class :: getPerson(person_class person) {
	int ID = person.getID();
	for (uint i = 0; i < list.size(); i++) {
		if (list[i].getID() == ID) {
			return person;
		}
	}
  std::cout << "Person was not found in the database" << std::endl;
	return NULL;	
}

void database_class :: toString() {
	for (uint i = 0; i < list.size(); i++) {
    std::cout << "Person: " << list[i].getID() << "Age: " << list[i].getAge() << "Sex: " << list[i].getsex() << "Mood: " << list[i].getMood() << std::endl;
	}
}
