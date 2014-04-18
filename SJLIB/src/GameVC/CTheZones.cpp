#include "SJLIB/stdinc.h"

DWORD dwFunc_CTheZones__CreateZone = 0x04DDB80;
__declspec (naked) void CTheZones::CreateZone(const char* szName, 
                            int iType, 
                            float fX1, 
                            float fY1, 
                            float fZ1,
                            float fX2,
                            float fY2,
                            float fZ2,
                            int iIsland)
{
    __asm jmp dwFunc_CTheZones__CreateZone
}