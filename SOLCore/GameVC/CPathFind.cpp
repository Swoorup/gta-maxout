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

int CPathFind::g_nCarGroupNodes = 0;
int CPathFind::g_nPedGroupNodes = 0;
CPathInfoForObject* CPathFind::g_pCarPathInfos = NULL;
CPathInfoForObject* CPathFind::g_pPedPathInfos = NULL;
CTempDetachedNode* CPathFind::s_pTempExternalNodes = NULL;

CPathFind::CPathFind() {
    ZeroMemory(this->m_infoConnectedNodes, sizeof(this->m_infoConnectedNodes));
    ZeroMemory(this->DetachedPointsInfo, sizeof(this->DetachedPointsInfo));
    ZeroMemory(this->m_nConnectionWeight, sizeof(this->m_nConnectionWeight));
}

#ifdef PATHFINDUSEORIGINAL
__declspec (naked) void CPathFind::StoreNodeInfoCar(int iNodeInfo_InternalNodesCount, uint8_t iNode_NodeType, int8_t iNode_NextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t nLeftLanes, uint8_t nRightLanes, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint8_t bSpeedLimit, bool bIsPoliceRoadBlock, uint8_t nVehicleType, uint32_t dwSpawnRate, uint8_t bUnknown) {
    __asm jmp dwFunc_CPathFind__StoreNodeInfoCar
}

#else

//435C30h
void CPathFind::StoreNodeInfoCar(int nInternalNodeCount, unsigned char iNodeType, signed char iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, unsigned char nLeftLanes, unsigned char nRightLanes, bool bIsIgnoredNode, bool bIsRestrictedAccess, unsigned char bSpeedLimit, bool bIsPoliceRoadBlock, unsigned char byteVehicleType, unsigned int dwSpawnRate, unsigned char bUnknown) {
  if (g_nCarGroupNodes < MAXCARGROUPNODE){
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].fX = fNodeX / 16.0f;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].fY = fNodeY / 16.0f;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].fZ = fNodeZ / 16.0f;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteNodeType = iNodeType;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].sbNextNode = iNextNode;
    if (fMedianWidth > 15.0f) fMedianWidth = 15.0f;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].sbMedianWidth = (signed int)(8.0f * fMedianWidth);
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteLeftLanes = nLeftLanes;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteRightLanes = nRightLanes;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteSpeedLimit = bSpeedLimit;
    // Set the first bit to zero
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags &= ~NODEINFOFLAGS_ISCROSSROAD;

    if (bUnknown)
        g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags |= NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS;
    if (bIsPoliceRoadBlock)
        g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags |= NODEINFOFLAGS_POLICEROADBLOCK;
    if (bIsIgnoredNode)
        g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags |= NODEINFOFLAGS_IGNORENODEAREA;
    if (byteVehicleType == VTYPE_BOAT)
        g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags |= NODEINFOFLAGS_VEHICLETYPEBOAT;
    if (bIsRestrictedAccess)
        g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteFlags |= NODEINFOFLAGS_RESTRICTEDACCESS;

    if (dwSpawnRate > 15) dwSpawnRate = 15;
    g_pCarPathInfos[nInternalNodeCount + 12 * g_nCarGroupNodes].byteSpawnRate = unsigned char(dwSpawnRate);
    if (nInternalNodeCount == 11)
      g_pCarPathInfos[12 * g_nCarGroupNodes++].SwapConnectionsToBeRightWayRound();
  }
}


