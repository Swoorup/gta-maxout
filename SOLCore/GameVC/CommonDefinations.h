#ifndef _COMMONDEFINATIONS_H
#define _COMMONDEFINATIONS_H
#include "../StdInc.h"

typedef class CPathNode CPathNode;
typedef struct CVehicle CVehicle;
typedef class CMatrix CMatrix;

#pragma pack(push, 1)
struct CEntity__vtbl
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
#pragma pack(pop)


#pragma pack(push, 1)
struct CEntity
{
  CEntity__vtbl *__vmt;
  CMatrix matrix;
  void *rwObject;
  unsigned __int8 flags;
  char type;
  char field_52;
  char field_53;
  char field_54;
  char field_55;
  char gap_56[2];
  __int16 field_58;
  __int16 uiPathMedianRand;
  __int16 modelIndex;
  char buildingIsland;
  char interior;
  int pReference;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CPhysical
{
  CEntity __parent;
  int audioID;
  int field_68;
  int field_6C;
  RwV3d velocity;
  RwV3d angularVelocity;
  int field_88;
  int field_8C;
  int field_90;
  int field_94;
  int field_98;
  int field_9C;
  int field_A0;
  int field_A4;
  int field_A8;
  int field_AC;
  int field_B0;
  int field_B4;
  float fMass;
  float fTurnMass;
  int field_C0;
  float AirResistance;
  float Elasticy;
  int PercentSubmerged;
  RwV3d CenterOfMass;
  int field_DC;
  void *ptrNode;
  char field_E4;
  char field_E5;
  char field_E6;
  char field_E7;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  int field_100;
  int field_104;
  int field_108;
  int field_10C;
  int field_110;
  int field_114;
  __int16 field_118;
  char field_11A;
  char field_11B;
  char field_11C;
  char islandNo;
  __int16 __padding;
};
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
struct CTransmissionData
{
  char nDriveType;
  char nEngineType;
  char nNumberOfGears;
  char flags;
  int fEngineAcceleration;
  int fMaxVelocity;
};
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#include "CAutoPilot.h"
#include "CPed.h"

#pragma pack(push, 1)
struct CVehicle
{
  CPhysical __parent;
  CHandlingVehicle *pVehicleHandling;
  void *pFlyingHandling;
  CAutoPilot Autopilot;
  char primaryColor;
  char secondaryColor;
  char tertiaryColor;
  char quaternaryColor;
  __int16 field_1A4;
  __int16 field_1A6;
  CPed *pDriver;
  int passangers[8];
  char numOfPassangers;
  char field_1CD;
  char field_1CE;
  char field_1CF;
  char maxPassangers;
  char gap_1D1[19];
  int field_1E4;
  int fire;
  int field_1EC;
  int field_1F0;
  int field_1F4;
  char reference;
  char flags;
  char flags2;
  char modelFlags;
  char field_1FC;
  char field_1FD;
  char field_1FE;
  char field_1FF;
  char field_200;
  char field_201;
  char gap_202[2];
  int health;
  int field_208;
  int field_20C;
  int field_210;
  int field_214;
  int field_218;
  int field_21C;
  __int16 field_220;
  __int16 field_222;
  int field_224;
  int field_228;
  int field_22C;
  int doorStatus;
  char lastDamageType;
  char gap_235[3];
  int field_238;
  char field_23C;
  char field_23D;
  char field_23E;
  char gap_23F[1];
  int horn;
  char field_244;
  char sirenOn;
  char field_246;
  char field_247;
  char field_248[80];
  int field_298;
  int carType;
};
#pragma pack(pop)


#endif
