
#ifndef DISPLAY_H
#define DISPLAY_H

#include <fstream>
#include <imagecapture.h>


class display_class
{
  public: 
    display_class(std::ifstream img);
    void gui();

  private:
    std::ifstream image;
    imagecapture_class image_capture;
};

#endif

