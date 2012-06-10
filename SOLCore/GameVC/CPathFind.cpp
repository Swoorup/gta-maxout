#include "../StdInc.h"

DWORD dwFunc_CPathFind__StoreNodeInfoCar = 0x00435C30;
DWORD dwFunc_CPathFind__StoreNodeInfoPed = 0x00435FA0;

#define VTYPE_CAR 0
#define VTYPE_BOAT 1

#define NODEINFOTYPE_EXTERNAL 1
#define NODEINFOTYPE_INTERNAL 2
#define NODEINFOTYPE_NULL     0

#define NODEINFOFLAGS_ISCROSSROAD     0x01 //00000001b
#define NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS     0x02 //00000010b
#define NODEINFOFLAGS_POLICEROADBLOCK       0x04 //00000100b
#define NODEINFOFLAGS_IGNORENODEAREA        0x08 //00001000b
#define NODEINFOFLAGS_VEHICLETYPEBOAT       0x10 //00010000b
#define NODEINFOFLAGS_RESTRICTEDACCESS      0x20 //00100000b

#define PATHDATAFOR_CAR 0
#define PATHDATAFOR_PED 1

int CPathFind::g_nCarGroupNodes = 0;
int CPathFind::g_nPedGroupNodes = 0;
CPathInfoForObject* CPathFind::g_pCarPathInfos = NULL;
CPathInfoForObject* CPathFind::g_pPedPathInfos = NULL;
CTempDetachedNode* CPathFind::g_pTempDetachedNodes = NULL;

#ifdef PATHFINDUSEORIGINAL
__declspec (naked) void CPathFind::StoreNodeInfoCar( int iNodeInfo_InternalNodesCount,
                                   uint8_t iNode_NodeType,
                                   int8_t iNode_NextNode,
                                   float fNodeX,
                                   float fNodeY,
                                   float fNodeZ,
                                   float fMedianWidth,
                                   uint8_t nLeftLanes,
                                   uint8_t nRightLanes,
                                   bool bIsIgnoredNode,
                                   bool bIsRestrictedAccess,
                                   uint8_t bSpeedLimit,
                                   bool bIsPoliceRoadBlock,
                                   uint8_t nVehicleType,
                                   uint32_t dwSpawnRate,
                                   uint8_t bUnknown)
{
    __asm jmp dwFunc_CPathFind__StoreNodeInfoCar
}


#else

//435C30h
void CPathFind::StoreNodeInfoCar( int nInternalNodeCount,
                                          unsigned char iNodeType,
                                          signed char iNextNode,
                                          float fNodeX,
                                          float fNodeY,
                                          float fNodeZ,
                                          float fMedianWidth,
                                          unsigned char nLeftLanes,
                                          unsigned char nRightLanes,
                                          bool bIsIgnoredNode,
                                          bool bIsRestrictedAccess,
                                          unsigned char bSpeedLimit,
                                          bool bIsPoliceRoadBlock,
                                          unsigned char byteVehicleType,
                                          unsigned int dwSpawnRate,
                                          unsigned char bUnknown)
{
  if (g_nCarGroupNodes < 1024){
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
      CPathFind::ArrangeOneNodeList(&g_pCarPathInfos[12 * g_nCarGroupNodes++]);
  }
}


//43C060h
void __stdcall CPathFind::ArrangeOneNodeList(CPathInfoForObject *PathInfo){
  for (int i = 0; i < 12; i++){
    if (PathInfo[i].byteNodeType == NODEINFOTYPE_EXTERNAL && PathInfo[i].sbNextNode == -1){
      for (int j = 0; j < 12; j++){
        if (PathInfo[j].byteNodeType == NODEINFOTYPE_INTERNAL && PathInfo[j].sbNextNode == i){
          PathInfo[i].sbNextNode = j;
          PathInfo[j].sbNextNode = -1;
          
          // Swap the right most significant bit
          bool bTempPedSpecificUnkBit = PathInfo[i].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
          PathInfo[i].byteFlags = PathInfo[i].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | PathInfo[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD;
          PathInfo[j].byteFlags = PathInfo[j].byteFlags & ~NODEINFOFLAGS_ISCROSSROAD | bTempPedSpecificUnkBit & NODEINFOFLAGS_ISCROSSROAD;
        }
      } 
    }
  }
}
#endif

#ifdef PATHFINDUSEORIGINAL
__declspec (naked) void CPathFind::StoreNodeInfoPed( int iNodeInfo_InternalNodesCount, 
                                   uint8_t eNodeType, 
                                   int8_t iNextNode, 
                                   float fNodeX, 
                                   float fNodeY,
                                   float fNodeZ,
                                   float fMedianWidth,
                                   uint8_t iNode_unknown,
                                   bool bIsIgnoredNode,
                                   bool bIsRestrictedAccess,
                                   uint32_t dwSpawnRate)
{
    __asm jmp dwFunc_CPathFind__StoreNodeInfoPed
}

#else
//435FA0h
void CPathFind::StoreNodeInfoPed( int nInternalNodeCount, 
                                   unsigned char iNodeType, 
                                   signed char iNextNode, 
                                   float fNodeX, 
                                   float fNodeY,
                                   float fNodeZ,
                                   float fMedianWidth,
                                   unsigned char iunknown,
                                   bool bIsIgnoredNode,
                                   bool bIsRestrictedAccess,
                                   unsigned int dwSpawnRate)
{
  if (g_nPedGroupNodes < 1214){
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fX = fNodeX / 16.0f;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fY = fNodeY / 16.0f;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].fZ = fNodeZ / 16.0f;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteNodeType = iNodeType;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].sbNextNode = iNextNode;
    if (fMedianWidth > 31.0f) fMedianWidth = 31.0f;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].sbMedianWidth = (signed int)(8.0f * fMedianWidth);
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteLeftLanes = 0;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteRightLanes = 0;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteSpeedLimit = 0;
    
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_POLICEROADBLOCK;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags &= ~NODEINFOFLAGS_VEHICLETYPEBOAT; 
    if (iunknown)               
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_ISCROSSROAD;
    if (bIsIgnoredNode)         
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_IGNORENODEAREA;
    if (bIsRestrictedAccess)    
        g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteFlags |= NODEINFOFLAGS_RESTRICTEDACCESS;

    if (dwSpawnRate > 15) dwSpawnRate = 15;
    g_pPedPathInfos[nInternalNodeCount + 12 * g_nPedGroupNodes].byteSpawnRate = unsigned char(dwSpawnRate);
    if (nInternalNodeCount == 11)
      CPathFind::ArrangeOneNodeList(&g_pPedPathInfos[12 * g_nPedGroupNodes++]);
  }
}

void CPathFind::Init(void){
    this->m_nAttachedNodes = 0;
    this->w_nTreadables = 0;
    this->m_nAttachedPoints = 0;
    this->m_nDetachedPoints = 0;
    this->Unusedfield_53804 = 0;
    for (int i =0; i<9650; i++)
        this->m_AttachedPaths[i].wUnkDist0x0A = 0x7FFE;
}   

