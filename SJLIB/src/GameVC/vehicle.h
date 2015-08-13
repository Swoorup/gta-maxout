#pragma once

#include "SJLIB/stdinc.h"
class CPed;

#pragma pack(push,1)
class CVehicle : public CPhysical
{
public:
	CHandlingVehicle *pHandling;
	void *pAeroHandling;
	CAutoPilot stAutopilot;
	CVehicle* pVehicleToRam;
	char uMainColour;
	char uExtraColour;
	char nSpecialPanel1;
	char nSpecialPanel2;
	__int16 uWantedStarsOnEnter;
	__int16 wMissionValue;
	CPed *pDriver;
	int passangers[8];
	char nPassengerCount;
	char nNumEntering;
	char uEnterSlotsFlags;
	char uExitSlotsFlags;
	char nMaxPassangers;
	char __f01CD[3];
	int nUnusedOne;
	CVector vecUnusedTwo;
	int pColRoad;
	int pFire;
	int fSteerAngle;
	int fAcceleratorPedal;
	int fBrakePedal;
	char uControlState;
	char bfVehFlagsA;
	char bfVehFlagsB;
	char bfVehFlagsC;
	char bfVehFlagsD;
	char bfVehFlagsE;
	char __p01FA[6];
	int fHealth;
	char nCurrentGear;
	char __f0205[3];
	char __p0208[36];
	int uDoorLockedFlags;
	char nDamageType;
	char __f0231[3];
	int pLastDamEntity;
	int nRadio;
	char bHornEnabled;
	char __p023D[4];
	char bSirenEnabled;
	char nSirenExtra;
	char __p0243;
	CCollPoly polyCreatedAt;
	CCollPoly polyCreatedAtCopy;
	int fSteerRatio;
	int nVehicleType;

	void KillPedsInVehicle(void);
	void ProcessCarAlarm(void);
	void ActivateBomb(void);
	void FlyingControl(unsigned int eFlightModel);
};
#pragma pack(pop)