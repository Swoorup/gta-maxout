#include "../StdInc.h"

CSectorList& CWorld::stSectorList = *(CSectorList*)0x792D30;

DWORD dwFunc_CWorld_GetIsLineOfSightClear = 0x4DA560;
DWORD dwFunc_CWorld_FindGroundZFor3DCoord = 0x4D53A0;

_declspec (naked) bool CWorld::GetIsLineOfSightClear(CVector *a, CVector *b,unsigned char cc , unsigned char dc , unsigned char ec , unsigned char fc, unsigned char gc, unsigned char hcc, unsigned char ic)
{
    _asm jmp dwFunc_CWorld_GetIsLineOfSightClear
}

_declspec (naked) float CWorld::FindGroundZFor3DCoord(float fX, float fY, float fZ, bool* bOutDoesGroundExist)
{
    _asm jmp dwFunc_CWorld_FindGroundZFor3DCoord
}