void CPathFind::AllocatePathFindInfoMem(void){
    if (g_pCarPathInfos){
        delete [] g_pCarPathInfos;
        g_pCarPathInfos = NULL;
    }
    if (g_pPedPathInfos){
        delete [] g_pPedPathInfos;
        g_pPedPathInfos = NULL;
    }
    if (g_pTempDetachedNodes){
        delete [] g_pTempDetachedNodes;
        g_pTempDetachedNodes = NULL;
    }

    g_pCarPathInfos = new CPathInfoForObject[20000]; //Heap corruption chances
    memset(g_pCarPathInfos, 0, sizeof(CPathInfoForObject) * 20000); 
    g_pPedPathInfos = new CPathInfoForObject[20000]; //Heap corruption chances
    memset(g_pCarPathInfos, 0, sizeof(CPathInfoForObject) * 20000);
    g_pTempDetachedNodes = new CTempDetachedNode[4600];
    memset(g_pTempDetachedNodes, 0, sizeof(CTempDetachedNode) * 4600);
    g_nPedGroupNodes = 0;
    g_nCarGroupNodes = 0;
}

void CPathFind::PreparePathData(void){
    CDebug::DebugAddText("Custom Code: PreparePathData");
    CFileMgr::SetDir("");
    if ( g_pCarPathInfos && g_pPedPathInfos && g_pTempDetachedNodes){
        CTempNode* pTempNodes = new CTempNode[5000];
        m_nAttachedPoints = 0;
        m_nAttachedNodes = 0;
        PreparePathDataForType(PATHDATAFOR_CAR, pTempNodes, NULL, 1.0f, g_pCarPathInfos, g_nCarGroupNodes);
        m_nCarAttachedNodes = m_nAttachedNodes;
        PreparePathDataForType(PATHDATAFOR_PED, pTempNodes, NULL, 1.0f, g_pPedPathInfos, g_nPedGroupNodes);
        m_nPedAttachedNodes = m_nAttachedNodes - m_nCarAttachedNodes;
        if (pTempNodes)
            delete [] pTempNodes;
        CountFloodFillGroups(PATHDATAFOR_CAR);
        CountFloodFillGroups(PATHDATAFOR_PED);
        delete [] g_pCarPathInfos;
        g_pCarPathInfos = NULL;
        delete [] g_pPedPathInfos;
        g_pPedPathInfos = NULL;
        if (g_pTempDetachedNodes)
            delete [] g_pTempDetachedNodes;
        g_pTempDetachedNodes = NULL;
    }
    CDebug::DebugAddText("Custom code: Done with PreparePathData\n");
}

void CPathFind::CountFloodFillGroups(unsigned char iPathDataFor){
	int iStartNodeIndex, iEndNodeIndex;
	
	switch (iPathDataFor)
	{
		case PATHDATAFOR_CAR:
			iStartNodeIndex = 0;
			iEndNodeIndex = m_nCarAttachedNodes;
			break;
		case PATHDATAFOR_PED:
			iStartNodeIndex = m_nCarAttachedNodes;
			iEndNodeIndex = m_nAttachedNodes;
			break;
	}
	
	if (iStartNodeIndex < iEndNodeIndex){
		for (int i = iStartNodeIndex; i < iEndNodeIndex; i++){
			m_AttachedPaths[i].sbField0x0F = 0;
		}
	}
	
	int j = 0;
	while (true){
		++j;
		if (j > 1500){
			int k = iStartNodeIndex;
			while (m_AttachedPaths[k].sbField0x0F && k < iEndNodeIndex)	k++;
			CDebug::DebugAddText("NumNodes: %d Accounted for: %d\n", iEndNodeIndex - iStartNodeIndex, k - iStartNodeIndex);
		}
		int k = iStartNodeIndex;
		while (m_AttachedPaths[k].sbField0x0F && k < iEndNodeIndex) ++k;
		if (k == iEndNodeIndex) break;
		CPathNode* pNode = &m_AttachedPaths[k];
		pNode->wField0x02 = -1;
		pNode->sbField0x0F = j;
		if ( !(pNode->bitUnkCount4To7)){ //if not 
			if ( iPathDataFor == PATHDATAFOR_PED)
				CDebug::DebugAddText("Single ped node: %f %f %f\n", pNode->wX, pNode->wY, pNode->wZ);
			else
				CDebug::DebugAddText("Single car node: %f %f %f\n",	pNode->wX, pNode->wY, pNode->wZ);
		}
		
		while (pNode){
			CPathNode* pPrevNode = pNode;
			if ( pNode->wField0x02 >= 0){
				if (pNode->wField0x02 >= 512)
					pNode = &m_AttachedPaths[pPrevNode->wField0x02 - 512];
				else
					pNode = &m_UnknownNodeList[pPrevNode->wField0x02];
			}
			else 
				pNode = NULL;
			
			for (int i = 0; i < (pPrevNode->bitUnkCount4To7); ++i){
				int l = AttachedPointsInfo[i + pPrevNode->wRouteInfoIndex] & 0x3FFF;
				if ( !m_AttachedPaths[l].sbField0x0F){

                    // The following code is bugged as it does not consider the limit on 1 byte space
					/*if (j) m_AttachedPaths[l].sbField0x0F = j;
					else m_AttachedPaths[l].sbField0x0F = 128;*/

                    m_AttachedPaths[l].sbField0x0F = j;
                    if ( !m_AttachedPaths[l].sbField0x0F ) //If it is 0 or j has maxed out (256) maximum char value then this is 0
                        m_AttachedPaths[l].sbField0x0F = 128;

					if (pNode){
						if (pNode < m_UnknownNodeList || pNode >= &m_UnknownNodeList[512])
							m_AttachedPaths[l].wField0x02 = signed int(pNode - m_AttachedPaths)/ sizeof(CPathNode) + 512;
						else
							m_AttachedPaths[l].wField0x02 = signed int((pNode - m_UnknownNodeList) / sizeof(CPathNode));// 0x66666667 * (pNode - m_UnknownNodeList) >> 32) >> 3 + (pNode - m_UnknownNodeList) >> 31;
					}
					else 
						m_AttachedPaths[l].wField0x02 = -1;
					
					pNode = &m_AttachedPaths[l];
				}
			}
		}
	}
	Unusedfield_53808[iPathDataFor] = j - 1;
	CDebug::DebugAddText("GraphType:%d. FloodFill groups:%d\n", iPathDataFor, j);
}

