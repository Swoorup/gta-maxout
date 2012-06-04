#ifndef CMEMORY_H
#define CMEMORY_H

#include <windows.h>

#define ASM_CALL 0xE8
#define ASM_JMP  0xE9

class CMemory{
public:
    static void NoOperation(DWORD Addr, DWORD dwNopBytes);
    static DWORD UnProtect(DWORD dwAddress, DWORD dwUnProtectBytes);
    static void RestoreProtection(DWORD dwAddress, DWORD dwProtBytes, DWORD dwProt);
    static void InstallCallHook(DWORD dwAddress, DWORD dwCallTarget, BYTE bCallByte);

    template <class Type> // this is the template parameter declaration
    static void InstallPatch(DWORD dwAddress, Type patchData){ //This isn't actually a real function. Its a template so it gets instiantiated
        DWORD dwProt;
        VirtualProtect((void*)dwAddress, sizeof(patchData), PAGE_EXECUTE_READWRITE, &dwProt);
        *(Type*)dwAddress = patchData;
        VirtualProtect((void*)dwAddress, sizeof(patchData), dwProt, &dwProt);
    }
};

void UnProtect(DWORD dwAddress, DWORD dwUnProtectBytes);
void InstallHook(DWORD dwAddress, DWORD dwFunctionAddr, DWORD dwFunctionAddrPtr, BYTE* bCode, int iCodeSize);
void InstallMethodHook(DWORD dwAddress, DWORD dwFunctionAddr);
#endif
