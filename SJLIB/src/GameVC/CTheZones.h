#ifndef __CTHEZONES_H
#define __CTHEZONES_H

#include "SJLIB/stdinc.h"

class CTheZones{
public:
    static void CreateZone(const char* szName, 
                            int iType, 
                            float fX1, 
                            float fY1, 
                            float fZ1,
                            float fX2,
                            float fY2,
                            float fZ2,
                            int iIsland);
};

#endif