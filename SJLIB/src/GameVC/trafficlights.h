#include "SJLIB/stdinc.h"

#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#pragma pack(push,1)

#define TL_GREENLIGHT 0
#define TL_YELLOWLIGHT 1
#define TL_REDLIGHT 2

class CTrafficLights
{
public:
	static bool& bGreenLightsCheatPx;

	static uint8_t LightsForCars1(void);
	static uint8_t LightsForCars2(void);
	static void _cdecl ScanForLightsOnMapN(void);
	static bool _cdecl ShouldCarStopForLightN(CVehicle* pVeh, bool bCheck);

	
};

#pragma pack(pop)
#endif