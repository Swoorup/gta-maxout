#include "../stdinc.h"

#define THEPATHS CGameVariables::GetPathFind()

bool CPed::FindBestCoordsFromNodes(float fUnusedX, float fUnusedY, float fUnusedZ, CVector* vecBestCoords) {
	if(this->m_pNextNode == NULL && (this->m_field_14F & 0x20)) {
		CVector *vecPedPosition = (CVector*)&this->__parent.__parent.matrix.rwMatrix.vPos;
		int dwNodeClosestToPed = THEPATHS->FindNodeClosestToCoors(vecPedPosition->fX, vecPedPosition->fY, vecPedPosition->fZ, 1, 999999.88f, 0, 0, 0, 0);
		CVector vecTargetPath = m_vecTargetPath;
		vecTargetPath.fZ += 1.0f;
		
		if(CWorld::GetIsLineOfSightClear(vecPedPosition, &vecTargetPath, true, false, false, true, false, false, false)) {
			return false;
		}
		
		this->m_pNextNode = NULL;
		CPathNode* pNodeClosestToPed = &THEPATHS->m_AttachedPaths[dwNodeClosestToPed];
		CVector2D v2dPedPosRelative, v2dClosestPedNodeRel;
		v2dPedPosRelative.fX = this->m_vecTargetPath.fX - vecPedPosition->fX;
		v2dPedPosRelative.fY = this->m_vecTargetPath.fY - vecPedPosition->fY;
		v2dClosestPedNodeRel.fX = this->m_vecTargetPath.fX - (float)(pNodeClosestToPed->wX) / 8.0f;
		v2dClosestPedNodeRel.fY = this->m_vecTargetPath.fY - (float)(pNodeClosestToPed->wY) / 8.0f;
		
		for(int i = 0; i < pNodeClosestToPed->bitUnkCount4To7; i++) {
			CPathNode* pNextConnectedNode = &THEPATHS->m_AttachedPaths[THEPATHS->AttachedPointsInfo[i + pNodeClosestToPed->wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY];
			float fNextNodeX = (float)(pNextConnectedNode->wX) / 8.0f;
			float fNextNodeY = (float)(pNextConnectedNode->wY) / 8.0f;
			CVector2D v2dNextNodeRel;
			v2dNextNodeRel.fX = this->m_vecTargetPath.fX - fNextNodeX;
			v2dNextNodeRel.fY = this->m_vecTargetPath.fY - fNextNodeY;
			float fNextNodeLengthFromTargetPath = v2dNextNodeRel.fX * v2dNextNodeRel.fX + v2dNextNodeRel.fY * v2dNextNodeRel.fY;
			
			if((v2dPedPosRelative.fX * v2dPedPosRelative.fX + v2dPedPosRelative.fY * v2dPedPosRelative.fY) > fNextNodeLengthFromTargetPath) {
				if((v2dClosestPedNodeRel.fX * v2dClosestPedNodeRel.fX + v2dClosestPedNodeRel.fY * v2dClosestPedNodeRel.fY) <= fNextNodeLengthFromTargetPath) {
					this->m_pNextNode = pNodeClosestToPed;
					v2dClosestPedNodeRel.fX = v2dNextNodeRel.fX;
					v2dClosestPedNodeRel.fY = v2dNextNodeRel.fY;
				}
				else {
					this->m_pNextNode = pNextConnectedNode;
					v2dPedPosRelative.fX = v2dNextNodeRel.fX;
					v2dPedPosRelative.fY = v2dNextNodeRel.fY;
				}
			}
			
			for(int j = 0; j < pNextConnectedNode->bitUnkCount4To7; j++) {
				CPathNode* pNodeFurtherNext = &THEPATHS->m_AttachedPaths[THEPATHS->AttachedPointsInfo[j + pNextConnectedNode->wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY];
				if(pNodeFurtherNext != pNodeClosestToPed) {
					CVector2D vecFurtherNode;
					vecFurtherNode.fX = this->m_vecTargetPath.fX - (float)(pNodeFurtherNext->wX) / 8.0f;
					vecFurtherNode.fY = this->m_vecTargetPath.fY - (float)(pNodeFurtherNext->wY) / 8.0f;
					float fFurtherNodeDisplacement = vecFurtherNode.fY *vecFurtherNode.fY + vecFurtherNode.fX * vecFurtherNode.fX;
					if((v2dPedPosRelative.fX * v2dPedPosRelative.fX +v2dPedPosRelative.fY * v2dPedPosRelative.fY) > fFurtherNodeDisplacement) {
						if((v2dClosestPedNodeRel.fY * v2dClosestPedNodeRel.fY + v2dClosestPedNodeRel.fX * v2dClosestPedNodeRel.fX) <= fFurtherNodeDisplacement) {
							this->m_pNextNode = pNodeClosestToPed;
							v2dClosestPedNodeRel.fX = vecFurtherNode.fX;
							v2dClosestPedNodeRel.fY = vecFurtherNode.fY;
						}
						else {
							this->m_pNextNode = pNextConnectedNode;
							v2dPedPosRelative.fX = vecFurtherNode.fX;
							v2dPedPosRelative.fY = vecFurtherNode.fY;
						}
					}
					for(int k = 0; k < pNodeFurtherNext->bitUnkCount4To7; k++) {
						CPathNode* pNodeFurtherConnected = &THEPATHS->m_AttachedPaths[THEPATHS->AttachedPointsInfo[k+pNodeFurtherNext->wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY];
						if(pNodeFurtherConnected != pNextConnectedNode) {
							CVector2D vecFurtherConnectedNode;
							vecFurtherConnectedNode.fX = this->m_vecTargetPath.fX - (float)(pNodeFurtherConnected->wX) / 8.0f;
							vecFurtherConnectedNode.fY = this->m_vecTargetPath.fY - (float)(pNodeFurtherConnected->wY) / 8.0f;
							float fDistanceFurtherConnected = vecFurtherConnectedNode.fX * vecFurtherConnectedNode.fX + vecFurtherConnectedNode.fY * vecFurtherConnectedNode.fY;
							if((v2dPedPosRelative.fY * v2dPedPosRelative.fY + v2dPedPosRelative.fX * v2dPedPosRelative.fX) > fDistanceFurtherConnected) {
								if((v2dClosestPedNodeRel.fX * v2dClosestPedNodeRel.fX + v2dClosestPedNodeRel.fY * v2dClosestPedNodeRel.fY) <= fDistanceFurtherConnected) {
									this->m_pNextNode = pNodeClosestToPed;
									v2dClosestPedNodeRel.fX = vecFurtherConnectedNode.fX;
									v2dClosestPedNodeRel.fY = vecFurtherConnectedNode.fY;
								}
								else {
									this->m_pNextNode = pNextConnectedNode;
									v2dPedPosRelative.fX = vecFurtherConnectedNode.fX;
									v2dPedPosRelative.fY = vecFurtherConnectedNode.fY;
								}
							}
						}
					}
				}
			}
		}
		if(this->m_pNextNode) {
			CVector vecRandCoors;
			CPedPath::CalculateRandomCoordinates(&vecRandCoors, this->m_pNextNode, this->__parent.__parent.uiPathMedianRand);
			float fPedRelativeRandX = vecRandCoors.fX - vecPedPosition->fX;
			float fPedRelativeRandY = vecRandCoors.fY - vecPedPosition->fY;
			if((fPedRelativeRandX * fPedRelativeRandX + fPedRelativeRandY * fPedRelativeRandY) < (v2dPedPosRelative.fY * v2dPedPosRelative.fY + v2dPedPosRelative.fX * v2dPedPosRelative.fX)) {
				CPedPath::CalculateRandomCoordinates(&vecRandCoors, this->m_pNextNode, this->__parent.__parent.uiPathMedianRand);
				*vecBestCoords = vecRandCoors;
				return true;
			}
			this->m_pNextNode = 0;
		}
	}
	return false;
}