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


//---------------------------------------------------------------------
// List Of Functions Hooked
// i.   CPathFind::Init
// ii.  CPathFind::PreparePathDataForType
// iii. CPathFind::StoreNodeInfoPed
// iv.  CPathFind::StoreNodeInfoCar
// v.   CPathFind::ArrangeOneNodeList
// vi.  CFileLoader::LoadScene
// vii. CPathFind::PreparePathData
// viii.CPathFind::AllocatePathFindInfoMem
//---------------------------------------------------------------------

void TEMPTESTPATCH(){
    //CMemory::NoOperation(0x4391ED, 11); // Disable CPathFind::AddNodeToList
    //CMemory::NoOperation(0x439311, 9);  // Disable CPathFind::AddNodeToList
}

void CPathFindHook::ApplyHook(){
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

    // Install PreparePathDataHook
    p_mPreparePathDataForType = &CPathFind::PreparePathDataForType;
    CMemory::InstallCallHook(0x43BF3C, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL); // a very tricky cast
    CMemory::InstallCallHook(0x43BF74, (DWORD)(void*&)p_mPreparePathDataForType, ASM_CALL);
    TEMPTESTPATCH();
    
}

void CPathFindHook::RemoveHook(){
}