void CPathFind::AddNodeToList(CPathNode *pTargetNode, int iParamDisplacement){
	signed short iDisplacement = iParamDisplacement & 511;
	signed short iGridIndex01 = m_UnknownNodeList[iDisplacement].wField0x02;
	CPathNode* pGridNode1; // edx
	if (iGridIndex01 >=0){
		if (iGridIndex01 >= 512)
            pGridNode1 = &m_AttachedPaths[iGridIndex01 - 512];
		else
			pGridNode1 = &m_UnknownNodeList[iGridIndex01];
    }
	else
		pGridNode1 = NULL;
	//loc_43739A
	if (pGridNode1){
		if ( pGridNode1 < &m_UnknownNodeList[0] || pGridNode1 >= &m_UnknownNodeList[512])
			pTargetNode->wField0x02 = ((uint32_t)pGridNode1 - (uint32_t)&m_AttachedPaths[0])/sizeof(CPathNode) + 512;
		else
			pTargetNode->wField0x02 = ((uint32_t)pGridNode1 - (uint32_t)&m_UnknownNodeList[0])/sizeof(CPathNode);
    }
	else
		pTargetNode->wField0x02 = -1;
		
	//Process for the First Field
	CPathNode* pGridNode2 = &m_UnknownNodeList[iDisplacement]; // eax
	if (pGridNode2){
		if (pGridNode2 < &m_UnknownNodeList[0] || pGridNode2 >= &m_UnknownNodeList[512])
			pTargetNode->wField0x00 = ((uint32_t)pGridNode2 - (uint32_t)&m_AttachedPaths[0])/sizeof(CPathNode) + 512;
		else
			pTargetNode->wField0x00 = ((uint32_t)&m_AttachedPaths[iDisplacement] - (uint32_t)&m_AttachedPaths[0])/sizeof(CPathNode);
    }
	else
		pTargetNode->wField0x00 = -1;
	
	// Phase 2
	signed short iGridIndex03 = m_UnknownNodeList[iDisplacement].wField0x02; //dx
	CPathNode* pGridNode03; //eax
	if (iGridIndex03 >= 0 ){
		if (iGridIndex03 >= 512)
			pGridNode03 = &m_AttachedPaths[iGridIndex03 - 512];
		else
			pGridNode03 = &m_UnknownNodeList[iGridIndex03];
    }
	else
		pGridNode03 = NULL;
	
	if (pGridNode03){ // test eax, eax
        CPathNode* pGridesi;
        if (iGridIndex03 >= 0){ // test dx, dx
            if (iGridIndex03 >= 512)
                pGridesi = &m_AttachedPaths[iGridIndex03 - 512];
            else
                pGridesi = &m_UnknownNodeList[iGridIndex03];
        }
        else
            pGridesi = NULL;
    
		if (pTargetNode){ // ebx
			if (pTargetNode < &m_UnknownNodeList[0] || pTargetNode >= &m_UnknownNodeList[512])
				pGridesi->wField0x00 = ((uint32_t)pTargetNode - (uint32_t)&m_AttachedPaths[0])/sizeof(CPathNode) + 512;
			else
				pGridesi->wField0x00 = ((uint32_t)pTargetNode - (uint32_t)&m_UnknownNodeList[0])/sizeof(CPathNode);
        }
		else
			pGridesi->wField0x00 = -1;
    }
	if (pTargetNode){
		if (pTargetNode < &m_UnknownNodeList[0] || pTargetNode >= &m_UnknownNodeList[512])
			m_UnknownNodeList[iDisplacement].wField0x02 = ((uint32_t)pTargetNode - (uint32_t)&m_AttachedPaths[0])/sizeof(CPathNode) + 512;
		else 
			m_UnknownNodeList[iDisplacement].wField0x02 = ((uint32_t)pTargetNode - (uint32_t)&m_UnknownNodeList[0])/sizeof(CPathNode);
    }
	else
		m_UnknownNodeList[iDisplacement].wField0x02 = -1;
		
	pTargetNode->wUnkDist0x0A = (signed short)iParamDisplacement;
}

void CPathFind::RemoveNodeFromList(CPathNode *pRemoveNode){
	signed short iGridIndexTwo00 = pRemoveNode->wField0x02;
	CPathNode* pGrid1; //edx
	if (iGridIndexTwo00 >= 0){
		if (iGridIndexTwo00 >= 512)
			pGrid1 = &m_AttachedPaths[iGridIndexTwo00 - 512];
		else
			pGrid1 = &m_UnknownNodeList[iGridIndexTwo00];
	}
	else
		pGrid1 = NULL;
	
	CPathNode* pGrid2; //ebp
	signed short iGridIndexOne00 = pRemoveNode->wField0x00;
	if (iGridIndexOne00 >= 0){
		if (iGridIndexOne00 >= 512)
			pGrid2 = &m_AttachedPaths[iGridIndexOne00 - 512];
		else
			pGrid2 = &m_UnknownNodeList[iGridIndexOne00];
    }
	else
		pGrid2 = NULL;
		
    //if (pGrid2){
	if (pGrid1){
		if (pGrid1 < &m_UnknownNodeList[0] || pGrid1 >= &m_UnknownNodeList[512])
			pGrid2->wField0x02 = (pGrid1 - &m_AttachedPaths[0]) + 512;
		else
			pGrid2->wField0x02 = (pGrid1 - &m_UnknownNodeList[0]);
	}
	else
		pGrid2->wField0x02 = -1;
    //}
	
	signed short iGridIndexTwo01 = pRemoveNode->wField0x02;
	CPathNode* pGrid3; //eax
	if (iGridIndexTwo01 >= 0){
		if (iGridIndexTwo01 >= 512)
			pGrid3 = &m_AttachedPaths[iGridIndexTwo01-512];
		else
			pGrid3 = &m_UnknownNodeList[iGridIndexTwo01];
	}
	else
		pGrid3 = NULL;
	
	if (pGrid3){ //branch saved for later
		signed short iGridIndexOne01 = pRemoveNode->wField0x00;
		CPathNode* pGrid4; //edx
		if (iGridIndexOne01 >= 0){
			if (iGridIndexOne01 >= 512)
				pGrid4 = &m_AttachedPaths[iGridIndexOne01 - 512];
			else
				pGrid4 = &m_UnknownNodeList[iGridIndexOne01];
		}
		else
			pGrid4 = NULL;
			
		CPathNode* pGrid5; //ebx
		if (iGridIndexTwo01 >= 0){ //cx
			if (iGridIndexTwo01 >= 512)
				pGrid5 = &m_AttachedPaths[iGridIndexTwo01 - 512];
			else
				pGrid5 = &m_UnknownNodeList[iGridIndexTwo01];
		}
		else
			pGrid5 = NULL;
		
        //if (pGrid5){
		if (pGrid4){
			if (pGrid4 < &m_UnknownNodeList[0] || pGrid4 >= &m_UnknownNodeList[512])
				pGrid5->wField0x00 = (pGrid4 - &m_AttachedPaths[0])+ 512;
			else
				pGrid5->wField0x00 = (pGrid4 - &m_UnknownNodeList[0]);
		}
		else
			pGrid5->wField0x00 = -1;
        //}
	}
}

