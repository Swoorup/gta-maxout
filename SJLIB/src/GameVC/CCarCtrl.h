#pragma once

#include "SJLIB/stdinc.h"

class CCarCtrl 
{
public:
    static bool _cdecl PickNextNodeToFollowPath(CVehicle* pVehicle);
    static void _cdecl PickNextNodeToChaseCar(CVehicle* pVehicle, float fTargetX, float fTargetY, CVehicle* pTargetVehicle);
    static void _cdecl PickNextNodeRandomly(CVehicle* pVehicle);
    static byte _cdecl FindPathDirection(int nPreviousMainNode, int nCurrentNode, int nNextNode);
    static bool _cdecl PickNextNodeAccordingStrategy(CVehicle* pVehicle);
    static void _cdecl UpdateCarOnRails(CVehicle* pVehicle);
	static void _cdecl FindLinksToGoWithTheseNodes(CVehicle* pVehicle);
	static void _cdecl JoinCarWithRoadSystem(CVehicle* pVehicle);

    static void _cdecl SlowCarOnRailsDownForTrafficAndLights(CVehicle *pVehicle);
    static void _cdecl DragCarToPoint(CVehicle* pVehicle, CVector* pvecGotoPoint);
	
};