#include "../StdInc.h"

template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;

CPathFind* pThePaths = NULL;

CPathFindHook::CPathFindHook() {
    //pThePaths = new CPathFind();   
    pThePaths = (CPathFind*)0x9B6E5C;
}

CPathFindHook::~CPathFindHook() {
    RemoveHook();
    //delete pThePaths;
    //pThePaths = NULL;
}

int _nHookDetachedNodeIndex;
CPathNode* _pHookPathNode;
wchar_t* _pwszHookString;
int* _pHookEditValue;
void* _pHookReturn;
DWORD _dwIndexWithSize;
DWORD _dwHookArgOne, _dwHookArgTwo;
CPathFind* _pHookPathFind;
CDetachedNode* _pHookDetachedNode;
DWORD _dwHookLocal;
float _fHookFloatOne, _fHookFloatTwo;
int _nHookReturn;
#define ASMJMP(x) {_asm push x _asm retn} 

//-----------------------------------------------------------
// These are hooks inside CAutopilot::ModifySpeed. They make
// sure the coordinates values are calculated properly with 
// the new path system
//-----------------------------------------------------------

//418D48
void _declspec(naked) HookGetDetachedNormalComponentXOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad
    
    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecX;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov ecx, _dwIndexWithSize
    _asm mov eax, _nHookReturn
    ASMJMP(418D59h)
}

//418D68
void _declspec(naked) HookGetDetachedYCoorOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.0099999998f;
    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm fmul _fHookFloatOne
    _asm mov eax, _nHookReturn
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(418D80h)
}

//418DAA
void _declspec(naked) HookGetDetachedNormalComponentXTwo(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad
    
    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize / sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DB1h)
}

//418DCB
void _declspec(naked) HookGetDetachedXCoorOne(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DD2h)
}

//418DEF
void _declspec(naked) HookGetDetachedNormalYOne(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DF6h)
}

//418E21
void _declspec(naked) HookGetDetachedYCoorTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov edx, _dwIndexWithSize
    ASMJMP(418E32h)
}

//418E48
void _declspec(naked) HookGetDetachedXCoorTwo(void) {
    _asm mov _dwIndexWithSize, edx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418E4Fh)
}

//418E7C
void _declspec(naked) HookGetDetachedNormalYTwo(void) {
    _asm mov _dwIndexWithSize, ecx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418E83h)
}

//418EB8
void _declspec(naked) HookGetDetachedNormalYThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(418ECAh)
}

//418EE9
void _declspec(naked) HookGetDetachedNormalXThree(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418EF0h)
}

//418F15
void _declspec(naked) HookGetDetachedNormalYFour(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov edx, _dwIndexWithSize
    ASMJMP(418F26h)
}

//418F45
void _declspec(naked) HookGetDetachedNormalXFour(void) {
    _asm mov _dwIndexWithSize, edx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418F4Ch)
}

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
// 20. CPathFind::TestCrossesRoad
// 21. CPathFind::TestForPedTrafficLight
//-------------------------------------------------------------------------------

void CPathFindHook::ApplyHook(){
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
    bool (CPathFind::*p_mTestCrossesRoad)(CPathNode* pStartNode, CPathNode* pConnectedNode);
    bool (CPathFind::*p_mTestForPedTrafficLight)(CPathNode* pStartNode, CPathNode* pConnectedNode);

    float (CDetachedNode::*p_mCalculateLaneDistance)();
    // CDetachedNode::CalculateLaneDistance - REVISION NEEDED

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
    p_mTestCrossesRoad = &CPathFind::TestCrossesRoad;
    p_mTestForPedTrafficLight = &CPathFind::TestForPedTrafficLight;

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
    CMemory::InstallCallHook(0x4354E0, (DWORD)(void*&)p_mTestCrossesRoad, ASM_JMP);
    CMemory::InstallCallHook(0x4356B0, (DWORD)(void*&)p_mTestForPedTrafficLight, ASM_JMP);

    CMemory::InstallCallHook(0x434EB0, (DWORD)(void*&)p_mCalculateLaneDistance, ASM_JMP);
    CMemory::InstallCallHook(0x435140, (DWORD)&CPedPath::CalculateBestRandomCoors, ASM_JMP);
    CMemory::InstallCallHook(0x4351C0, (DWORD)&CPedPath::CalculateRandomCoordinates, ASM_JMP);
    
    // Hooks inside CAutopilot::ModifySpeed
    CMemory::InstallCallHook(0x418D48, (DWORD)HookGetDetachedNormalComponentXOne, ASM_JMP);
    CMemory::InstallCallHook(0x418D68, (DWORD)HookGetDetachedYCoorOne, ASM_JMP);
    CMemory::InstallCallHook(0x418DAA, (DWORD)HookGetDetachedNormalComponentXTwo, ASM_JMP);
    CMemory::InstallCallHook(0x418DCB, (DWORD)HookGetDetachedXCoorOne, ASM_JMP);
    CMemory::InstallCallHook(0x418DEF, (DWORD)HookGetDetachedNormalYOne, ASM_JMP);
    CMemory::InstallCallHook(0x418E21, (DWORD)HookGetDetachedYCoorTwo, ASM_JMP);
    CMemory::InstallCallHook(0x418E48, (DWORD)HookGetDetachedXCoorTwo, ASM_JMP);
    CMemory::InstallCallHook(0x418E7C, (DWORD)HookGetDetachedNormalYTwo, ASM_JMP);
    CMemory::InstallCallHook(0x418EB8, (DWORD)HookGetDetachedNormalYThree, ASM_JMP);
    CMemory::InstallCallHook(0x418EE9, (DWORD)HookGetDetachedNormalXThree, ASM_JMP);
    CMemory::InstallCallHook(0x418F15, (DWORD)HookGetDetachedNormalYFour, ASM_JMP);
    CMemory::InstallCallHook(0x418F45, (DWORD)HookGetDetachedNormalXFour, ASM_JMP);
}

void CPathFindHook::RemoveHook(){
}