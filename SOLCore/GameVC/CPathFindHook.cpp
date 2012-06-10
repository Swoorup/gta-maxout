#include "../StdInc.h"


template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;
CPathFindHook::CPathFindHook( void){
}

CPathFindHook::~CPathFindHook(void){
    RemoveHook();
}

void (CPathFind::*p_mPreparePathDataForType)(uint8_t bytePathDataFor, 
                            CTempNode* pTempNode, 
                            CPathInfoForObject* pUnusedPathInfos, 
                            float fUnkRange, 
                            CPathInfoForObject* pPathInfosForObject,
                            int nGroupNodesForObject);
void (CPathFind::*p_mInit)(void);
void (CPathFind::*p_mAllocatePathFindInfoMem)(void);
void (CPathFind::*p_mPreparePathData)(void);
void (CPathFind::*p_mDoPathSearch)(int iPathDataFor, 
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
										int iLastNode);
int (CPathFind::*p_mFindNodeClosestToCoors)(float fX, 
                             float fY, 
                             float fZ, 
                             unsigned char iPathDataFor, 
                             float fRangeCoefficient, 
                             bool bCheckIgnored, 
                             bool bCheckRestrictedAccess, 
                             bool bCheckUnkFlagFor2, 
                             bool bIsVehicleBoat);
void (CPathFind::*p_mRemoveNodeFromList)(CPathNode *pRemoveNode);
void (CPathFind::*p_mAddNodeToList)(CPathNode *pTargetNode, int iParamDisplacement);
void (CPathFind::*p_mRemoveBadStartNode)(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps);
void (CPathFind::*p_mFindNextNodeWandering)(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection);

//---------------------------------------------------------------------
// List Of Functions Hooked
// i.   CPathFind::Init                 -FINE GRAINED
// ii.  CPathFind::PreparePathDataForType-THOROUGH REVISION AND DUMP TEST NEEDED
// iii. CPathFind::StoreNodeInfoPed     -FINE GRAINED
// iv.  CPathFind::StoreNodeInfoCar     -FINE GRAINED
// v.   CPathFind::ArrangeOneNodeList   -FINE GRAINED
// vi.  CFileLoader::LoadScene          -FINE GRAINED
// vii. CPathFind::PreparePathData      -FINE GRAINED
// viii.CPathFind::AllocatePathFindInfoMem- FINE GRAINED
// ix.  CPathFind::AddNodeToList        - FINE GRAINED
// x.   CPathFind::RemoveNodeFromList   - FINE GRAINED
// xi.  CPathFind::FindNodeToCoors      - REVISION NEEDED
// xii. CPathFind::DoPathSearch         - REVISION NEEDED
// xiii.CPathFind::RemoveBadStartNode   - REVISION DONE
// xiv. CPathFind::FindNextNodeWandering -REVISION NEEDED
//---------------------------------------------------------------------

void TEMPTESTPATCH(){
    //CMemory::NoOperation(0x4391ED, 11); // Disable CPathFind::AddNodeToList
    //CMemory::NoOperation(0x439311, 9);  // Disable CPathFind::AddNodeToList
}

void CPathFindHook::ApplyHook(){
    p_mDoPathSearch = &CPathFind::DoPathSearch;
    p_mFindNodeClosestToCoors = &CPathFind::FindNodeClosestToCoors;
    p_mRemoveNodeFromList = &CPathFind::RemoveNodeFromList;
    p_mAddNodeToList = &CPathFind::AddNodeToList;
    p_mRemoveBadStartNode = &CPathFind::RemoveBadStartNode;
    p_mFindNextNodeWandering = &CPathFind::FindNextNodeWandering;

    // Disable Unused CPathFind Treadables in CFileLoader::LoadObjectInstance
    CMemory::NoOperation(0x48AE30, 44);

    // Hooks in CGame::Init
    p_mInit = &CPathFind::Init;
    CMemory::InstallCallHook(0x4A4C0C, (DWORD)(void*&)p_mInit, ASM_CALL);

    p_mAllocatePathFindInfoMem = &CPathFind::AllocatePathFindInfoMem;
    CMemory::NoOperation(0x4A4C16, 5); // Remove One Unused Parameter
    CMemory::InstallCallHook(0x4A4C1B, (DWORD)(void*&)p_mAllocatePathFindInfoMem, ASM_CALL);

    p_mPreparePathData = &CPathFind::PreparePathData;
    CMemory::InstallCallHook(0x4A4CE7, (DWORD)(void*&)p_mPreparePathData, ASM_CALL);

    CMemory::InstallCallHook(0x439070, (DWORD)(void*&)p_mDoPathSearch, ASM_JMP);
    CMemory::InstallCallHook(0x437150, (DWORD)(void*&)p_mFindNodeClosestToCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437330, (DWORD)(void*&)p_mAddNodeToList, ASM_JMP);
    CMemory::InstallCallHook(0x4375C0, (DWORD)(void*&)p_mRemoveNodeFromList, ASM_JMP);
    CMemory::InstallCallHook(0x438F90, (DWORD)(void*&)p_mRemoveBadStartNode , ASM_JMP);
    CMemory::InstallCallHook(0x4386D0, (DWORD)(void*&)p_mFindNextNodeWandering, ASM_JMP);

    // Install PreparePathDataHook
    p_mPreparePathDataForType = &CPathFind::PreparePathDataForType;
    CMemory::InstallCallHook(0x43BF3C, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL);
    CMemory::InstallCallHook(0x43BF74, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL);
    TEMPTESTPATCH();
}

void CPathFindHook::RemoveHook(){
}