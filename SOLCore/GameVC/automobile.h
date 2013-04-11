#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include "CommonDefinations.h"


#pragma pack(push, 1)
class CAutomobile
{
public:
	CAutomobile_vtbl* pfnVMT;
	CAutomobileR _;

	void PlayHornIfNecessary();
	bool HasCarStoppedBecauseOfLight();
	void PlayCarHorn(void);
	void BlowUpCar(CEntity* ent);
	void BurstTyre(unsigned char uUnk, bool bUnk);
};

#pragma pack(pop)

#endif