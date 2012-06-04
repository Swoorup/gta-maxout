#ifndef GAMEVC_H
#define GAMEVC_H
#include "..\main.h"

typedef RwV3d* (__cdecl *FindPlayerCentreOfWorld_NoSniperShift_t)(void);  
extern FindPlayerCentreOfWorld_NoSniperShift_t FindPlayerCentreOfWorld_NoSniperShift;

typedef int (__cdecl *FindPlayerPed_t)(void);
extern FindPlayerPed_t FindPlayerPed;

typedef void (__cdecl *LoadingScreen_t)(char const *gameStateText, char const *loadingStageText, char const *);
extern LoadingScreen_t LoadingScreen;
#endif