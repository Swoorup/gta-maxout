#include "../StdInc.h"

#ifdef INSTALL_PATCH_FOR_VCPATH_INSTANCE

/* 
 * This function has weird effects on traffic vehicles. It does not
 * even follow the paths. 
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
        CGameVariables::GetPathFind()->DoPathSearch(0, pVehicle->__parent.__parent.matrix.rwMatrix.vPos.x,
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
    pVehicle->Autopilot.m_dwNextNodeIndex = pVehicle->Autopilot.m_pIntermediateRouteList[0] - &pThePaths->m_AttachedPaths[0];
    pVehicle->Autopilot.RemoveOnePathNode();
    pVehicle->Autopilot.m_dwCurrentSpeedScaleFactor += pVehicle->Autopilot.m_dwNextSpeedScaleFactor;
    pVehicle->Autopilot.m_dwPrevDetachedNodeIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
    pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
    pVehicle->Autopilot.m_bytePrevDirectionScale = pVehicle->Autopilot.m_byteCurrentDirectionScale;
    pVehicle->Autopilot.m_byteCurrentDirectionScale = pVehicle->Autopilot.m_byteNextDirectionScale;
    pVehicle->Autopilot.m_byteCurrentLanes = pVehicle->Autopilot.m_byteNextLanes;

    int nMainRouteInfoIndex = CGameVariables::GetPathFind()->m_AttachedPaths[pVehicle->Autopilot.m_dwMainNode].wRouteInfoIndex;
    int nConnectedNodeIndex = 0;
    while(pVehicle->Autopilot.m_dwNextNodeIndex != (CGameVariables::GetPathFind()->AttachedPointsInfo[nMainRouteInfoIndex + nConnectedNodeIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY)) {
        nConnectedNodeIndex++;
    }

    pVehicle->Autopilot.m_dwNextDetachedNodeIndex = CGameVariables::GetPathFind()->DetachedPointsInfo[nMainRouteInfoIndex + nConnectedNodeIndex];

    int nRequiredLanes;
    if(nPreviousNextNodeIndex >= pVehicle->Autopilot.m_dwNextNodeIndex) {
        pVehicle->Autopilot.m_byteNextDirectionScale = 1;
        nRequiredLanes = CGameVariables::GetPathFind()->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitRightLanes;
    }
    else {
        pVehicle->Autopilot.m_byteNextDirectionScale = -1;
        nRequiredLanes = CGameVariables::GetPathFind()->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitLeftLanes;
    }

    CVector2D v2dCurrentDirection, v2dNextDirection;
    int dwCurrentDetachedIndex = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
    int dwNextDetachedIndex = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
    v2dCurrentDirection.fX = (float)pVehicle->Autopilot.m_byteCurrentDirectionScale * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedIndex].NormalVecX) / 100.0f;
    v2dCurrentDirection.fY = (float)pVehicle->Autopilot.m_byteCurrentDirectionScale * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedIndex].NormalVecY) / 100.0f;
    v2dNextDirection.fX = (float)pVehicle->Autopilot.m_byteNextDirectionScale * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedIndex].NormalVecX) / 100.0f;
    v2dNextDirection.fY = (float)pVehicle->Autopilot.m_byteNextDirectionScale * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedIndex].NormalVecY) / 100.0f;
    CVector2D v2dCurrentPoint, v2dNextPoint;
    v2dCurrentPoint.fX = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedIndex].wX) / 8.0f;
    v2dCurrentPoint.fY = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedIndex].wY) / 8.0f;
    v2dNextPoint.fX = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedIndex].wX) / 8.0f;
    v2dNextPoint.fY = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedIndex].wY) / 8.0f;
    if(nRequiredLanes >= 0) {
        float fDisplacement = (v2dNextPoint.fY - v2dCurrentPoint.fY) * (v2dNextPoint.fY - v2dCurrentPoint.fY) + (v2dNextPoint.fX - v2dCurrentPoint.fX) * (v2dNextPoint.fX - v2dCurrentPoint.fX);
        if(fDisplacement > 49.0f && !(rand() & 0x600)) {
            bool bRandTest = rand() < CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY;
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
    float fCurrentLaneLength = (CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedIndex].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
    float fNextLaneLength = (CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedIndex].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
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
	vecStart.fX = (float)(CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wX) / 8.0f;
	vecStart.fY = (float)(CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wY) / 8.0f;
	vecStart.fZ = (float)(CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wZ) / 8.0f;
	
	CPathNode* pInstantRoutes[2];
	short sRouteStep;
	float fNodeDistance;
	int nNodeWithSmallestDiversion, nFoundConnectedBit;
	
	CGameVariables::GetPathFind()->DoPathSearch(0, vecStart.fX, vecStart.fY, vecStart.fZ, dwNextNode, fTargetX, fTargetY, 0.0f, pInstantRoutes, &sRouteStep, 2, pVehicle, &fNodeDistance, 999999.88f, -1);
	if(sRouteStep != 1 && sRouteStep != 2 || pInstantRoutes[0] == &CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode]) {
		if(sRouteStep != 2 || pInstantRoutes[1] == &CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode]) {
			CVector2D v2dVehiclePos;
			v2dVehiclePos.fX = fTargetX - pVehicle->__parent.__parent.matrix.rwMatrix.vPos.x;
			v2dVehiclePos.fY = fTargetY - pVehicle->__parent.__parent.matrix.rwMatrix.vPos.y;
			float fTargetAngle = CGeneral::GetATanOfXY(v2dVehiclePos);
			int nConnectedSets = CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].bitUnkCount4To7;
			float fPreviousFoundAngle = 10.0f;
			for(int i = 0; i < nConnectedSets; i++) {
				int nNext = CGameVariables::GetPathFind()->AttachedPointsInfo[i + CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY;
				if(nNext != dwMainNode || nConnectedSets <= 1) {
					CVector2D v2dDeltaRelativeCarNode;
					v2dDeltaRelativeCarNode.fX = (float)(CGameVariables::GetPathFind()->m_AttachedPaths[nNext].wX) / 8.0f - vecStart.fX;
					v2dDeltaRelativeCarNode.fY = (float)(CGameVariables::GetPathFind()->m_AttachedPaths[nNext].wY) / 8.0f - vecStart.fY;
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
			nNodeWithSmallestDiversion = pInstantRoutes[1] - &CGameVariables::GetPathFind()->m_AttachedPaths[0];
			nFoundConnectedBit = 0;
			int nNextNodeRouteIndex = CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wRouteInfoIndex;
			while (nNodeWithSmallestDiversion != (CGameVariables::GetPathFind()->AttachedPointsInfo[nNextNodeRouteIndex + nFoundConnectedBit] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY)) {
				nFoundConnectedBit++;
			}
		}
	}
	else {
		nNodeWithSmallestDiversion = pInstantRoutes[0] - &CGameVariables::GetPathFind()->m_AttachedPaths[0];
		nFoundConnectedBit = 0;
		int nNextNodeRouteIndex = CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wRouteInfoIndex;
		while (nNodeWithSmallestDiversion != (CGameVariables::GetPathFind()->AttachedPointsInfo[nNextNodeRouteIndex + nFoundConnectedBit] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY)) {
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
	pVehicle->Autopilot.m_dwNextDetachedNodeIndex = CGameVariables::GetPathFind()->DetachedPointsInfo[nFoundConnectedBit + CGameVariables::GetPathFind()->m_AttachedPaths[dwNextNode].wRouteInfoIndex];
	
	int nRequiredLanes;
	if(dwNextNode >= pVehicle->Autopilot.m_dwNextNodeIndex) {
		pVehicle->Autopilot.m_byteNextDirectionScale = 1;
		nRequiredLanes = CGameVariables::GetPathFind()->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitRightLanes;
	}
	else {
		pVehicle->Autopilot.m_byteNextDirectionScale = -1;
		nRequiredLanes = CGameVariables::GetPathFind()->m_DetachedNodes[pVehicle->Autopilot.m_dwNextDetachedNodeIndex].bitLeftLanes;
	}
	int dwCurrentDetachedNode = pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex;
	int dwNextDetachedNode = pVehicle->Autopilot.m_dwNextDetachedNodeIndex;
	CVector2D v2dCurrentDirection, v2dNextDirection;
	v2dCurrentDirection.fX = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedNode].NormalVecX) / 100.0f;
	v2dCurrentDirection.fY = (float)(pVehicle->Autopilot.m_byteCurrentDirectionScale) * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedNode].NormalVecY) / 100.0f;
	v2dNextDirection.fX = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedNode].NormalVecX) / 100.0f;
	v2dNextDirection.fY = (float)(pVehicle->Autopilot.m_byteNextDirectionScale) * (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedNode].NormalVecY) / 100.0f;
	
	CVector vecCurrentDetached, vecNextDetached;
	vecCurrentDetached.fX = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedNode].wX) / 8.0f;
	vecCurrentDetached.fY = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedNode].wY) / 8.0f;
	vecNextDetached.fX = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedNode].wX) / 8.0f;
	vecNextDetached.fY = (float)(CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedNode].wY) / 8.0f;
	if(nRequiredLanes >= 0) {
		float fDetachedDisplacement = (vecNextDetached.fY - vecCurrentDetached.fY) * (vecNextDetached.fY - vecCurrentDetached.fY) + (vecNextDetached.fX - vecCurrentDetached.fX) * (vecNextDetached.fX - vecCurrentDetached.fX);
		if(fDetachedDisplacement > 49.0f) {
			int eAutoPilotBehaviour = pVehicle->Autopilot.m_DriverBehaviour;
			if(eAutoPilotBehaviour != 2 && eAutoPilotBehaviour != 4 && eAutoPilotBehaviour != 15 && eAutoPilotBehaviour != 17 && !(rand() & 0x600)) {
				if(rand() < CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY) {
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
	float fCurrentLaneLength = (CGameVariables::GetPathFind()->m_DetachedNodes[dwCurrentDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteCurrentLanes)) * 5.0f;
	float fNextLaneLength = (CGameVariables::GetPathFind()->m_DetachedNodes[dwNextDetachedNode].CalculateLaneDistance() + (float)(pVehicle->Autopilot.m_byteNextLanes)) * 5.0f;
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


#endif