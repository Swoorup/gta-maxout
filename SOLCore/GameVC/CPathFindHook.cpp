#include "../StdInc.h"

template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;
CPathFindHook::CPathFindHook( void){
}

CPathFindHook::~CPathFindHook(void){
    RemoveHook();
}

void (CPathFind::*p_mPreparePathDataForType)(uint8_t bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject);
void (CPathFind::*p_mInit)(void);
void (CPathFind::*p_mAllocatePathFindInfoMem)(void);
void (CPathFind::*p_mPreparePathData)(void);
void (CPathFind::*p_mDoPathSearch)(int iPathDataFor, float fOriginX, float fOriginY, float fOriginZ, int iFirstNode, float fDestX, float fDestY, float fDestZ, CPathNode **pIntermediateNodeList, short *pSteps, short sMaxSteps, void *pVehicle, float *pfDistance, float fMaxRadius, int iLastNode); //pVehicle, pfDistance and iLastNode are ununsed
int (CPathFind::*p_mFindNodeClosestToCoors)(float fX, float fY, float fZ, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat);
void (CPathFind::*p_mRemoveNodeFromList)(CPathNode *pRemoveNode);
void (CPathFind::*p_mAddNodeToList)(CPathNode *pTargetNode, int iParamDisplacement);
void (CPathFind::*p_mRemoveBadStartNode)(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps);
void (CPathFind::*p_mFindNextNodeWandering)(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection);
bool (CPathFind::*p_mNewGenerateCarCreationCoors)(float fX, float fY, float fDirectionVecX, float fDirectionVecY, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored);
bool (CPathFind::*p_mGeneratePedCreationCoors)(float fX, float fY, float fRangeForRand, float fRange, float fRange1, float fRange2, CVector *pVecOutPosition, int *aStartNodeIndex, int *aFollowNodeIndex, float *frand, RwMatrix *rwMatrix);
bool (CPathFind::*p_mTestCoorsCloseness)(float fDestinationX, float fDestinationY, float fDestinationZ, uint8_t uiPathDataFor, float fOriginX, float fOriginY, float fOriginZ);
float (CPathFind::*p_mCalcRoadDensity)(float fX, float fY);
int (CPathFind::*p_mFindNodeClosestToCoorsFavourDirection)(float fX, float fY, float fZ, uint8_t uiPathDataFor, float fLookAtX, float fLookAtY);
//-----------------------------------------------------------------------------
// List Of Functions Hooked
// 1.  CPathFind::Init                 -FINE GRAINED
// 2.  CPathFind::PreparePathDataForType-THOROUGH REVISION AND DUMP TEST NEEDED
// 3.  CPathFind::StoreNodeInfoPed     -FINE GRAINED
// 4.  CPathFind::StoreNodeInfoCar     -FINE GRAINED
// 5.  CPathFind::ArrangeOneNodeList   -FINE GRAINED
// 6.  CFileLoader::LoadScene          -FINE GRAINED
// 7.  CPathFind::PreparePathData      -FINE GRAINED
// 8.  CPathFind::AllocatePathFindInfoMem- FINE GRAINED
// 9.  CPathFind::AddNodeToList - FINE GRAINED
// 10. CPathFind::RemoveNodeFromList - FINE GRAINED
// 11. CPathFind::FindNodeClosestToCoors - REVISION NEEDED
//          -can be optimized by setting up a grid system.
//          -work is needed in improving generation per calls
// 12. CPathFind::DoPathSearch - REVISION NEEDED
// 13. CPathFind::RemoveBadStartNode   - REVISION DONE
// 14. CPathFind::FindNextNodeWandering -REVISION NEEDED
// 15. CPathFind::NewGenerateCarCreationCoors - Optimization needed, finding new nodes - work is needed in improving generation per calls
// 16. CPathFind::GeneratePedCreationCoors - FINE GRAINED - work is needed in improving generation per calls
// 17. CPathFind::TestCoorsCloseness - FINE GRAINED
// 18. CPathFind::CalcRoadDensity - FINE GRAINED
//          This functions calculates the sum of displacement between car nodes inside an area.
//          The number is the divided by the area of the game (2500.0) to get the actual density
// 19. CPathFind::FindNodeClosestToCoorsFavourDirection - REVISION NEEEDED
//          This function calculates the nearest node favouring the direction an entity is heading
//          or if not specified the x/straight direction of the entity
//          -can be optimized using a grid system
//-------------------------------------------------------------------------------

