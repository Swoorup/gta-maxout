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
struct CPed
{
  CPhysical __parent;
  char gap_120[44];
  char field_14C;
  char field_14D;
  char field_14E;
  char field_14F;
  char field_150;
  char flags;
  char field_152;
  char field_153;
  char field_154;
  char field_155;
  char field_156;
  char field_157;
  char field_158;
  char gap_159[3];
  char field_15C;
  char gap_15D[3];
  char reference;
  char gap_161[3];
  int objective;
  int field_168;
  CEntity *field_16C;
  int targetEntity;
  char gap_174[12];
  int field_180;
  CEntity *damageEntity;
  int field_188;
  int threatPlayer;
  int field_190;
  int field_194;
  int field_198;
  int field_19C;
  int field_1A0;
  int field_1A4;
  int field_1A8;
  char gap_1AC[35];
  char field_1CF;
  char field_1D0;
  char gap_1D1[31];
  int field_1F0;
  int field_1F4;
  int field_1F8;
  int field_1FC;
  int field_200;
  int field_204;
  int field_208;
  int field_20C;
  CPedIK pedIK;
  int field_238;
  int field_23C;
  int field_240;
  int current_status;
  int field_248;
  int field_24C;
  int field_250;
  int field_254;
  int animationID;
  int animationTime;
  CPathNode *ppPathNodes[8];
  WORD pPedIntermediateNodes;
  __int16 nIntermediateSteps;
  int field_284;
  int field_288;
  int field_28C;
  char field_290;
  char gap_291[159];
  int field_330;
  char bytePathHeadDirection;
  char gap_335[3];
  CPathNode *pCurrentPedNode;
  CPathNode *pNextNode;
  float targetX;
  float targety;
  float targetZ;
  int field_34C;
  int field_350;
  float health;
  float armour;
  char gap_35C[4];
  __int16 field_360;
  __int16 field_362;
  __int16 field_364;
  __int16 field_366;
  char gap_368[4];
  int field_36C;
  int field_370;
  float field_374;
  float field_378;
  float headingChangeRate;
  __int16 field_380;
  __int16 field_382;
  int field_384;
  int field_388;
  int field_38C;
  int field_390;
  int field_394;
  float fpathX;
  float fpathY;
  float fpathZ;
  void *field_3A4;
  CVehicle *pVehicle;
  char inVehicle;
  char gap_3AD[3];
  float field_3B0;
  int field_3B4;
  char gap_3B8[4];
  int field_3BC;
  int field_3C0;
  char field_3C4;
  char field_3C5;
  __int16 field_3C6;
  char gap_3C8[4];
  int field_3CC;
  int field_3D0;
  int pedType;
  void *pedStatsPtr;
  int field_3DC;
  int field_3E0;
  void *field_3E4;
  int field_3E8;
  int field_3EC;
  char gap_3F0[4];
  int field_3F4;
  int field_3F8;
  char field_3FC;
  char gap_3FD[3];
  int field_400;
  int field_404;
  CWeaponSlot weaponSlots[10];
  int field_4F8;
  int currentWeaponId;
  int currentWeaponAmmo;
  char currentWeapon;
  char field_505;
  char weaponAccuracy;
  char gap_507[1];
  int field_508;
  char field_50C;
  char gap_50D[6];
  char field_513;
  int field_514;
  int field_518;
  char gap_51C[8];
  int fire;
  int field_528;
  float field_52C;
  int field_530;
  int field_534;
  int field_538;
  int field_53C;
  int field_540;
  int field_544;
  int field_548;
  int field_54C;
  float field_550;
  int field_554;
  int field_558;
  int ClosestPedsTimer;
  int field_560;
  int field_564;
  char field_568;
  char bleeding;
  char field_56A;
  char gap_56B[1];
  void *closestPeds[10];
  __int16 numberOfPeds;
  __int16 money;
  int lastDamageType;
  int lastDamageEntity;
  int field_5A0;
  char gap_5A4[20];
  int field_5B8;
  int field_5BC;
  int field_5C0;
  int field_5C4;
  char gap_5C8[8];
  int field_5D0;
  int field_5D4;
  __int16 field_5D8;
  __int16 field_5DA;
  char muted;
  char gap_5DD[3];
  int field_5E0;
  int field_5E4;
  int field_5E8;
  int field_5EC;
  int field_5F0;
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
