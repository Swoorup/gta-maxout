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

    int nPreviousNextNodeIndex = pVehicle->_.stAutopilot.m_dwNextNode;
	int m_beginRouteStep = pVehicle->_.stAutopilot.m_nRouteListStep;
    //if(pVehicle->_.stAutopilot.m_nRouteListStep == 0)  // SOMEFUNCTIONS CAUSES THE ERROR DOWN BELOW
	{
        THEPATHS->DoPathSearch(0, pVehicle->_.phys.ent.mat.vPos,
            pVehicle->_.stAutopilot.m_dwNextNode,
            pVehicle->_.stAutopilot.m_vecTargetPoint,
            pVehicle->_.stAutopilot.m_pIntermediateRouteList,
            &pVehicle->_.stAutopilot.m_nRouteListStep,
            8,
            pVehicle,
            0,
            999999.88f,
            -1);

        if(pVehicle->_.stAutopilot.m_nRouteListStep < 2)
            return true;
        
		// remove the first node since it is already known
        pVehicle->_.stAutopilot.RemoveOnePathNode();
    }

    pVehicle->_.stAutopilot.m_dwPrevNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
    pVehicle->_.stAutopilot.m_dwCurrentNode = pVehicle->_.stAutopilot.m_dwNextNode;
    /*if(pVehicle->_.stAutopilot.m_pIntermediateRouteList[0] < &THEPATHS->m_AttachedPaths[0] || pVehicle->_.stAutopilot.m_pIntermediateRouteList[0] > &THEPATHS->m_AttachedPaths[THEPATHS->m_nAttachedNodes -1]){
        //sometimes the m_pIntermediateRouteList contains inappropriate value which is below m_AttachedPaths[0] temp fix
        char buf[256];
        sprintf(buf, "Intermediate Address: 0x%X \nStupidNode: 0x%X", pVehicle->_.stAutopilot.m_pIntermediateRouteList, pVehicle->_.stAutopilot.m_pIntermediateRouteList[0]);
        CDebug::DebugAddText(buf);
        //MessageBoxA(NULL, buf, NULL, NULL);
        return false;
    }*/

	// nextNode is gibberish
	
    pVehicle->_.stAutopilot.m_dwNextNode = pVehicle->_.stAutopilot.m_pIntermediateRouteList[0] - &THEPATHS->m_AttachedPaths[0];
	if (pVehicle->_.stAutopilot.m_dwNextNode <0)
		
	{
		short val = (short)pVehicle->_.stAutopilot.m_pIntermediateRouteList[0];
		int iVal = (int)pVehicle->_.stAutopilot.m_pIntermediateRouteList[0];
		char buf[256];
		sprintf(buf, "ERROR: function began with %d as Steps", m_beginRouteStep);
		MessageBoxA(NULL, buf, NULL, 0);
	}
    pVehicle->_.stAutopilot.RemoveOnePathNode();
    pVehicle->_.stAutopilot.m_dwCurrentSpeedScaleFactor += pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor;
    pVehicle->_.stAutopilot.m_dwPrevCarLinkNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
    pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
    pVehicle->_.stAutopilot.m_bytePrevDirectionScale = pVehicle->_.stAutopilot.m_byteCurrentDirectionScale;
    pVehicle->_.stAutopilot.m_byteCurrentDirectionScale = pVehicle->_.stAutopilot.m_byteNextDirectionScale;
    pVehicle->_.stAutopilot.m_byteCurrentLanes = pVehicle->_.stAutopilot.m_byteNextLanes;

    int nCurrentNodeRouteInfo = THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwCurrentNode].wRouteInfoIndex;
    int nConnectedNodeIndex = 0;
    
	/// MAJOR BUG WHAT IF NOT EVER FOUND, COULD GO UP TO HUGE LOOPS
	while(pVehicle->_.stAutopilot.m_dwNextNode != (THEPATHS->m_infoConnectedNodes[nCurrentNodeRouteInfo + nConnectedNodeIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY)) 
	{
        nConnectedNodeIndex++;	
    }

    pVehicle->_.stAutopilot.m_dwNextCarLinkNode = THEPATHS->m_InfoCarPathLinks[nCurrentNodeRouteInfo + nConnectedNodeIndex];

    int nRequiredLanes;
    if(nPreviousNextNodeIndex >= pVehicle->_.stAutopilot.m_dwNextNode) {
        pVehicle->_.stAutopilot.m_byteNextDirectionScale = 1;
        nRequiredLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitRightLanes;
    }
    else {
        pVehicle->_.stAutopilot.m_byteNextDirectionScale = -1;
        nRequiredLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitLeftLanes;
    }

    CVector2D v2dCurrentDirection, v2dNextDirection;
    int dwCurrentDetachedIndex = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
    int dwNextDetachedIndex = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
    v2dCurrentDirection.fX = (float)pVehicle->_.stAutopilot.m_byteCurrentDirectionScale * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedIndex].NormalVecX) / 100.0f;
    v2dCurrentDirection.fY = (float)pVehicle->_.stAutopilot.m_byteCurrentDirectionScale * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedIndex].NormalVecY) / 100.0f;
    v2dNextDirection.fX = (float)pVehicle->_.stAutopilot.m_byteNextDirectionScale * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedIndex].NormalVecX) / 100.0f;
    v2dNextDirection.fY = (float)pVehicle->_.stAutopilot.m_byteNextDirectionScale * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedIndex].NormalVecY) / 100.0f;
    CVector2D v2dCurrentPoint, v2dNextPoint;
    v2dCurrentPoint.fX = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedIndex].wX) / 8.0f;
    v2dCurrentPoint.fY = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedIndex].wY) / 8.0f;
    v2dNextPoint.fX = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedIndex].wX) / 8.0f;
    v2dNextPoint.fY = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedIndex].wY) / 8.0f;
    if(nRequiredLanes >= 0) {
        float fDisplacement = (v2dNextPoint.fY - v2dCurrentPoint.fY) * (v2dNextPoint.fY - v2dCurrentPoint.fY) + (v2dNextPoint.fX - v2dCurrentPoint.fX) * (v2dNextPoint.fX - v2dCurrentPoint.fX);
        if(fDisplacement > 49.0f && !(rand() & 0x600)) {
            bool bRandTest = rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY;
            if(bRandTest) {
                pVehicle->_.stAutopilot.m_byteNextLanes++;
            }
            else {
                pVehicle->_.stAutopilot.m_byteNextLanes--;
            }
        }
        if(pVehicle->_.stAutopilot.m_byteNextLanes >= nRequiredLanes - 1) {
            pVehicle->_.stAutopilot.m_byteNextLanes = nRequiredLanes - 1;
        }
        if(pVehicle->_.stAutopilot.m_byteNextLanes <= 0) {
            pVehicle->_.stAutopilot.m_byteNextLanes = 0;
        }
    }
    else {
        pVehicle->_.stAutopilot.m_byteNextLanes = pVehicle->_.stAutopilot.m_byteCurrentLanes;
    }
    if((pVehicle->_.stAutopilot.m_flags >> 3) & 1) {
        pVehicle->_.stAutopilot.m_byteNextLanes = 0;
    }
    float fCurrentLaneLength = (THEPATHS->m_CarPathLinks[dwCurrentDetachedIndex].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteCurrentLanes)) * 5.0f;
    float fNextLaneLength = (THEPATHS->m_CarPathLinks[dwNextDetachedIndex].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteNextLanes)) * 5.0f;
    CVector2D v2dCurrentTest, v2dNextTest;
    v2dCurrentTest.fX = v2dCurrentPoint.fX + v2dCurrentDirection.fY * fCurrentLaneLength;
    v2dCurrentTest.fY = v2dCurrentPoint.fY - v2dCurrentDirection.fX * fCurrentLaneLength;
    v2dNextTest.fX = v2dNextPoint.fX + v2dNextDirection.fY * fNextLaneLength;
    v2dNextTest.fY = v2dNextPoint.fY - v2dNextDirection.fX * fNextLaneLength;

    pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentTest, &v2dNextTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f / pVehicle->_.stAutopilot.m_fCurrentSpeed);
    if(pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor <= 10) {
        pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = 10;
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
	int dwMainNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
	int dwNextNode = pVehicle->_.stAutopilot.m_dwNextNode;
	
	// the start node vector is taken from the next node
	CVector vecStart = THEPATHS ->m_AttachedPaths[dwNextNode].Form3DVector();
	
	CPathNode* pInstantRoutes[2];
	short sRouteStep;
	float fNodeDistance;
	int nNodeWithSmallestDiversion, nFoundConnectedBit;
	
	THEPATHS->DoPathSearch(0, vecStart, dwNextNode, CVector(fTargetX, fTargetY, 0.0f), pInstantRoutes, &sRouteStep, 2, pVehicle, &fNodeDistance, 999999.88f, -1);
	if(sRouteStep != 1 && sRouteStep != 2 || pInstantRoutes[0] == &THEPATHS->m_AttachedPaths[dwNextNode]) 
	{
		if(sRouteStep != 2 || pInstantRoutes[1] == &THEPATHS->m_AttachedPaths[dwNextNode]) 
		{
			CVector2D v2dVehiclePos(CVector2D(fTargetX, fTargetY) - CVector2D(pVehicle->_.phys.ent.mat.vPos));

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
					if(fCurrentAngleDiff <= fPreviousFoundAngle) 
					{
						fPreviousFoundAngle = fCurrentAngleDiff;
						nNodeWithSmallestDiversion = nNext;
						nFoundConnectedBit = i;
					}
				}
			}
		}
		else 
		{
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
	
	pVehicle->_.stAutopilot.m_dwPrevNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
	pVehicle->_.stAutopilot.m_dwCurrentNode = pVehicle->_.stAutopilot.m_dwNextNode;
	pVehicle->_.stAutopilot.m_dwNextNode = nNodeWithSmallestDiversion;
	pVehicle->_.stAutopilot.m_dwCurrentSpeedScaleFactor += pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor;
	pVehicle->_.stAutopilot.m_dwPrevCarLinkNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
	pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
	pVehicle->_.stAutopilot.m_bytePrevDirectionScale = pVehicle->_.stAutopilot.m_byteCurrentDirectionScale;
	pVehicle->_.stAutopilot.m_byteCurrentDirectionScale = pVehicle->_.stAutopilot.m_byteNextDirectionScale;
	pVehicle->_.stAutopilot.m_byteCurrentLanes = pVehicle->_.stAutopilot.m_byteNextLanes;
	pVehicle->_.stAutopilot.m_dwNextCarLinkNode = THEPATHS->m_InfoCarPathLinks[nFoundConnectedBit + THEPATHS->m_AttachedPaths[dwNextNode].wRouteInfoIndex];
	
	int nRequiredLanes;
	if(dwNextNode >= pVehicle->_.stAutopilot.m_dwNextNode) 
	{
		pVehicle->_.stAutopilot.m_byteNextDirectionScale = 1;
		nRequiredLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitRightLanes;
	}
	else 
	{
		pVehicle->_.stAutopilot.m_byteNextDirectionScale = -1;
		nRequiredLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitLeftLanes;
	}
	int dwCurrentDetachedNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
	int dwNextDetachedNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
	CVector2D v2dCurrentDirection, v2dNextDirection;
	v2dCurrentDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].NormalVecX) / 100.0f;
	v2dCurrentDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].NormalVecY) / 100.0f;
	v2dNextDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].NormalVecX) / 100.0f;
	v2dNextDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].NormalVecY) / 100.0f;
	
	CVector vecCurrentDetached, vecNextDetached;
	vecCurrentDetached.fX = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].wX) / 8.0f;
	vecCurrentDetached.fY = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].wY) / 8.0f;
	vecNextDetached.fX = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].wX) / 8.0f;
	vecNextDetached.fY = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].wY) / 8.0f;
	if(nRequiredLanes >= 0) 
	{
		float fDetachedDisplacement = (vecNextDetached.fY - vecCurrentDetached.fY) * (vecNextDetached.fY - vecCurrentDetached.fY) + (vecNextDetached.fX - vecCurrentDetached.fX) * (vecNextDetached.fX - vecCurrentDetached.fX);
		if(fDetachedDisplacement > 49.0f) 
		{
			int eAutoPilotBehaviour = pVehicle->_.stAutopilot.m_DriverBehaviour;
			if(eAutoPilotBehaviour != 2 && eAutoPilotBehaviour != 4 && eAutoPilotBehaviour != 15 && eAutoPilotBehaviour != 17 && !(rand() & 0x600)) {
				if(rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY) 
				{
					pVehicle->_.stAutopilot.m_byteNextLanes++;
				}
				else 
				{
					pVehicle->_.stAutopilot.m_byteNextLanes--;
				}
			}
		}
		if(pVehicle->_.stAutopilot.m_byteNextLanes >= (nRequiredLanes - 1)) 
		{
			pVehicle->_.stAutopilot.m_byteNextLanes = nRequiredLanes - 1;
		}
		if(pVehicle->_.stAutopilot.m_byteNextLanes <= 0) 
		{
			pVehicle->_.stAutopilot.m_byteNextLanes = 0;
		}
	}
	else 
	{
		pVehicle->_.stAutopilot.m_byteNextLanes = pVehicle->_.stAutopilot.m_byteCurrentLanes;
	}
	if((pVehicle->_.stAutopilot.m_flags >> 3) & 1) 
	{
		pVehicle->_.stAutopilot.m_byteNextLanes = 0;
	}
	float fCurrentLaneLength = (THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteCurrentLanes)) * 5.0f;
	float fNextLaneLength = (THEPATHS->m_CarPathLinks[dwNextDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteNextLanes)) * 5.0f;
	CVector2D v2dCurrentDetachedTest, v2dNextDetachedTest;
	v2dCurrentDetachedTest.fX = vecCurrentDetached.fX + v2dCurrentDirection.fY * fCurrentLaneLength;
	v2dCurrentDetachedTest.fY = vecCurrentDetached.fY - v2dCurrentDirection.fX * fCurrentLaneLength;
	v2dNextDetachedTest.fX = vecNextDetached.fX + v2dNextDirection.fY * fNextLaneLength;
	v2dNextDetachedTest.fY = vecNextDetached.fY - v2dNextDirection.fX * fNextLaneLength;
	
	pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentDetachedTest, &v2dNextDetachedTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f/ pVehicle->_.stAutopilot.m_fCurrentSpeed);
	if(pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor <= 10) {
		pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = 10;
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
	
	int dwPrevNextNode = pVehicle->_.stAutopilot.m_dwNextNode;
	int nNextConnectedSets = THEPATHS->m_AttachedPaths[dwPrevNextNode].bitnumberOfNodesConnected;
	int dwPrevMainNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
	int dwNextDetachedNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
	int nRequiredLanes = 0;
	bool bIsFirstOtherLaneNull = false;
	if(THEPATHS->m_CarPathLinks[dwNextDetachedNode].nIndexToAttachedNode == dwPrevNextNode) {
		nRequiredLanes = THEPATHS->m_CarPathLinks[dwNextDetachedNode].bitLeftLanes;
		bIsFirstOtherLaneNull = THEPATHS->m_CarPathLinks[dwNextDetachedNode].bitRightLanes == 0 ? true : false;
	}
	else {
		nRequiredLanes = THEPATHS->m_CarPathLinks[dwNextDetachedNode].bitRightLanes;
		bIsFirstOtherLaneNull = THEPATHS->m_CarPathLinks[dwNextDetachedNode].bitLeftLanes == 0 ? true : false;
	}
	
	unsigned char byteAutoNextLane = pVehicle->_.stAutopilot.m_byteNextLanes;
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
	pVehicle->_.stAutopilot.m_dwPrevNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
	pVehicle->_.stAutopilot.m_dwCurrentNode = pVehicle->_.stAutopilot.m_dwNextNode;
	int nLoopConnectedBits = 0;
    int nRandomConnectedBit = 0;
	while(nLoopConnectedBits < 15) {
		nRandomConnectedBit = rand() % nNextConnectedSets;
		pVehicle->_.stAutopilot.m_dwNextNode = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
		unsigned char bytePathDirection = CCarCtrl::FindPathDirection(dwPrevMainNode, dwPrevNextNode, pVehicle->_.stAutopilot.m_dwNextNode);
		
		bool bIsOtherLaneNull = false;
		bool bIsTestLaneNull = false;
		int nTestDetachedRoute = THEPATHS->m_InfoCarPathLinks[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
		if(THEPATHS->m_CarPathLinks[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
			bIsOtherLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			bIsTestLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
		}
		else {
			bIsOtherLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			bIsTestLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
		}
		int dwNextDeltaNode = pVehicle->_.stAutopilot.m_dwNextNode;
		if(dwPrevMainNode != dwNextDeltaNode && (byteTestPathDirection & bytePathDirection)) {
			if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitUnknownFlag3) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitUnknownFlag3){
				if((!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode)
				&& (!((pVehicle->_.stAutopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
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
			pVehicle->_.stAutopilot.m_dwNextNode = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
			bool bIsOtherLaneNull = false;
			int nTestDetachedRoute = THEPATHS->m_InfoCarPathLinks[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
			if(THEPATHS->m_CarPathLinks[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
				bIsOtherLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			}
			else {
				bIsOtherLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			}
			int dwNextDeltaNode = pVehicle->_.stAutopilot.m_dwNextNode;
			if(dwPrevMainNode != dwNextDeltaNode) {
				if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode) {
					if((!((pVehicle->_.stAutopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
					|| THEPATHS->m_AttachedPaths[dwPrevMainNode].bitRestrictedAccess) && bIsOtherLaneNull == false) {
						break;
					}
				}
			}
		}
	}
	if(nLoopConnectedBits >= 15) {
		for(nRandomConnectedBit = 0; nRandomConnectedBit < nNextConnectedSets; nRandomConnectedBit++) {
			pVehicle->_.stAutopilot.m_dwNextNode = THEPATHS->m_infoConnectedNodes[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
			bool bIsTestLaneNull = false;
			int nTestDetachedRoute = THEPATHS->m_InfoCarPathLinks[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
			if(THEPATHS->m_CarPathLinks[nTestDetachedRoute].nIndexToAttachedNode == dwPrevNextNode) {
				bIsTestLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitRightLanes == 0 ? true : false;
			}
			else {
				bIsTestLaneNull = THEPATHS->m_CarPathLinks[nTestDetachedRoute].bitLeftLanes == 0 ? true : false;
			}
			if(bIsTestLaneNull == false) {
				int dwNextDeltaNode = pVehicle->_.stAutopilot.m_dwNextNode;
				if(!(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitIsIgnoredNode) || THEPATHS->m_AttachedPaths[dwPrevMainNode].bitIsIgnoredNode) {
					if(!((pVehicle->_.stAutopilot.m_flags >> 2) & 1) || !(THEPATHS->m_AttachedPaths[dwNextDeltaNode].bitRestrictedAccess)
					|| THEPATHS->m_AttachedPaths[dwPrevMainNode].bitRestrictedAccess) {
						nRandomConnectedBit = 1000;
					}
				}
			}
		}
		if(nRandomConnectedBit < 999) {
			pVehicle->_.stAutopilot.m_dwNextNode = dwPrevMainNode;
		}
	}
	if(dwPrevMainNode == pVehicle->_.stAutopilot.m_dwNextNode) {
		pVehicle->_.phys.ent.bfTypeStatus = pVehicle->_.phys.ent.bfTypeStatus & 7 | 0x18;
		pVehicle->_.stAutopilot.m_DriverBehaviour = 1;
		pVehicle->_.stAutopilot.m_eSimpleAction = 0;
		pVehicle->_.stAutopilot.m_snGettingNewCommandTimeStamp = CGameVariables::GetTimeInMilliseconds();
		pVehicle->_.stAutopilot.m_snUnknownTimeStamp = CGameVariables::GetTimeInMilliseconds();
	}
	pVehicle->_.stAutopilot.m_dwCurrentSpeedScaleFactor += pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor;
	pVehicle->_.stAutopilot.m_dwPrevCarLinkNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
	pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
	pVehicle->_.stAutopilot.m_bytePrevDirectionScale = pVehicle->_.stAutopilot.m_byteCurrentDirectionScale;
	pVehicle->_.stAutopilot.m_byteCurrentDirectionScale = pVehicle->_.stAutopilot.m_byteNextDirectionScale;
	pVehicle->_.stAutopilot.m_byteCurrentLanes = pVehicle->_.stAutopilot.m_byteNextLanes;
	pVehicle->_.stAutopilot.m_dwNextCarLinkNode = THEPATHS->m_InfoCarPathLinks[nRandomConnectedBit + THEPATHS->m_AttachedPaths[dwPrevNextNode].wRouteInfoIndex];
	
	int dwNextLanes;
	if(dwPrevNextNode >= pVehicle->_.stAutopilot.m_dwNextNode) {
		pVehicle->_.stAutopilot.m_byteNextDirectionScale = 1;
		dwNextLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitLeftLanes;
	}
	else {
		pVehicle->_.stAutopilot.m_byteNextDirectionScale = -1;
		dwNextLanes = THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].bitRightLanes;
	}
	CVector2D v2dCurrentDirection, v2dNextDirection, v2dCurrentDetachedTest, v2dNextDetachedTest;
	v2dCurrentDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode].NormalVecX) / 100.0f;
	v2dCurrentDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode].NormalVecY) / 100.0f;
	v2dNextDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].NormalVecX) / 100.0f;
	v2dNextDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[pVehicle->_.stAutopilot.m_dwNextCarLinkNode].NormalVecY) / 100.0f;
	
	if(dwNextLanes >= 0) {
		if(!(rand() & 0x600)) {
			CVector2D v2dCurrentAttached, v2dNextAttached;
			v2dCurrentAttached.fX = (float)(THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwCurrentNode].wX) / 8.0f;
			v2dCurrentAttached.fY = (float)(THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwCurrentNode].wY) / 8.0f;
			v2dNextAttached.fX = (float)(THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwNextNode].wX) / 8.0f;
			v2dNextAttached.fY = (float)(THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwNextNode].wY) / 8.0f;
			
			float fAttachedNodeDisplacement = (v2dNextAttached.fY - v2dCurrentAttached.fY) * (v2dNextAttached.fY - v2dCurrentAttached.fY) + (v2dNextAttached.fX - v2dCurrentAttached.fX) * (v2dNextAttached.fX - v2dCurrentAttached.fX);
			if(fAttachedNodeDisplacement >= 196.0f) {
				if(rand() < CPathFind::em_infoConnectedNodesNODEINDEXONLY) {
					pVehicle->_.stAutopilot.m_byteNextLanes++;
				}
				else {
					pVehicle->_.stAutopilot.m_byteNextLanes--;
				}
			}
		}
		if(pVehicle->_.stAutopilot.m_byteNextLanes >= (dwNextLanes - 1)) {
			pVehicle->_.stAutopilot.m_byteNextLanes = dwNextLanes - 1;
		}
		if(pVehicle->_.stAutopilot.m_byteNextLanes <= 0) {
			pVehicle->_.stAutopilot.m_byteNextLanes = 0;
		}
	}
	else {
		pVehicle->_.stAutopilot.m_byteNextLanes = pVehicle->_.stAutopilot.m_byteCurrentLanes;
	}
	
	if((pVehicle->_.stAutopilot.m_flags >> 3) & 1) {
		pVehicle->_.stAutopilot.m_byteNextLanes = 0;
	}
	int dwTestCurrentDetachedNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
	int dwTestNextDetachedNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
	float fCurrentLaneLength = (THEPATHS->m_CarPathLinks[dwTestCurrentDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteCurrentLanes)) * 5.0f;
	float fNextLaneLength = (THEPATHS->m_CarPathLinks[dwTestNextDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteNextLanes)) * 5.0f;
	v2dNextDetachedTest.fX = (float)(THEPATHS->m_CarPathLinks[dwTestNextDetachedNode].wX) / 8.0f + fNextLaneLength;
	v2dNextDetachedTest.fY = (float)(THEPATHS->m_CarPathLinks[dwTestNextDetachedNode].wY) / 8.0f - v2dNextDirection.fX * fNextLaneLength;
	v2dCurrentDetachedTest.fX = (float)(THEPATHS->m_CarPathLinks[dwTestCurrentDetachedNode].wX) / 8.0f + fCurrentLaneLength;
	v2dCurrentDetachedTest.fY = (float)(THEPATHS->m_CarPathLinks[dwTestCurrentDetachedNode].wY) / 8.0f - v2dCurrentDirection.fX * fCurrentLaneLength;
	
	pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&v2dCurrentDetachedTest, &v2dNextDetachedTest, v2dCurrentDirection, v2dNextDirection) * 1000.0f / pVehicle->_.stAutopilot.m_fCurrentSpeed);
	if(pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor <= 10){
		pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor = 10;
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
	pVehicle->_.stAutopilot.m_byteSpeedLimit = THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwNextNode].bitSpeedLimit;
	switch(pVehicle->_.stAutopilot.m_DriverBehaviour) {
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
			PickNextNodeToChaseCar(pVehicle, pVehicle->_.pVehicleToRam->_.phys.ent.mat.vPos.fX, pVehicle->_.pVehicleToRam->_.phys.ent.mat.vPos.fY, pVehicle->_.pVehicleToRam);
			return false;
			break;
		case 8:
		case 12:
			return PickNextNodeToFollowPath(pVehicle);
			break;
		default:
        {
			PickNextNodeRandomly(pVehicle);
			if(THEPATHS->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwNextNode].bitHaveUnrandomizedVehClass) {
				if(pVehicle->_.phys.ent.nModelIndex == BOAT_RIO || pVehicle->_.phys.ent.nModelIndex == BOAT_TROPIC || pVehicle->_.phys.ent.nModelIndex == BOAT_MARQUIS) {
					pVehicle->_.stAutopilot.m_nMaxSpeed = 0;
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
	if(pVehicle->_.stAutopilot.m_eSimpleAction == 1) {
		pVehicle->_.phys.vecMoveSpeed.fX = 0.0f;
		pVehicle->_.phys.vecMoveSpeed.fY = 0.0f;
		pVehicle->_.phys.vecMoveSpeed.fZ = 0.0f;
		pVehicle->_.stAutopilot.ModifySpeed(0.0f);
		if((int)CGameVariables::GetTimeInMilliseconds() > pVehicle->_.stAutopilot.m_simple_action_time) {
			pVehicle->_.stAutopilot.m_eSimpleAction = 0;
			pVehicle->_.stAutopilot.m_snGettingNewCommandTimeStamp = CGameVariables::GetTimeInMilliseconds();
			pVehicle->_.stAutopilot.m_snUnknownTimeStamp = CGameVariables::GetTimeInMilliseconds();
		}
	}
	else {
		SlowCarOnRailsDownForTrafficAndLights(pVehicle);
		if(CGameVariables::GetTimeInMilliseconds() >= (int64_t)(pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor + pVehicle->_.stAutopilot.m_dwCurrentSpeedScaleFactor)) {
			PickNextNodeAccordingStrategy(pVehicle);
		}
		if((pVehicle->_.phys.ent.bfTypeStatus >> 3) != 3) {
			float fTimeDelta = (float)(uint32_t)(CGameVariables::GetTimeInMilliseconds() - pVehicle->_.stAutopilot.m_dwCurrentSpeedScaleFactor) / (float)(pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor);
			int dwCurrentDetachedNode = pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode;
			CVector2D vecCurrentDirection, vecNextDirection;
			vecCurrentDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].NormalVecX) / 100.0f;
			vecCurrentDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteCurrentDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].NormalVecY) / 100.0f;
			int dwNextDetachedNode = pVehicle->_.stAutopilot.m_dwNextCarLinkNode;
			vecNextDirection.fX = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].NormalVecX) / 100.0f;
			vecNextDirection.fY = (float)(pVehicle->_.stAutopilot.m_byteNextDirectionScale) * (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].NormalVecY) / 100.0f;
			
			float fCurrentLane = (THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteCurrentLanes)) * 5.0f;
			float fNextLane = (THEPATHS->m_CarPathLinks[dwNextDetachedNode].OneWayLaneOffset() + (float)(pVehicle->_.stAutopilot.m_byteNextLanes)) * 5.0f;
			
			CVector2D vecCurrentLane, vecNextLane;
			vecCurrentLane.fX = (double)(((dwCurrentDetachedNode + pVehicle->_.phys.ent.uiPathMedianRand) & 7) - 3) * 0.0089999996f;
			vecCurrentLane.fY = (double)((((dwCurrentDetachedNode + pVehicle->_.phys.ent.uiPathMedianRand) >> 3) & 7) -3) * 0.0089999996f;
			vecNextLane.fX = (double)(((dwNextDetachedNode + pVehicle->_.phys.ent.uiPathMedianRand) & 7) - 3) * 0.0089999996f;
			vecNextLane.fY = (double)((((dwNextDetachedNode + pVehicle->_.phys.ent.uiPathMedianRand) >> 3) & 7) - 3) * 0.0089999996f;
			
			vecCurrentLane.fX += vecCurrentDirection.fX;
			vecCurrentLane.fY += vecCurrentDirection.fY;
			vecNextLane.fX += vecNextDirection.fX;
			vecNextLane.fY += vecNextDirection.fY;
			
			vecCurrentLane.Normalize();
			vecNextLane.Normalize();
			
			CVector vecCurrentDetachedTest, vecNextDetachedTest;
			vecCurrentDetachedTest.fZ = 0.0f;
			vecNextDetachedTest.fZ = 0.0f;
			
			vecCurrentDetachedTest.fX = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].wX) / 8.0f + vecCurrentDirection.fY * fCurrentLane;
			vecCurrentDetachedTest.fY = (float)(THEPATHS->m_CarPathLinks[dwCurrentDetachedNode].wY) / 8.0f - vecCurrentDirection.fX * fCurrentLane;
			vecNextDetachedTest.fX = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].wX) / 8.0f + vecNextDirection.fY * fNextLane;
			vecNextDetachedTest.fY = (float)(THEPATHS->m_CarPathLinks[dwNextDetachedNode].wY) / 8.0f - vecNextDirection.fX * fNextLane;
			
			CVector vecGotoPoint, vecRequiredVelocity;
			CCurves::CalcCurvePoint(&vecCurrentDetachedTest, &vecNextDetachedTest, &vecCurrentLane, &vecNextLane, fTimeDelta, pVehicle->_.stAutopilot.m_dwNextSpeedScaleFactor, &vecGotoPoint, &vecRequiredVelocity);
			vecGotoPoint.fZ = 15.0f;
			DragCarToPoint(pVehicle, &vecGotoPoint);
			vecRequiredVelocity *= 0.016666668f;
			pVehicle->_.phys.vecMoveSpeed.fX = vecRequiredVelocity.fX;
			pVehicle->_.phys.vecMoveSpeed.fY = vecRequiredVelocity.fY;
			pVehicle->_.phys.vecMoveSpeed.fZ = vecRequiredVelocity.fZ;
		}
	}
}

