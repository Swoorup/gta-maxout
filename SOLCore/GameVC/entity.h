#ifndef ENTITY_H
#define ENTITY_H

#include "CommonDefinations.h"

#pragma pack(push,1)
class CEntity
{
public:
	int pfnVMT;
	CEntityR _;

	void AttachToRwObject(RwObject *);
};
#pragma pack(pop)
#endif