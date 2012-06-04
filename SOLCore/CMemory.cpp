#include "CMemory.h"

void CMemory::NoOperation(DWORD dwAddress, DWORD dwNopBytes){
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, dwNopBytes, PAGE_EXECUTE_READWRITE, &dwProt);
	memset((void*)(dwAddress), 0x90, dwNopBytes);
	VirtualProtect((void*)dwAddress, dwNopBytes, dwProt, &dwProt);
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

void CMemory::InstallCallHook(DWORD dwAddress, DWORD dwCallTarget, BYTE bCallByte){
	DWORD dwProt;
	VirtualProtect((void*)dwAddress, 5, PAGE_EXECUTE_READWRITE, &dwProt);
	*(BYTE*)dwAddress = bCallByte;
	*(DWORD*)(dwAddress+1) = dwCallTarget-dwAddress-0x5;
	VirtualProtect((void*)dwAddress, 5, dwProt, &dwProt);
}

void InstallHook(DWORD dwAddress, DWORD dwFunctionAddr, DWORD dwFunctionAddrPtr, BYTE* bCode, int iCodeSize){ //Needs thorough testing
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, iCodeSize, PAGE_EXECUTE_READWRITE, &dwProt);
	for (int i = 0; i<iCodeSize; i++){
	    *(BYTE*)(dwAddress + i) = bCode[i];
	}
	VirtualProtect((void*)dwFunctionAddr, 4, PAGE_EXECUTE_READWRITE, &dwProt);
	*(DWORD*)dwFunctionAddrPtr = dwFunctionAddr;
	VirtualProtect((void*)dwAddress, iCodeSize, dwProt, &dwProt);
}

void UnProtect(DWORD dwAddress, DWORD dwUnProtectBytes){
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, dwUnProtectBytes, PAGE_EXECUTE_READWRITE, &dwProt);
}

void InstallMethodHook(DWORD dwAddress, DWORD dwFunctionAddr){ //Need to check this dwFunctionAddr should actually be an offset not address directly
    DWORD dwProt;
	VirtualProtect((void*)dwAddress, 5, PAGE_EXECUTE_READWRITE, &dwProt);
	*(DWORD*)dwAddress =  dwFunctionAddr;
	VirtualProtect((void*)dwAddress, 5, dwProt, &dwProt);
}
