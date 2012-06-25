#include "../stdinc.h"

//418CA0
void CAutoPilot::RemoveOnePathNode(void) {
	m_nRouteListStep--;
	for(int i = 0; i < m_nRouteListStep; i++) {
		m_pIntermediateRouteList[i] = m_pIntermediateRouteList[i + 1];
	}
}

/*
 * Purpose: Modify the Autopilot mode speed in accordance to the situation.
 * eg. When a player stops in front of a vehicle then the autopilot speed 
 * needs to be modified to match the actual changes. If this code is removed 
 * or ModifySpeed was not there then even if the player stops in front of 
 * the vehicle, the vehicle seems to be approaching in a halt but only in 
 * visual rendering only. Few Seconds later the vehicle might seem to be 
 * teleported ahead!
 */

#ifdef INSTALL_PATCH_FOR_VCPATH_INSTANCE
//418CD0h
void CAutoPilot::ModifySpeed(float fModSpeed) {
	const float fDetachedPathNormalVecMinifier = 1.0f/100.0f;
	CVector2D vecCurrentDirection;
	CVector2D vecNextDirection;
	CVector2D vecCurrentPoint;
	CVector2D vecNextPoint;
	
	if(fModSpeed <= fDetachedPathNormalVecMinifier) {
		m_fCurrentSpeed = fDetachedPathNormalVecMinifier;
	}
	else {
		m_fCurrentSpeed = fModSpeed;
	}
	
	float fDeltaSpeedChange = (double)(CGameVariables::GetTimeInMilliseconds() - m_dwCurrentSpeedScaleFactor) / (double)m_dwNextSpeedScaleFactor;
	vecCurrentDirection.fX = (float)m_byteCurrentDirectionScale * (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwCurrentDetachedNodeIndex].NormalVecX) * fDetachedPathNormalVecMinifier;
	vecCurrentDirection.fY = (float)m_byteCurrentDirectionScale * (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwCurrentDetachedNodeIndex].NormalVecY) * fDetachedPathNormalVecMinifier;
	vecNextDirection.fX = (float)m_byteNextDirectionScale * (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwNextDetachedNodeIndex].NormalVecX) * fDetachedPathNormalVecMinifier;
	vecNextDirection.fY = (float)m_byteNextDirectionScale * (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwNextDetachedNodeIndex].NormalVecY) * fDetachedPathNormalVecMinifier;
	
	float fCurrentLaneLength = ((float)m_byteCurrentLanes + 0.5f) * 5.0f;
	float fNextLaneLength = ((float)m_byteNextLanes + 0.5f) * 5.0f;
	vecCurrentPoint.fX = (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwCurrentDetachedNodeIndex].wX) / 8.0f + vecCurrentDirection.fY * fCurrentLaneLength;
	vecCurrentPoint.fY = (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwCurrentDetachedNodeIndex].wY) / 8.0f + vecCurrentDirection.fX * fCurrentLaneLength;
	vecNextPoint.fX = (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwNextDetachedNodeIndex].wX) / 8.0f + vecNextDirection.fY * fNextLaneLength;
	vecNextPoint.fY = (float)(CGameVariables::GetGamePathFindInstance()->m_DetachedNodes[m_dwNextDetachedNodeIndex].wY) / 8.0f + vecNextDirection.fX * fNextLaneLength;
	
	m_dwNextSpeedScaleFactor = (signed int)(CCurves::CalcSpeedScaleFactor(&vecCurrentPoint, &vecNextPoint, vecCurrentDirection, vecNextDirection) * 1000.0f / m_fCurrentSpeed);
	m_dwCurrentSpeedScaleFactor = (signed int)((double)CGameVariables::GetTimeInMilliseconds() - (double)m_dwNextSpeedScaleFactor * fDeltaSpeedChange);
}

#else
//418CD0h
void CAutoPilot::ModifySpeed(float fModSpeed) {
	CAutoPilot* pThis = this;
	_asm {
		mov ecx, pThis
		push fModSpeed
		mov eax, 418CD0h
		call eax
	}
}
#endif