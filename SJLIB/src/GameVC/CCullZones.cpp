#include "SJLIB/stdinc.h"

DWORD dwFunc_CCullZones__AddCullZone = 0x0057E330;

__declspec (naked) int CCullZones::AddCullZone(CVector& Center,
                  float LowerLeft_X,
                  float UpperRight_X,
                  float LowerLeft_Y,
                  float UpperRight_Y,
                  float LowerLeft_Z,
                  float UpperRight_Z,
                  uint32_t dwFlags,
                  int iUnk)
{
    __asm jmp dwFunc_CCullZones__AddCullZone
}