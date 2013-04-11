#include "../StdInc.h"

void CEntity::AttachToRwObject(RwObject* rwObject)
{
	_asm
	{
		mov ecx, this
		mov eax, 4897C0h
		push rwObject
		call eax
	}
}