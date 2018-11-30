
#ifndef MOOD_H
#define MOOD_H

#include <vector>
#include <string>

class mood_class
{
  public:
    mood_class(vector<Rect>, vector<Rect>);
    std::vector<std::string> getMood();
    void setHugLevel(int);
    float getHugLevel();
    bool needHug();

  private:
    std::vector<std::string> mood;
    float huglevel;
};

#endif
