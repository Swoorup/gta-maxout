#ifndef __CFILELOADER_H
#define __CFILELOADER_H

#include "SJLIB/stdinc.h"

class CFileLoader{

public:
    static void LoadLevel(const char* szDatFile);
    static void LoadObjectInstance(const char* szInstLine);
    static void LoadScene(const char* szSceneFile);
    static int AddOcclusions(float fMidX, 
                             float fMidY, 
                             float fBottomZ, 
                             float fWidthX, 
                             float fWidthY, 
                             float fBoxHeight, 
                             float fRotation);
};

#endif