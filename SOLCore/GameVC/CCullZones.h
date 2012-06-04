#ifndef __CCULLZONES_H
#define __CCULLZONES_H

#include "../StdInc.h"

class CCullZones{
public:
    static int AddCullZone(CVector& Center,
                  float LowerLeft_X,
                  float UpperRight_X,
                  float LowerLeft_Y,
                  float UpperRight_Y,
                  float LowerLeft_Z,
                  float UpperRight_Z,
                  uint32_t dwFlags,
                  int iUnk);
};

#endif