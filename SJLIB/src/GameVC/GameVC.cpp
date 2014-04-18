#include "SJLIB/stdinc.h"

#define Func_FindPlayerCentreOfWorld_NoSniperShift 0x4BC020
#define Func_FindPlayerPed                         0x4BC120
#define Func_LoadingScreen                         0x4A69D0
#define FUnc_FindPlayerVehicle                     0x4BC1E0
#define Func_FindPlayerCoors                       0x4BC240

/*****************************************************************************/
/** Game Global functions mapping						                    **/
/*****************************************************************************/

FindPlayerCentreOfWorld_NoSniperShift_t				    FindPlayerCentreOfWorld_NoSniperShift =				(FindPlayerCentreOfWorld_NoSniperShift_t)			    Func_FindPlayerCentreOfWorld_NoSniperShift;
FindPlayerPed_t                                         FindPlayerPed                         =             (FindPlayerPed_t)                                       Func_FindPlayerPed;
LoadingScreen_t                                         LoadingScreen                         =             (LoadingScreen_t)                                       Func_LoadingScreen;
FindPlayerVehicle_t                                     FindPlayerVehicle                     =             (FindPlayerVehicle_t)                                   FUnc_FindPlayerVehicle;
FindPlayerCoors_t                                       FindPlayerCoors                       =             (FindPlayerCoors_t)                                     Func_FindPlayerCoors;

//----------------------------------------------------------------
// Global Variables for the game
//----------------------------------------------------------------
CCameraVC& TheCamera = *(CCameraVC*)0x7E4688;