#include "../StdInc.h"

#ifdef INSTALL_PATCH_FOR_VCPATH_INSTANCE
/* This function has weird effects on traffic vehicles. It does not
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



#endif