CPathNode* CPathFind::staticNodes[9650] = {NULL};
void CPathFind::DoPathSearch(int iPathDataFor, 
										float fOriginX, 
										float fOriginY, 
										float fOriginZ, 
										int iFirstNode, 
										float fDestX, 
										float fDestY, 
										float fDestZ, 
										CPathNode **pIntermediateNodeList, 
										short *pSteps, 
										short sMaxSteps, 
										void *pVehicle, //Unused
										float *pfDistance, //Always 0
										float fMaxRadius, 
										int iLastNode) //Always -1 meaning not known
{
    CDebug::DebugAddText("%d %f %f %f %d %f %f %f 0x%X 0x%X %d 0x%X 0x%X %f %d" , iPathDataFor, 
										 fOriginX, 
										 fOriginY, 
										 fOriginZ, 
										 iFirstNode, 
										 fDestX, 
										 fDestY, 
										 fDestZ, 
										pIntermediateNodeList, 
										pSteps, 
										sMaxSteps, 
										pVehicle, //Unused
										pfDistance, //Always 0
										fMaxRadius, 
										iLastNode);
	int iDestNodeIndex = iLastNode;
	int iOriginNodeIndex = iFirstNode;
	if (iDestNodeIndex == -1)
		iDestNodeIndex = FindNodeClosestToCoors(fDestX, fDestY, fDestZ, iPathDataFor, fMaxRadius, 0, 0, 0, 0);
	if (iOriginNodeIndex == -1)
		iOriginNodeIndex = FindNodeClosestToCoors(fOriginX, fOriginY, fOriginZ, iPathDataFor, fMaxRadius, 0, 0, 0, 0);
		
	if ((iDestNodeIndex >= 0) && (iOriginNodeIndex >= 0)){
		if (iOriginNodeIndex == iDestNodeIndex){
			*pSteps = 0;
			if ( pfDistance) *pfDistance = 0.0f;
		}
		else if (m_AttachedPaths[iDestNodeIndex].sbField0x0F == m_AttachedPaths[iOriginNodeIndex].sbField0x0F){
			for (int i = 0; i < 512; i++) 
                m_UnknownNodeList[i].wField0x02 = -1;
            CPathNode* pDestinationNode = &m_AttachedPaths[iDestNodeIndex];
		    AddNodeToList(pDestinationNode, 0);
		    int nStaticNodeStored = 1;
            staticNodes[0] = pDestinationNode;
            short nCircleList = 0;
            bool bFound = false;
            // Phase 1
            do {
                short sField02 = m_UnknownNodeList[nCircleList].wField0x02;
                CPathNode* pNodeForPhase1Check;
                if ( sField02 >= 0){
                    if (sField02 >= 512)
                        pNodeForPhase1Check = &m_AttachedPaths[sField02 - 512];
                    else
                        pNodeForPhase1Check = &m_UnknownNodeList[sField02];
                }
                else 
                    pNodeForPhase1Check = NULL;
                while (pNodeForPhase1Check){
                    if (pNodeForPhase1Check == &m_AttachedPaths[iOriginNodeIndex])
                    bFound = true;
                    for (int i = 0; i < (int)(pNodeForPhase1Check->bitUnkCount4To7); i++){
                        int iConnectedRouteIndex = i + pNodeForPhase1Check->wRouteInfoIndex;
                        int iNextNodeIndex = AttachedPointsInfo[iConnectedRouteIndex] & 0x3FFF;
                        int iDispl = short(pNodeForPhase1Check->wUnkDist0x0A + m_InRangedDisplacement[iConnectedRouteIndex]);
                        if (iDispl < (int)m_AttachedPaths[iNextNodeIndex].wUnkDist0x0A){
                            if (m_AttachedPaths[iNextNodeIndex].wUnkDist0x0A != 32766)
                                RemoveNodeFromList(&m_AttachedPaths[iNextNodeIndex]);
                            if (m_AttachedPaths[iNextNodeIndex].wUnkDist0x0A == 32766)
                                staticNodes[nStaticNodeStored++] = &m_AttachedPaths[iNextNodeIndex];
                            AddNodeToList(&m_AttachedPaths[iNextNodeIndex], iDispl);
                        }
                    }
                    RemoveNodeFromList(pNodeForPhase1Check);
                    sField02 = pNodeForPhase1Check->wField0x02;
                    if (sField02 >= 0){
                        if (sField02 >= 512)
                            pNodeForPhase1Check = &m_AttachedPaths[sField02 - 512];
                        else
                            pNodeForPhase1Check = &m_UnknownNodeList[sField02];
                    }
                    else 
                        pNodeForPhase1Check = NULL;
                }
                nCircleList = (nCircleList + 1) & 511;
            } while (bFound == false);
            // Phase 2
            CPathNode* pNodeForPhase2Check = &m_AttachedPaths[iOriginNodeIndex];
            *pSteps = 0;
            if (pfDistance)
                *pfDistance = m_AttachedPaths[iOriginNodeIndex].wUnkDist0x0A;
            pIntermediateNodeList[(*pSteps)++] = &m_AttachedPaths[iOriginNodeIndex];
            while (*pSteps < sMaxSteps && pNodeForPhase2Check != pDestinationNode){
                for (int i = 0; (signed short)i < pNodeForPhase2Check->bitUnkCount4To7; i++){
                    int iConnectedRouteIndex = i + pNodeForPhase2Check->wRouteInfoIndex;
                    if (pNodeForPhase2Check->wUnkDist0x0A - m_InRangedDisplacement[iConnectedRouteIndex] == m_AttachedPaths[AttachedPointsInfo[iConnectedRouteIndex] & 0x3FFF].wUnkDist0x0A){
                        pNodeForPhase2Check = &m_AttachedPaths[AttachedPointsInfo[iConnectedRouteIndex] & 0x3FFF];
                        pIntermediateNodeList[(*pSteps)++] = pNodeForPhase2Check;
                        i = 29030; // break out from loop?
                    }
                }
            }
            // Need to optimize the following function by breaking into 8 aligned boundaries
            for (int i = 0; i < nStaticNodeStored; i++)
            staticNodes[i]->wUnkDist0x0A = 32766;
      }
      else{
        *pSteps = 0;
        if ( pfDistance) *pfDistance = 100000.0f;
      }
    }
    else{
      *pSteps = 0;
      if ( pfDistance) *pfDistance = 100000.0f;
    }
}

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
	
	switch (iPathDataFor){
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
		if ((bCheckIgnored == false || !(pNode->bitIgnoredNode)) &&
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

void CPathFind::FindNextNodeWandering(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection){
    CVector VectorCurrentPos(fX, fY, fZ + 1.0f);
    CPathNode* pCurrentActPedNode;
    if (pCurrentNode == NULL || 
        (*pCurrentNode) == NULL || 
        ((fY - float((*pCurrentNode)->wY) / 8.0f) * (fY - float((*pCurrentNode)->wY) / 8.0f) + 
         (fX - float((*pCurrentNode)->wX) / 8.0f) * (fX - float((*pCurrentNode)->wX) / 8.0f) + 
         (fZ - float((*pCurrentNode)->wZ) / 8.0f) * (fZ - float((*pCurrentNode)->wZ) / 8.0f)) > 49.0f)
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
    for (int i = 0; i < pCurrentActPedNode->bitUnkCount4To7; i++){
        CPathNode* pDeltaNextNode = &m_AttachedPaths[AttachedPointsInfo[i+pCurrentActPedNode->wRouteInfoIndex] & 0x3FFF];
        if ((pCurrentActPedNode->bitIgnoredNode) || 
            !(pDeltaNextNode->bitIgnoredNode))
        {
            CVector VectorNextDeltaPos(float(pDeltaNextNode->wX)/8.0f, float(pDeltaNextNode->wY)/8.0f, float(pDeltaNextNode->wZ)/8.0f + 1.0f);
            if (CWorld::GetIsLineOfSightClear(&VectorCurrentPos, &VectorNextDeltaPos, 1, 0, 0, 0, 0, 0, 0)){
                double fDeltaNextNodeLength = sqrt(VectorNextDeltaPos.x*VectorNextDeltaPos.x + VectorNextDeltaPos.y*VectorNextDeltaPos.y);
                double fDeltaNormalX = VectorNextDeltaPos.x / fDeltaNextNodeLength;
                double fDeltaNormalY = VectorNextDeltaPos.y / fDeltaNextNodeLength;

                double fDeltaCoefficient = fDeltaNormalX * dPrevNormalX + fDeltaNormalY * dPrevNormalY;
                if (fDeltaCoefficient >= (double)fPrevFoundRangeCoeff){
                    fPrevFoundRangeCoeff = fDeltaCoefficient;
                    *pNextNode = pDeltaNextNode;
                    if (fDeltaNormalX < 0.0f){
                        double fabsDeltaNormalY = utl::abs<double>(fDeltaNormalY);
                        double fabsDeltaNormalX = -fDeltaNormalX;
                        if (2.0f * fabsDeltaNormalY >= fabsDeltaNormalX){
                            if (2.0f * fabsDeltaNormalX >= fDeltaNormalY){
                                if (2.0f * fDeltaNormalX <= fDeltaNormalY){
                                    if (fDeltaNormalY <= 0.0f)
                                        *byteNewDirection = 5;
                                    else
                                        *byteNewDirection = 7;
                                }
                                else
                                    *byteNewDirection = 4;
                            }
                            else
                                *byteNewDirection = 0;
                        }
                        else
                            *byteNewDirection = 6;
                    }
                    else{
                        double fabsDeltaNormalY = utl::abs<double>(fDeltaNormalY);
                        if (2.0f * fabsDeltaNormalY >= fDeltaNormalX){
                            if (2.0f * fDeltaNormalX >= fDeltaNormalY){
                                if ( -2.0f * fDeltaNormalX <= fDeltaNormalY){
                                    if (fDeltaNormalY <= 0.0f)
                                        *byteNewDirection = 3;
                                    else
                                        *byteNewDirection = 1;
                                }
                                else
                                    *byteNewDirection = 4;
                            }
                            else
                                *byteNewDirection = 0;
                        }
                        else
                            *byteNewDirection = 2;
                    }
                }
            }
        }
    }
    if (!(*pNextNode)){
        *byteNewDirection = 0;
        *pNextNode = pCurrentActPedNode;
    }
}

void CPathFind::PreparePathDataForType( unsigned char bytePathDataFor,
												CTempNode* pTempNode,
												CPathInfoForObject* pUnusedPathInfos,
												float fUnkRange,
												CPathInfoForObject* pPathInfosForObject,
												int nGroupNodesForObject)
{
    signed short *ptempIndices = new signed short[9650];
	int32_t nTmpDetachedNodes = 0;
	int32_t nPrevObjectAttachedNodes = m_nAttachedNodes;
	int32_t nPrevObjectAttachedPoints = m_nAttachedPoints;

	if (nGroupNodesForObject > 0){
		for (int i = 0; i < nGroupNodesForObject; i++){
			int nAttachedPathsForCurrentGroup = m_nAttachedNodes;
			for (int j = i*12; j < (i*12 + 12); j++){
				if ( pPathInfosForObject[j].byteNodeType == NODEINFOTYPE_INTERNAL){
					m_AttachedPaths[m_nAttachedNodes].wX = (signed int)(8.0f * pPathInfosForObject[j].fX);
					m_AttachedPaths[m_nAttachedNodes].wY = (signed int)(8.0f * pPathInfosForObject[j].fY);
					m_AttachedPaths[m_nAttachedNodes].wZ = (signed int)(8.0f * pPathInfosForObject[j].fZ);

					ptempIndices[m_nAttachedNodes] = -(1  + i);
					m_AttachedPaths[m_nAttachedNodes].sbMedianWidth = pPathInfosForObject[j].sbMedianWidth;
					m_AttachedPaths[m_nAttachedNodes].byteSpawnRate = pPathInfosForObject[j].byteSpawnRate;

					m_AttachedPaths[m_nAttachedNodes].bitSpeedLimit = pPathInfosForObject[j].byteSpeedLimit;
					m_AttachedPaths[m_nAttachedNodes].bitCopsRoadBlock = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_POLICEROADBLOCK) >> 2;
					m_AttachedPaths[m_nAttachedNodes].bitIgnoredNode = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_IGNORENODEAREA) >> 3;
					m_AttachedPaths[m_nAttachedNodes].bitIsVehicleBoat = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_VEHICLETYPEBOAT) >> 4;
					m_AttachedPaths[m_nAttachedNodes].bitHaveUnrandomizedVehClass = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_HAVEUNRANDOMIZEDVEHCLASS) >> 1;
					m_AttachedPaths[m_nAttachedNodes].bitRestrictedAccess = (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_RESTRICTEDACCESS) >> 5;
					m_nAttachedNodes++;
				}
				else if ( pPathInfosForObject[j].byteNodeType == NODEINFOTYPE_EXTERNAL){
					g_pTempDetachedNodes[nTmpDetachedNodes].fX = pPathInfosForObject[j].fX;
					g_pTempDetachedNodes[nTmpDetachedNodes].fY = pPathInfosForObject[j].fY;
					g_pTempDetachedNodes[nTmpDetachedNodes].fZ = pPathInfosForObject[j].fZ;
					g_pTempDetachedNodes[nTmpDetachedNodes].sNextNodeIndex = pPathInfosForObject[j].sbNextNode + nAttachedPathsForCurrentGroup;
					g_pTempDetachedNodes[nTmpDetachedNodes].byteLeftLanes = pPathInfosForObject[j].byteLeftLanes;
					g_pTempDetachedNodes[nTmpDetachedNodes].byteRightLanes = pPathInfosForObject[j].byteRightLanes;
					g_pTempDetachedNodes[nTmpDetachedNodes].sbMedianWidth = pPathInfosForObject[j].sbMedianWidth;
					if (pPathInfosForObject[j].byteFlags & NODEINFOFLAGS_ISCROSSROAD)
						g_pTempDetachedNodes[nTmpDetachedNodes++].bIsCrossRoad = true;
					else
						g_pTempDetachedNodes[nTmpDetachedNodes++].bIsCrossRoad = false;
				}
			}
		}
	}
	// Phase 1 ended. Now close and prepare files{

	//Phase 2 Started{
	//int& DWORDunk = *(int*)0x6F99F8;
	int DWORDunk = 0;
    for (int i= 0; i < nTmpDetachedNodes; i++){
		float fRange = fUnkRange;
		int iInRangeNode = -1;
		for (int j = 0; j < DWORDunk; j++){
			if ( pTempNode[j].processState == 1){
				float fDetachedCoorsXDiff = pTempNode[j].fX - g_pTempDetachedNodes[i].fX;
				float fDetachedCoorsYDiff = pTempNode[j].fY - g_pTempDetachedNodes[i].fY;
				fDetachedCoorsXDiff = fDetachedCoorsXDiff < 0.0f ? -fDetachedCoorsXDiff : fDetachedCoorsXDiff;
				fDetachedCoorsYDiff = fDetachedCoorsYDiff < 0.0f ? -fDetachedCoorsYDiff : fDetachedCoorsYDiff;
				if (fDetachedCoorsXDiff <= fRange &&
                    fDetachedCoorsYDiff <= fRange)
                {
					if (fDetachedCoorsXDiff <= fDetachedCoorsYDiff)
                        fRange = fDetachedCoorsYDiff;
                    else
                        fRange = fDetachedCoorsXDiff;
                    iInRangeNode = j;
				}
			}
		}
		if (iInRangeNode == -1){
			pTempNode[DWORDunk].fX = g_pTempDetachedNodes[i].fX;
			pTempNode[DWORDunk].fY = g_pTempDetachedNodes[i].fY;
			pTempNode[DWORDunk].fZ = g_pTempDetachedNodes[i].fZ;
			pTempNode[DWORDunk].PrevDetachedIndex = g_pTempDetachedNodes[i].sNextNodeIndex;
			if (bytePathDataFor == PATHDATAFOR_CAR){
				pTempNode[DWORDunk].byteLeftLanes = g_pTempDetachedNodes[i].byteLeftLanes;
				pTempNode[DWORDunk].byteRightLanes = g_pTempDetachedNodes[i].byteRightLanes;
			}
			pTempNode[DWORDunk].sbMedianWidth = g_pTempDetachedNodes[i].sbMedianWidth;
			pTempNode[DWORDunk].bIsCrossRoad = g_pTempDetachedNodes[i].bIsCrossRoad;
			pTempNode[DWORDunk++].processState = 1;
		}
		else {
			pTempNode[iInRangeNode].NextDetachedIndex = g_pTempDetachedNodes[i].sNextNodeIndex;
			pTempNode[iInRangeNode].processState = 2;
			float fVecX = float(m_AttachedPaths[pTempNode[iInRangeNode].PrevDetachedIndex].wX
							   -m_AttachedPaths[pTempNode[iInRangeNode].NextDetachedIndex].wX)/8.0f;
			float fVecY = float(m_AttachedPaths[pTempNode[iInRangeNode].PrevDetachedIndex].wY
                               -m_AttachedPaths[pTempNode[iInRangeNode].NextDetachedIndex].wY)/8.0f;
            float fLength = sqrt(fVecX * fVecX + fVecY * fVecY);
            pTempNode[iInRangeNode].byteNormalX = (signed char)(fVecX/ fLength * 100.0f);
			pTempNode[iInRangeNode].byteNormalY = (signed char)(fVecY/ fLength * 100.0f);
            pTempNode[iInRangeNode].fX += g_pTempDetachedNodes[i].fX;
            pTempNode[iInRangeNode].fX *= 1.0f/2.0f;
			pTempNode[iInRangeNode].fY += g_pTempDetachedNodes[i].fY;
            pTempNode[iInRangeNode].fY *= 1.0f/2.0f;
			pTempNode[iInRangeNode].fZ += g_pTempDetachedNodes[i].fZ;
            pTempNode[iInRangeNode].fZ *= 1.0f/2.0f;

			if (pTempNode[iInRangeNode].sbMedianWidth <= g_pTempDetachedNodes[i].sbMedianWidth)
				pTempNode[iInRangeNode].sbMedianWidth = g_pTempDetachedNodes[i].sbMedianWidth;
			pTempNode[iInRangeNode].bIsCrossRoad = g_pTempDetachedNodes[i].bIsCrossRoad;
			if (bytePathDataFor == PATHDATAFOR_CAR &&
                pTempNode[iInRangeNode].byteLeftLanes &&
                pTempNode[iInRangeNode].byteRightLanes &&
                (!g_pTempDetachedNodes[i].byteLeftLanes || !g_pTempDetachedNodes[i].byteRightLanes))
			{
				pTempNode[iInRangeNode].byteLeftLanes = g_pTempDetachedNodes[i].byteRightLanes;
				pTempNode[iInRangeNode].byteRightLanes = g_pTempDetachedNodes[i].byteLeftLanes;
			}
		}
    }
	//Phase 2 Ended{
    //Phase 3 Started Error exist here
	for (int i = nPrevObjectAttachedNodes; i < m_nAttachedNodes; i++){
		m_AttachedPaths[i].bitUnkCount4To7 = 0;
		m_AttachedPaths[i].wRouteInfoIndex =  m_nAttachedPoints;
		for (int j = 0; j < DWORDunk; j++){
			if (pTempNode[j].processState == 2){
				if (i == pTempNode[j].PrevDetachedIndex || i == pTempNode[j].NextDetachedIndex){
					if ( i == pTempNode[j].PrevDetachedIndex )
						AttachedPointsInfo[m_nAttachedPoints] = pTempNode[j].NextDetachedIndex;
					else
						AttachedPointsInfo[m_nAttachedPoints] = pTempNode[j].PrevDetachedIndex;
					CPathNode* pCurrentNode = &m_AttachedPaths[AttachedPointsInfo[m_nAttachedPoints] & 0x3FFF];
					float fDistance = sqrt((float(m_AttachedPaths[i].wX - pCurrentNode->wX)/8.0f * float(m_AttachedPaths[i].wX - pCurrentNode->wX)/8.0f) +
										   (float(m_AttachedPaths[i].wY - pCurrentNode->wY)/8.0f * float(m_AttachedPaths[i].wY - pCurrentNode->wY)/8.0f) +
										   (float(m_AttachedPaths[i].wZ - pCurrentNode->wZ)/8.0f * float(m_AttachedPaths[i].wZ - pCurrentNode->wZ)/8.0f));
					if (fDistance > 255.0f) fDistance = 255.0f;
					m_InRangedDisplacement[m_nAttachedPoints] = (signed char)fDistance;
					if (pTempNode[j].bIsCrossRoad) AttachedPointsInfo[m_nAttachedPoints] |= 0x8000;
					if (bytePathDataFor == PATHDATAFOR_CAR){
						int k = 0;
                        for (k=0;;++k){
                            if ( k >= m_nDetachedPoints) 
                                break;
							if (m_DetachedNodes[k].NormalVecX == (signed char)pTempNode[j].byteNormalX &&
								m_DetachedNodes[k].NormalVecY == (signed char)pTempNode[j].byteNormalY &&
								m_DetachedNodes[k].wX == (signed short)(8.0f * pTempNode[j].fX) &&
								m_DetachedNodes[k].wY == (signed short)(8.0f * pTempNode[j].fY) )
							{
								DetachedPointsInfo[m_nAttachedPoints] = k;
								k = m_nDetachedPoints;
							}
                        }
						if (k == m_nDetachedPoints){
							m_DetachedNodes[m_nDetachedPoints].NormalVecX = pTempNode[j].byteNormalX;
							m_DetachedNodes[m_nDetachedPoints].NormalVecY = pTempNode[j].byteNormalY;
							m_DetachedNodes[m_nDetachedPoints].wX = (signed short)(8.0f * pTempNode[j].fX);
							m_DetachedNodes[m_nDetachedPoints].wY = (signed short)(8.0f * pTempNode[j].fY);
							m_DetachedNodes[m_nDetachedPoints].wPathsIndex = i;
							m_DetachedNodes[m_nDetachedPoints].bitLeftLanes = pTempNode[j].byteLeftLanes;
							m_DetachedNodes[m_nDetachedPoints].bitRightLanes = pTempNode[j].byteRightLanes;
							m_DetachedNodes[m_nDetachedPoints].byteTrafficFlags &= 0xFC;
							m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = pTempNode[j].sbMedianWidth;
							DetachedPointsInfo[m_nAttachedPoints] = m_nDetachedPoints;
							m_nDetachedPoints++;
                        }
					}
					m_AttachedPaths[i].bitUnkCount4To7 = m_AttachedPaths[i].bitUnkCount4To7 + 1;
					m_nAttachedPoints++;
				}
			}
		}

		CPathInfoForObject *pPathInfoGroup = &pPathInfosForObject[12 * (-1 - ptempIndices[i])];
        int iGroupNodeIndex = 0;
		int nAdjustedPrevNodes = 0;
		if (nPrevObjectAttachedNodes <=( i -12))
			nAdjustedPrevNodes = i - 12;
		else
			nAdjustedPrevNodes = nPrevObjectAttachedNodes;
		
		for (int k = nAdjustedPrevNodes; k<i;++k)
			if (ptempIndices[i] == ptempIndices[k]) iGroupNodeIndex++;
        int n = nAdjustedPrevNodes;
		
		while (true){
			int nNodesCheck = m_nAttachedNodes;
			if (nNodesCheck >= (i + 12)) nNodesCheck = i+ 12;
			if (n >= nNodesCheck) break;
			if (ptempIndices[i] == ptempIndices[n]){
				if (n != i){
					int iActualNodeInfo = iGroupNodeIndex + n - i; //I had  written 1 instead of i
					if (iActualNodeInfo == pPathInfoGroup[iGroupNodeIndex].sbNextNode ||
						iGroupNodeIndex == pPathInfoGroup[iActualNodeInfo].sbNextNode)
						{
							AttachedPointsInfo[m_nAttachedPoints] = n;
							float fDist = sqrt((float(m_AttachedPaths[i].wX - m_AttachedPaths[n].wX)/8.0f * float(m_AttachedPaths[i].wX - m_AttachedPaths[n].wX)/8.0f) +
										   (float(m_AttachedPaths[i].wY - m_AttachedPaths[n].wY)/8.0f * float(m_AttachedPaths[i].wY - m_AttachedPaths[n].wY)/8.0f) +
										   (float(m_AttachedPaths[i].wZ - m_AttachedPaths[n].wZ)/8.0f * float(m_AttachedPaths[i].wZ - m_AttachedPaths[n].wZ)/8.0f));
							if (fDist > 255.0f) fDist = 255.0f;
							m_InRangedDisplacement[m_nAttachedPoints] = (signed char)fDist;
							if (bytePathDataFor == PATHDATAFOR_PED){
								if (iActualNodeInfo == pPathInfoGroup[iGroupNodeIndex].sbNextNode && //NOT FEELING WELL HERE
									pPathInfoGroup[iGroupNodeIndex].byteFlags & 0x01 ||
								    iGroupNodeIndex == pPathInfoGroup[iActualNodeInfo].sbNextNode &&
								    pPathInfoGroup[iActualNodeInfo].byteFlags & 0x01)
								    {
								    	AttachedPointsInfo[m_nAttachedPoints] |= 0x8000;
								    }
							}
							else {
								float fiCoorX = (float)(m_AttachedPaths[i].wX)/8.0f;
								float fiCoorY = (float)(m_AttachedPaths[i].wY)/8.0f;

								float fjCoorX = (float)(m_AttachedPaths[n].wX)/8.0f;
								float fjCoorY = (float)(m_AttachedPaths[n].wY)/8.0f;

								float fijCoorAvgX = (fjCoorX + fiCoorX)/2.0f;
								float fijCoorAvgY = (fjCoorY + fiCoorY)/2.0f;

								float fijXDiff = fjCoorX - fiCoorX;
								float fijYDiff = fjCoorY - fiCoorY;

								float fLength = sqrt(fijXDiff * fijXDiff + fijYDiff * fijYDiff);
								float VecijNormalX = fijXDiff / fLength;
								float VecijNormalY = fijYDiff / fLength;
								if (i < n ){
									VecijNormalX = -VecijNormalX;
									VecijNormalY = -VecijNormalY;
								}
								int k = 0;
								for (k=0;;++k){
                                    if ( k >= m_nDetachedPoints) break;
									if (m_DetachedNodes[k].NormalVecX == (signed char)(100.0f * VecijNormalX) &&
										m_DetachedNodes[k].NormalVecY == (signed char)(100.0f * VecijNormalY) &&
										m_DetachedNodes[k].wX == (signed short)(8.0f * fijCoorAvgX) &&
										m_DetachedNodes[k].wY == (signed short)(8.0f * fijCoorAvgY))
										{
											DetachedPointsInfo[m_nAttachedPoints] = k;
											k = m_nDetachedPoints;
										}
                                }
								if ( k == m_nDetachedPoints){
									m_DetachedNodes[m_nDetachedPoints].NormalVecX = (signed char)(100.0f * VecijNormalX);
									m_DetachedNodes[m_nDetachedPoints].NormalVecY = (signed char)(100.0f * VecijNormalY);
									m_DetachedNodes[m_nDetachedPoints].wX = (signed short)(8.0f * fijCoorAvgX);
									m_DetachedNodes[m_nDetachedPoints].wY = (signed short)(8.0f * fijCoorAvgY);
									m_DetachedNodes[m_nDetachedPoints].wPathsIndex = i;
									m_DetachedNodes[m_nDetachedPoints].bitLeftLanes = 7; //Max value
									m_DetachedNodes[m_nDetachedPoints].bitRightLanes = 7;
									m_DetachedNodes[m_nDetachedPoints].byteTrafficFlags &= 0xFC;
									if ((unsigned __int8)m_AttachedPaths[n].sbMedianWidth <= m_AttachedPaths[i].sbMedianWidth)
										m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = m_AttachedPaths[i].sbMedianWidth;
									else
										m_DetachedNodes[m_nDetachedPoints].sbMedianWidth = m_AttachedPaths[n].sbMedianWidth;
									DetachedPointsInfo[m_nAttachedPoints] = m_nDetachedPoints;
									++m_nDetachedPoints;
                                }
							}
							m_AttachedPaths[i].bitUnkCount4To7 = m_AttachedPaths[i].bitUnkCount4To7+1;
							++m_nAttachedPoints;
						}
				}
			}
            ++n;
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
                if (m_AttachedPaths[j].bitUnkCount4To7 == 2){
                    int iCurrentDetachedIndex = DetachedPointsInfo[m_AttachedPaths[j].wRouteInfoIndex];
                    int iForwardDetachedIndex = DetachedPointsInfo[m_AttachedPaths[j].wRouteInfoIndex + 1];

                    int iCurrentDetachedLeftLane = m_DetachedNodes[iCurrentDetachedIndex].bitLeftLanes;
                    int iCurrentDetachedRightLane = m_DetachedNodes[iCurrentDetachedIndex].bitRightLanes;
                    int iForwardDetachedLeftLane = m_DetachedNodes[iForwardDetachedIndex].bitLeftLanes;
                    int iForwardDetachedRightLane = m_DetachedNodes[iForwardDetachedIndex].bitRightLanes;
                    
                    int *iCurrentLane1, *iCurrentLane2, *iForwardLane1, *iForwardLane2;
                    if (m_DetachedNodes[iCurrentDetachedIndex].wPathsIndex == j){
                        iCurrentLane1 = &iCurrentDetachedLeftLane;
                        iCurrentLane2 = &iCurrentDetachedRightLane;
                    }
                    else{
                        iCurrentLane1 = &iCurrentDetachedRightLane;
                        iCurrentLane2 = &iCurrentDetachedLeftLane;
                    }
                    if (m_DetachedNodes[iForwardDetachedIndex].wPathsIndex == j){
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
            for (int k = 0; k < m_AttachedPaths[j].bitUnkCount4To7; k++){
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
                    for (int j=0; j<m_AttachedPaths[i].bitUnkCount4To7; j++){
                        if (!m_AttachedPaths[AttachedPointsInfo[j + m_AttachedPaths[i].wRouteInfoIndex] & 0x3FFF].bitUnknownFlag3)
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

    if (bytePathDataFor == PATHDATAFOR_PED){
        while (nPrevObjectAttachedNodes < m_nAttachedNodes){
            if (!m_AttachedPaths[nPrevObjectAttachedNodes].bitUnkCount4To7){
                for (int m = nPrevObjectAttachedNodes; m < (m_nAttachedNodes - 1); m++){
                    m_AttachedPaths[m].wField0x00 = m_AttachedPaths[m+1].wField0x00;
                    m_AttachedPaths[m].wField0x02 = m_AttachedPaths[m+1].wField0x02;
                    m_AttachedPaths[m].wX = m_AttachedPaths[m+1].wX;
                    m_AttachedPaths[m].wY = m_AttachedPaths[m+1].wY;
                    m_AttachedPaths[m].wZ = m_AttachedPaths[m+1].wZ;
                    m_AttachedPaths[m].wUnkDist0x0A = m_AttachedPaths[m+1].wUnkDist0x0A;
                    m_AttachedPaths[m].wRouteInfoIndex = m_AttachedPaths[m+1].wRouteInfoIndex;
                    m_AttachedPaths[m].sbMedianWidth = m_AttachedPaths[m+1].sbMedianWidth;
                    m_AttachedPaths[m].sbField0x0F = m_AttachedPaths[m+1].sbField0x0F;
                    m_AttachedPaths[m].sbMedianWidth = m_AttachedPaths[m+1].sbMedianWidth;
                    m_AttachedPaths[m].bitUnkCount4To7 = m_AttachedPaths[m+1].bitUnkCount4To7;
                    m_AttachedPaths[m].bitUnknownFlag3 = m_AttachedPaths[m+1].bitUnknownFlag3;
                    m_AttachedPaths[m].bitIgnoredNode = m_AttachedPaths[m+1].bitIgnoredNode;
                    m_AttachedPaths[m].bitRestrictedAccess = m_AttachedPaths[m+1].bitRestrictedAccess;
                    m_AttachedPaths[m].bitCopsRoadBlock = m_AttachedPaths[m+1].bitCopsRoadBlock;

	                m_AttachedPaths[m].bitIsVehicleBoat = m_AttachedPaths[m+1].bitIsVehicleBoat;
	                m_AttachedPaths[m].bitHaveUnrandomizedVehClass = m_AttachedPaths[m+1].bitHaveUnrandomizedVehClass;
	                m_AttachedPaths[m].bitUnkFlagFor2 = m_AttachedPaths[m+1].bitUnkFlagFor2;
                    m_AttachedPaths[m].bitSpeedLimit = m_AttachedPaths[m+1].bitSpeedLimit;
                    m_AttachedPaths[m].bitPadFlags8To10 = m_AttachedPaths[m+1].bitPadFlags8To10;
                    m_AttachedPaths[m].byteSpawnRate = m_AttachedPaths[m +1].byteSpawnRate;
                }
                for (int n = nPrevObjectAttachedPoints; n < m_nAttachedPoints;n++){
                    if ((AttachedPointsInfo[n] & 0x3FFF) >= nPrevObjectAttachedNodes)
                        AttachedPointsInfo[n] = (AttachedPointsInfo[n] & 0x3FFF) - 1;
                }
                --nPrevObjectAttachedNodes;
                --m_nAttachedNodes;
            }
            ++nPrevObjectAttachedNodes;
        }
    }
    delete [] ptempIndices;
}
            

CPathNode::CPathNode(){
    memset(this, 0, sizeof(CPathNode));
    wField0x00 = -1;
    wField0x02 = -1;
    sbField0x0F = 0;
    bitUnkFlagFor2 = 0;
    bitPadFlags8To10 = 0;
    byteField0x013 = 0;
    bitUnkCount4To7 = 0;
}

CDetachedNode::CDetachedNode(){
    memset(this, 0, sizeof(CDetachedNode));
}
#endif