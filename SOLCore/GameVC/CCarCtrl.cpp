#include "../StdInc.h"

#define THEPATHS CGameVariables::GetPathFind()

#ifdef INSTALL_PATCH_FOR_VCPATH_INSTANCE
/* 
 * This function has weird effects on traffic vehicles. It does not
 * even follow the paths. 
 * This functions may be incorrect.
 */
//420D50h
bool _cdecl CCarCtrl::PickNextNodeToFollowPath(CVehicle* pVehicle) {
    //calls tlsSetValue 
    //unused?
    /*_dwHookArgOne = pVehicle->field_1A6;

    if (_dwHookArgOne) {
        _asm mov _dwHookArgOne, eax
        _asm push eax
        _asm mov eax, 649A30h
        _asm call eax
        _asm pop eax
    }*/

    int nPreviousNextNodeIndex = pVehicle->Autopilot.m_dwNextNodeIndex;
    if(!pVehicle->Autopilot.m_nRouteListStep) {
        THEPATHS->DoPathSearch(0, pVehicle->__parent.__parent.matrix.rwMatrix.vPos.x,
            pVehicle->__parent.__parent.matrix.rwMatrix.vPos.y,
            pVehicle->__parent.__parent.matrix.rwMatrix.vPos.z,
            pVehicle->Autopilot.m_dwNextNodeIndex,
            pVehicle->Autopilot.m_vecTargetPoint.fX,
            pVehicle->Autopilot.m_vecTargetPoint.fY,
            pVehicle->Autopilot.m_vecTargetPoint.fZ,
            pVehicle->Autopilot.m_pIntermediateRouteList,
            &pVehicle->Autopilot.m_nRouteListStep,
            8,
            pVehicle,
            0,
            999999.88f,
            -1);
        if(pVehicle->Autopilot.m_nRouteListStep < 2) {
            return true;
        }
        pVehicle->Autopilot.RemoveOnePathNode();
    }
    pVehicle->Autopilot.m_dwPrevMainNode = pVehicle->Autopilot.m_dwMainNode;
    pVehicle->Autopilot.m_dwMainNode = pVehicle->Autopilot.m_dwNextNodeIndex;
    if(pVehicle->Autopilot.m_pIntermediateRouteList[0] < &THEPATHS->m_AttachedPaths[0] || pVehicle->Autopilot.m_pIntermediateRouteList[0] > &THEPATHS->m_AttachedPaths[THEPATHS->m_nAttachedNodes -1]){
        //sometimes the m_pIntermediateRouteList contains inappropriate value which is below m_AttachedPaths[0] temp fix
        char buf[256];
        sprintf(buf, "Intermediate Address: 0x%X \nStupidNode: 0x%X", pVehicle->Autopilot.m_pIntermediateRouteList, pVehicle->Autopilot.m_pIntermediateRouteList[0]);
        CDebug::DebugAddText(buf);
        //MessageBoxA(NULL, buf, NULL, NULL);
        return false;
    }
    pVehicle->Autopilot.m_dwNextNodeIndex = ((uint32_t)pVehicle->Autopilot.m_pIntermediateRouteList[0] - (uint32_t)&THEPATHS->m_AttachedPaths[0])/sizeof(CPathNode);
    pVehicle->Autopilot.RemoveOnePathNode();
    pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor += pVehicle->Autopilot.m_dwNextSpeedScaleFactor;
    pVehicle->Autopilot.m_dwPrevDetachedNodeIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
    pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
    pVehicle->Autopilot.m_bytePrevDirectionScale = pVehicle->Autopilot.m_byteCurrentDirectionScale;
    pVehicle->Autopilot.m_byteCurrentDirectionScale = pVehicle->Autopilot.m_byteNextDirectionScale;
    pVehicle->Autopilot.m_byteCurrentLanes = pVehicle->Autopilot.m_byteNextLanes;

    int nMainRouteInfoIndex = THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwMainNode].wRouteInfoIndex;
    int nConnectedNodeIndex = 0;
    while(pVehicle->Autopilot.m_dwNextNodeIndex != (THEPATHS->m_infoConnectedNodes[nMainRouteInfoIndex + nConnectedNodeIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY)) {
        nConnectedNodeIndex++;
    }

    pVehicle->Autopilot.m_dwNextDetachedNodeIndex = THEPATHS->DetachedPointsInfo[nMainRouteInfoIndex + nConnectedNodeIndex];

    int nRequiredLanes;
    if(nPreviousNextNodeIndex >= pVehicle->Autopilot.m_dwNextNodeIndex) {
        pVehicle->Autopilot.m_byteNextDirectionScale = 1;
        nRequiredLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitRightLanes;
    }
    else {
        pVehicle->Autopilot.m_byteNextDirectionScale = -1;
        nRequiredLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitLeftLanes;
    }

    CVector2D v2dCurrentDirection, v2dNextDirection;
    int dwCurrentDetachedIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
    int dwNextDetachedIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
    v2dCurrentDirection.fX = (float)pVehicle->Autopilot.m_byteCurrentDirectionScale * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedIndex].NormalVecX) / 100.0f;
    v2dCurrentDirection.fY = (float)pVehicle->Autopilot.m_byteCurrentDirectionScale * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedIndex].NormalVecY) / 100.0f;
    v2dNextDirection.fX = (float)pVehicle->Autopilot.m_byteNextDirectionScale * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedIndex].NormalVecX) / 100.0f;
    v2dNextDirection.fY = (float)pVehicle->Autopilot.m_byteNextDirectionScale * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedIndex].NormalVecY) / 100.0f;
    CVector2D v2dCurrentPoint, v2dNextPoint;
    v2dCurrentPoint.fX = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedIndex].wX) / 8.0f;
    v2dCurrentPoint.fY = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedIndex].wY) / 8.0f;
    v2dNextPoint.fX = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedIndex].wX) / 8.0f;
    v2dNextPoint.fY = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedIndex].wY) / 8.0f;
    if(nRequiredLanes >= 0) {
        float fDisplacement = (v2dNextPoint.fY - v2dCurrentPoint.fY) * (v2dNextPoint.fY - v2dCurrentPoint.fY) + (v2dNextPoint.fX - v2dCurrentPoint.fX) * (v2dNextPoint.fX - v2dCurrentPoint.fX);
        if(fDisplacement > 49.0f && !(rand() & 0x600)) {
            bool bRandTest = rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY;
            if(bRandTest) {
                pVehicle->Autopilot.m_byteNextLanes++;
            }
            else {
                pVehicle->Autopilot.m_byteNextLanes--;
            }
        }
        if(pVehicle->Autopilot.m_byteNextLanes >= nRequiredLanes - 1) {
            pVehicle->Autopilot.m_byteNextLanes = nRequiredLanes - 1;
        }
        if(pVehicle->Autopilot.m_byteNextLanes <= 0) {
            pVehicle->Autopilot.m_byteNextLanes = 0;
        }
    }
    else {
        pVehicle->Autopilot.m_byteNextLanes = pVehicle->Autopilot.m_byteCurrentLanes;
    }
    if((pVehicle->Autopilot.m_flags >> 3) & 1) {
        pVehicle->Autopilot.m_byteNextLanes = 0;
    }
    float fCurrentLaneLength = (THEPATHS->m_DetachedNodes[dwCurrentDetachedIndex].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
    float fNextLaneLength = (THEPATHS->m_DetachedNodes[dwNextDetachedIndex].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
    CVector2D v2dCurrentTest, v2dNextTest;
    v2dCurrentTest.fX = v2dCurrentPoint.fX + v2dCurrentDirection.fY * fCurrentLaneLength;
    v2dCurrentTest.fY = v2dCurrentPoint.fY - v2dCurrentDirection.fX * fCurrentLaneLength;
    v2dNextTest.fX = v2dNextPoint.fX + v2dNextDirection.fY * fNextLaneLength;
    v2dNextTest.fY = v2dNextPoint.fY - v2dNextDirection.fX * fNextLaneLength;

    pVehicle->Autopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentTest, &v2dNextTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f / pVehicle->Autopilot.m_fCurrentSpeed);
    if(pVehicle->Autopilot.m_dwNextSpeedScaleFactor <= 10) {
        pVehicle->Autopilot.m_dwNextSpeedScaleFactor = 10;
    }
    return false;
}

