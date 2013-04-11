#include "../StdInc.h"

void CVehicle::KillPedsInVehicle(void)
{
	_asm
	{
		mov ecx, this
		mov eax, 5B8560h
		call eax
	}
}

void CVehicle::ProcessCarAlarm(void)
{
	_asm 
	{
		mov ecx, this
		mov eax, 5B8040h
		call eax
	}
}

void CVehicle::ActivateBomb(void)
{
	_asm
	{
		mov ecx, this
		mov eax, 5B79E0h
		call eax
	}
}

void CVehicle::FlyingControl(unsigned int eFlightModel)
{
	_asm
	{
		mov ecx, this
		mov eax, 5B54C0h
		push eFlightModel
		call eax
	}
}