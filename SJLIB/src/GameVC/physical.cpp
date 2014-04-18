#include "SJLIB/stdinc.h"

void CPhysical::ApplyMoveSpeed()
{
	if (byteCollFlags & 1)
	{
		vecMoveSpeed.fY = vecMoveSpeed.fZ;
		vecMoveSpeed.fX = vecMoveSpeed.fY;
	}
	else
	{
		mat.vPos += vecMoveSpeed * CTimer::get_ms_fTimeStep();
	}
}