/*
 * This function is used for making up routes to go to
 * a certain coordinates.eg. When the cops are far away
 * this function is called and it assigns proper node 
 * indexes. When the cop is quite close enough then the
 * chase is carried out be a separate function which may
 * be not having any relation with the PathFind.
 * Note: The last parameter is not used anywhere.
 * TODO: correct the function which relies on processing
 * random values
 */
//4213A0h
void _cdecl CCarCtrl::PickNextNodeToChaseCar(CVehicle* pVehicle, float fTargetX, float fTargetY, CVehicle* pTargetVehicle) {
	//calls tlsSetValue 
    //unused random?
    /*_dwHookArgOne = pVehicle->field_1A6;

    if (_dwHookArgOne) {
        _asm mov _dwHookArgOne, eax
        _asm push eax
        _asm mov eax, 649A30h
        _asm call eax
        _asm pop eax
    }*/
	int dwMainNode = pVehicle->Autopilot.m_dwMainNode;
	int dwNextNode = pVehicle->Autopilot.m_dwNextNodeIndex;
	
	// the start node vector is taken from the next node
	CVector vecStart;
	vecStart.fX = (float)(THEPATHS->m_AttachedPaths[dwNextNode].wX) / 8.0f;
	vecStart.fY = (float)(THEPATHS->m_AttachedPaths[dwNextNode].wY) / 8.0f;
	vecStart.fZ = (float)(THEPATHS->m_AttachedPaths[dwNextNode].wZ) / 8.0f;
	
	CPathNode* pInstantRoutes[2];
	short sRouteStep;
	float fNodeDistance;
	int nNodeWithSmallestDiversion, nFoundConnectedBit;
	
	THEPATHS->DoPathSearch(0, vecStart.fX, vecStart.fY, vecStart.fZ, dwNextNode, fTargetX, fTargetY, 0.0f, pInstantRoutes, &sRouteStep, 2, pVehicle, &fNodeDistance, 999999.88f, -1);
	if(sRouteStep != 1 && sRouteStep != 2 || pInstantRoutes[0] == &THEPATHS->m_AttachedPaths[dwNextNode]) {
		if(sRouteStep != 2 || pInstantRoutes[1] == &THEPATHS->m_AttachedPaths[dwNextNode]) {
			CVector2D v2dVehiclePos;
			v2dVehiclePos.fX = fTargetX - pVehicle->__parent.__parent.matrix.rwMatrix.vPos.x;
			v2dVehiclePos.fY = fTargetY - pVehicle->__parent.__parent.matrix.rwMatrix.vPos.y;
			float fTargetAngle = CGeneral::GetATanOfXY(v2dVehiclePos);
			int nConnectedSets = THEPATHS->m_AttachedPaths[dwNextNode].bitnumberOfNodesConnected;
			float fPreviousFoundAngle = 10.0f;
			for(int i = 0; i < nConnectedSets; i++) {
				int nNext = THEPATHS->m_infoConnectedNodes[i + THEPATHS->m_AttachedPaths[dwNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
				if(nNext != dwMainNode || nConnectedSets <= 1) {
					CVector2D v2dDeltaRelativeCarNode;
					v2dDeltaRelativeCarNode.fX = (float)(THEPATHS->m_AttachedPaths[nNext].wX) / 8.0f - vecStart.fX;
					v2dDeltaRelativeCarNode.fY = (float)(THEPATHS->m_AttachedPaths[nNext].wY) / 8.0f - vecStart.fY;
					float fTestAngle = CGeneral::GetATanOfXY(v2dDeltaRelativeCarNode);
					float fCurrentAngleDiff = utl::abs<float>(utl::AdjustLimitsToAngle(fTestAngle - fTargetAngle, -M_PI, M_PI));
					if(fCurrentAngleDiff <= fPreviousFoundAngle) {
						fPreviousFoundAngle = fCurrentAngleDiff;
						nNodeWithSmallestDiversion = nNext;
						nFoundConnectedBit = i;
					}
				}
			}
		}
		else {
			nNodeWithSmallestDiversion = pInstantRoutes[1] - &THEPATHS->m_AttachedPaths[0];
			nFoundConnectedBit = 0;
			int nNextNodeRouteIndex = THEPATHS->m_AttachedPaths[dwNextNode].wRouteInfoIndex;
			while (nNodeWithSmallestDiversion != (THEPATHS->m_infoConnectedNodes[nNextNodeRouteIndex + nFoundConnectedBit] & CPathFind::em_infoConnectedNodesNODEINDEXONLY)) {
				nFoundConnectedBit++;
			}
		}
	}
	else {
		nNodeWithSmallestDiversion = pInstantRoutes[0] - &THEPATHS->m_AttachedPaths[0];
		nFoundConnectedBit = 0;
		int nNextNodeRouteIndex = THEPATHS->m_AttachedPaths[dwNextNode].wRouteInfoIndex;
		while (nNodeWithSmallestDiversion != (THEPATHS->m_infoConnectedNodes[nNextNodeRouteIndex + nFoundConnectedBit] & CPathFind::em_infoConnectedNodesNODEINDEXONLY)) {
			nFoundConnectedBit++;
		}
	}
	
	pVehicle->Autopilot.m_dwPrevMainNode = pVehicle->Autopilot.m_dwMainNode;
	pVehicle->Autopilot.m_dwMainNode = pVehicle->Autopilot.m_dwNextNodeIndex;
	pVehicle->Autopilot.m_dwNextNodeIndex = nNodeWithSmallestDiversion;
	pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor += pVehicle->Autopilot.m_dwNextSpeedScaleFactor;
	pVehicle->Autopilot.m_dwPrevDetachedNodeIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
	pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	pVehicle->Autopilot.m_bytePrevDirectionScale = pVehicle->Autopilot.m_byteCurrentDirectionScale;
	pVehicle->Autopilot.m_byteCurrentDirectionScale = pVehicle->Autopilot.m_byteNextDirectionScale;
	pVehicle->Autopilot.m_byteCurrentLanes = pVehicle->Autopilot.m_byteNextLanes;
	pVehicle->Autopilot.m_dwNextDetachedNodeIndex = THEPATHS->DetachedPointsInfo[nFoundConnectedBit + THEPATHS->m_AttachedPaths[dwNextNode].wRouteInfoIndex];
	
	int nRequiredLanes;
	if(dwNextNode >= pVehicle->Autopilot.m_dwNextNodeIndex) {
		pVehicle->Autopilot.m_byteNextDirectionScale = 1;
		nRequiredLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitRightLanes;
	}
	else {
		pVehicle->Autopilot.m_byteNextDirectionScale = -1;
		nRequiredLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitLeftLanes;
	}
	int dwCurrentDetachedNode = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
	int dwNextDetachedNode = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	CVector2D v2dCurrentDirection, v2dNextDirection;
	v2dCurrentDirection.fX = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].NormalVecX) / 100.0f;
	v2dCurrentDirection.fY = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].NormalVecY) / 100.0f;
	v2dNextDirection.fX = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].NormalVecX) / 100.0f;
	v2dNextDirection.fY = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].NormalVecY) / 100.0f;
	
	CVector vecCurrentDetached, vecNextDetached;
	vecCurrentDetached.fX = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].wX) / 8.0f;
	vecCurrentDetached.fY = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].wY) / 8.0f;
	vecNextDetached.fX = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].wX) / 8.0f;
	vecNextDetached.fY = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].wY) / 8.0f;
	if(nRequiredLanes >= 0) {
		float fDetachedDisplacement = (vecNextDetached.fY - vecCurrentDetached.fY) * (vecNextDetached.fY - vecCurrentDetached.fY) + (vecNextDetached.fX - vecCurrentDetached.fX) * (vecNextDetached.fX - vecCurrentDetached.fX);
		if(fDetachedDisplacement > 49.0f) {
			int eAutoPilotBehaviour = pVehicle->Autopilot.m_DriverBehaviour;
			if(eAutoPilotBehaviour != 2 && eAutoPilotBehaviour != 4 && eAutoPilotBehaviour != 15 && eAutoPilotBehaviour != 17 && !(rand() & 0x600)) {
				if(rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY) {
					pVehicle->Autopilot.m_byteNextLanes++;
				}
				else {
					pVehicle->Autopilot.m_byteNextLanes--;
				}
			}
		}
		if(pVehicle->Autopilot.m_byteNextLanes >= (nRequiredLanes - 1)) {
			pVehicle->Autopilot.m_byteNextLanes = nRequiredLanes - 1;
		}
		if(pVehicle->Autopilot.m_byteNextLanes <= 0) {
			pVehicle->Autopilot.m_byteNextLanes = 0;
		}
	}
	else {
		pVehicle->Autopilot.m_byteNextLanes = pVehicle->Autopilot.m_byteCurrentLanes;
	}
	if((pVehicle->Autopilot.m_flags >> 3) & 1) {
		pVehicle->Autopilot.m_byteNextLanes = 0;
	}
	float fCurrentLaneLength = (THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
	float fNextLaneLength = (THEPATHS->m_DetachedNodes[dwNextDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
	CVector2D v2dCurrentDetachedTest, v2dNextDetachedTest;
	v2dCurrentDetachedTest.fX = vecCurrentDetached.fX + v2dCurrentDirection.fY * fCurrentLaneLength;
	v2dCurrentDetachedTest.fY = vecCurrentDetached.fY - v2dCurrentDirection.fX * fCurrentLaneLength;
	v2dNextDetachedTest.fX = vecNextDetached.fX + v2dNextDirection.fY * fNextLaneLength;
	v2dNextDetachedTest.fY = vecNextDetached.fY - v2dNextDirection.fX * fNextLaneLength;
	
	pVehicle->Autopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentDetachedTest, &v2dNextDetachedTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f/ pVehicle->Autopilot.m_fCurrentSpeed);
	if(pVehicle->Autopilot.m_dwNextSpeedScaleFactor <= 10) {
		pVehicle->Autopilot.m_dwNextSpeedScaleFactor = 10;
	}
}

/*
 * This function assigns random node indexes to a vehicle so
 * that the vehicle would follow a random route in the game.
 * All the traffic vehicles are usually initiated and made to 
 * follow a random route by this function.
 */
 //421F70h
void _cdecl CCarCtrl::PickNextNodeRandomly(CVehicle* pVehicle) {
	//calls tlsSetValue 
    //unused random function?
    /*_dwHookArgOne = pVehicle->field_1A6;

    if (_dwHookArgOne) {
        _asm mov _dwHookArgOne, eax
        _asm push eax
        _asm mov eax, 649A30h
        _asm call eax
        _asm pop eax
    }*/
	
	int dwPrevNextNode = pVehicle->Autopilot.m_dwNextNodeIndex;
	int nNextConnectedSets = THEPATHS->m_AttachedPaths[dwPrevNextNode].bitnumberOfNodesConnected;
	int dwPrevMainNode = pVehicle->Autopilot.m_dwMainNode;
	int dwNextDetachedNode = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	int nRequiredLanes = 0;
	bool bIsFirstOtherLaneNull = false;
	if(THEPATHS->m_DetachedNodes[dwNextDetachedNode].nIndexToAttachedNode == dwPrevNextNode) {
		nRequiredLanes = THEPATHS->m_DetachedNodes[dwNextDetachedNode].bitLeftLanes;
		bIsFirstOtherLaneNull = THEPATHS->m_DetachedNodes[dwNextDetachedNode].bitRightLanes == 0 ? true : false;
	}
	else {
		nRequiredLanes = THEPATHS->m_DetachedNodes[dwNextDetachedNode].bitRightLanes;
		bIsFirstOtherLaneNull = THEPATHS->m_DetachedNodes[dwNextDetachedNode].bitLeftLanes == 0 ? true : false;
	}
	
	unsigned char byteAutoNextLane = pVehicle->Autopilot.m_byteNextLanes;
	unsigned char byteTestPathDirection = 0;
	if(byteAutoNextLane == 0) {
		byteTestPathDirection = 4;
	}
	if(byteAutoNextLane == nRequiredLanes -1) {
		byteTestPathDirection = 2;
	}
	if(nRequiredLanes < 3 || byteTestPathDirection == 0) {
		byteTestPathDirection = 1;
	}
	pVehicle->Autopilot.m_dwPrevMainNode = pVehicle->Autopilot.m_dwMainNode;
	pVehicle->Autopilot.m_dwMainNode = pVehicle->Autopilot.m_dwNextNodeIndex;
	int nLoopConnectedBits = 0;
    int nRandomConnectedBit = 0;
	while(nLoopConnectedBits < 15) {
		nRandomConnectedBit = rand() % nNextConnectedSets;
		pVehicle->Autopilot.m_dwNextNodeIndex = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
		unsigned char bytePathDirection = CCarCtrl::FindPathDirection(dwPrevMainNode, dwPrevNextNode, pVehicle->Autopilot.m_dwNextNodeIndex);
		
		bool bIsOtherLaneNull = false;
		bool bIsTestLaneNull = false;
		int nTestDetachedRoute = THEPATHS->DetachedPointsInfo[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
		if(THEPATHS->m_DetachedNodes[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
			bIsOtherLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			bIsTestLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
		}
		else {
			bIsOtherLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			bIsTestLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
		}
		int dwNextDeltaNode = pVehicle->Autopilot.m_dwNextNodeIndex;
		if(dwPrevMainNode != dwNextDeltaNode && (byteTestPathDirection & bytePathDirection)) {
			if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitUnknownFlag3) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitUnknownFlag3){
				if((!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode)
				&& (!((pVehicle->Autopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
				|| (THEPATHS->m_AttachedPaths[dwPrevMainNode].bitRestrictedAccess)) && bIsOtherLaneNull == false
				&& (bIsFirstOtherLaneNull == false || bIsTestLaneNull == false)){
					break;
				}
			}
		}
		nLoopConnectedBits++;
	}
	if(nLoopConnectedBits >= 15) {
		for(nLoopConnectedBits = 0; nLoopConnectedBits < 15; nLoopConnectedBits++) {
			nRandomConnectedBit = rand() % nNextConnectedSets;
			pVehicle->Autopilot.m_dwNextNodeIndex = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
			bool bIsOtherLaneNull = false;
			int nTestDetachedRoute = THEPATHS->DetachedPointsInfo[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
			if(THEPATHS->m_DetachedNodes[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
				bIsOtherLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			}
			else {
				bIsOtherLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			}
			int dwNextDeltaNode = pVehicle->Autopilot.m_dwNextNodeIndex;
			if(dwPrevMainNode != dwNextDeltaNode) {
				if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode) {
					if((!((pVehicle->Autopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
					|| THEPATHS->m_AttachedPaths[dwPrevMainNode].bitRestrictedAccess) && bIsOtherLaneNull == false) {
						break;
					}
				}
			}
		}
	}
	if(nLoopConnectedBits >= 15) {
		for(nRandomConnectedBit = 0; nRandomConnectedBit < nNextConnectedSets; nRandomConnectedBit++) {
			pVehicle->Autopilot.m_dwNextNodeIndex = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
			bool bIsTestLaneNull = false;
			int nTestDetachedRoute = THEPATHS->DetachedPointsInfo[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
			if(THEPATHS->m_DetachedNodes[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
				bIsTestLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			}
			else {
				bIsTestLaneNull = THEPATHS->m_DetachedNodes[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			}
			if(bIsTestLaneNull == false) {
				int dwNextDeltaNode = pVehicle->Autopilot.m_dwNextNodeIndex;
				if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode) {
					if(!((pVehicle->Autopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
					|| THEPATHS->m_AttachedPaths[dwPrevMainNode].bitRestrictedAccess) {
						nRandomConnectedBit = 1000;
					}
				}
			}
		}
		if(nRandomConnectedBit < 999) {
			pVehicle->Autopilot.m_dwNextNodeIndex = dwPrevMainNode;
		}
	}
	if(dwPrevMainNode == pVehicle->Autopilot.m_dwNextNodeIndex) {
		pVehicle->__parent.__parent.flags = pVehicle->__parent.__parent.flags & 7 | 0x18;
		pVehicle->Autopilot.m_DriverBehaviour = 1;
		pVehicle->Autopilot.m_eSimpleAction = 0;
		pVehicle->Autopilot.m_snGettingNewCommandTimeStamp = CGameVariables::GetTimeInMilliseconds();
		pVehicle->Autopilot.m_snUnknownTimeStamp = CGameVariables::GetTimeInMilliseconds();
	}
	pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor += pVehicle->Autopilot.m_dwNextSpeedScaleFactor;
	pVehicle->Autopilot.m_dwPrevDetachedNodeIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
	pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	pVehicle->Autopilot.m_bytePrevDirectionScale = pVehicle->Autopilot.m_byteCurrentDirectionScale;
	pVehicle->Autopilot.m_byteCurrentDirectionScale = pVehicle->Autopilot.m_byteNextDirectionScale;
	pVehicle->Autopilot.m_byteCurrentLanes = pVehicle->Autopilot.m_byteNextLanes;
	pVehicle->Autopilot.m_dwNextDetachedNodeIndex = THEPATHS->DetachedPointsInfo[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
	
	int dwNextLanes;
	if(dwPrevNextNode >= pVehicle->Autopilot.m_dwNextNodeIndex) {
		pVehicle->Autopilot.m_byteNextDirectionScale = 1;
		dwNextLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitLeftLanes;
	}
	else {
		pVehicle->Autopilot.m_byteNextDirectionScale = -1;
		dwNextLanes = THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitRightLanes;
	}
	CVector2D v2dCurrentDirection, v2dNextDirection, v2dCurrentDetachedTest, v2dNextDetachedTest;
	v2dCurrentDirection.fX = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex].NormalVecX) / 100.0f;
	v2dCurrentDirection.fY = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex].NormalVecY) / 100.0f;
	v2dNextDirection.fX = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].NormalVecX) / 100.0f;
	v2dNextDirection.fY = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].NormalVecY) / 100.0f;
	
	if(dwNextLanes >= 0) {
		if(!(rand() & 0x600)) {
			CVector2D v2dCurrentAttached, v2dNextAttached;
			v2dCurrentAttached.fX = (float)(THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwMainNode].wX) / 8.0f;
			v2dCurrentAttached.fY = (float)(THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwMainNode].wY) / 8.0f;
			v2dNextAttached.fX = (float)(THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwNextNodeIndex].wX) / 8.0f;
			v2dNextAttached.fY = (float)(THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwNextNodeIndex].wY) / 8.0f;
			
			float fAttachedNodeDisplacement = (v2dNextAttached.fY - v2dCurrentAttached.fY) * (v2dNextAttached.fY - v2dCurrentAttached.fY) + (v2dNextAttached.fX - v2dCurrentAttached.fX) * (v2dNextAttached.fX - v2dCurrentAttached.fX);
			if(fAttachedNodeDisplacement >= 196.0f) {
				if(rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY) {
					pVehicle->Autopilot.m_byteNextLanes++;
				}
				else {
					pVehicle->Autopilot.m_byteNextLanes--;
				}
			}
		}
		if(pVehicle->Autopilot.m_byteNextLanes >= (dwNextLanes - 1)) {
			pVehicle->Autopilot.m_byteNextLanes = dwNextLanes - 1;
		}
		if(pVehicle->Autopilot.m_byteNextLanes <= 0) {
			pVehicle->Autopilot.m_byteNextLanes = 0;
		}
	}
	else {
		pVehicle->Autopilot.m_byteNextLanes = pVehicle->Autopilot.m_byteCurrentLanes;
	}
	
	if((pVehicle->Autopilot.m_flags >> 3) & 1) {
		pVehicle->Autopilot.m_byteNextLanes = 0;
	}
	int dwTestCurrentDetachedNode = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
	int dwTestNextDetachedNode = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	float fCurrentLaneLength = (THEPATHS->m_DetachedNodes[dwTestCurrentDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
	float fNextLaneLength = (THEPATHS->m_DetachedNodes[dwTestNextDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
	v2dNextDetachedTest.fX = (float)(THEPATHS->m_DetachedNodes[dwTestNextDetachedNode].wX) / 8.0f + fNextLaneLength;
	v2dNextDetachedTest.fY = (float)(THEPATHS->m_DetachedNodes[dwTestNextDetachedNode].wY) / 8.0f - v2dNextDirection.fX * fNextLaneLength;
	v2dCurrentDetachedTest.fX = (float)(THEPATHS->m_DetachedNodes[dwTestCurrentDetachedNode].wX) / 8.0f + fCurrentLaneLength;
	v2dCurrentDetachedTest.fY = (float)(THEPATHS->m_DetachedNodes[dwTestCurrentDetachedNode].wY) / 8.0f - v2dCurrentDirection.fX * fCurrentLaneLength;
	
	pVehicle->Autopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentDetachedTest, &v2dNextDetachedTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f / pVehicle->Autopilot.m_fCurrentSpeed);
	if(pVehicle->Autopilot.m_dwNextSpeedScaleFactor <= 10){
		pVehicle->Autopilot.m_dwNextSpeedScaleFactor = 10;
		CDebug::DebugAddText("fout\n");
	}
}

//421DC0h
byte _cdecl CCarCtrl::FindPathDirection(int nPreviousMainNode, int nCurrentNode, int nNextNode) {
	CVector2D v2dCurrentNode, v2dPrevNodeFromCurrent, v2dNextNodeFromCurrent;
	v2dCurrentNode.fX = (float)(THEPATHS->m_AttachedPaths[nCurrentNode].wX) / 8.0f;
	v2dCurrentNode.fY = (float)(THEPATHS->m_AttachedPaths[nCurrentNode].wY) / 8.0f;
	v2dPrevNodeFromCurrent.fX = v2dCurrentNode.fX - (float)(THEPATHS->m_AttachedPaths[nPreviousMainNode].wX) / 8.0f;
	v2dPrevNodeFromCurrent.fY = v2dCurrentNode.fY - (float)(THEPATHS->m_AttachedPaths[nPreviousMainNode].wY) / 8.0f;
	v2dNextNodeFromCurrent.fX = (float)(THEPATHS->m_AttachedPaths[nNextNode].wX) / 8.0f - v2dCurrentNode.fX;
	v2dNextNodeFromCurrent.fY = (float)(THEPATHS->m_AttachedPaths[nNextNode].wY) / 8.0f - v2dCurrentNode.fY;
	
	if(v2dPrevNodeFromCurrent.Length() != 0.0f) {
		v2dPrevNodeFromCurrent.Normalize();
		if(v2dNextNodeFromCurrent.Length() != 0.0f){
			v2dNextNodeFromCurrent.Normalize();
			float fProduct = v2dPrevNodeFromCurrent.fX * v2dNextNodeFromCurrent.fY - v2dPrevNodeFromCurrent.fY * v2dNextNodeFromCurrent.fX;
			if(fProduct <= 0.76999998f) {
				if(fProduct < -0.76999998f) {
					return 2;
				}
				else {
					return 1;
				}
			}
			else {
				return 4;
			}
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

/*
 * The following functions calls the proper function which
 * assigns the path nodes to the car according to behavior
 * vehicle
 */
 //422A10h
bool _cdecl CCarCtrl::PickNextNodeAccordingStrategy(CVehicle* pVehicle) {
	pVehicle->Autopilot.m_byteSpeedLimit = THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwNextNodeIndex].bitSpeedLimit;
	switch(pVehicle->Autopilot.m_DriverBehaviour) {
		case 2:
		case 4:
        {
			CVehicle* pPlayerVehicle = FindPlayerVehicle();
			CVector vecPlayerPosition;
			FindPlayerCoors(&vecPlayerPosition);
			PickNextNodeToChaseCar(pVehicle, vecPlayerPosition.fX, vecPlayerPosition.fY, pPlayerVehicle);
			return false;
			break;
        }
		case 15:
		case 17:
			PickNextNodeToChaseCar(pVehicle, pVehicle->Autopilot.m_pTargetVehicle->__parent.__parent.matrix.rwMatrix.vPos.x, pVehicle->Autopilot.m_pTargetVehicle->__parent.__parent.matrix.rwMatrix.vPos.y, pVehicle->Autopilot.m_pTargetVehicle);
			return false;
			break;
		case 8:
		case 12:
			return PickNextNodeToFollowPath(pVehicle);
			break;
		default:
        {
			PickNextNodeRandomly(pVehicle);
			if(THEPATHS->m_AttachedPaths[pVehicle->Autopilot.m_dwNextNodeIndex].bitHaveUnrandomizedVehClass) {
				if(pVehicle->__parent.__parent.modelIndex == BOAT_RIO || pVehicle->__parent.__parent.modelIndex == BOAT_TROPIC || pVehicle->__parent.__parent.modelIndex == BOAT_MARQUIS) {
					pVehicle->Autopilot.m_nMaxSpeed = 0;
				}
			}
			return false;
			break;
        }
	}
}

/* This functions moves the car before the state it is
 * touched by the player. If this function is nopped 
 * then the car does not move in traffic until the player
 * touches the vehicle. It does not seem to have any 
 * effects on boats though.
 */
//425BF0h
void _cdecl CCarCtrl::UpdateCarOnRails(CVehicle* pVehicle) {
	if(pVehicle->Autopilot.m_eSimpleAction == 1) {
		pVehicle->__parent.velocity.x = 0.0f;
		pVehicle->__parent.velocity.y = 0.0f;
		pVehicle->__parent.velocity.z = 0.0f;
		pVehicle->Autopilot.ModifySpeed(0.0f);
		if(CGameVariables::GetTimeInMilliseconds() > pVehicle->Autopilot.m_simple_action_time) {
			pVehicle->Autopilot.m_eSimpleAction = 0;
			pVehicle->Autopilot.m_snGettingNewCommandTimeStamp = CGameVariables::GetTimeInMilliseconds();
			pVehicle->Autopilot.m_snUnknownTimeStamp = CGameVariables::GetTimeInMilliseconds();
		}
	}
	else {
		SlowCarOnRailsDownForTrafficAndLights(pVehicle);
		if(CGameVariables::GetTimeInMilliseconds() >= (int64_t)(pVehicle->Autopilot.m_dwNextSpeedScaleFactor + pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor)) {
			PickNextNodeAccordingStrategy(pVehicle);
		}
		if((pVehicle->__parent.__parent.flags >> 3) != 3) {
			float fTimeDelta = (float)(uint32_t)(CGameVariables::GetTimeInMilliseconds() - pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor) / (float)(pVehicle->Autopilot.m_dwNextSpeedScaleFactor);
			int dwCurrentDetachedNode = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
			CVector2D vecCurrentDirection, vecNextDirection;
			vecCurrentDirection.fX = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].NormalVecX) / 100.0f;
			vecCurrentDirection.fY = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].NormalVecY) / 100.0f;
			int dwNextDetachedNode = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
			vecNextDirection.fX = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].NormalVecX) / 100.0f;
			vecNextDirection.fY = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].NormalVecY) / 100.0f;
			
			float fCurrentLane = (THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
			float fNextLane = (THEPATHS->m_DetachedNodes[dwNextDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
			
			CVector2D vecCurrentLane, vecNextLane;
			vecCurrentLane.fX = (double)(((dwCurrentDetachedNode + pVehicle->__parent.__parent.uiPathMedianRand) & 7) - 3) * 0.0089999996f;
			vecCurrentLane.fY = (double)((((dwCurrentDetachedNode + pVehicle->__parent.__parent.uiPathMedianRand) >> 3) & 7) -3) * 0.0089999996f;
			vecNextLane.fX = (double)(((dwNextDetachedNode + pVehicle->__parent.__parent.uiPathMedianRand) & 7) - 3) * 0.0089999996f;
			vecNextLane.fY = (double)((((dwNextDetachedNode + pVehicle->__parent.__parent.uiPathMedianRand) >> 3) & 7) - 3) * 0.0089999996f;
			
			vecCurrentLane.fX += vecCurrentDirection.fX;
			vecCurrentLane.fY += vecCurrentDirection.fY;
			vecNextLane.fX += vecNextDirection.fX;
			vecNextLane.fY += vecNextDirection.fY;
			
			vecCurrentLane.Normalize();
			vecNextLane.Normalize();
			
			CVector vecCurrentDetachedTest, vecNextDetachedTest;
			vecCurrentDetachedTest.fZ = 0.0f;
			vecNextDetachedTest.fZ = 0.0f;
			
			vecCurrentDetachedTest.fX = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].wX) / 8.0f + vecCurrentDirection.fY * fCurrentLane;
			vecCurrentDetachedTest.fY = (float)(THEPATHS->m_DetachedNodes[dwCurrentDetachedNode].wY) / 8.0f - vecCurrentDirection.fX * fCurrentLane;
			vecNextDetachedTest.fX = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].wX) / 8.0f + vecNextDirection.fY * fNextLane;
			vecNextDetachedTest.fY = (float)(THEPATHS->m_DetachedNodes[dwNextDetachedNode].wY) / 8.0f - vecNextDirection.fX * fNextLane;
			
			CVector vecGotoPoint, vecRequiredVelocity;
			CCurves::CalcCurvePoint(&vecCurrentDetachedTest, &vecNextDetachedTest, &vecCurrentLane, &vecNextLane, fTimeDelta, pVehicle->Autopilot.m_dwNextSpeedScaleFactor, &vecGotoPoint, &vecRequiredVelocity);
			vecGotoPoint.fZ = 15.0f;
			DragCarToPoint(pVehicle, &vecGotoPoint);
			vecRequiredVelocity *= 0.016666668f;
			pVehicle->__parent.velocity.x = vecRequiredVelocity.fX;
			pVehicle->__parent.velocity.y = vecRequiredVelocity.fY;
			pVehicle->__parent.velocity.z = vecRequiredVelocity.fZ;
		}
	}
}

#endif

//4254C0h
void CCarCtrl::SlowCarOnRailsDownForTrafficAndLights(CVehicle *pVehicle) {
    _asm {
        push pVehicle
        mov eax, 4254C0h
        call eax
        add esp, 4
    }
}

void CCarCtrl::DragCarToPoint(CVehicle* pVehicle, CVector* pvecGotoPoint) {
    _asm {
        push pvecGotoPoint
        push pVehicle
        mov eax, 4208B0h
        call eax
        add esp, 8
    }
}