#pragma once

#include "../StdInc.h"

class CCarCtrl {
public:
    static bool _cdecl PickNextNodeToFollowPath(CVehicle* pVehicle);
    static void _cdecl PickNextNodeToChaseCar(CVehicle* pVehicle, float fTargetX, float fTargetY, CVehicle* pTargetVehicle);
    static void _cdecl PickNextNodeRandomly(CVehicle* pVehicle);
    static byte _cdecl FindPathDirection(int nPreviousMainNode, int nCurrentNode, int nNextNode);
};