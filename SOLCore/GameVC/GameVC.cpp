#include "GameVC.h"

#define Func_FindPlayerCentreOfWorld_NoSniperShift 0x4BC020
#define Func_FindPlayerPed                         0x4BC120
#define Func_LoadingScreen                         0x4A69D0

/*****************************************************************************/
/** Game Global functions mapping						                    **/
/*****************************************************************************/

FindPlayerCentreOfWorld_NoSniperShift_t				    FindPlayerCentreOfWorld_NoSniperShift =				(FindPlayerCentreOfWorld_NoSniperShift_t)			    Func_FindPlayerCentreOfWorld_NoSniperShift;
FindPlayerPed_t                                         FindPlayerPed                         =             (FindPlayerPed_t)                                       Func_FindPlayerPed;
LoadingScreen_t                                         LoadingScreen                         =             (LoadingScreen_t)                                       Func_LoadingScreen;

//----------------------------------------------------------------
// Global Variables for the game
//----------------------------------------------------------------
CCamera& TheCamera = *(CCamera*)0x7E4688;