//43C060h
void CPathInfoForObject::SwapConnectionsToBeRightWayRound(void)
{
	CPathInfoForObject* pPathInfoTile = this;
	for (int i = 0; i < 12; i++)
	{
		if (pPathInfoTile[i].byteNodeType == NODEINFOTYPE_EXTERNAL && pPathInfoTile[i].sbNextNode == -1)
		{
			for (int j = 0; j < 12; j++)
			{
		        if (pPathInfoTile[j].byteNodeType == NODEINFOTYPE_INTERNAL && pPathInfoTile[j].sbNextNode == i)
				{
					pPathInfoTile[i].sbNextNode = j;
					pPathInfoTile[j].sbNextNode = -1;
		
					// Swap the right most significant bit
					bool bIsCrossRoad = pPathInfoTile[i].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
					pPathInfoTile[i].byteFlags = pPathInfoTile[i].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | pPathInfoTile[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
					pPathInfoTile[j].byteFlags = pPathInfoTile[j].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | bIsCrossRoad & NODEINFOFLAGS_ISCROSSROAD;
				}
			}
		}
	}
}
#endif

#ifdef PATHFINDUSEORIGINAL
_declspec (naked) void CPathFind::StoreNodeInfoPed(int iNodeInfo_InternalNodesCount, uint8_t eNodeType, int8_t iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t iNode_unknown, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint32_t dwSpawnRate) {
    _asm jmp dwFunc_CPathFind__StoreNodeInfoPed
}

#else
//435FA0h
void CPathFind::StoreNodeInfoPed(int nInternalNodeCount, unsigned char iNodeType, signed char iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, unsigned char iunknown, bool bIsIgnoredNode, bool bIsRestrictedAccess, unsigned int dwSpawnRate) {
    if (g_nPedGroupNodes < MAXPEDGROUPNODE){
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fX = fNodeX / 16.0f;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fY = fNodeY / 16.0f;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fZ = fNodeZ / 16.0f;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteNodeType = iNodeType;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].sbNextNode = iNextNode;
        if(fMedianWidth > 31.0f)
            fMedianWidth = 31.0f;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].sbMedianWidth = (signed int)(8.0f * fMedianWidth);
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteLeftLanes = 0;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteRightLanes = 0;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteSpeedLimit = 0;

        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_POLICEROADBLOCK;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_VEHICLETYPEBOAT;
        if(iunknown)
            g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_ISCROSSROAD;
        if(bIsIgnoredNode)
            g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_IGNORENODEAREA;
        if(bIsRestrictedAccess)
            g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_RESTRICTEDACCESS;

        if (dwSpawnRate > 15) dwSpawnRate = 15;
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteSpawnRate = unsigned char(dwSpawnRate);
        if (nInternalNodeCount == 11)
			g_pPedPathInfos[12 * g_nPedGroupNodes++].SwapConnectionsToBeRightWayRound();
    }
}

void CPathFind::Init(void){
    this->m_nAttachedNodes = 0;
    this->w_nTreadables = 0;
    this->m_nConnectedNodes = 0;
    this->m_nDetachedPoints = 0;
    this->Unusedfield_53804 = 0;

    
    for (int i =0; i < (9650 * PATHMUL); i++)
        this->m_AttachedPaths[i].heuristicCost = 32766;
}

void CPathFind::AllocatePathFindInfoMem(void){
    if(g_pCarPathInfos) {
        delete [] g_pCarPathInfos;
        g_pCarPathInfos = NULL;
    }
    if(g_pPedPathInfos) {
        delete [] g_pPedPathInfos;
        g_pPedPathInfos = NULL;
    }
    if(s_pTempExternalNodes) {
        delete [] s_pTempExternalNodes;
        s_pTempExternalNodes = NULL;
    }

    //heap corruption chances, so sizes might need increasing
    g_pCarPathInfos = new CPathInfoForObject[20000 * PATHMUL];
    g_pPedPathInfos = new CPathInfoForObject[20000 * PATHMUL];
    s_pTempExternalNodes = new CTempDetachedNode[4600 * PATHMUL];

    memset(g_pCarPathInfos, 0, sizeof(CPathInfoForObject) * 20000 * PATHMUL);
    memset(g_pCarPathInfos, 0, sizeof(CPathInfoForObject) * 20000 * PATHMUL);
    memset(s_pTempExternalNodes, 0, sizeof(CTempDetachedNode) * 4600 * PATHMUL);
    g_nPedGroupNodes = 0;
    g_nCarGroupNodes = 0;
}

void CPathFind::PreparePathData(void){
    CDebug::DebugAddText("PreparePathData");
    CFileMgr::SetDir("");

    //check if path info pointers are not null
    if ( g_pCarPathInfos && g_pPedPathInfos && s_pTempExternalNodes){
        CTempNode* pTempNodes = new CTempNode[MAXPATHTEMPNODE];

        m_nConnectedNodes = 0;
        m_nAttachedNodes = 0;
        PreparePathDataForType(PATHDATAFOR_CAR, pTempNodes, NULL, 1.0f, g_pCarPathInfos, g_nCarGroupNodes);
        m_nCarAttachedNodes = m_nAttachedNodes;
        PreparePathDataForType(PATHDATAFOR_PED, pTempNodes, NULL, 1.0f, g_pPedPathInfos, g_nPedGroupNodes);
        m_nPedAttachedNodes = m_nAttachedNodes - m_nCarAttachedNodes;

        delete [] pTempNodes;
        CountFloodFillGroups(PATHDATAFOR_CAR);
        CountFloodFillGroups(PATHDATAFOR_PED);
        delete [] g_pCarPathInfos;
        g_pCarPathInfos = NULL;
        delete [] g_pPedPathInfos;
        g_pPedPathInfos = NULL;

        delete [] s_pTempExternalNodes;
        s_pTempExternalNodes = NULL;
    }
    CDebug::DebugAddText("Done with PreparePathData\n");
}

