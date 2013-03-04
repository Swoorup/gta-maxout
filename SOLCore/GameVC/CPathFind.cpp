#include "../StdInc.h"

DWORD dwFunc_CPathFind__StoreNodeInfoCar = 0x00435C30;
DWORD dwFunc_CPathFind__StoreNodeInfoPed = 0x00435FA0;

#define VTYPE_CAR 0
#define VTYPE_BOAT 1

#define NODEINFOTYPE_EXTERNAL 1
#define NODEINFOTYPE_INTERNAL 2
#define NODEINFOTYPE_NULL 0

#define NODEINFOFLAGS_ISCROSSROAD                   0x01 //00000001b
#define NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS      0x02 //00000010b
#define NODEINFOFLAGS_POLICEROADBLOCK               0x04 //00000100b
#define NODEINFOFLAGS_IGNORENODEAREA                0x08 //00001000b
#define NODEINFOFLAGS_VEHICLETYPEBOAT               0x10 //00010000b
#define NODEINFOFLAGS_RESTRICTEDACCESS              0x20 //00100000b

#define PATHDATAFOR_CAR 0
#define PATHDATAFOR_PED 1

//Limits here
#define PATHMUL 15
//#define MAXCARGROUPNODE 1024
#define MAXCARGROUPNODE (1024 * PATHMUL)
//#define MAXPEDGROUPNODE 1214
#define MAXPEDGROUPNODE (1214 * PATHMUL)
//#define MAXPATHTEMPNODE 5000
#define MAXPATHTEMPNODE (5000 * PATHMUL)

int c_nCarPathTiles = 0;
int c_nPedPathTiles = 0;
CPathInfoForObject* cptr_InfoForTileCars = NULL;
CPathInfoForObject* cptr_InfoForTilePeds = NULL;

CTempDetachedNode* CPathFind::s_pTempExternalNodes = NULL;

CPathFind::CPathFind() 
{
    ZeroMemory(this->m_infoConnectedNodes, sizeof(this->m_infoConnectedNodes));
    ZeroMemory(this->m_InfoCarPathLinks, sizeof(this->m_InfoCarPathLinks));
    ZeroMemory(this->m_nConnectionWeight, sizeof(this->m_nConnectionWeight));
}


//435C30h
void CPathFind::StoreNodeInfoCar(int nInternalNodeCount, unsigned char iNodeType, signed char iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, unsigned char nLeftLanes, unsigned char nRightLanes, bool bIsIgnoredNode, bool bIsRestrictedAccess, unsigned char bSpeedLimit, bool bIsPoliceRoadBlock, unsigned char byteVehicleType, unsigned int dwSpawnRate, unsigned char bUnknown)
{
	if (c_nCarPathTiles < MAXCARGROUPNODE)
	{
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].fX = fNodeX / 16.0f;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].fY = fNodeY / 16.0f;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].fZ = fNodeZ / 16.0f;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteNodeType = iNodeType;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].sbNextNode = iNextNode;
	    if (fMedianWidth > 15.0f) fMedianWidth = 15.0f;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].sbMedianWidth = (signed int)(8.0f * fMedianWidth);
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteLeftLanes = nLeftLanes;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteRightLanes = nRightLanes;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteSpeedLimit = bSpeedLimit;
	    // Set the first bit to zero
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags &= ~NODEINFOFLAGS_ISCROSSROAD;
	
	    if (bUnknown)
			cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS;
		if (bIsPoliceRoadBlock)
	        cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_POLICEROADBLOCK;
	    if (bIsIgnoredNode)
			cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_IGNORENODEAREA;
		if (byteVehicleType == VTYPE_BOAT)
	        cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_VEHICLETYPEBOAT;
	    if (bIsRestrictedAccess)
			cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_RESTRICTEDACCESS;
	
	    if (dwSpawnRate > 15) dwSpawnRate = 15;
	    cptr_InfoForTileCars[c_nCarPathTiles].m_pathinfo[nInternalNodeCount].byteSpawnRate = unsigned char(dwSpawnRate);
	    if (nInternalNodeCount == 11)
		{
			cptr_InfoForTileCars[c_nCarPathTiles].SwapConnectionsToBeRightWayRound();
			c_nCarPathTiles++;
		}
	}
}


//43C060h
void CPathInfoForObject::SwapConnectionsToBeRightWayRound(void)
{
	for (int i = 0; i < 12; i++)
	{
		if (m_pathinfo[i].byteNodeType == NODEINFOTYPE_EXTERNAL && m_pathinfo[i].sbNextNode == -1)
		{
			for (int j = 0; j < 12; j++)
			{
		        if (m_pathinfo[j].byteNodeType == NODEINFOTYPE_INTERNAL && m_pathinfo[j].sbNextNode == i)
				{
					m_pathinfo[i].sbNextNode = j;
					m_pathinfo[j].sbNextNode = -1;
		
					// Swap the right most significant bit
					bool bIsCrossRoad = m_pathinfo[i].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
					m_pathinfo[i].byteFlags = m_pathinfo[i].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | m_pathinfo[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
					m_pathinfo[j].byteFlags = m_pathinfo[j].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | bIsCrossRoad & NODEINFOFLAGS_ISCROSSROAD;
				}
			}
		}
	}
}


//435FA0h
void CPathFind::StoreNodeInfoPed(int nInternalNodeCount, unsigned char iNodeType, signed char iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, unsigned char iunknown, bool bIsIgnoredNode, bool bIsRestrictedAccess, unsigned int dwSpawnRate) 
{
    if (c_nPedPathTiles < MAXPEDGROUPNODE)
	{
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].fX = fNodeX / 16.0f;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].fY = fNodeY / 16.0f;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].fZ = fNodeZ / 16.0f;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteNodeType = iNodeType;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].sbNextNode = iNextNode;
        if(fMedianWidth > 31.0f)
            fMedianWidth = 31.0f;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].sbMedianWidth = (signed int)(8.0f * fMedianWidth);
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteLeftLanes = 0;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteRightLanes = 0;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteSpeedLimit = 0;

        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags &= ~NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags &= ~NODEINFOFLAGS_POLICEROADBLOCK;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags &= ~NODEINFOFLAGS_VEHICLETYPEBOAT;
        if(iunknown)
            cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_ISCROSSROAD;
        if(bIsIgnoredNode)
            cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_IGNORENODEAREA;
        if(bIsRestrictedAccess)
            cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteFlags |= NODEINFOFLAGS_RESTRICTEDACCESS;

        if (dwSpawnRate > 15) dwSpawnRate = 15;
        cptr_InfoForTilePeds[c_nPedPathTiles].m_pathinfo[nInternalNodeCount].byteSpawnRate = unsigned char(dwSpawnRate);
        if (nInternalNodeCount == 11)
		{
			cptr_InfoForTilePeds[c_nPedPathTiles].SwapConnectionsToBeRightWayRound();
			c_nPedPathTiles++;
		}
    }
}

void CPathFind::Init(void){
    this->m_nAttachedNodes = 0;
    this->w_nTreadables = 0;
    this->m_nConnectedNodes = 0;
    this->m_nCarPathLinks = 0;
    this->Unusedfield_53804 = 0;

    
    for (int i =0; i < (9650 * PATHMUL); i++)
       this->m_AttachedPaths[i].heuristicCost = 32766;
}

void CPathFind::AllocatePathFindInfoMem(void){
    if(cptr_InfoForTileCars) 
	{
        delete [] cptr_InfoForTileCars;
        cptr_InfoForTileCars = NULL;
    }
    if(cptr_InfoForTilePeds) 
	{
        delete [] cptr_InfoForTilePeds;
        cptr_InfoForTilePeds = NULL;
    }
    if(s_pTempExternalNodes) 
	{
        delete [] s_pTempExternalNodes;
        s_pTempExternalNodes = NULL;
    }

    //heap corruption chances, so sizes might need increasing
    cptr_InfoForTileCars = new CPathInfoForObject[20000 * PATHMUL];
    cptr_InfoForTilePeds = new CPathInfoForObject[20000 * PATHMUL];
    s_pTempExternalNodes = new CTempDetachedNode[4600 * PATHMUL];

    memset(cptr_InfoForTileCars, 0, sizeof(CPathInfoForObject) * 20000 * PATHMUL);
    memset(cptr_InfoForTilePeds, 0, sizeof(CPathInfoForObject) * 20000 * PATHMUL);
    memset(s_pTempExternalNodes, 0, sizeof(CTempDetachedNode) * 4600 * PATHMUL);
    c_nPedPathTiles = 0;
    c_nCarPathTiles = 0;
}

void CPathFind::PreparePathData(void){
    CDebug::DebugAddText("PreparePathData");
    CFileMgr::SetDir("");

    //check if path info pointers are not null
    if (cptr_InfoForTileCars && cptr_InfoForTilePeds && s_pTempExternalNodes)
	{
        CTempNode* pTempNodes = new CTempNode[MAXPATHTEMPNODE];

        m_nConnectedNodes = 0;
        m_nAttachedNodes = 0;
        PreparePathDataForType(PATHDATAFOR_CAR, pTempNodes, NULL, 1.0f, cptr_InfoForTileCars, c_nCarPathTiles);
        m_nCarAttachedNodes = m_nAttachedNodes;
        PreparePathDataForType(PATHDATAFOR_PED, pTempNodes, NULL, 1.0f, cptr_InfoForTilePeds, c_nPedPathTiles);
        m_nPedAttachedNodes = m_nAttachedNodes - m_nCarAttachedNodes;

        delete [] pTempNodes;
        CountFloodFillGroups(PATHDATAFOR_CAR);
        CountFloodFillGroups(PATHDATAFOR_PED);
        delete [] cptr_InfoForTileCars;
        cptr_InfoForTileCars = NULL;
        delete [] cptr_InfoForTilePeds;
        cptr_InfoForTilePeds = NULL;

        delete [] s_pTempExternalNodes;
        s_pTempExternalNodes = NULL;
    }
    CDebug::DebugAddText("Done with PreparePathData\n");
}

