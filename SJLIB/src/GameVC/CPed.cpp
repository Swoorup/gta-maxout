#include "SJLIB/stdinc.h"

#define THEPATHS CGameVariables::GetPathFind()

bool CPed::FindBestCoordsFromNodes(float fUnusedX, float fUnusedY, float fUnusedZ, CVector* vecBestCoords) {
	if(this->m_pNextNode == NULL && (this->bfFlagsD & 0x20)) {
		CVector *vecPedPosition = (CVector*)&this->mat.vPos;
		int dwNodeClosestToPed = THEPATHS->FindNodeClosestToCoors(*vecPedPosition, 1, 999999.88f, 0, 0, 0, 0);
		CVector vecTargetPath = vecSeekVehicle;
		vecTargetPath.fZ += 1.0f;
		
		if(CWorld::GetIsLineOfSightClear(vecPedPosition, &vecTargetPath, true, false, false, true, false, false, false)) {
			return false;
		}
		
		this->m_pNextNode = NULL;
		CPathNode* pNodeClosestToPed = &THEPATHS->m_AttachedPaths[dwNodeClosestToPed];
		CVector2D v2dPedPosRelative, v2dClosestPedNodeRel;
		v2dPedPosRelative.fX = this->vecSeekVehicle.fX - vecPedPosition->fX;
		v2dPedPosRelative.fY = this->vecSeekVehicle.fY - vecPedPosition->fY;
		v2dClosestPedNodeRel.fX = this->vecSeekVehicle.fX - (float)(pNodeClosestToPed->wX) / 8.0f;
		v2dClosestPedNodeRel.fY = this->vecSeekVehicle.fY - (float)(pNodeClosestToPed->wY) / 8.0f;
		
		for(int i = 0; i < pNodeClosestToPed->bitnumberOfNodesConnected; i++) {
			CPathNode* pNextConnectedNode = &THEPATHS->m_AttachedPaths[THEPATHS->m_infoConnectedNodes[i + pNodeClosestToPed->wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY];
			float fNextNodeX = (float)(pNextConnectedNode->wX) / 8.0f;
			float fNextNodeY = (float)(pNextConnectedNode->wY) / 8.0f;
			CVector2D v2dNextNodeRel;
			v2dNextNodeRel.fX = this->vecSeekVehicle.fX - fNextNodeX;
			v2dNextNodeRel.fY = this->vecSeekVehicle.fY - fNextNodeY;
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
			
			for(int j = 0; j < pNextConnectedNode->bitnumberOfNodesConnected; j++) {
				CPathNode* pNodeFurtherNext = &THEPATHS->m_AttachedPaths[THEPATHS->m_infoConnectedNodes[j + pNextConnectedNode->wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY];
				if(pNodeFurtherNext != pNodeClosestToPed) {
					CVector2D vecFurtherNode;
					vecFurtherNode.fX = this->vecSeekVehicle.fX - (float)(pNodeFurtherNext->wX) / 8.0f;
					vecFurtherNode.fY = this->vecSeekVehicle.fY - (float)(pNodeFurtherNext->wY) / 8.0f;
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
					for(int k = 0; k < pNodeFurtherNext->bitnumberOfNodesConnected; k++) {
						CPathNode* pNodeFurtherConnected = &THEPATHS->m_AttachedPaths[THEPATHS->m_infoConnectedNodes[k+pNodeFurtherNext->wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY];
						if(pNodeFurtherConnected != pNextConnectedNode) {
							CVector2D vecFurtherConnectedNode;
							vecFurtherConnectedNode.fX = this->vecSeekVehicle.fX - (float)(pNodeFurtherConnected->wX) / 8.0f;
							vecFurtherConnectedNode.fY = this->vecSeekVehicle.fY - (float)(pNodeFurtherConnected->wY) / 8.0f;
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
			CPathFind::TakeWidthIntoAccountForWandering(&vecRandCoors, this->m_pNextNode, this->uiPathMedianRand);
			float fPedRelativeRandX = vecRandCoors.fX - vecPedPosition->fX;
			float fPedRelativeRandY = vecRandCoors.fY - vecPedPosition->fY;
			if((fPedRelativeRandX * fPedRelativeRandX + fPedRelativeRandY * fPedRelativeRandY) < (v2dPedPosRelative.fY * v2dPedPosRelative.fY + v2dPedPosRelative.fX * v2dPedPosRelative.fX)) {
				CPathFind::TakeWidthIntoAccountForWandering(&vecRandCoors, this->m_pNextNode, this->uiPathMedianRand);
				*vecBestCoords = vecRandCoors;
				return true;
			}
			this->m_pNextNode = 0;
		}
	}
	return false;
}