void CPathFind::PreparePathDataForType( unsigned char bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject) {
    signed int *aGroupNodeIndex_InternalNode = new signed int[9650 * PATHMUL];
	int32_t nTempExternalNodes = 0;
	int32_t nPrevObjectAttachedNodes = m_nAttachedNodes;
	int32_t nPrevObjectAttachedPoints = m_nConnectedNodes;

	if (nGroupNodesForObject > 0)
	{
		for (int i = 0; i < nGroupNodesForObject; i++)
		{
			int nAttachedPathsForCurrentGroup = m_nAttachedNodes;
			for (int j = i * 12; j < (i * 12 + 12); j++)
			{
				if ( pPathInfosForObject[j].byteNodeType == NODEINFOTYPE_INTERNAL)
				{
					m_AttachedPaths[m_nAttachedNodes].wX = (signed int)(8.0f * pPathInfosForObject[j].fX);
					m_AttachedPaths[m_nAttachedNodes].wY = (signed int)(8.0f * pPathInfosForObject[j].fY);
					m_AttachedPaths[m_nAttachedNodes].wZ = (signed int)(8.0f * pPathInfosForObject[j].fZ);

					aGroupNodeIndex_InternalNode[m_nAttachedNodes] = -(1  + i);
					m_AttachedPaths[m_nAttachedNodes].sbMedianWidth = pPathInfosForObject[j].sbMedianWidth;
					m_AttachedPaths[m_nAttachedNodes].byteSpawnRate = pPathInfosForObject[j].byteSpawnRate;

					m_AttachedPaths[m_nAttachedNodes].bitSpeedLimit = pPathInfosForObject[j].byteSpeedLimit;
					m_AttachedPaths[m_nAttachedNodes].bitCopsRoadBlock = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_POLICEROADBLOCK) >> 2;
					m_AttachedPaths[m_nAttachedNodes].bitIsIgnoredNode = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_IGNORENODEAREA) >> 3;
					m_AttachedPaths[m_nAttachedNodes].bitIsVehicleBoat = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_VEHICLETYPEBOAT) >> 4;
					m_AttachedPaths[m_nAttachedNodes].bitHaveUnrandomizedVehClass = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS) >> 1;
					m_AttachedPaths[m_nAttachedNodes].bitRestrictedAccess = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_RESTRICTEDACCESS) >> 5;
					m_nAttachedNodes++;
				}
				else if ( pPathInfosForObject[j].byteNodeType == NODEINFOTYPE_EXTERNAL)
				{
					s_pTempExternalNodes[nTempExternalNodes].fX = pPathInfosForObject[j].fX;
					s_pTempExternalNodes[nTempExternalNodes].fY = pPathInfosForObject[j].fY;
					s_pTempExternalNodes[nTempExternalNodes].fZ = pPathInfosForObject[j].fZ;
					s_pTempExternalNodes[nTempExternalNodes].sNextNodeIndex = pPathInfosForObject[j].sbNextNode + nAttachedPathsForCurrentGroup;
					s_pTempExternalNodes[nTempExternalNodes].byteLeftLanes = pPathInfosForObject[j].byteLeftLanes;
					s_pTempExternalNodes[nTempExternalNodes].byteRightLanes = pPathInfosForObject[j].byteRightLanes;
					s_pTempExternalNodes[nTempExternalNodes].sbMedianWidth = pPathInfosForObject[j].sbMedianWidth;
					if (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD)
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
                        for (int k = 0; k < m_nDetachedPoints; k++)
						{
							if (
								m_DetachedNodes[k].NormalVecX == (signed char)pTempNode[j].byteNormalX &&
								m_DetachedNodes[k].NormalVecY == (signed char)pTempNode[j].byteNormalY &&
								m_DetachedNodes[k].wX == (signed int)(8.0f * pTempNode[j].fX) &&
								m_DetachedNodes[k].wY == (signed int)(8.0f * pTempNode[j].fY) 
							)
							{
								DetachedPointsInfo[m_nConnectedNodes] = k;
								bIsDetachedNodeAlreadyStored = true;
								break;
							}
                        }
						if (!bIsDetachedNodeAlreadyStored)
						{
							m_DetachedNodes[m_nDetachedPoints].NormalVecX = pTempNode[j].byteNormalX;
							m_DetachedNodes[m_nDetachedPoints].NormalVecY = pTempNode[j].byteNormalY;
							m_DetachedNodes[m_nDetachedPoints].wX = (signed int)(8.0f * pTempNode[j].fX);
							m_DetachedNodes[m_nDetachedPoints].wY = (signed int)(8.0f * pTempNode[j].fY);
							m_DetachedNodes[m_nDetachedPoints].nIndexToAttachedNode = i;
							m_DetachedNodes[m_nDetachedPoints].bitLeftLanes = pTempNode[j].byteLeftLanes;
							m_DetachedNodes[m_nDetachedPoints].bitRightLanes = pTempNode[j].byteRightLanes;
							m_DetachedNodes[m_nDetachedPoints].byteTrafficFlags &= 0xFC;
							m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = pTempNode[j].sbMedianWidth;
							DetachedPointsInfo[m_nConnectedNodes] = m_nDetachedPoints;
							m_nDetachedPoints++;
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
		CPathInfoForObject *pPathInfoGroup = &pPathInfosForObject[12 * (-1 - aGroupNodeIndex_InternalNode[i])];
        int iOffsetInGroup = 0;
		int nAssumedGroupFirstNode = 0;
		if (( i -12) >= nPrevObjectAttachedNodes)
			nAssumedGroupFirstNode = i - 12;
		else
			nAssumedGroupFirstNode = nPrevObjectAttachedNodes;

		for (int k = nAssumedGroupFirstNode; k < i; k++)
			if (aGroupNodeIndex_InternalNode[i] == aGroupNodeIndex_InternalNode[k]) iOffsetInGroup++;
        
        int nAssumedGroupLastNode;

        if ((i + 12) <= m_nAttachedNodes)
            nAssumedGroupLastNode = i + 12;
        else 
			nAssumedGroupLastNode = m_nAttachedNodes;

		for(int nNodesInCurrentGroup = nAssumedGroupFirstNode; nNodesInCurrentGroup < nAssumedGroupLastNode; nAssumedGroupLastNode++)
        {
        	//check if they are in the same group
			if (aGroupNodeIndex_InternalNode[i] == aGroupNodeIndex_InternalNode[nNodesInCurrentGroup]){
				if (nNodesInCurrentGroup != i){
					int currentOffsetInGroup = iOffsetInGroup + nNodesInCurrentGroup - i; //I had  written 1 instead of i
					if (currentOffsetInGroup == pPathInfoGroup[iOffsetInGroup].sbNextNode ||
						iOffsetInGroup == pPathInfoGroup[currentOffsetInGroup].sbNextNode)
                    {
						m_infoConnectedNodes[m_nConnectedNodes] = nNodesInCurrentGroup;
						float fDist = sqrt((float(m_AttachedPaths[i].wX - m_AttachedPaths[nAssumedGroupFirstNode].wX)/8.0f * float(m_AttachedPaths[i].wX - m_AttachedPaths[nAssumedGroupFirstNode].wX)/8.0f) +
									       (float(m_AttachedPaths[i].wY - m_AttachedPaths[nAssumedGroupFirstNode].wY)/8.0f * float(m_AttachedPaths[i].wY - m_AttachedPaths[nAssumedGroupFirstNode].wY)/8.0f) +
									       (float(m_AttachedPaths[i].wZ - m_AttachedPaths[nAssumedGroupFirstNode].wZ)/8.0f * float(m_AttachedPaths[i].wZ - m_AttachedPaths[nAssumedGroupFirstNode].wZ)/8.0f));
						if (fDist > 255.0f) fDist = 255.0f;
						m_nConnectionWeight[m_nConnectedNodes] = (signed char)fDist;
						if (bytePathDataFor == PATHDATAFOR_PED)
						{
							if (currentOffsetInGroup == pPathInfoGroup[iOffsetInGroup].sbNextNode && //NOT FEELING WELL HERE
								pPathInfoGroup[iOffsetInGroup].byteFlags & NODEINFOFLAGS_ISCROSSROAD ||
							    iOffsetInGroup == pPathInfoGroup[currentOffsetInGroup].sbNextNode &&
							    pPathInfoGroup[currentOffsetInGroup].byteFlags & NODEINFOFLAGS_ISCROSSROAD)
						    {
						    	m_infoConnectedNodes[m_nConnectedNodes] |= em_infoConnectedNodesCROSSROAD;
						    }
						}
						else 
						{
							float fiCoorX = (float)(m_AttachedPaths[i].wX)/8.0f;
							float fiCoorY = (float)(m_AttachedPaths[i].wY)/8.0f;

							float fjCoorX = (float)(m_AttachedPaths[nAssumedGroupFirstNode].wX)/8.0f;
							float fjCoorY = (float)(m_AttachedPaths[nAssumedGroupFirstNode].wY)/8.0f;

							float fijCoorAvgX = (fjCoorX + fiCoorX)/2.0f;
							float fijCoorAvgY = (fjCoorY + fiCoorY)/2.0f;

							float fijXDiff = fjCoorX - fiCoorX;
							float fijYDiff = fjCoorY - fiCoorY;

							float fLength = sqrt(fijXDiff * fijXDiff + fijYDiff * fijYDiff);
							float VecijNormalX = fijXDiff / fLength;
							float VecijNormalY = fijYDiff / fLength;
							if (i < nNodesInCurrentGroup ){
								VecijNormalX = -VecijNormalX;
								VecijNormalY = -VecijNormalY;
							}
							bool bIsDetachedNodeAlreadyStored = false;
							for (int k = 0; k < m_nDetachedPoints; k++){
								if (
									m_DetachedNodes[k].NormalVecX == (signed char)(100.0f * VecijNormalX) &&
									m_DetachedNodes[k].NormalVecY == (signed char)(100.0f * VecijNormalY) &&
									m_DetachedNodes[k].wX == (signed int)(8.0f * fijCoorAvgX) &&
									m_DetachedNodes[k].wY == (signed int)(8.0f * fijCoorAvgY)
								)
								{
									DetachedPointsInfo[m_nConnectedNodes] = k;
									bIsDetachedNodeAlreadyStored = true;
									break;
									// if it exist don't create new detached nodes
								}
							}
							
							if (!bIsDetachedNodeAlreadyStored)
							{
								m_DetachedNodes[m_nDetachedPoints].NormalVecX = (signed char)(100.0f * VecijNormalX);
								m_DetachedNodes[m_nDetachedPoints].NormalVecY = (signed char)(100.0f * VecijNormalY);
								m_DetachedNodes[m_nDetachedPoints].wX = (signed int)(8.0f * fijCoorAvgX);
								m_DetachedNodes[m_nDetachedPoints].wY = (signed int)(8.0f * fijCoorAvgY);
								m_DetachedNodes[m_nDetachedPoints].nIndexToAttachedNode = i;
								m_DetachedNodes[m_nDetachedPoints].bitLeftLanes = 7; //Max value
								m_DetachedNodes[m_nDetachedPoints].bitRightLanes = 7;
								m_DetachedNodes[m_nDetachedPoints].byteTrafficFlags &= 0xFC;
								if ((unsigned __int8)m_AttachedPaths[nAssumedGroupFirstNode].sbMedianWidth <= m_AttachedPaths[i].sbMedianWidth)
									m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = m_AttachedPaths[i].sbMedianWidth;
								else
									m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = m_AttachedPaths[nAssumedGroupFirstNode].sbMedianWidth;
								DetachedPointsInfo[m_nConnectedNodes] = m_nDetachedPoints;
								++m_nDetachedPoints;
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
                    int iCurrentDetachedIndex = DetachedPointsInfo[m_AttachedPaths[j].wRouteInfoIndex];
                    int iForwardDetachedIndex = DetachedPointsInfo[m_AttachedPaths[j].wRouteInfoIndex + 1];

                    int iCurrentDetachedLeftLane = m_DetachedNodes[iCurrentDetachedIndex].bitLeftLanes;
                    int iCurrentDetachedRightLane = m_DetachedNodes[iCurrentDetachedIndex].bitRightLanes;
                    int iForwardDetachedLeftLane = m_DetachedNodes[iForwardDetachedIndex].bitLeftLanes;
                    int iForwardDetachedRightLane = m_DetachedNodes[iForwardDetachedIndex].bitRightLanes;

                    int *iCurrentLane1, *iCurrentLane2, *iForwardLane1, *iForwardLane2;
                    if (m_DetachedNodes[iCurrentDetachedIndex].nIndexToAttachedNode == j){
                        iCurrentLane1 = &iCurrentDetachedLeftLane;
                        iCurrentLane2 = &iCurrentDetachedRightLane;
                    }
                    else{
                        iCurrentLane1 = &iCurrentDetachedRightLane;
                        iCurrentLane2 = &iCurrentDetachedLeftLane;
                    }
                    if (m_DetachedNodes[iForwardDetachedIndex].nIndexToAttachedNode == j){
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

                    m_DetachedNodes[iCurrentDetachedIndex].bitLeftLanes = iCurrentDetachedLeftLane;
                    m_DetachedNodes[iCurrentDetachedIndex].bitRightLanes = iCurrentDetachedRightLane;
                    m_DetachedNodes[iForwardDetachedIndex].bitLeftLanes = iForwardDetachedLeftLane;
                    m_DetachedNodes[iForwardDetachedIndex].bitRightLanes = iForwardDetachedRightLane;
                }
            }
        }

        for (int j = 0; j < m_nAttachedNodes; j++){
            for (int k = 0; k < m_AttachedPaths[j].bitnumberOfNodesConnected; k++){
                if (m_DetachedNodes[DetachedPointsInfo[k + m_AttachedPaths[j].wRouteInfoIndex]].bitLeftLanes == 7)
                    m_DetachedNodes[DetachedPointsInfo[k + m_AttachedPaths[j].wRouteInfoIndex]].bitLeftLanes = 0;
                if (m_DetachedNodes[DetachedPointsInfo[k + m_AttachedPaths[j].wRouteInfoIndex]].bitRightLanes == 7)
                    m_DetachedNodes[DetachedPointsInfo[k + m_AttachedPaths[j].wRouteInfoIndex]].bitRightLanes = 0;
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
void CPathFind::DoPathSearch(int iPathDataFor, float fOriginX, float fOriginY, float fOriginZ, int iFirstNode, float fDestX, float fDestY, float fDestZ, CPathNode **pIntermediateNodeList, short *pSteps, short sMaxSteps, void *pVehicle, float *pfPathCost, float fMaxRadius, int iLastNode) {
	int iDestNodeIndex = iLastNode;
	int iOriginNodeIndex = iFirstNode;

	static CPathNode* c_pResetNodeList[9650 * PATHMUL];

	if(iDestNodeIndex == -1)
		iDestNodeIndex = FindNodeClosestToCoors(fDestX, fDestY, fDestZ, iPathDataFor, fMaxRadius, 0, 0, 0, 0);

	if(iOriginNodeIndex == -1)
		iOriginNodeIndex = FindNodeClosestToCoors(fOriginX, fOriginY, fOriginZ, iPathDataFor, fMaxRadius, 0, 0, 0, 0);

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
void CPathFind::RemoveBadStartNode(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps){
    if (*pSteps >= 2){
        if ((((float)(pIntermediateNodeList[1]->wY)/8.0f - fY) * ((float)(pIntermediateNodeList[0]->wY)/8.0f - fY)) +
            (((float)(pIntermediateNodeList[1]->wX)/8.0f - fX) * ((float)(pIntermediateNodeList[0]->wX)/8.0f - fX)) < 0.0f)
        {
            --(*pSteps);
            for (int i = 0; i < *pSteps; i++)
                pIntermediateNodeList[i] = pIntermediateNodeList[i + 1];
        }
    }
}

int CPathFind::FindNodeClosestToCoors(float fX, float fY, float fZ, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat){
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
			float fXDiff = utl::abs<float>(((float)pNode->wX / 8.0f) - fX);
			float fYDiff = utl::abs<float>(((float)pNode->wY / 8.0f) - fY);
			float fZDiff = utl::abs<float>(((float)pNode->wZ / 8.0f) - fZ);

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

void CPathFind::FindNextNodeWandering(uint8_t iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection){
    CVector vecCurrentPos(fX, fY, fZ + 1.0f);
    CPathNode* pCurrentActPedNode;

    if(pCurrentNode == NULL || (*pCurrentNode) == NULL ||
        ((fY - float((*pCurrentNode)->wY) / 8.0f) * (fY - float((*pCurrentNode)->wY) / 8.0f) + (fX - float((*pCurrentNode)->wX) / 8.0f) * (fX - float((*pCurrentNode)->wX) / 8.0f) + (fZ - float((*pCurrentNode)->wZ) / 8.0f) * (fZ - float((*pCurrentNode)->wZ) / 8.0f)) > 49.0f)
    {
        pCurrentActPedNode = &m_AttachedPaths[FindNodeClosestToCoors(fX, fY, fZ, iPathDataFor, 999999.88f, 0, 0, 0, 0)];
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

bool CPathFind::NewGenerateCarCreationCoors(float fX, float fY, float fDirectionVecX, float fDirectionVecY, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored) {
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
				float fDistanceToRandNode = (m_AttachedPaths[nRandIndex].Form2DVector() - CVector2D(fX, fY)).Length();

                if(fDistanceToRandNode < fReqRange) 
				{
                    for(int j = 0; j < m_AttachedPaths[nRandIndex].bitnumberOfNodesConnected; j++) {
                        int nNextNodeIndex = m_infoConnectedNodes[j + m_AttachedPaths[nRandIndex].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
                        if(!(m_AttachedPaths[nNextNodeIndex].bitIsIgnoredNode) || bDontCheckIgnored == true) 
						{
							float fDistanceToNextNode = (m_AttachedPaths[nNextNodeIndex].Form2DVector() - CVector2D(fX, fY)).Length();
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
                                
								CVector2D norV2dToAvgNode =  CVector2D(vecOutPosition) - CVector2D(fX, fY);
								norV2dToAvgNode.Normalize();

								float fProjectionOfDirection = norV2dToAvgNode.DotProduct(CVector2D(fDirectionVecX, fDirectionVecY));

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

bool CPathFind::GeneratePedCreationCoors(float fX, float fY, float fMinRange, float fMaxRange, float fSecMinRange, float fSecMaxRange, CVector *pvecSpawnPos, int *pStartNodeIndex, int *pNextNodeIndex, float *fRandomByte, RwMatrix *rwTransformationMatrix) {
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
	    float fStartNodeX = (float)(m_AttachedPaths[nStartNodeIndex].wX) / 8.0f;
	    float fStartNodeY = (float)(m_AttachedPaths[nStartNodeIndex].wY) / 8.0f;
	    float fStartNodeDisplacement = sqrt((fStartNodeY - fY) * (fStartNodeY - fY) + (fStartNodeX - fX) * (fStartNodeX - fX));
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
		    float fNextNodeX = (float)(m_AttachedPaths[nNextNodeIndex].wX) / 8.0f;
		    float fNextNodeY = (float)(m_AttachedPaths[nNextNodeIndex].wY) / 8.0f;
		    float fNextNodeDisplacement = sqrt((fNextNodeX - fX) * (fNextNodeX - fX) + (fNextNodeY - fY) * (fNextNodeY - fY));

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
				    RwV3d vecMeanPos;
				    vecMeanPos.x = fStartNodeX * (1.0f - *fRandomByte) + fNextNodeX * (*fRandomByte);
				    vecMeanPos.y = fStartNodeY * (1.0f - *fRandomByte) + fNextNodeY * (*fRandomByte);
				    vecMeanPos.z = fStartNodeZ * (1.0f - *fRandomByte) + fNextNodeZ * (*fRandomByte);
				    float fRandNodeDisplacement = sqrt((vecMeanPos.x - fX) * (vecMeanPos.x - fX) + (vecMeanPos.y - fY) * (vecMeanPos.y - fY));
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

float CPathFind::CalcRoadDensity(float fX, float fY) {
	float fDeltaDensity = 0.0f;
	for (int i = 0; i < m_nCarAttachedNodes; i++) {
		float fStartNodeX = (float)(m_AttachedPaths[i].wX) / 8.0f;
		float fStartNodeY = (float)(m_AttachedPaths[i].wY) / 8.0f;

        // ignore nodes that are over 80 units range
		if (utl::abs<float>(fStartNodeX - fX) >= 80.0f) {
			continue;
		}
		if (utl::abs<float>(fStartNodeX - fY) >= 80.0f) {
			continue;
		}

		for (int j = 0; j < m_AttachedPaths[i].bitnumberOfNodesConnected; j++) {
			int nNextNodeIndex = m_infoConnectedNodes[j+ m_AttachedPaths[i].wRouteInfoIndex] & em_infoConnectedNodesNODEINDEXONLY;
			int nDetachedNodeIndex = DetachedPointsInfo[j+ m_AttachedPaths[i].wRouteInfoIndex];
			float fnextNodeX = (float)(m_AttachedPaths[nNextNodeIndex].wX) / 8.0f;
			float fnextNodeY = (float)(m_AttachedPaths[nNextNodeIndex].wY) / 8.0f;
			float fDisplacement = sqrt((fStartNodeX - fnextNodeX) * (fStartNodeX - fnextNodeX) + (fStartNodeY - fnextNodeY) * (fStartNodeY - fnextNodeY));
			fDeltaDensity += (float)(m_DetachedNodes[nDetachedNodeIndex].bitLeftLanes) * fDisplacement + (float)(m_DetachedNodes[nDetachedNodeIndex].bitRightLanes) * fDisplacement;
		}
	}

	// sum of displacements between ranged nodes is divided by the area of game to get the density
	float fViceCityRoadDensity = fDeltaDensity / (2500.0f * (float)PATHMUL);
    CDebug::DebugAddText("Road Density: %f", fViceCityRoadDensity);
	return fViceCityRoadDensity;
}

int CPathFind::FindNodeClosestToCoorsFavourDirection(float fX, float fY, float fZ, uint8_t uiPathDataFor, float fLookAtX, float fLookAtY) {
	// normalize the LookAt vector
	float fLookAtLength = sqrt(fLookAtX * fLookAtX + fLookAtY * fLookAtY);
	if (fLookAtLength == 0.0f) {
		// maybe the LookAt vector components was set to 0.0
		fLookAtX = 1.0f;
	}
	else {
		fLookAtX = fLookAtX / fLookAtLength;
		fLookAtY = fLookAtY / fLookAtLength;
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

	for (int i = iStartNodeIndex; i < iEndNodeIndex; i++) {
		float fnodeDiffX = (float)(m_AttachedPaths[i].wX) / 8.0f - fX;
		float fnodeDiffY = (float)(m_AttachedPaths[i].wY) / 8.0f - fY;
		float fnodeDiffZ = (float)(m_AttachedPaths[i].wZ) / 8.0f - fZ;

		float fcurDistCoefficient = utl::abs<float>(fnodeDiffX) + utl::abs<float>(fnodeDiffY) + 3.0f* utl::abs<float>(fnodeDiffZ);
		if (fcurDistCoefficient < fprevRangedCoefficient) {
			float fdirectionVecX, fdirectionVecY;
			float flengthBetweenNodes = sqrt(fnodeDiffX * fnodeDiffX + fnodeDiffY * fnodeDiffY);

			// may be there was no distance between caller's position and paths node
			if (flengthBetweenNodes == 0.0f) {
				fdirectionVecX = 1.0f;
				fdirectionVecY = 0.0f;
			}
			else {
				fdirectionVecX = fnodeDiffX / flengthBetweenNodes;
				fdirectionVecY = fnodeDiffY / flengthBetweenNodes;
			}

			float fimmCoefficientWithDirection = fcurDistCoefficient + (fdirectionVecY * fLookAtY + fdirectionVecX * fLookAtX - 1.0f) * -20.0f;
			if (fimmCoefficientWithDirection < fprevRangedCoefficient) {
				fprevRangedCoefficient = fimmCoefficientWithDirection;
				ifoundNode = i;
			}
		}
	}
    CDebug::DebugAddText("ifoundNode %d", ifoundNode);
	return ifoundNode;
}


bool CPathFind::TestCoorsCloseness(float fDestinationX, float fDestinationY, float fDestinationZ, uint8_t uiPathDataFor, float fOriginX, float fOriginY, float fOriginZ) {
    static CPathNode *pIntermediateCarRouteInfos[32] = {0};
    static short sCarSteps = 0;
    static short sPedSteps = 0;
    float fDistance;

    switch (uiPathDataFor) {
        case PATHDATAFOR_CAR:
            DoPathSearch(PATHDATAFOR_CAR, fOriginX, fOriginY, fOriginZ, -1, fDestinationX, fDestinationY, fDestinationZ, pIntermediateCarRouteInfos, &sCarSteps, 32, NULL, &fDistance, 999999.88f, -1);
            if (fDistance < 150.0f) {
                return true;
            }
            else {
                return false;
            }
            break;
        case PATHDATAFOR_PED:
            DoPathSearch(PATHDATAFOR_PED, fOriginX, fOriginY, fOriginZ, -1, fDestinationX, fDestinationY, fDestinationZ, NULL, &sPedSteps, 0, NULL, &fDistance, 50.0f, -1);
            if (fDistance < 100.0f) {
                return true;
            }
            else {
                return false;
            }
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

CDetachedNode::CDetachedNode(){
    memset(this, 0, sizeof(CDetachedNode));
}

float CDetachedNode::CalculateLaneDistance() {
	float fdistance;

	if (this->bitLeftLanes) {
		if (this->bitRightLanes) {
			fdistance = (float)(this->sbMedianWidth) / 80.0f + 1.0f/2.0f;
		}
		else {
			fdistance = 1.0f/2.0f - (float)(this->bitLeftLanes) * 1.0f/2.0f;
		}
    }
	else {
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

#endif