void CPathFind::PreparePathDataForType( unsigned char bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathTiles, int nGroupNodesForObject) {
    signed int *aGroupNodeIndex_InternalNode = new signed int[9650 * PATHMUL];
	int32_t nTempExternalNodes = 0;
	int32_t nPrevObjectAttachedNodes = m_nAttachedNodes;
	int32_t nPrevObjectAttachedPoints = m_nConnectedNodes;
	DWORD pas = (DWORD)pThePaths;

	if (nGroupNodesForObject > 0)
	{
		for (int i = 0; i < nGroupNodesForObject; i++)
		{
			int nAttachedPathsForCurrentGroup = m_nAttachedNodes;
			for (int j = 0; j < 12; j++)
			{
				if ( pPathTiles[i].m_pathinfo[j].byteNodeType == NODEINFOTYPE_INTERNAL)
				{
					m_AttachedPaths[m_nAttachedNodes].wX = (signed int)(8.0f * pPathTiles[i].m_pathinfo[j].fX);
					m_AttachedPaths[m_nAttachedNodes].wY = (signed int)(8.0f * pPathTiles[i].m_pathinfo[j].fY);
					m_AttachedPaths[m_nAttachedNodes].wZ = (signed int)(8.0f * pPathTiles[i].m_pathinfo[j].fZ);

					aGroupNodeIndex_InternalNode[m_nAttachedNodes] = -(1  + i);
					m_AttachedPaths[m_nAttachedNodes].sbMedianWidth = pPathTiles[i].m_pathinfo[j].sbMedianWidth;
					m_AttachedPaths[m_nAttachedNodes].byteSpawnRate = pPathTiles[i].m_pathinfo[j].byteSpawnRate;

					m_AttachedPaths[m_nAttachedNodes].bitSpeedLimit = pPathTiles[i].m_pathinfo[j].byteSpeedLimit;
					m_AttachedPaths[m_nAttachedNodes].bitCopsRoadBlock = (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_POLICEROADBLOCK) >> 2;
					m_AttachedPaths[m_nAttachedNodes].bitIsIgnoredNode = (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_IGNORENODEAREA) >> 3;
					m_AttachedPaths[m_nAttachedNodes].bitIsVehicleBoat = (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_VEHICLETYPEBOAT) >> 4;
					m_AttachedPaths[m_nAttachedNodes].bitHaveUnrandomizedVehClass = (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS) >> 1;
					m_AttachedPaths[m_nAttachedNodes].bitRestrictedAccess = (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_RESTRICTEDACCESS) >> 5;
					m_nAttachedNodes++;
				}
				else if ( pPathTiles[i].m_pathinfo[j].byteNodeType == NODEINFOTYPE_EXTERNAL)
				{
					s_pTempExternalNodes[nTempExternalNodes].fX = pPathTiles[i].m_pathinfo[j].fX;
					s_pTempExternalNodes[nTempExternalNodes].fY = pPathTiles[i].m_pathinfo[j].fY;
					s_pTempExternalNodes[nTempExternalNodes].fZ = pPathTiles[i].m_pathinfo[j].fZ;
					s_pTempExternalNodes[nTempExternalNodes].sNextNodeIndex = pPathTiles[i].m_pathinfo[j].sbNextNode + nAttachedPathsForCurrentGroup;
					s_pTempExternalNodes[nTempExternalNodes].byteLeftLanes = pPathTiles[i].m_pathinfo[j].byteLeftLanes;
					s_pTempExternalNodes[nTempExternalNodes].byteRightLanes = pPathTiles[i].m_pathinfo[j].byteRightLanes;
					s_pTempExternalNodes[nTempExternalNodes].sbMedianWidth = pPathTiles[i].m_pathinfo[j].sbMedianWidth;
					if (pPathTiles[i].m_pathinfo[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD)
						s_pTempExternalNodes[nTempExternalNodes++].bIsCrossRoad = true;
					else
						s_pTempExternalNodes[nTempExternalNodes++].bIsCrossRoad = false;
				}
			}
		}
	}
	// Phase 1 ended.

	//Phase 2 Started

	// this phase combines all the external nodes from all groups together uniquely 
	// and specifies the pointers to each end or each internal node ends
	int nNewDetachedNode = 0;
    for (int i= 0; i < nTempExternalNodes; i++)
	{
		float fRange = fUnkRange;
		int nClosestDetachedNodeToExternalNode = -1;

		// check all new detached nodes if they lie in the range with the external node
		for (int j = 0; j < nNewDetachedNode; j++)
		{
			if ( pTempNode[j].stateStoreType == CTempNode::NOT_IN_RANGE)
			{
				float fxDiff = pTempNode[j].fX - s_pTempExternalNodes[i].fX;
				float fyDiff = pTempNode[j].fY - s_pTempExternalNodes[i].fY;
				fxDiff = fxDiff < 0.0f ? -fxDiff : fxDiff;
				fyDiff = fyDiff < 0.0f ? -fyDiff : fyDiff;

				//check if nodes are close enough 
				if (fxDiff <= fRange && fyDiff <= fRange)
                {
					// to check if more closer new-detached node exist
					if (fxDiff <= fyDiff)
                        fRange = fyDiff;
                    else
                        fRange = fxDiff;
                    nClosestDetachedNodeToExternalNode = j;
				}
			}
		}

		// if the two compared nodes are not close, directly assign the attributes
		if (nClosestDetachedNodeToExternalNode == -1)
		{
			pTempNode[nNewDetachedNode].fX = s_pTempExternalNodes[i].fX;
			pTempNode[nNewDetachedNode].fY = s_pTempExternalNodes[i].fY;
			pTempNode[nNewDetachedNode].fZ = s_pTempExternalNodes[i].fZ;
			pTempNode[nNewDetachedNode].nConnectedAttachedNode = s_pTempExternalNodes[i].sNextNodeIndex;
			if (bytePathDataFor == PATHDATAFOR_CAR){
				pTempNode[nNewDetachedNode].byteLeftLanes = s_pTempExternalNodes[i].byteLeftLanes;
				pTempNode[nNewDetachedNode].byteRightLanes = s_pTempExternalNodes[i].byteRightLanes;
			}
			pTempNode[nNewDetachedNode].sbMedianWidth = s_pTempExternalNodes[i].sbMedianWidth;
			pTempNode[nNewDetachedNode].bIsCrossRoad = s_pTempExternalNodes[i].bIsCrossRoad;
			pTempNode[nNewDetachedNode].stateStoreType = CTempNode::NOT_IN_RANGE;
			nNewDetachedNode++;
		}
		// if they are close enough nClosestDetachedNodeToExternalNode points to index of the newly stored nodes
		else 
		{
                //work on existing node
                //handle other external node closest to the temp node
			
			pTempNode[nClosestDetachedNodeToExternalNode].nOtherConnectedAttachedNode = s_pTempExternalNodes[i].sNextNodeIndex;
			pTempNode[nClosestDetachedNodeToExternalNode].stateStoreType = CTempNode::AVERAGED_NODE;
			float fVecX = float(m_AttachedPaths[pTempNode[nClosestDetachedNodeToExternalNode].nConnectedAttachedNode].wX
							   -m_AttachedPaths[pTempNode[nClosestDetachedNodeToExternalNode].nOtherConnectedAttachedNode].wX)/8.0f;
			float fVecY = float(m_AttachedPaths[pTempNode[nClosestDetachedNodeToExternalNode].nConnectedAttachedNode].wY
                               -m_AttachedPaths[pTempNode[nClosestDetachedNodeToExternalNode].nOtherConnectedAttachedNode].wY)/8.0f;
            float fLength = sqrt(fVecX * fVecX + fVecY * fVecY);
            pTempNode[nClosestDetachedNodeToExternalNode].byteNormalX = (signed char)(fVecX/ fLength * 100.0f);
			pTempNode[nClosestDetachedNodeToExternalNode].byteNormalY = (signed char)(fVecY/ fLength * 100.0f);

            //get the average of the two closest node
            pTempNode[nClosestDetachedNodeToExternalNode].fX += s_pTempExternalNodes[i].fX;
            pTempNode[nClosestDetachedNodeToExternalNode].fX /= 2.0f;
			pTempNode[nClosestDetachedNodeToExternalNode].fY += s_pTempExternalNodes[i].fY;
            pTempNode[nClosestDetachedNodeToExternalNode].fY /= 2.0f;
			pTempNode[nClosestDetachedNodeToExternalNode].fZ += s_pTempExternalNodes[i].fZ;
            pTempNode[nClosestDetachedNodeToExternalNode].fZ /= 2.0f;

			if (pTempNode[nClosestDetachedNodeToExternalNode].sbMedianWidth <= s_pTempExternalNodes[i].sbMedianWidth)
				pTempNode[nClosestDetachedNodeToExternalNode].sbMedianWidth = s_pTempExternalNodes[i].sbMedianWidth;
			pTempNode[nClosestDetachedNodeToExternalNode].bIsCrossRoad = s_pTempExternalNodes[i].bIsCrossRoad;
			if (bytePathDataFor == PATHDATAFOR_CAR &&
                pTempNode[nClosestDetachedNodeToExternalNode].byteLeftLanes &&
                pTempNode[nClosestDetachedNodeToExternalNode].byteRightLanes &&
                (!s_pTempExternalNodes[i].byteLeftLanes || !s_pTempExternalNodes[i].byteRightLanes))
			{
				pTempNode[nClosestDetachedNodeToExternalNode].byteLeftLanes = s_pTempExternalNodes[i].byteRightLanes;
				pTempNode[nClosestDetachedNodeToExternalNode].byteRightLanes = s_pTempExternalNodes[i].byteLeftLanes;
			}
		}
    }
	//Phase 2 Ended{
    //Phase 3 Started Error exist here

		/*
	*	Assigns the next node a pathnode is connected to specified by 
		m_nConnectedNodes index array. This array is accessed through
		wRouteInfoIndex.
	*	Number of nodes that is attached to one node is specified by
		bitnumberOfNodesConnected and the connection array is stored
		sequentially in m_nConnectedNodes index array.
		*/
	for (int i = nPrevObjectAttachedNodes; i < m_nAttachedNodes; i++)
	{
		m_AttachedPaths[i].bitnumberOfNodesConnected = 0;
		m_AttachedPaths[i].wRouteInfoIndex =  m_nConnectedNodes;


		// core loop statements succeed only if external node is connected to internal node / i
		for (int j = 0; j < nNewDetachedNode; j++)
		{
			if (pTempNode[j].stateStoreType == CTempNode::AVERAGED_NODE)
			{
				// this happens only at the time external node is connected to internal node
				if (i == pTempNode[j].nConnectedAttachedNode || i == pTempNode[j].nOtherConnectedAttachedNode)
				{
					// at this point pTempNode acts as a bridge between two internal nodes
					if ( i == pTempNode[j].nConnectedAttachedNode )
						m_infoConnectedNodes[m_nConnectedNodes] = pTempNode[j].nOtherConnectedAttachedNode;
					else
						m_infoConnectedNodes[m_nConnectedNodes] = pTempNode[j].nConnectedAttachedNode;

					CPathNode* pCurrentNode = &m_AttachedPaths[m_infoConnectedNodes[m_nConnectedNodes] & em_infoConnectedNodesNODEINDEXONLY];
					//calculate the distance between internal or attached nodes connected by a external node
					float fDistance = sqrt((float(m_AttachedPaths[i].wX - pCurrentNode->wX)/8.0f * float(m_AttachedPaths[i].wX - pCurrentNode->wX)/8.0f) +
										   (float(m_AttachedPaths[i].wY - pCurrentNode->wY)/8.0f * float(m_AttachedPaths[i].wY - pCurrentNode->wY)/8.0f) +
										   (float(m_AttachedPaths[i].wZ - pCurrentNode->wZ)/8.0f * float(m_AttachedPaths[i].wZ - pCurrentNode->wZ)/8.0f));
					if (fDistance > 255.0f) fDistance = 255.0f;
					m_nConnectionWeight[m_nConnectedNodes] = (signed char)fDistance;
					if (pTempNode[j].bIsCrossRoad) m_infoConnectedNodes[m_nConnectedNodes] |= em_infoConnectedNodesCROSSROAD;
					if (bytePathDataFor == PATHDATAFOR_CAR)
					{
						bool bIsDetachedNodeAlreadyStored = false;
                        for (int k = 0; k < m_nCarPathLinks; k++)
						{
							if (
								m_CarPathLinks[k].NormalVecX == (signed char)pTempNode[j].byteNormalX &&
								m_CarPathLinks[k].NormalVecY == (signed char)pTempNode[j].byteNormalY &&
								m_CarPathLinks[k].wX == (signed int)(8.0f * pTempNode[j].fX) &&
								m_CarPathLinks[k].wY == (signed int)(8.0f * pTempNode[j].fY) 
							)
							{
								m_InfoCarPathLinks[m_nConnectedNodes] = k;
								bIsDetachedNodeAlreadyStored = true;
								break;
							}
                        }
						if (!bIsDetachedNodeAlreadyStored)
						{
							m_CarPathLinks[m_nCarPathLinks].NormalVecX = pTempNode[j].byteNormalX;
							m_CarPathLinks[m_nCarPathLinks].NormalVecY = pTempNode[j].byteNormalY;
							m_CarPathLinks[m_nCarPathLinks].wX = (signed int)(8.0f * pTempNode[j].fX);
							m_CarPathLinks[m_nCarPathLinks].wY = (signed int)(8.0f * pTempNode[j].fY);
							m_CarPathLinks[m_nCarPathLinks].nIndexToAttachedNode = i;
							m_CarPathLinks[m_nCarPathLinks].bitLeftLanes = pTempNode[j].byteLeftLanes;
							m_CarPathLinks[m_nCarPathLinks].bitRightLanes = pTempNode[j].byteRightLanes;
							m_CarPathLinks[m_nCarPathLinks].byteTrafficFlags &= 0xFC;
							m_CarPathLinks[m_nCarPathLinks].sbMedianWidth = pTempNode[j].sbMedianWidth;
							m_InfoCarPathLinks[m_nConnectedNodes] = m_nCarPathLinks;
							m_nCarPathLinks++;
                        }
					}
					// increment number of connected nodes to node[i]
					m_AttachedPaths[i].bitnumberOfNodesConnected = m_AttachedPaths[i].bitnumberOfNodesConnected + 1;
					m_nConnectedNodes++;
				}
			}
		}

		// following codes handles the internally connected nodes
        //Only select the internal nodes
		CPathInfoForObject *pPathInfoGroup = &pPathTiles[(-1 - aGroupNodeIndex_InternalNode[i])];
        int offsetOfiInGroup = 0;
		int nAssumedGroupFirstNode = 0;
		if (( i -12) >= nPrevObjectAttachedNodes)
			nAssumedGroupFirstNode = i - 12;
		else
			nAssumedGroupFirstNode = nPrevObjectAttachedNodes;

		for (int k = nAssumedGroupFirstNode; k < i; k++)
			if (aGroupNodeIndex_InternalNode[i] == aGroupNodeIndex_InternalNode[k]) offsetOfiInGroup++;
        
        int nAssumedGroupLastNode;

        if ((i + 12) <= m_nAttachedNodes)
            nAssumedGroupLastNode = i + 12;
        else 
			nAssumedGroupLastNode = m_nAttachedNodes;

		for(int nNodesInCurrentGroup = nAssumedGroupFirstNode; nNodesInCurrentGroup < nAssumedGroupLastNode; nNodesInCurrentGroup++)
        {
        	//check if they are in the same group
			if (aGroupNodeIndex_InternalNode[i] == aGroupNodeIndex_InternalNode[nNodesInCurrentGroup]){
				if (nNodesInCurrentGroup != i){
					int currentOffsetInGroup = offsetOfiInGroup + nNodesInCurrentGroup - i; //I had  written 1 instead of i
					if (currentOffsetInGroup == pPathInfoGroup[offsetOfiInGroup].sbNextNode ||
						offsetOfiInGroup == pPathInfoGroup[currentOffsetInGroup].sbNextNode)
                    {
						m_infoConnectedNodes[m_nConnectedNodes] = nNodesInCurrentGroup;
						CVector vecCurrentTestNode = m_AttachedPaths[i].Form3DVector() - m_AttachedPaths[nNodesInCurrentGroup].Form3DVector();

						float fDist = vecCurrentTestNode.Length();
						if (fDist > 255.0f) fDist = 255.0f;
						m_nConnectionWeight[m_nConnectedNodes] = (signed char)fDist;
						if (bytePathDataFor == PATHDATAFOR_PED)
						{
							if (currentOffsetInGroup == pPathInfoGroup[offsetOfiInGroup].sbNextNode && //NOT FEELING WELL HERE
								pPathInfoGroup[offsetOfiInGroup].byteFlags & NODEINFOFLAGS_ISCROSSROAD ||
							    offsetOfiInGroup == pPathInfoGroup[currentOffsetInGroup].sbNextNode &&
							    pPathInfoGroup[currentOffsetInGroup].byteFlags & NODEINFOFLAGS_ISCROSSROAD)
						    {
						    	m_infoConnectedNodes[m_nConnectedNodes] |= em_infoConnectedNodesCROSSROAD;
						    }
						}
						else 
						{
							CVector2D iPoint = m_AttachedPaths[i].Form2DVector();
							CVector2D nPoint = m_AttachedPaths[nNodesInCurrentGroup].Form2DVector();

							CVector2D middlePoint = (iPoint + nPoint) / 2.0f;
							CVector2D v2dCurrentTestNode = nPoint - iPoint;

							v2dCurrentTestNode.Normalize();
							if (i < nNodesInCurrentGroup ){
								v2dCurrentTestNode.fX = -v2dCurrentTestNode.fX;
								v2dCurrentTestNode.fY = -v2dCurrentTestNode.fY;
							}
							bool bIsDetachedNodeAlreadyStored = false;
							for (int k = 0; k < m_nCarPathLinks; k++)
							{
								if (
									m_CarPathLinks[k].NormalVecX == (signed char)(100.0f * v2dCurrentTestNode.fX) &&
									m_CarPathLinks[k].NormalVecY == (signed char)(100.0f * v2dCurrentTestNode.fY) &&
									m_CarPathLinks[k].wX == (signed int)(middlePoint.fX * 8.0f) &&
									m_CarPathLinks[k].wY == (signed int)(middlePoint.fY * 8.0f)
								)
								{
									m_InfoCarPathLinks[m_nConnectedNodes] = k;
									bIsDetachedNodeAlreadyStored = true;
									break;
									// if it exist don't create new detached nodes
								}
							}
							
							if (!bIsDetachedNodeAlreadyStored)
							{
								m_CarPathLinks[m_nCarPathLinks].NormalVecX = (signed char)(100.0f * v2dCurrentTestNode.fX);
								m_CarPathLinks[m_nCarPathLinks].NormalVecY = (signed char)(100.0f * v2dCurrentTestNode.fY);
								m_CarPathLinks[m_nCarPathLinks].wX = (signed int)(8.0f * middlePoint.fX);
								m_CarPathLinks[m_nCarPathLinks].wY = (signed int)(8.0f * middlePoint.fY);
								m_CarPathLinks[m_nCarPathLinks].nIndexToAttachedNode = i;
								m_CarPathLinks[m_nCarPathLinks].bitLeftLanes = 7; //Max value
								m_CarPathLinks[m_nCarPathLinks].bitRightLanes = 7;
								m_CarPathLinks[m_nCarPathLinks].byteTrafficFlags &= 0xFC;
								if ((unsigned __int8)m_AttachedPaths[nNodesInCurrentGroup].sbMedianWidth <= m_AttachedPaths[i].sbMedianWidth)
									m_CarPathLinks[m_nCarPathLinks].sbMedianWidth = m_AttachedPaths[i].sbMedianWidth;
								else
									m_CarPathLinks[m_nCarPathLinks].sbMedianWidth = m_AttachedPaths[nNodesInCurrentGroup].sbMedianWidth;
								m_InfoCarPathLinks[m_nConnectedNodes] = m_nCarPathLinks;
								++m_nCarPathLinks;
							}
						}
						m_AttachedPaths[i].bitnumberOfNodesConnected = m_AttachedPaths[i].bitnumberOfNodesConnected + 1;
						++m_nConnectedNodes;
                    }
				}
			}
		}
	}
	//BIG BOY Is now close wooohooo

    //Phase 4
    if (bytePathDataFor == PATHDATAFOR_CAR){
        DWORD dwNodeCountBound = 0;
        bool bShouldLoopExit = false;
        while ( bShouldLoopExit == false && dwNodeCountBound < 12){
            ++dwNodeCountBound;
            bShouldLoopExit = true;
            for (int j= 0; j < m_nAttachedNodes; j++){
                if (m_AttachedPaths[j].bitnumberOfNodesConnected == 2){
                    int iCurrentDetachedIndex = m_InfoCarPathLinks[m_AttachedPaths[j].wRouteInfoIndex];
                    int iForwardDetachedIndex = m_InfoCarPathLinks[m_AttachedPaths[j].wRouteInfoIndex + 1];

                    int iCurrentDetachedLeftLane = m_CarPathLinks[iCurrentDetachedIndex].bitLeftLanes;
                    int iCurrentDetachedRightLane = m_CarPathLinks[iCurrentDetachedIndex].bitRightLanes;
                    int iForwardDetachedLeftLane = m_CarPathLinks[iForwardDetachedIndex].bitLeftLanes;
                    int iForwardDetachedRightLane = m_CarPathLinks[iForwardDetachedIndex].bitRightLanes;

                    int *iCurrentLane1, *iCurrentLane2, *iForwardLane1, *iForwardLane2;
                    if (m_CarPathLinks[iCurrentDetachedIndex].nIndexToAttachedNode == j){
                        iCurrentLane1 = &iCurrentDetachedLeftLane;
                        iCurrentLane2 = &iCurrentDetachedRightLane;
                    }
                    else{
                        iCurrentLane1 = &iCurrentDetachedRightLane;
                        iCurrentLane2 = &iCurrentDetachedLeftLane;
                    }
                    if (m_CarPathLinks[iForwardDetachedIndex].nIndexToAttachedNode == j){
                        iForwardLane1 = &iForwardDetachedRightLane;
                        iForwardLane2 = &iForwardDetachedLeftLane;
                    }
                    else{
                        iForwardLane1 = &iForwardDetachedLeftLane;
                        iForwardLane2 = &iForwardDetachedRightLane;
                    }

                    if (*iCurrentLane1 == 7 && *iForwardLane1 != 7){
                        *iCurrentLane1 = *iForwardLane1;
                        bShouldLoopExit = false;
                    }
                    if (*iCurrentLane2 == 7 && *iForwardLane2 != 7){
                        *iCurrentLane2 = *iForwardLane2;
                        bShouldLoopExit = false;
                    }

                    if (*iForwardLane2 == 7 && *iCurrentLane2 != 7){
                        *iForwardLane2 = *iCurrentLane2;
                        bShouldLoopExit = false;
                    }
                    if (*iForwardLane1 == 7 && *iCurrentLane1 != 7){
                        *iForwardLane1 = *iCurrentLane1;
                        bShouldLoopExit = false;
                    }

                    if (*iCurrentLane1 == 7 && *iForwardLane1 == 7)
                        bShouldLoopExit = false;
                    if (*iForwardLane2 == 7 && *iForwardLane2 == 7)
                        bShouldLoopExit = false;

                    m_CarPathLinks[iCurrentDetachedIndex].bitLeftLanes = iCurrentDetachedLeftLane;
                    m_CarPathLinks[iCurrentDetachedIndex].bitRightLanes = iCurrentDetachedRightLane;
                    m_CarPathLinks[iForwardDetachedIndex].bitLeftLanes = iForwardDetachedLeftLane;
                    m_CarPathLinks[iForwardDetachedIndex].bitRightLanes = iForwardDetachedRightLane;
                }
            }
        }

        for (int j = 0; j < m_nAttachedNodes; j++){
            for (int k = 0; k < m_AttachedPaths[j].bitnumberOfNodesConnected; k++){
                if (m_CarPathLinks[m_InfoCarPathLinks[k + m_AttachedPaths[j].wRouteInfoIndex]].bitLeftLanes == 7)
                    m_CarPathLinks[m_InfoCarPathLinks[k + m_AttachedPaths[j].wRouteInfoIndex]].bitLeftLanes = 0;
                if (m_CarPathLinks[m_InfoCarPathLinks[k + m_AttachedPaths[j].wRouteInfoIndex]].bitRightLanes == 7)
                    m_CarPathLinks[m_InfoCarPathLinks[k + m_AttachedPaths[j].wRouteInfoIndex]].bitRightLanes = 0;
            }
        }
    }

        //Phase 5
    if ( bytePathDataFor == PATHDATAFOR_CAR){
        bool bKeepLoop;
        do{
            bKeepLoop= false;
            for (int i=0; i<m_nAttachedNodes; i++){
                if (!m_AttachedPaths[i].bitUnknownFlag3){
                    int nUnknownFlag3 = 0;
                    for (int j=0; j<m_AttachedPaths[i].bitnumberOfNodesConnected; j++){
                        if (!m_AttachedPaths[m_infoConnectedNodes[j + m_AttachedPaths[i].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY].bitUnknownFlag3)
                            nUnknownFlag3++;
                    }
                    if (nUnknownFlag3 < 2){
                        m_AttachedPaths[i].bitUnknownFlag3 = 1;
                        bKeepLoop = true;
                    }
                }
            }
        } while (bKeepLoop == true);
    }

	// if the last car attached node set is not connected to any other nodes, move up by one PathNode
    if (bytePathDataFor == PATHDATAFOR_PED){
        while (nPrevObjectAttachedNodes < m_nAttachedNodes){
            if (m_AttachedPaths[nPrevObjectAttachedNodes].bitnumberOfNodesConnected == 0){
                for (int m = nPrevObjectAttachedNodes; m < (m_nAttachedNodes - 1); m++){
                    m_AttachedPaths[m].wNextListOrNodeIndex = m_AttachedPaths[m+1].wNextListOrNodeIndex;
                    m_AttachedPaths[m].wPreviousNodeIndex = m_AttachedPaths[m+1].wPreviousNodeIndex;
                    m_AttachedPaths[m].wX = m_AttachedPaths[m+1].wX;
                    m_AttachedPaths[m].wY = m_AttachedPaths[m+1].wY;
                    m_AttachedPaths[m].wZ = m_AttachedPaths[m+1].wZ;
                    m_AttachedPaths[m].heuristicCost = m_AttachedPaths[m+1].heuristicCost;
                    m_AttachedPaths[m].wRouteInfoIndex = m_AttachedPaths[m+1].wRouteInfoIndex;
                    m_AttachedPaths[m].sbMedianWidth = m_AttachedPaths[m+1].sbMedianWidth;
                    m_AttachedPaths[m].ucFloodColor = m_AttachedPaths[m+1].ucFloodColor;
                    m_AttachedPaths[m].sbMedianWidth = m_AttachedPaths[m+1].sbMedianWidth;
                    m_AttachedPaths[m].bitnumberOfNodesConnected = m_AttachedPaths[m+1].bitnumberOfNodesConnected;
                    m_AttachedPaths[m].bitUnknownFlag3 = m_AttachedPaths[m+1].bitUnknownFlag3;
                    m_AttachedPaths[m].bitIsIgnoredNode = m_AttachedPaths[m+1].bitIsIgnoredNode;
                    m_AttachedPaths[m].bitRestrictedAccess = m_AttachedPaths[m+1].bitRestrictedAccess;
                    m_AttachedPaths[m].bitCopsRoadBlock = m_AttachedPaths[m+1].bitCopsRoadBlock;

	                m_AttachedPaths[m].bitIsVehicleBoat = m_AttachedPaths[m+1].bitIsVehicleBoat;
	                m_AttachedPaths[m].bitHaveUnrandomizedVehClass = m_AttachedPaths[m+1].bitHaveUnrandomizedVehClass;
	                m_AttachedPaths[m].bitUnkFlagFor2 = m_AttachedPaths[m+1].bitUnkFlagFor2;
                    m_AttachedPaths[m].bitSpeedLimit = m_AttachedPaths[m+1].bitSpeedLimit;
                    m_AttachedPaths[m].bitPadFlags8To10 = m_AttachedPaths[m+1].bitPadFlags8To10;
                    m_AttachedPaths[m].byteSpawnRate = m_AttachedPaths[m +1].byteSpawnRate;
                }
                for (int n = nPrevObjectAttachedPoints; n < m_nConnectedNodes;n++){
                    if ((m_infoConnectedNodes[n] & em_infoConnectedNodesNODEINDEXONLY) >= nPrevObjectAttachedNodes)
                        m_infoConnectedNodes[n] = (m_infoConnectedNodes[n] & em_infoConnectedNodesNODEINDEXONLY) - 1;
                }
                --nPrevObjectAttachedNodes;
                --m_nAttachedNodes;
            }
            ++nPrevObjectAttachedNodes;
        }
    }
    delete [] aGroupNodeIndex_InternalNode;
}

void CPathFind::CountFloodFillGroups(unsigned char iPathDataFor){
	int indexStartNode, indexEndNode;

	switch(iPathDataFor) 
	{
		case PATHDATAFOR_CAR:
			indexStartNode = 0;
			indexEndNode = m_nCarAttachedNodes;
			break;
		case PATHDATAFOR_PED:
			indexStartNode = m_nCarAttachedNodes;
			indexEndNode = m_nAttachedNodes;
			break;
	}

	// reset all flood fill colours to zero
	if(indexStartNode < indexEndNode) 
		for(int i = indexStartNode; i < indexEndNode; i++) 
			m_AttachedPaths[i].ucFloodColor = 0;

	int j = 0;
	while (true)
	{
		++j;
		if (j > (1500)) 
		{
			int k;
			for (k = indexStartNode; m_AttachedPaths[k].ucFloodColor && k < indexEndNode; k++) ;
			CDebug::DebugAddText("NumNodes: %d Accounted for: %d\n", indexEndNode - indexStartNode, k - indexStartNode);
		}
		int k;
		for (k = indexStartNode; m_AttachedPaths[k].ucFloodColor && k < indexEndNode; k++) ;
		if (k == indexEndNode) 
			break;

		CPathNode* pNode = &m_AttachedPaths[k];
		pNode->wPreviousNodeIndex = -1;
		pNode->ucFloodColor = j;

		if(pNode->bitnumberOfNodesConnected == 0)
		{
			if(iPathDataFor == PATHDATAFOR_PED)
				CDebug::DebugAddText("Single ped node: %f %f %f\n", (float)(pNode->wX) / 8.0f, (float)(pNode->wY) / 8.0f, (float)(pNode->wZ) / 8.0f);
			else
				CDebug::DebugAddText("Single car node: %f %f %f\n",	(float)(pNode->wX) / 8.0f, (float)(pNode->wY) / 8.0f, (float)(pNode->wZ) / 8.0f);
		}

		// the following while loop assigns a unique flood fill ID to lists of connected nodes accessing other nodes via a common node
		while(pNode) 
		{
			CPathNode* pPrevCommonFloodFillNodes = pNode;
			pNode = GetAppropriateListFromIndex(pPrevCommonFloodFillNodes->wPreviousNodeIndex);

			for(int i = 0; i < (pPrevCommonFloodFillNodes->bitnumberOfNodesConnected); ++i) 
			{
				int indexAttachedNode = m_infoConnectedNodes[i + pPrevCommonFloodFillNodes->wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
				if(!m_AttachedPaths[indexAttachedNode].ucFloodColor)
				{
                    m_AttachedPaths[indexAttachedNode].ucFloodColor = j;
                    //if j is 0 or 255
                    if(!m_AttachedPaths[indexAttachedNode].ucFloodColor)
                        m_AttachedPaths[indexAttachedNode].ucFloodColor = 128;
                    

					// the following code helps gen reverse list of nodes attached to a common node in the same flood fill
					m_AttachedPaths[indexAttachedNode].wPreviousNodeIndex = GetAppropriateIndexFromPathNode(pNode);

					pNode = &m_AttachedPaths[indexAttachedNode];
				}
			}
		}
	}
	m_nFloodFillAmountUsed[iPathDataFor] = j - 1;
	CDebug::DebugAddText("GraphType:%d. FloodFill groups:%d\n", iPathDataFor, j);
}

void CPathFind::AddNodeToList(CPathNode *pTargetNode, int nHeuristicCostAndListIndex){
	signed short newIndexToList = nHeuristicCostAndListIndex & 511;
	// at first search, -1 is gonna be in m_OpenNodeList
	signed int indexPrevNode = m_OpenNodeList[newIndexToList].wPreviousNodeIndex;

	/*if (GetAppropriateListFromIndex(indexCommonNode))
		pTargetNode->wPreviousNodeIndex = indexCommonNode;
	else
		pTargetNode->wPreviousNodeIndex = -1;*/
	pTargetNode->wPreviousNodeIndex = indexPrevNode;
	pTargetNode->wNextListOrNodeIndex = newIndexToList;

	CPathNode* pCommonNode = GetAppropriateListFromIndex(indexPrevNode);
	if(pCommonNode)
		pCommonNode->wNextListOrNodeIndex = GetAppropriateIndexFromPathNode(pTargetNode);

	m_OpenNodeList[newIndexToList].wPreviousNodeIndex = GetAppropriateIndexFromPathNode(pTargetNode);

	pTargetNode->heuristicCost = (signed short)nHeuristicCostAndListIndex;
}

// behaves like a stack, 
void CPathFind::RemoveNodeFromList(CPathNode *pRemoveNode) {
	CPathNode* pListObject = GetAppropriateListFromIndex(pRemoveNode->wNextListOrNodeIndex);

	pListObject->wPreviousNodeIndex = pRemoveNode->wPreviousNodeIndex;

	CPathNode* pNext = GetAppropriateListFromIndex(pRemoveNode->wPreviousNodeIndex);

	if (pNext)
		pNext->wNextListOrNodeIndex = pRemoveNode->wNextListOrNodeIndex;
}

// I have high doubts in this function
void CPathFind::DoPathSearch(int iPathDataFor, CVector& posOrigin, int iFirstNode, CVector& posDest, CPathNode **pIntermediateNodeList, short *pSteps, short sMaxSteps, void *pVehicle, float *pfPathCost, float fMaxRadius, int iLastNode) {
	int iDestNodeIndex = iLastNode;
	int iOriginNodeIndex = iFirstNode;

	static CPathNode* c_pResetNodeList[9650 * PATHMUL];

	if(iDestNodeIndex == -1)
		iDestNodeIndex = FindNodeClosestToCoors(posDest, iPathDataFor, fMaxRadius, 0, 0, 0, 0);

	if(iOriginNodeIndex == -1)
		iOriginNodeIndex = FindNodeClosestToCoors(posOrigin, iPathDataFor, fMaxRadius, 0, 0, 0, 0);

	if (iDestNodeIndex >= 0 && iOriginNodeIndex >= 0)
	{
		if (iOriginNodeIndex == iDestNodeIndex)
		{
			*pSteps = 0;
			if ( pfPathCost) *pfPathCost = 0.0f;
		}
	    else if (m_AttachedPaths[iDestNodeIndex].ucFloodColor == m_AttachedPaths[iOriginNodeIndex].ucFloodColor)
		{
	        for (int i = 0; i < 512; i++)
                m_OpenNodeList[i].wPreviousNodeIndex = -1;

            CPathNode* pDestinationNode = &m_AttachedPaths[iDestNodeIndex];
		    AddNodeToList(pDestinationNode, 0);
		    int nNodesToReset = 1;
            c_pResetNodeList[0] = pDestinationNode;
            short nCircleList = 0;
            bool bFound = false;
            // Phase 1
			// loop through the linear array created at run-time
            do 
			{
				// set the base node for searching its connected nodes
                CPathNode* pInitialSearchNode = GetAppropriateListFromIndex(m_OpenNodeList[nCircleList].wPreviousNodeIndex);

				// the following code finds the best possible path cost for all nodes to reach pInitialSearchNode
				// loop through the list 
                while(pInitialSearchNode) 
				{
                    if (pInitialSearchNode == &m_AttachedPaths[iOriginNodeIndex])
						bFound = true;

                    for(int i = 0; i < pInitialSearchNode->bitnumberOfNodesConnected; i++) 
					{
                        int indexArrayAttached = i + pInitialSearchNode->wRouteInfoIndex;
                        int indexNodeAttached = m_infoConnectedNodes[indexArrayAttached] & em_infoConnectedNodesNODEINDEXONLY;

                        int bestEstimatedCost = pInitialSearchNode->heuristicCost + m_nConnectionWeight[indexArrayAttached];
							
                        if (bestEstimatedCost < m_AttachedPaths[indexNodeAttached].heuristicCost) 
						{
							// we found the node that has already been added but has higher path cost
                            if (m_AttachedPaths[indexNodeAttached].heuristicCost != 32766)
                                RemoveNodeFromList(&m_AttachedPaths[indexNodeAttached]);
                            
							// the node has the default path cost and is going to be added to the list
                            if (m_AttachedPaths[indexNodeAttached].heuristicCost == 32766)
                                c_pResetNodeList[nNodesToReset++] = &m_AttachedPaths[indexNodeAttached];
                            
                            AddNodeToList(&m_AttachedPaths[indexNodeAttached], bestEstimatedCost);
                        }
                    }
                    RemoveNodeFromList(pInitialSearchNode);
                    pInitialSearchNode = GetAppropriateListFromIndex(pInitialSearchNode->wPreviousNodeIndex);
                }

                nCircleList = (nCircleList + 1) & 511;
            } while (bFound == false);

            // Phase 2
            CPathNode* pNodeTransverseToDest = &m_AttachedPaths[iOriginNodeIndex];
            *pSteps = 0;
            if (pfPathCost)
                *pfPathCost = m_AttachedPaths[iOriginNodeIndex].heuristicCost;
            pIntermediateNodeList[(*pSteps)++] = &m_AttachedPaths[iOriginNodeIndex];
            while (*pSteps < sMaxSteps && pNodeTransverseToDest != pDestinationNode)
			{
                for (int i = 0; i < pNodeTransverseToDest->bitnumberOfNodesConnected; i++)
				{
                    int indexArrayAttached = i + pNodeTransverseToDest->wRouteInfoIndex;
					// get closer to the destination by transvering to lower heuristic cost
                    if (pNodeTransverseToDest->heuristicCost - m_nConnectionWeight[indexArrayAttached] == m_AttachedPaths[m_infoConnectedNodes[indexArrayAttached] & em_infoConnectedNodesNODEINDEXONLY].heuristicCost)
					{
                        pNodeTransverseToDest = &m_AttachedPaths[m_infoConnectedNodes[indexArrayAttached] & em_infoConnectedNodesNODEINDEXONLY];
                        pIntermediateNodeList[(*pSteps)++] = pNodeTransverseToDest;
						if(*pSteps == sMaxSteps) break;
                        i = 29030; // break out from loop?
                    }
                }
            }
            // reset the heuristic cost of affected nodes to default
            for (int i = 0; i < nNodesToReset; i++)
				c_pResetNodeList[i]->heuristicCost = 32766;
        }
        else
		{
            *pSteps = 0;
            if ( pfPathCost) *pfPathCost = 100000.0f;
        }
    }
    else{
        *pSteps = 0;
        if ( pfPathCost) *pfPathCost = 100000.0f;
    }
}

// this stuff would rarely happen
void CPathFind::RemoveBadStartNode(CVector& posCoors, CPathNode **pIntermediateNodeList, short *pSteps){
    if (*pSteps >= 2){
        if ((((float)(pIntermediateNodeList[1]->wY)/8.0f - posCoors.fY) * ((float)(pIntermediateNodeList[0]->wY)/8.0f - posCoors.fY)) +
            (((float)(pIntermediateNodeList[1]->wX)/8.0f - posCoors.fX) * ((float)(pIntermediateNodeList[0]->wX)/8.0f - posCoors.fX)) < 0.0f)
        {
            --(*pSteps);
            for (int i = 0; i < *pSteps; i++)
                pIntermediateNodeList[i] = pIntermediateNodeList[i + 1];
        }
    }
}

int CPathFind::FindNodeClosestToCoors(CVector& posCoors, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat){
	int iStartNodeIndex, iEndNodeIndex;

	switch(iPathDataFor) {
		case PATHDATAFOR_CAR:
			iStartNodeIndex = 0;
			iEndNodeIndex = m_nCarAttachedNodes;
			break;
		case PATHDATAFOR_PED:
			iStartNodeIndex = m_nCarAttachedNodes;
			iEndNodeIndex = m_nAttachedNodes;
			break;
	}

	float fPrevFoundRangeCoeff = 10000.0f;
	int iPrevFoundRangedNode = 0;
	CPathNode* pNode = &m_AttachedPaths[iStartNodeIndex];
	for (int i = iStartNodeIndex; i < iEndNodeIndex; i++){
		if ((bCheckIgnored == false || !(pNode->bitIsIgnoredNode)) &&
		   (bCheckRestrictedAccess == false || !(pNode->bitRestrictedAccess)) &&
		   (bCheckUnkFlagFor2 == false || !(pNode->bitUnkFlagFor2)) &&
		   (bIsVehicleBoat == pNode->bitIsVehicleBoat))
		{
			float fXDiff = utl::abs<float>(((float)pNode->wX / 8.0f) - posCoors.fX);
			float fYDiff = utl::abs<float>(((float)pNode->wY / 8.0f) - posCoors.fY);
			float fZDiff = utl::abs<float>(((float)pNode->wZ / 8.0f) - posCoors.fZ);

			float fCurrentCoeff = fXDiff + fYDiff + fZDiff * 3.0f;
			if ( fCurrentCoeff < fPrevFoundRangeCoeff){
				fPrevFoundRangeCoeff = fCurrentCoeff;
				iPrevFoundRangedNode = i;
			}
		}
		pNode++;
	}
	if ( fPrevFoundRangeCoeff < fRangeCoefficient)
		return iPrevFoundRangedNode;
	else
		return -1;
}

void CPathFind::FindNextNodeWandering(uint8_t iPathDataFor, CVector& posCoors, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection){
    CVector vecCurrentPos(posCoors);
	vecCurrentPos.fZ += 1.0f;
    CPathNode* pCurrentActPedNode;

    if(pCurrentNode == NULL || (*pCurrentNode) == NULL ||
        ((posCoors.fY - float((*pCurrentNode)->wY) / 8.0f) * (posCoors.fY - float((*pCurrentNode)->wY) / 8.0f) + (posCoors.fX - float((*pCurrentNode)->wX) / 8.0f) * (posCoors.fX - float((*pCurrentNode)->wX) / 8.0f) + (posCoors.fZ - float((*pCurrentNode)->wZ) / 8.0f) * (posCoors.fZ - float((*pCurrentNode)->wZ) / 8.0f)) > 49.0f)
    {
        pCurrentActPedNode = &m_AttachedPaths[FindNodeClosestToCoors(posCoors, iPathDataFor, 999999.88f, 0, 0, 0, 0)];
    }
    else
        pCurrentActPedNode = *pCurrentNode;

    // get normal vectors along with translation of bytePreviousDirection which is limited to maximum value of 8
    // optimization is needed so as to directly use floating point assembly function
    double dPrevNormalX = sin((double)bytePreviousDirection  * 2.0*M_PI/8.0);
    double dPrevNormalY = cos((double)bytePreviousDirection  * 2.0*M_PI/8.0);

    // initialize the next node with null
    *pNextNode = NULL;

    // initialize fPrevFoundRangeCoeff with the minimum value
    float fPrevFoundRangeCoeff = -999999.0f;

    // loop for current node's other segments
    for (int i = 0; i < pCurrentActPedNode->bitnumberOfNodesConnected; i++){
        CPathNode* pNextConnectedNode = &m_AttachedPaths[m_infoConnectedNodes[i+pCurrentActPedNode->wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY];
        if ((pCurrentActPedNode->bitIsIgnoredNode) || !(pNextConnectedNode->bitIsIgnoredNode))
        {
            CVector vecNextDeltaPos(float(pNextConnectedNode->wX)/8.0f, float(pNextConnectedNode->wY)/8.0f, float(pNextConnectedNode->wZ)/8.0f + 1.0f);
            if (CWorld::GetIsLineOfSightClear(&vecCurrentPos, &vecNextDeltaPos, 1, 0, 0, 0, 0, 0, 0)){
				
				CVector2D v2dUnitDelta(vecNextDeltaPos);
				
				v2dUnitDelta.Normalize();

                double fUnitLengthSq = v2dUnitDelta.LengthSquared();
                if (fUnitLengthSq >= (double)fPrevFoundRangeCoeff)
				{
                    fPrevFoundRangeCoeff = (float)fUnitLengthSq;
                    *pNextNode = pNextConnectedNode;
                    if (v2dUnitDelta.fX < 0.0f)
					{
                        double fabsDeltaNormalY = utl::abs<double>(v2dUnitDelta.fY);
                        double fabsDeltaNormalX = -v2dUnitDelta.fX;
                        if (2.0f * fabsDeltaNormalY >= fabsDeltaNormalX)
                            if (2.0f * fabsDeltaNormalX >= v2dUnitDelta.fY)
                                if (2.0f * v2dUnitDelta.fX <= v2dUnitDelta.fY)
                                    if (v2dUnitDelta.fY <= 0.0f)
                                        *byteNewDirection = 5;
                                    else
                                        *byteNewDirection = 7;
                                else
                                    *byteNewDirection = 4;
                            else
                                *byteNewDirection = 0;
                        else
                            *byteNewDirection = 6;
                    }
                    else
					{
                        double fabsDeltaNormalY = utl::abs<double>(v2dUnitDelta.fY);
                        if (2.0f * fabsDeltaNormalY >= v2dUnitDelta.fX)
                            if (2.0f * v2dUnitDelta.fX >= v2dUnitDelta.fY)
                                if ( -2.0f * v2dUnitDelta.fX <= v2dUnitDelta.fY)
                                    if (v2dUnitDelta.fY <= 0.0f)
                                        *byteNewDirection = 3;
                                    else
                                        *byteNewDirection = 1;
                                else
                                    *byteNewDirection = 4;
                            else
                                *byteNewDirection = 0;
                        else
                            *byteNewDirection = 2;
                    }
                }
            }
        }
    }
    if(!(*pNextNode)) {
        *byteNewDirection = 0;
        *pNextNode = pCurrentActPedNode;
    }
}

//-----------------------------------------------------------------------------
// This is a CPathFind member function which generates two random nodes which
// the newly created vehicles follow. It is called at two places: CCarCtrl::
// GenerateOneEmergencyServicesCar and CCarCtrl::GenerateRandomCar. The method
// it currently uses is unreliable and should be later on dependant on a grid
// based setup through which only random nodes can be selected there in that
// particular area.
//
// To do: Implement CarGenerate Request Rejects per second.
//-----------------------------------------------------------------------------

bool CPathFind::NewGenerateCarCreationCoors(CVector2D& pos2DCoors, CVector2D& v2dDirection, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored) {
    //CDebug::DebugAddText("UnkX1 : %f, UnkY1: %f, UnkX2: %f, charUnk: %d", fDirectionVecX, fDirectionVecY, fZlookUp, (int)bShouldSpawnPositiveDirection);
    if(m_nCarAttachedNodes) {
        float fReqRange = 70.0f + fRange;
        if(fReqRange <= (1.7f * fRange)) {
            fReqRange = 1.7f * fRange;
        }

        for(int i = 0; i < (500 * PATHMUL); i++) 
		{
            int nRandIndex = (rand() /*>> 3*/) % m_nCarAttachedNodes;
            if(!(m_AttachedPaths[nRandIndex].bitIsIgnoredNode) || bDontCheckIgnored == true) 
			{
				float fDistanceToRandNode = (m_AttachedPaths[nRandIndex].Form2DVector() - pos2DCoors).Length();

                if(fDistanceToRandNode < fReqRange) 
				{
                    for(int j = 0; j < m_AttachedPaths[nRandIndex].bitnumberOfNodesConnected; j++) {
                        int nNextNodeIndex = m_infoConnectedNodes[j + m_AttachedPaths[nRandIndex].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
                        if(!(m_AttachedPaths[nNextNodeIndex].bitIsIgnoredNode) || bDontCheckIgnored == true) 
						{
							float fDistanceToNextNode = (m_AttachedPaths[nNextNodeIndex].Form2DVector() - pos2DCoors).Length();
                            float frandNodeRangeDelta, fnextNodeRangeDelta;

                            if(m_AttachedPaths[nRandIndex].bitIsVehicleBoat) {
                                frandNodeRangeDelta = fDistanceToRandNode - 1.5f * fRange;
                                fnextNodeRangeDelta = fDistanceToNextNode - 1.5f * fRange;
                            }
                            else {
                                frandNodeRangeDelta = fDistanceToRandNode - fRange;
                                fnextNodeRangeDelta = fDistanceToNextNode - fRange;
                            }

                            if((frandNodeRangeDelta * fnextNodeRangeDelta) < 0.0f) {
                                float fabsRandNodeRangeDelta = utl::abs<float>(frandNodeRangeDelta);
                                float fabsNextNodeRangeDelta = utl::abs<float>(fnextNodeRangeDelta);

                                *aNodeRangeDiffCoeff = fabsRandNodeRangeDelta / (fabsRandNodeRangeDelta + fabsNextNodeRangeDelta);
                                CVector vecOutPosition = (m_AttachedPaths[nNextNodeIndex].Form3DVector() * (*aNodeRangeDiffCoeff)) + (m_AttachedPaths[nRandIndex].Form3DVector() * (1.0f - (*aNodeRangeDiffCoeff)));
                                
								CVector2D norV2dToAvgNode =  CVector2D(vecOutPosition) - pos2DCoors;
								norV2dToAvgNode.Normalize();

								float fProjectionOfDirection = norV2dToAvgNode.DotProduct(v2dDirection);

                                if((bShouldSpawnPositiveDirection == true && fProjectionOfDirection > fZlookUp) || (bShouldSpawnPositiveDirection == false && fProjectionOfDirection <= fZlookUp)) {
                                    *aMainNodeIndex = nRandIndex;
                                    *aSubNodeIndex = nNextNodeIndex;
                                    *pVecPosition = vecOutPosition;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    else {
        return false;
    }
}

//----------------------------------------------------------------------------
// This is a function which generates ped creation coordinates by an unhealthy
// algorithm which cannot be utilized by StateOfLiberty since it is expected
// to contain larger number path nodes altogether about 80k which is 9 times
// than that was in Vice city. This function is called at CPopulation::
// AddToPopulation only. This algorithm is subject to change if the current
// implementation does not generate coordinates which may be required
// immediately.
//----------------------------------------------------------------------------

bool CPathFind::GeneratePedCreationCoors(CVector2D& pos2dCoors, float fMinRange, float fMaxRange, float fSecMinRange, float fSecMaxRange, CVector *pvecSpawnPos, int *pStartNodeIndex, int *pNextNodeIndex, float *fRandomByte, RwMatrix *rwTransformationMatrix) {
    static bool staticPedNodeCheck = false;
    static int staticPedNodesCount;
    if (staticPedNodeCheck == false) {
    	staticPedNodeCheck = true;
    	staticPedNodesCount = 0;
    }

    if (m_nPedAttachedNodes == 0) {
    	return false;
    }

    float fReqRange = 30.0f + fMaxRange;
    for (int i = 0; i < (230*PATHMUL); i++) {
    	staticPedNodesCount++;
    	if (staticPedNodesCount >= m_nPedAttachedNodes) {
    		staticPedNodesCount = 0;
	    }
	    int nStartNodeIndex = m_nCarAttachedNodes + staticPedNodesCount;
		CVector2D v2dStartNodeToCoors(m_AttachedPaths[nStartNodeIndex].Form2DVector() - pos2dCoors);

	    float fStartNodeDisplacement = v2dStartNodeToCoors.Length();
	    if (fStartNodeDisplacement >= fReqRange) {
		    continue;
    	}

	    if ((m_AttachedPaths[nStartNodeIndex].bitnumberOfNodesConnected) == 0) {
		    continue;
    	}

	    int nConnectedNodeSets = m_AttachedPaths[nStartNodeIndex].bitnumberOfNodesConnected;
	    for (int j = 0; j < nConnectedNodeSets; j++) {
		    if (m_infoConnectedNodes[j+ m_AttachedPaths[nStartNodeIndex].wRouteInfoIndex] & em_infoConnectedNodesCROSSROAD) {
    			continue;
		    }
		    int nNextNodeIndex = m_infoConnectedNodes[j+ m_AttachedPaths[nStartNodeIndex].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
		    if (m_AttachedPaths[nStartNodeIndex].bitIsIgnoredNode) {
    			continue;
		    }
		    if (m_AttachedPaths[nNextNodeIndex].bitIsIgnoredNode) {
    			continue;
		    }

			CVector2D v2dNextNodeToCoors(m_AttachedPaths[nNextNodeIndex].Form2DVector() - pos2dCoors);
		   
		    float fNextNodeDisplacement = v2dNextNodeToCoors.Length();

		    if ((fStartNodeDisplacement < fMaxRange || fNextNodeDisplacement < fMaxRange) &&
    		    (fStartNodeDisplacement > fSecMinRange || fNextNodeDisplacement > fSecMinRange))
		    {
			    for (int k = 0; k < 5; k++) {
				    float fRandomLimiter = 1.0f/256.0f;
				    // call the random procedure
				    _asm {
					    mov eax, 6499F0h
					    call eax
					    and eax, 255
                        fld fRandomLimiter
                        mov fRandomLimiter, eax
					    fild fRandomLimiter
					    fmulp st(1), st
					    mov eax, fRandomByte
    					fstp dword ptr [eax]
				    }
				    float fStartNodeZ = (float)(m_AttachedPaths[nStartNodeIndex].wZ) / 8.0f;
				    float fNextNodeZ = (float)(m_AttachedPaths[nNextNodeIndex].wZ) / 8.0f;
				    
					CVector vTemp = m_AttachedPaths[nStartNodeIndex].Form3DVector() * (1.0f - *fRandomByte) + m_AttachedPaths[nNextNodeIndex].Form3DVector() * (*fRandomByte);
					RwV3d& vecMeanPos = *(RwV3d*)&vTemp; //WHAT DUCKINGL
				    float fRandNodeDisplacement = (CVector2D(vTemp) - pos2dCoors).Length();
				    bool bLiesInViewableRange = false;
				    RwV3d vecTransform = vecMeanPos;
				    if (rwTransformationMatrix == NULL) {
    					RwV3dTransformPoints(&vecTransform, &vecTransform, 1, &TheCamera.field_820.rwMatrix);
				    }
				    else {
    					RwV3dTransformPoints(&vecTransform, &vecTransform, 1, rwTransformationMatrix);
				    }
				    if ((vecTransform.y + 2.0f) >= CGameVariables::GetNearClipZ() &&
					    (vecTransform.y - 2.0f) <= CGameVariables::GetFarClipZ() &&
					    (vecTransform.y * TheCamera.field_8B8.y + vecTransform.x * TheCamera.field_8B8.x) <= 2.0f &&
					    (vecTransform.y * TheCamera.field_8C4.y + vecTransform.x * TheCamera.field_8C4.x) <= 2.0f &&
					    (vecTransform.z * TheCamera.field_8D0.z + vecTransform.y * TheCamera.field_8D0.y) <= 2.0f &&
    					(vecTransform.z * TheCamera.field_8DC.z + vecTransform.y * TheCamera.field_8DC.y) <= 2.0f)
				    {
    					bLiesInViewableRange = true;
				    }
				    if ((bLiesInViewableRange == false && fRandNodeDisplacement > fSecMinRange && fRandNodeDisplacement < fSecMaxRange) ||
				    (fRandNodeDisplacement > fMinRange && fRandNodeDisplacement < fMaxRange))
				    {
					    *pStartNodeIndex = nStartNodeIndex;
					    *pNextNodeIndex = nNextNodeIndex;
					    pvecSpawnPos->fX = vecMeanPos.x;
					    pvecSpawnPos->fY = vecMeanPos.y;
					    pvecSpawnPos->fZ = vecMeanPos.z;
					    bool bDoesGroundExist;
					    float fSpawnPosCollisionGround = CWorld::FindGroundZFor3DCoord(vecMeanPos.x, vecMeanPos.y, vecMeanPos.z + 2.0f, &bDoesGroundExist);
					    if (bDoesGroundExist == false) {
    						continue;
					    }
					    if (utl::abs<float>(fSpawnPosCollisionGround - vecMeanPos.z) <= 3.0f) {
						    pvecSpawnPos->fZ = fSpawnPosCollisionGround;
    						return true;
					    }
					    else {
						    return false;
    					}
				    }
    			}
		    }
    	}
    }
    return false;
}

float CPathFind::CalcRoadDensity(CVector2D& pos2dCoors) {
	float fDeltaDensity = 0.0f;
	for (int i = 0; i < m_nCarAttachedNodes; i++) 
	{
		CVector2D pos2dStartNode(m_AttachedPaths[i].Form2DVector());
		CVector2D v2dStartNodeToCoors(pos2dStartNode - pos2dCoors);

        // ignore nodes that are over 80 units range
		if (utl::abs<float>(v2dStartNodeToCoors.fX) >= 80.0f)
			continue;
		
		if (utl::abs<float>(v2dStartNodeToCoors.fY) >= 80.0f)
			continue;
		

		for (int j = 0; j < m_AttachedPaths[i].bitnumberOfNodesConnected; j++) {
			int nNextNodeIndex = m_infoConnectedNodes[j+ m_AttachedPaths[i].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
			int nDetachedNodeIndex = m_InfoCarPathLinks[j+ m_AttachedPaths[i].wRouteInfoIndex];
			CVector2D pos2dNextNode(m_AttachedPaths[nNextNodeIndex].Form2DVector());
			float fDisplacement = (pos2dStartNode - pos2dNextNode).Length();
			fDeltaDensity += (float)(m_CarPathLinks[nDetachedNodeIndex].bitLeftLanes) * fDisplacement + (float)(m_CarPathLinks[nDetachedNodeIndex].bitRightLanes) * fDisplacement;
		}
	}

	// sum of displacements between ranged nodes is divided by the area of game to get the density
	float fViceCityRoadDensity = fDeltaDensity / (2500.0f * (float)PATHMUL);
    CDebug::DebugAddText("Road Density: %f", fViceCityRoadDensity);
	return fViceCityRoadDensity;
}

int CPathFind::FindNodeClosestToCoorsFavourDirection(CVector& posCoors, uint8_t uiPathDataFor, CVector2D& v2dPreferedDirection) {
	// checked if it is normalized
	if (v2dPreferedDirection.Length() == 0.0f) {
		// maybe the LookAt vector components was set to 0.0
		v2dPreferedDirection.fX = 1.0f;
	}
	else {
		v2dPreferedDirection.Normalize();
	}
	int ifoundNode = 0;
	float fprevRangedCoefficient = 10000.0f;
	int iStartNodeIndex, iEndNodeIndex;

	switch (uiPathDataFor) {
		case PATHDATAFOR_CAR:
			iStartNodeIndex = 0;
			iEndNodeIndex = m_nCarAttachedNodes;
			break;
		case PATHDATAFOR_PED:
			iStartNodeIndex = m_nCarAttachedNodes;
			iEndNodeIndex = m_nAttachedNodes;
			break;
	}

	// if some PathFind member function tricked us
	if (iStartNodeIndex >= iEndNodeIndex) {
		return 0;
	}

	for (int i = iStartNodeIndex; i < iEndNodeIndex; i++) 
	{
		CVector vecStartNodeToCoors(m_AttachedPaths[i].Form3DVector() - posCoors);

		float fcurDistCoefficient = utl::abs<float>(vecStartNodeToCoors.fX) + utl::abs<float>(vecStartNodeToCoors.fY) + 3.0f* utl::abs<float>(vecStartNodeToCoors.fZ);
		if (fcurDistCoefficient < fprevRangedCoefficient) {
			CVector2D v2dNodeDirection;

			// may be there was no distance between caller's position and paths node
			if (CVector2D(vecStartNodeToCoors).Length() == 0.0f) 
			{
				v2dNodeDirection.fX = 1.0f;
				v2dNodeDirection.fY = 0.0f;
			}
			else 
			{
				v2dNodeDirection = CVector2D(vecStartNodeToCoors);
				v2dNodeDirection.Normalize();
			}

			float fimmCoefficientWithDirection = fcurDistCoefficient + (v2dNodeDirection.DotProduct(v2dPreferedDirection) - 1.0f) * -20.0f;
			if (fimmCoefficientWithDirection < fprevRangedCoefficient) {
				fprevRangedCoefficient = fimmCoefficientWithDirection;
				ifoundNode = i;
			}
		}
	}
    CDebug::DebugAddText("ifoundNode %d", ifoundNode);
	return ifoundNode;
}


bool CPathFind::TestCoorsCloseness(CVector& posDest, uint8_t uiPathDataFor, CVector& posOrigin) 
{
    static CPathNode *pIntermediateCarRouteInfos[32] = {0};
    static short sCarSteps = 0;
    static short sPedSteps = 0;
    float fDistance;

    switch (uiPathDataFor) {
        case PATHDATAFOR_CAR:
            DoPathSearch(PATHDATAFOR_CAR, posOrigin, -1, posDest, pIntermediateCarRouteInfos, &sCarSteps, 32, NULL, &fDistance, 999999.88f, -1);
            if (fDistance < 150.0f) {
                return true;
            }
            else {
                return false;
            }
            break;
        case PATHDATAFOR_PED:
            DoPathSearch(PATHDATAFOR_PED, posOrigin, -1, posDest, NULL, &sPedSteps, 0, NULL, &fDistance, 50.0f, -1);
            if (fDistance < 100.0f)
                return true;
            else
                return false;
            break;
    }
}

bool CPathFind::TestCrossesRoad(CPathNode* pStartNode, CPathNode* pConnectedNode) {
    CDebug::DebugAddText("TestCrossesRoad");
    for(int i = 0; i < pStartNode->bitnumberOfNodesConnected; i++) 
	{
        if(&m_AttachedPaths[m_infoConnectedNodes[i + pStartNode->wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY] == pConnectedNode) 
		{
            if(m_infoConnectedNodes[i + pStartNode->wRouteInfoIndex] & em_infoConnectedNodesCROSSROAD)
                return true;
        }
    }
    return false;
}

bool CPathFind::TestForPedTrafficLight(CPathNode* pStartNode, CPathNode* pConnectedNode) {
    CDebug::DebugAddText("TestForPedTrafficLight");
    for(int i = 0; i < pStartNode->bitnumberOfNodesConnected; i++) 
	{
        if(&m_AttachedPaths[m_infoConnectedNodes[i + pStartNode->wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY] == pConnectedNode) 
		{
            if(m_infoConnectedNodes[i + pStartNode->wRouteInfoIndex] & em_infoConnectedNodesTRAFFICLIGHT)
                return true;
        }
    }
    return false;
}

CPathNode::CPathNode(){
    memset(this, 0, sizeof(CPathNode));
    wNextListOrNodeIndex = -1;
    wPreviousNodeIndex = -1;
    ucFloodColor = 0;
    bitUnkFlagFor2 = 0;
    bitPadFlags8To10 = 0;
    bitnumberOfNodesConnected = 0;
}

void CPathNode::GetNodeCoors(CVector* vecNodePosition) {
    vecNodePosition->fX = (float)(this->wX) / 8.0f;
    vecNodePosition->fY = (float)(this->wY) / 8.0f;
    vecNodePosition->fZ = (float)(this->wZ) / 8.0f;
}

CCarPathLink::CCarPathLink(){
    memset(this, 0, sizeof(CCarPathLink));
}

float CCarPathLink::OneWayLaneOffset() {
	float fdistance;

	if (this->bitLeftLanes){
		if (this->bitRightLanes){
			fdistance = (float)(this->sbMedianWidth) / 80.0f + 1.0f/2.0f;
		}
		else{
			fdistance = 1.0f/2.0f - (float)(this->bitLeftLanes) * 1.0f/2.0f;
		}
    }
	else{
		fdistance = 1.0f/2.0f - (float)(this->bitRightLanes) * 1.0f/2.0f;
	}
	return fdistance;
}

void _cdecl CPedPath::CalculateBestRandomCoors(CPathNode* pPathNodeA, CPathNode* pPathNodeB, short sRand, float* fX, float* fY) {
    char uiMedian = pPathNodeA->sbMedianWidth;

    if (uiMedian > pPathNodeB->sbMedianWidth) {
        uiMedian = pPathNodeB->sbMedianWidth;
    }
    *fX = (float)(((sRand & 15) - 7) * uiMedian) * 0.0077499999f + *fX;
    *fY = (float)((((sRand >> 4) & 15) - 7) * uiMedian) * 0.0077499999f + *fY;
}

CVector* _cdecl CPedPath::CalculateRandomCoordinates(CVector* pvecPosition, CPathNode* pPathNode, short sRand) {
    pvecPosition->fX = (float)(pPathNode->sbMedianWidth * ((sRand & 15) - 7)) * 0.0077499999f + (float)(pPathNode->wX) / 8.0f;
    pvecPosition->fY = (float)(pPathNode->sbMedianWidth * (((sRand >> 4) & 15) - 7)) * 0.0077499999f + (float)(pPathNode->wY) / 8.0f;
    pvecPosition->fZ = (float)(pPathNode->wZ) / 8.0f;

    return pvecPosition;
}

