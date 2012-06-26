#include "../StdInc.h"

extern DWORD dwFunc_CFileLoader__LoadScene;


template<> CGameHookManager * CSingleton<CGameHookManager>::m_pSingleton = NULL;
CGameHookManager::CGameHookManager( void){
    m_pPathFindHook = new CPathFindHook();
}

//---------------------------------------------------------------
// This is a self maintaining code. It removes the applied hook
// when the class is deleted.
//---------------------------------------------------------------
CGameHookManager::~CGameHookManager(void){
    RemoveHook();
    delete m_pPathFindHook;
}


void CGameHookManager::ApplyHook(void){
    // Hooked in CFileLoader::LoadLevel
    CMemory::InstallCallHook( 0x48DD5D, &CFileLoader::LoadScene, ASM_CALL);
    // Hooked in CGame::InitializeRenderware
    CMemory::InstallCallHook( 0x4A5298, &CDebug::Initialize, ASM_CALL);
    // Hooked in Idle(void*)
    CMemory::InstallCallHook( 0x4A614C, &CDebug::DebugDisplayText, ASM_CALL);
    // Hooked in CGame::ShutdownRenderware
    CMemory::InstallCallHook( 0x4A5140, &CDebug::Shutdown, ASM_CALL);
    // Hooked in Nullsub1 leftover
    CMemory::InstallCallHook(0x401000, &CDebug::DebugAddText, ASM_JMP); 
    // Hooked in Nullsub16 leftover
    CMemory::InstallCallHook(0x48A270, &CDebug::DebugAddText, ASM_JMP); 
    // Hooked in printf leftover
    CMemory::InstallCallHook(0x648AC0, &CDebug::DebugAddText, ASM_JMP); 

    m_pPathFindHook->ApplyHook();
}

void CGameHookManager::RemoveHook(void){
    //Restore in CFileLoader::LoadLevel
    CMemory::InstallCallHook( 0x48DD5D, (void*)dwFunc_CFileLoader__LoadScene, ASM_CALL);
    //Restore NullSub1
    CMemory::InstallPatch<char>(0x401000, 0xC3);
    //Restore Nullsub16
    CMemory::InstallPatch<char>(0x48A270, 0xC3);
    //Restore printf
    CMemory::InstallPatch<char>(0x648AC0, 0xC3);
}