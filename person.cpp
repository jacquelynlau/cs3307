#include "person.h"

/** @brief The constructor for the person obj class (will initialize all the variables we need to have for the person)
  * @param iD, sex, age, moodd, image
  * @return nothing
  */
person_class :: person_class(int iD, std::string sexx, int agee, mood_class moodd, cv::Mat image) {
  id = iD;
  sex = sexx;
  age = agee;
  mood = moodd;
  img = image;
}

/** @brief Returns the sex of the person
  * @param nothing
  * @return their sex
  */
std::string person_class :: getsex() {
  return sex;
}

/** @brief Sets the sex of the person
  * @param nothing
  * @return nothing
  */
void person_class :: setSex(std::string sexx) {
  sex = sexx;
}

/** @brief returns the age of the person
  * @param nothing
  * @return the age of the person
  */
int person_class :: getAge() {
  return age; 
}

/** @brief returns the mood of the person
  * @param nothing
  * @return mood obj
  */
mood_class person_class :: getMood() {
  return mood;
}

/** @brief returns their ID. Each person obj will have a unique ID
  * @param nothing
  * @return their associated ID.
  */
int person_class :: getID() {
  return id; 
}

/** @brief sets the age of the person
  * @param agee
  * @return nothing
  */
void person_class :: setAge(int agee) {
  age = agee;
}

/** @brief sets the mood for the person
  * @param mood obj newMood
  * @return the new mood
  */
void person_class :: setMood(mood_class newMood) {
  mood = newMood;
}

/** @brief retrieves their photo
  * @param nothing
  * @return their picture
  */
Mat person_class :: getImg() {
  return img; 
}

/** @brief sets the image for the associated person
  * @param image
  * @return nothing
  */
void person_class :: setImg(Mat image) {
  img = image; 
}
}
