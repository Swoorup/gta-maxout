#ifndef VEHICLE_H
#define VEHICLE_h

#include "../StdInc.h"

#pragma pack(push,1)
class CVehicle
{
public:
	int pfnVMT;
	CVehicleR _;

	void KillPedsInVehicle(void);
	void ProcessCarAlarm(void);
	void ActivateBomb(void);
	void FlyingControl(unsigned int eFlightModel);
};
#pragma pack(pop)
#endif