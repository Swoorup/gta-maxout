#pragma once
#include <stdint.h>
#include <windows.h>
namespace HookSystem
{
	
	
	void InstallNOPs(uint32_t vAddress, int nNOPs);
	void InstallFnByCall(unsigned int vAddress, void* pFnToCall);
	void InstallFnByJump(uint32_t vAddress, void* pFnToCall);
};

#include <Windows.h>
class CMemory
{
public:
	 template <class Type> // this is the template parameter declaration
    static void InstallPatch(DWORD dwAddress, Type patchData){ //This isn't actually a real function. Its a template so it gets instiantiated
        DWORD dwProt;
        VirtualProtect((void*)dwAddress, sizeof(patchData), PAGE_EXECUTE_READWRITE, &dwProt);
        *(Type*)dwAddress = patchData;
        VirtualProtect((void*)dwAddress, sizeof(patchData), dwProt, &dwProt);
    }
	static DWORD UnProtect(DWORD dwAddress, DWORD dwUnProtectBytes);
	static void RestoreProtection(DWORD dwAddress, DWORD dwProtBytes, DWORD dwProt);
	static void InstallHook(DWORD dwAddress, DWORD dwFunctionAddr, DWORD dwFunctionAddrPtr, BYTE* bCode, int iCodeSize);
};