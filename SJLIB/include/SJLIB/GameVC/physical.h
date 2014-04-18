#pragma once

#include "SJLIB/stdinc.h"
#include "entity.h"
class CEntity;

#pragma pack(push, 1)
class CPhysical : public CEntity
{
public:
	virtual void Add(void);	// 00h
	virtual void Remove(void); // 04h
	virtual ~CPhysical(void); // 08h
	virtual void GetBoundRect(void); // 	
	virtual void ProcessControl(void); // 
	virtual void ProcessCollision(void); // 
	virtual void ProcessShift(void);
	virtual void ProcessEntityCollision(CEntity *,DWORD *); 

	int uAudioEntityId;
	char __f0004[8];
	CVector vecMoveSpeed;
	CVector vecTurnSpeed;
	CVector vecShiftVector1;
	CVector vecShiftVector2;
	CVector vecShiftVector3;
	CVector vecShiftVector4;
	float fMass;
	float fTurnMass;
	int fForceMultiplier;
	float fAirResistance;
	float fElasticy;
	int fPercentSubmerged;
	CVector vecCenterOfMass;
	int* pEntryInfoNode;
	void *pMovingListNode;
	char __f00E0[2];
	char uCollidingNum;
	char __fx00E3;
	int pCollisionRecords[6];
	int fTotSpeed;
	int fCollisionPower;
	int pPhysColling;
	CVector vecCollisionPower;
	__int16 wComponentCol;
	char byteMoveFlags;
	char byteCollFlags;
	char byteLastCollType;
	char byteZoneLevel;
	__int16 __padding;

	// non virtual member mothods
	void ApplyMoveSpeed(void);
};
#pragma pack(pop)
