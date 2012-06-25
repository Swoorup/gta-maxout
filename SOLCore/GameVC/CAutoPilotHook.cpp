#include "../stdinc.h"

template <> CAutoPilotHook* CSingleton <CAutoPilotHook>::m_pSingleton = NULL;
void CAutoPilotHook::ApplyHookForPaths(void) {
	void (CAutoPilot::*pCAutoPilot_ModifySpeed)(float fModSpeed);

	pCAutoPilot_ModifySpeed = &CAutoPilot::ModifySpeed;
	CMemory::InstallCallHook(0x418CD0, (DWORD)(void*&)pCAutoPilot_ModifySpeed, ASM_JMP);
}