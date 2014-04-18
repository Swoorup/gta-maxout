#include "SJLIB/stdinc.h"

namespace HookSystem
{	
	void InstallNOPs(uint32_t vAddress, int nNOPs)
	{
		DWORD dwProt;
		VirtualProtect((void*)vAddress, nNOPs, PAGE_EXECUTE_READWRITE, &dwProt);
		memset((void*)vAddress, 0x90, nNOPs);
		VirtualProtect((void*)vAddress, nNOPs, dwProt, &dwProt);
	}
	
	void InstallFnByCall(unsigned int vAddress, void* pFnToCall)
	{
		DWORD dwProt;
		VirtualProtect((void*)vAddress, 5, PAGE_EXECUTE_READWRITE, &dwProt);
		*(byte*)vAddress = 0xE8;
		*(DWORD*)(vAddress+1)=(uint32_t)pFnToCall - vAddress- 0x05;
		VirtualProtect((void*)vAddress, 5, dwProt, &dwProt);
	}
	
	void InstallFnByJump(uint32_t vAddress, void* pFnToCall)
	{
		DWORD dwProt;
		VirtualProtect((void*)vAddress, 5, PAGE_EXECUTE_READWRITE, &dwProt);
		*(byte*)vAddress = 0xE9;
		*(DWORD*)(vAddress+1)=(uint32_t)pFnToCall - vAddress- 0x05;
		VirtualProtect((void*)vAddress, 5, dwProt, &dwProt);
	}
}

DWORD CMemory::UnProtect(DWORD dwAddress, DWORD dwUnProtectBytes){
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, dwUnProtectBytes, PAGE_EXECUTE_READWRITE, &dwProt);
	return dwProt;
}

void CMemory::RestoreProtection(DWORD dwAddress, DWORD dwProtBytes, DWORD dwProt){
    DWORD dwPrevProt;
	VirtualProtect((void*)dwAddress, dwProtBytes, dwProt, &dwPrevProt);
}

void CMemory::InstallHook(DWORD dwAddress, DWORD dwFunctionAddr, DWORD dwFunctionAddrPtr, BYTE* bCode, int iCodeSize){ //Needs thorough testing
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, iCodeSize, PAGE_EXECUTE_READWRITE, &dwProt);
	for (int i = 0; i<iCodeSize; i++){
	    *(BYTE*)(dwAddress + i) = bCode[i];
	}
	VirtualProtect((void*)dwFunctionAddr, 4, PAGE_EXECUTE_READWRITE, &dwProt);
	*(DWORD*)dwFunctionAddrPtr = dwFunctionAddr;
	VirtualProtect((void*)dwAddress, iCodeSize, dwProt, &dwProt);
}