#endif

// This is a hook inside CCarCtrl::FindLinksToGoWithTheseNodes.
// It replaces the entire original function by jump to this 
// right after the function starts. This function seems to get 
// loaded when the a chasing cop car stops right near the player.
// To-Do: Change into a grid type setup

//41CC20
void _cdecl CCarCtrl::FindLinksToGoWithTheseNodes(CVehicle* pVehicle) 
{
    DWORD _dwHookArgOne = pVehicle->_.wMissionValue; // seedvalue
    CDebug::DebugAddText("HookFindLinksToGoWithTheseNodes");

    //unnecessary R* leftover?
    if (_dwHookArgOne) {
        _asm mov eax, _dwHookArgOne
        _asm push eax
        _asm mov eax, 649A30h
        _asm call eax
        _asm pop eax
    }
    
    int nConnectedPointInfo = pThePaths->m_AttachedPaths[pVehicle->_.stAutopilot.m_dwCurrentNode].wRouteInfoIndex;
    int _nLoop = 0;

    for(int _nLoop = 0; _nLoop < 12 && pVehicle->_.stAutopilot.m_dwNextNode != (pThePaths->m_infoConnectedNodes[_nLoop + nConnectedPointInfo] & CPathFind::em_infoConnectedNodesNODEINDEXONLY); _nLoop++);
    pVehicle->_.stAutopilot.m_dwNextCarLinkNode = pThePaths->m_InfoCarPathLinks[_nLoop + nConnectedPointInfo];
    if(pVehicle->_.stAutopilot.m_dwCurrentNode >= pVehicle->_.stAutopilot.m_dwNextNode) {
        pVehicle->_.stAutopilot.m_byteNextDirectionScale = 1;
    }
    else {
        pVehicle->_.stAutopilot.m_byteNextDirectionScale = -1;
    }

    int nStartNode = pVehicle->_.stAutopilot.m_dwCurrentNode;
    int nFoundNode, nFoundDetachedNode;

    if(pThePaths->m_AttachedPaths[nStartNode].bitnumberOfNodesConnected == 1) {
        nFoundNode = 0;
        nFoundDetachedNode = pThePaths->m_InfoCarPathLinks[pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex];
    }
    else {
        nFoundNode = -1;
        float fPrevCoefficient = 999999.88f;
        CPathNode* pPathNodeStart = &pThePaths->m_AttachedPaths[nStartNode];
        CVector vecStartNode((float)(pPathNodeStart->wX) / 8.0f, (float)(pPathNodeStart->wY) / 8.0f, (float)(pPathNodeStart->wZ) / 8.0f);

        for(int j = 0; j < pThePaths->m_AttachedPaths[nStartNode].bitnumberOfNodesConnected; j++) {
            int nConnectedNextNode = pThePaths->m_infoConnectedNodes[j+ pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
            if(nConnectedNextNode == pVehicle->_.stAutopilot.m_dwNextNode) {
                continue;
            }
            
            CVector vecNextConnectedNode = pThePaths->m_AttachedPaths[nConnectedNextNode].Form3DVector();
  
            float fCurrentCoefficient;
            CVector* vPosADDR = &pVehicle->_.phys.ent.mat.vPos;
            _asm mov eax, vPosADDR
            _asm push eax
            _asm lea eax, [vecNextConnectedNode]
            _asm push eax
            _asm lea eax, [vecStartNode]
            _asm push eax
            _asm mov eax, 414090h
            _asm call eax
            _asm fstp fCurrentCoefficient
			_asm add esp, 0Ch
			// oops we missed to clear the stack
			// why was not this noticed before :(
            if(fCurrentCoefficient < fPrevCoefficient) {
                nFoundNode = j;
                fPrevCoefficient = fCurrentCoefficient;
            }
        }
        nFoundDetachedNode = pThePaths->m_InfoCarPathLinks[nFoundNode + pPathNodeStart->wRouteInfoIndex];
    }
    pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode = nFoundDetachedNode;
    if((pThePaths->m_infoConnectedNodes[nFoundNode + pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY) >= nStartNode) {
        pVehicle->_.stAutopilot.m_byteCurrentDirectionScale = 1;
    }
    else {
        pVehicle->_.stAutopilot.m_byteCurrentDirectionScale = -1;
    }
}

/* 
 * This is a direct replacement hook for CCarCtrl::JoinCarWithRoadSystem.
 * This function is usually loaded when a wander system is initiated for
 * vehicles. 
 */

//41D000
void _cdecl CCarCtrl::JoinCarWithRoadSystem(CVehicle* pVehicle) {
    CDebug::DebugAddText("JoinCarWithRoadSystem working .....................");
	pVehicle->_.stAutopilot.m_dwNextNode = 0;
	pVehicle->_.stAutopilot.m_dwCurrentNode = 0;
	pVehicle->_.stAutopilot.m_dwPrevNode = 0;
	pVehicle->_.stAutopilot.m_dwNextCarLinkNode = 0;
	pVehicle->_.stAutopilot.m_dwPrevCarLinkNode = 0;
	pVehicle->_.stAutopilot.m_dwCurrentCarLinkNode = 0;
	
	int nNodeClosestToDirection = pThePaths->FindNodeClosestToCoorsFavourDirection(pVehicle->_.phys.ent.mat.vPos,
																		0,
																		CVector2D(pVehicle->_.phys.ent.mat.vLookAt));
																		
	float fnodeDirClosestX = (float)(pThePaths->m_AttachedPaths[nNodeClosestToDirection].wX) / 8.0f;
	float fnodeDirClosestY = (float)(pThePaths->m_AttachedPaths[nNodeClosestToDirection].wY) / 8.0f;
	
	int nClosestNode = -1;
	float fPreviousSearchCoefficient = 999999.88f;
	for(int i = 0; i < pThePaths->m_AttachedPaths[nNodeClosestToDirection].bitnumberOfNodesConnected; i++) {
		int nNextConnectedNode = pThePaths->m_infoConnectedNodes[i + pThePaths->m_AttachedPaths[nNodeClosestToDirection].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY;
		float fnextnodeX = (float)(pThePaths->m_AttachedPaths[nNextConnectedNode].wX) / 8.0f;
		float fnextnodeY = (float)(pThePaths->m_AttachedPaths[nNextConnectedNode].wY) / 8.0f;
		
		float fCurrentLength = sqrt((fnextnodeY - fnodeDirClosestY) * (fnextnodeY - fnodeDirClosestY) + (fnextnodeX - fnodeDirClosestX) * (fnextnodeX - fnodeDirClosestX));
		if(fCurrentLength < fPreviousSearchCoefficient) {
			fPreviousSearchCoefficient = fCurrentLength;
			nClosestNode = nNextConnectedNode;
		}
	}
	
	if (nClosestNode < 0) {
		return;
	}
	
	float fLookAtX = pVehicle->_.phys.ent.mat.vLookAt.fX;
	float fLookAtY = pVehicle->_.phys.ent.mat.vLookAt.fY;
	
	if(fLookAtX == 0.0f && fLookAtY == 0.0f) {
		fLookAtX = 1.0f;
	}
	
	float fClosestFoundX = (float)(pThePaths->m_AttachedPaths[nClosestNode].wX) / 8.0f;
	float fClosestFoundY = (float)(pThePaths->m_AttachedPaths[nClosestNode].wY) / 8.0f;
	
	if(((fnodeDirClosestY - fClosestFoundY) * fLookAtY + (fnodeDirClosestX - fClosestFoundX) * fLookAtX) < 0.0f) {
		int nTempIndex = nClosestNode;
		nClosestNode = nNodeClosestToDirection;
		nNodeClosestToDirection = nTempIndex;
	}
	
	pVehicle->_.stAutopilot.m_dwPrevNode = 0;
	pVehicle->_.stAutopilot.m_dwCurrentNode = nClosestNode;
	pVehicle->_.stAutopilot.m_dwNextNode = nNodeClosestToDirection;
	pVehicle->_.stAutopilot.m_nRouteListStep = 0;
	FindLinksToGoWithTheseNodes(pVehicle);
	pVehicle->_.stAutopilot.m_byteCurrentLanes = 0;
	pVehicle->_.stAutopilot.m_byteNextLanes = 0;
}

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