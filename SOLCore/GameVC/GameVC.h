#ifndef GAMEVC_H
#define GAMEVC_H

#include "..\StdInc.h"

typedef RwV3d* (__cdecl *FindPlayerCentreOfWorld_NoSniperShift_t)(void);  
typedef void (__cdecl *LoadingScreen_t)(char const *szGameStateText, char const *szLoadingStageText, char const *szUnusedStr);
typedef int (__cdecl *FindPlayerPed_t)(void);

extern FindPlayerCentreOfWorld_NoSniperShift_t FindPlayerCentreOfWorld_NoSniperShift;
extern FindPlayerPed_t FindPlayerPed;
extern LoadingScreen_t LoadingScreen;

extern CCamera& TheCamera;

#endif