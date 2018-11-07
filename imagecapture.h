
#ifndef IMAGECAPTURE_H
#define IMAGECAPTURE_H

#include "scan.h"

class imagecapture_class
{
  public:
    imagecapture_class();
    void capture();

  private:
    scan_class scan;
};

#endif
