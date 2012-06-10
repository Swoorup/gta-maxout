#include "../StdInc.h"

DWORD dwFunc_CWorld__GetIsLineOfSightClear = 0x4DA560;

__declspec (naked) bool CWorld::GetIsLineOfSightClear(CVector *a, CVector *b,unsigned char cc , unsigned char dc , unsigned char ec , unsigned char fc, unsigned char gc, unsigned char hcc, unsigned char ic){
    __asm jmp dwFunc_CWorld__GetIsLineOfSightClear
}