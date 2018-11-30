#include "database.h"
#include <stdio.h>

using namespace cv;

/** @brief returns a list that will be used for holding temporary person objs
  * @param none
  * @return the list
  */
std::vector<person_class> database_class :: getList() {
	return list;
}

/** @brief This will get the person from the database if they exist in it
  * @param person
  * @return the person if they are in the database. 
  */
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

/** @brief prints out the database with the user's respective age,sex, mood, etc.
  * @param none
  * @return nothing
  */
void database_class :: toString() {
	for (uint i = 0; i < list.size(); i++) {
    std::cout << "Person: " << list[i].getID() << "Age: " << list[i].getAge() << "Sex: " << list[i].getsex() << "Mood: " << list[i].getMood() << std::endl;
	}
}

/** @brief Saves the data to a remote text file in the same folder
  * @param person (they will be saved in the database), filename(the name of the file they want to write it to)
  * @return nothing
  */
void database_class :: saveData(person_class person, std::string filename) {
	//get person's data to write it off
	std::string ID = person.getID();
	std::string sex = person.getsex();
	int age = person.getAge();
	mood_class mood = person.getMood();
	Mat img = person.getImg();
	
	//open the file the user wants to write the data to
	ofstream file;
	file.open(filename);
	file << ID << "   ";
	file << sex << "   ";
	file << age << "   ";
	file << mood.getMood() << "   ";
	file << mood.getHugLevel() << "   \n";
	file.close();
	
	//write the mat img
	std::string imageName;
	imageName = ID + ".jpg";
	imwrite(imageName, img);
	
	
}

/** @brief This method will clear the database in the specified file name
  * @param fileName
  * @return nothing
  */
void clear(const char* fileName) {
	remove(fileName);
}