float (CDetachedNode::*p_mCalculateLaneDistance)();
// CDetachedNode::CalculateLaneDistance - REVISION NEEDED
void TemporaryTest(){
}

void CPathFindHook::ApplyHook(){
    p_mInit = &CPathFind::Init;
    p_mAllocatePathFindInfoMem = &CPathFind::AllocatePathFindInfoMem;
    p_mPreparePathData = &CPathFind::PreparePathData;
    p_mPreparePathDataForType = &CPathFind::PreparePathDataForType;

    p_mDoPathSearch = &CPathFind::DoPathSearch;
    p_mFindNodeClosestToCoors = &CPathFind::FindNodeClosestToCoors;
    p_mRemoveNodeFromList = &CPathFind::RemoveNodeFromList;
    p_mAddNodeToList = &CPathFind::AddNodeToList;
    p_mRemoveBadStartNode = &CPathFind::RemoveBadStartNode;
    p_mFindNextNodeWandering = &CPathFind::FindNextNodeWandering;
    p_mNewGenerateCarCreationCoors = &CPathFind::NewGenerateCarCreationCoors;
    p_mGeneratePedCreationCoors = &CPathFind::GeneratePedCreationCoors;
    p_mTestCoorsCloseness = &CPathFind::TestCoorsCloseness;
    p_mCalcRoadDensity = &CPathFind::CalcRoadDensity;
    p_mFindNodeClosestToCoorsFavourDirection = &CPathFind::FindNodeClosestToCoorsFavourDirection;

    p_mCalculateLaneDistance = &CDetachedNode::CalculateLaneDistance;
    // Disable Unused CPathFind Treadables in CFileLoader::LoadObjectInstance
    CMemory::NoOperation(0x48AE30, 44);
    // Hooks in CGame::Init
    CMemory::InstallCallHook(0x4A4C0C, (DWORD)(void*&)p_mInit, ASM_CALL);

    CMemory::NoOperation(0x4A4C16, 5); // Remove One Unused Parameter
    CMemory::InstallCallHook(0x4A4C1B, (DWORD)(void*&)p_mAllocatePathFindInfoMem, ASM_CALL);    
    CMemory::InstallCallHook(0x4A4CE7, (DWORD)(void*&)p_mPreparePathData, ASM_CALL);
    // Install PreparePathDataHook
    CMemory::InstallCallHook(0x43BF3C, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL);
    CMemory::InstallCallHook(0x43BF74, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL);

    CMemory::InstallCallHook(0x439070, (DWORD)(void*&)p_mDoPathSearch, ASM_JMP);
    CMemory::InstallCallHook(0x437150, (DWORD)(void*&)p_mFindNodeClosestToCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437330, (DWORD)(void*&)p_mAddNodeToList, ASM_JMP);
    CMemory::InstallCallHook(0x4375C0, (DWORD)(void*&)p_mRemoveNodeFromList, ASM_JMP);
    CMemory::InstallCallHook(0x438F90, (DWORD)(void*&)p_mRemoveBadStartNode , ASM_JMP);
    CMemory::InstallCallHook(0x4386D0, (DWORD)(void*&)p_mFindNextNodeWandering, ASM_JMP);
    CMemory::InstallCallHook(0x4382B0, (DWORD)(void*&)p_mNewGenerateCarCreationCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437B10, (DWORD)(void*&)p_mGeneratePedCreationCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437A40, (DWORD)(void*&)p_mTestCoorsCloseness, ASM_JMP);
    CMemory::InstallCallHook(0x4377F0, (DWORD)(void*&)p_mCalcRoadDensity, ASM_JMP);
    CMemory::InstallCallHook(0x436E40, (DWORD)(void*&)p_mFindNodeClosestToCoorsFavourDirection, ASM_JMP);

    CMemory::InstallCallHook(0x434EB0, (DWORD)(void*&)p_mCalculateLaneDistance, ASM_JMP);
    TemporaryTest();
}

void CPathFindHook::RemoveHook(){
}