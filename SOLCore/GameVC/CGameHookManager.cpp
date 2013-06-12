#include "../StdInc.h"

extern DWORD dwFunc_CFileLoader__LoadScene;
using namespace HookSystem;


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
    
    // Hooked in CGame::InitializeRenderware
    InstallFnByCall( 0x4A5298, &CDebug::Initialize);
    // Hooked in Idle(void*)
    InstallFnByCall( 0x4A614C, &CDebug::DebugDisplayText);
    // Hooked in CGame::ShutdownRenderware
    InstallFnByCall( 0x4A5140, &CDebug::Shutdown);
    // Hooked in Nullsub1 leftover
    InstallFnByJump(0x401000, &CDebug::DebugAddText); 
    // Hooked in Nullsub16 leftover
    InstallFnByJump(0x48A270, &CDebug::DebugAddText); 
    // Hooked in printf leftover
    InstallFnByJump(0x648AC0, &CDebug::DebugAddText); 

    m_pPathFindHook->ApplyHook();
}

void CGameHookManager::RemoveHook(void){
    //Restore in CFileLoader::LoadLevel
    InstallFnByCall( 0x48DD5D, (void*)dwFunc_CFileLoader__LoadScene);
    //Restore NullSub1
    CMemory::InstallPatch<char>(0x401000, 0xC3);
    //Restore Nullsub16
    CMemory::InstallPatch<char>(0x48A270, 0xC3);
    //Restore printf
    CMemory::InstallPatch<char>(0x648AC0, 0xC3);
}