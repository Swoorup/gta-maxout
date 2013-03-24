#ifndef _COMMONDEFINATIONS_H
#define _COMMONDEFINATIONS_H
#include "../StdInc.h"

typedef class CPathNode CPathNode;
typedef struct CVehicle CVehicle;
typedef class CMatrix CMatrix;
typedef class CEntity CEntity;

#pragma pack(push, 1)

struct CEntity_vtbl
{
  void *m0;
  void *m4;
  void *scalar_deleting_destructor;
  void *SetModelIndex;
  void *setModelIndexNoCreate;
  void *m14;
  void *Destroy;
  void *m1C;
  void *ProcessControl;
  void *m24;
  void *m28;
  void *PutAt;
  void *m30;
  void *Render;
  void *m38;
  void *m3C;
  void *RemoveFromVehicle;
};

#include "CMatrix.h"

struct CEntityR
{
  CMatrix mat;
  RpClump* pClump;
  unsigned __int8 bfTypeStatus;
  char bfFlagsA;
  char bfFlagsB;
  char bfFlagsC;
  char bfFlagsD;
  char bfFlagsE;
  char gap_56[2];
  __int16 field_58;
  __int16 uiPathMedianRand;
  __int16 nModelIndex;
  char byteLevel;
  char byteInterios;
  int pFirstRef;
};

struct CPhysicalR
{
  CEntityR ent;
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
  int pEntryInfoNode;
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
};

struct CPhysical
{
	int pfnVMT;
	CPhysicalR _;
};

struct CPedIK
{
  int pPed;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
};

struct CWeaponSlot {
  int m_nWeaponId; // 0-4
	//ID of the weapon in this slot
	int m_nWeaponState; // 4-8
	//state of ammo (1 - shooting, 2- reloading, 3 - out of ammo)
	int m_nAmmoLoaded; // 8-12
	//currently loaded amount of ammo
	int m_nAmmoTotal; // 12-16
	//total amount of ammo
	uint32_t m_dwNextShotTime; // 16-20
	//time when the next shot can be made
	bool m_bAddRotOffset; // 20-21
	//related to camera mode
	_pad(__fxpad00, 3); // 21-24
};

struct CTransmissionData
{
  char nDriveType;
  char nEngineType;
  char nNumberOfGears;
  char flags;
  int fEngineAcceleration;
  int fMaxVelocity;
};


struct CHandlingVehicle
{
  int ID;
  int fMass;
  char gap_8[4];
  int field_C;
  RwV3d Dimensions;
  RwV3d CentreOfMass;
  char nPercentSubmerged;
  char gap_29[3];
  int field_2C;
  int fTractionMultiplier;
  char gap_34[72];
  CTransmissionData TransmissionData;
  int fMaxSpeed;
  char gap_8C[8];
  int fBrakeDeceleration;
  int fBrakeBias;
  char bABS;
  char gap_9D[3];
  int fSteeringLock;
  int fTractionLoss;
  int fTractionBias;
  char gap_AC[4];
  int fSuspensionForceLevel;
  int fSuspensionDampingLevel;
  int suspension_upper_limit;
  int suspension_lower_limit;
  int suspension_bias_between_front_and_rear;
  int suspension_antidive_multiplier;
  int fCollisionDamageMultiplier;
  int flags;
  int fSeatOffsetDistance;
  int nMonetaryValue;
  char front_lights;
  char rear_lights;
  __int16 __padding;
};

struct CCollPoly
{
	CVector vecColPolyPoint1;
	CVector vecColPolyPoint2;
	CVector vecColPolyPoint3;
	char bIsValidCollision;
	char __fx0025[3];
};

#include "CAutoPilot.h"
#include "CPed.h"



struct CVehicleR
{
  CPhysicalR phys;
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
};

struct CDamageManager
{
  int uDamId;
  char bStates[12];
  int uLightBits;
  int uPanelBits;
};

struct CDoor
{
  int fAngleInPosOne;
  int fAngleInPosTwo;
  char nAxisDirection;
  char nAxis;
  char nState;
  char __f000B;
  int fAngle;
  int fPrevAngle;
  int fVelAngle;
  CVector vecVelocity;
};

struct CWheel
{
  CVector vecWheelPos;
  char __p000C[4];
  CVector vecWheelAngle;
  char __p001C[12];
};

struct CAutomobileR
{
  CVehicleR veh;
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
};

struct CAutomobile_vtbl
{
	unsigned int CPhysical_Add;	//0
	unsigned int CPhysical_Remove; //4h
	unsigned int SCALAR_DELETING_DESCTRUCTOR; //8h
	unsigned int SetModelIndex;//ch
	unsigned int CEntity_SetModelIndexNoCreate;//
	unsigned int CEntity_CreateRwObject;
	unsigned int CEntity_DeleteRwObject;
	unsigned int CPhysical_GetBoundRect;
	unsigned int CAutomobile_ProcessControl;
	unsigned int CPhysical_ProcessCollision;
	unsigned int CPhysical_ProcessShift;
	unsigned int CAutomobile_Teleport;
	unsigned int CAutomobile_PreRender;
	unsigned int CAutomobile_Render;
	unsigned int CVehicle_SetupLighting;
	unsigned int CVehicle_RemoveLighting;
	unsigned int CVehicle_FlagToDestroyWhenNextProcessed;
	unsigned int CAutomobile_ProcessEntityCollision;
	unsigned int CAutomobile_ProcessControlInputs;
	unsigned int CAutomobile_GetComponentWorldPosition;
	unsigned int CAutomobile_IsComponentPresent;
	unsigned int CAutomobile_SetComponentRotation;
	unsigned int CAutomobile_OpenDoor;
	unsigned int CAutomobile_ProcessOpenDoor;
	unsigned int CAutomobile_IsDoorReady;
	unsigned int CAutomobile_IsDoorFullyOpen;
	unsigned int CAutomobile_IsDoorClosed;
	unsigned int CAutomobile_IsDoorMissing;
	unsigned int CAutomobile_IsDoorReady2;
	unsigned int CAutomobile_IsDoorMissing2;
	unsigned int CAutomobile_IsOpenTopCar;
	unsigned int CAutomobile_RemoveRefsToVehicle;
	unsigned int CAutomobile_BlowUpCar;
	unsigned int CAutomobile_SetUpWheelColModel;
	unsigned int CAutomobile_BurstTyre;
	unsigned int CAutomobile_IsRoomForPedToLeaveCar;
	unsigned int CVehicle_IsClearToDriveAway;
	unsigned int CAutomobile_GetHeightAboveRoad;
	unsigned int CAutomobile_PlayCarHorn;
};
//80

class CPtrNode 
{
public:
 CPtrNode(CEntity* pEntity);

 //void* operator new(size_t uSize, bool bInternal);
 //void operator delete(void* pMem, bool bInternal);
 //void operator delete(void* pMem);

 CEntity* pEntity; // 0-4
 //entity of this linked element
 CPtrNode* pPrev; // 4-8
 //previous item in the list
 CPtrNode* pNext; // 8-12
 //next item in the list
};

class CPtrList 
{
public:
 //void Insert(CPtrNode* pNode);
 //void Remove(CPtrNode* pNode);

 CPtrNode* pStart; // 0-4
 //pointer to the first list element
};



#pragma pack(pop)


#endif
