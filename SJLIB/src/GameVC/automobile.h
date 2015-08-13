#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include "SJLIB\stdinc.h"
#include "CommonDefinations.h"
#include "vehicle.h"

#pragma pack(push, 1)
class CAutomobile
{
public:
	CVehicle veh;
	CDamageManager stDamage;
	char bDamSwitch;
	char __f02B5[3];
	CDoor stDoors[6];
	int pVehComponents[20];
	CWheel stWheels[4];
	int fWheelSuspDist[4];
	int fWheelSuspDistSoft[4];
	int fWheelContactRate[4];
	char __p04B0[28];
	int fWheelTotalRot[4];
	int fWheelRot[4];
	char __p04EC[4];
	int fNegSpeed;
	char __p04F4[9];
	char bfFlagsX;
	char __p04FE[46];
	int fWheelAngleMul;
	int fAIGripMultiplier;
	char __p0534[120];
	int fSpecialWepRotH;
	int fSpecialWepRotV;
	int fSpecialSteering;
	int fSpecialMoveState;
	int uUnusedX;
	char nWheelsOnGround;
	char nRearWheelsOnGround;
	char bytePrevRearWheelsOnGround;
	char __f05C3;
	int fSkidMarkDensity;
	int nTireFriction[4];

	void PlayHornIfNecessary();
	bool HasCarStoppedBecauseOfLight();
	void PlayCarHorn(void);
	void BlowUpCar(CEntity* ent);
	void BurstTyre(unsigned char uUnk, bool bUnk);
};

#pragma pack(pop)

#endif