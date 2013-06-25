#ifndef __CWORLD_H
#define __CWORLD_H

#include "../StdInc.h"

#define WORLDSECTORX 80
#define WORLDSECTORY 80

#define SL_BUILDINGCENTER 0
#define SL_BUILDINGEDGE 1
#define SL_OBJECTCENTER 2
#define SL_OBJECTEDGE 3
#define SL_VEHICLECENTER 4
#define SL_VEHICLEEDGE 5
#define SL_PEDCENTER 6
#define SL_PEDEDGE 7
#define SL_DUMMYCENTER 8
#define SL_DUMMYEDGE 9

class CSector 
{
public:
    CPtrList stNodeLists[10]; // 0-40
    //node lists, for every type a center list and an edge list
};

class CSectorList
{
public:
	CSector n[WORLDSECTORX * WORLDSECTORY];
};

class CWorld
{
public:
	// Variables
	static CSectorList& stSectorList;

	// Methods
    static bool _cdecl GetIsLineOfSightClear(CVector *a, CVector *b,unsigned char cc , unsigned char dc , unsigned char ec , unsigned char fc, unsigned char gc, unsigned char hcc, unsigned char ic);
    static float _cdecl FindGroundZFor3DCoord(float fX, float fY, float fZ, bool* bOutDoesGroundExist);
};

#endif