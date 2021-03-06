#pragma once
#include "SJLIB/stdinc.h"
#include "vehicle.h"

#pragma pack(push, 1)
class CPed : public CPhysical
{
public:    
    CCollPoly polyColliding;
	int fCollisionSpeed;
    char bfFlagsA;
	char bfFlagsB;
	char bfFlagsC;
	char bfFlagsD;
	char bfFlagsE;
	char bfFlagsF;
	char bfFlagsG;
	char bfFlagsH;
	char bfFlagsI;
	char bfFlagsJ;
	char bfFlagsK;
	char bfFlagsL;
	char bfFlagsM;
    char __f0155[3];
	char bfGangFlags;
	char __f0159[3];
    char bytePedStatus;
	char __fx015D[3];
    int dwObjective;
	int dwPrevObjective;
	int pObjectiveEntity;
    CPed *targetEntity;// udhvdfiugnsaiudfgnd
    CVector vecObjective;
	int fObjectiveAngle;
    CEntity* pGangLeader;
	int dwPedFormation;
	int dwFearFlags;
    int pThreatEntity;
	int fEventOrThreatX;
	int fEventOrThreatY;
	int dwEventType;
	int pEventEntity;
	int fAngleToEvent;
    int pFrames[18];
    int pCurWeaponAtomic;
    int dwAnimGroupId;
	int pVehicleAnim;
    CVector2D vecAnimMoveDelta;
    CVector vecOffsetSeek;
    CPedIK pedIK;
    int fActionX;
	int fActionY;
    int dwActionTimer;
	int dwAction;
	int dwLastAction;
	int dwMoveState;
	int dwStoredActionState;
    int dwPrevActionState;
	int dwWaitState;
	int dwWaitTimer;
    CPathNode *ppPathNodes[8];
    WORD pPedIntermediateNodes;
    __int16 nIntermediateSteps;
    int pPathRelEntity;
	int pNextNodeEntity;
	int dwPathNodeTimer;
    char HARDCORDEDMOTHERFUCKERPATHNODESSSSSSSSSSSSSSSSSSSSSSS[160];
    int pCurNodeState; //change asnd fahnsdfad
    char bytePathHeadDirection;
    char gap_335[3];
    CPathNode *pCurrentPedNode;
    CPathNode *m_pNextNode;
    CVector vecPathNextNode;
    int fPathNextNodeDir;
	int dwPathNodeType;
    int fHealth;
	int fArmour;
	int dwShadowUpdateTimer;;
	__int16 wRouteLastPoint;
	__int16 wRoutePoints;
	__int16 wRoutePos;
	__int16 wRouteType;
	__int16 wRouteCurDir;
    char __f0366[2];
	int fMovedX;
	int fMovedY;
    int fRotationCur;
	int fRotationDest;
	int fHeadingRate;
	__int16 wEnterType;
	__int16 wWalkAroundType;
    int pCurPhysSurface;
	CVector vecOffsetFromPhysSurface;
	int pCurSurface;
	CVector vecSeekVehicle;
    int pSeekTarget;
    CVehicle* pVehicle;
	char byteIsInVehicle;
	char __f03A9[3];
	int fSeatPrecisionX;
	int fSeatPrecisionY;
	int pFromVehicle;
	int pSeat;
	int dwSeatType;
	char byteHasPhone;
    char __f03C1;
	__int16 wPhoneId;
    int dwLookingForPhone;
	int dwPhoneTalkTimer;
	int pLastAccident;
    int dwPedType;
    void *pedStatsPtr;
	int fFleeFromPosX;
	int fFleeFromPosY;
	int pFleeFrom;
	int dwFleeTimer;
	int pThreatEx;
	int pLastThreatAt;
	int dwLastThreatTimer;
	int pVehicleColliding;
    char byteStateUnused;
	char __f03F9[3];;
    int dwTimerUnused;
	int pTargetUnused;
    CWeaponSlot stWeps[10];
	int dwAtchStoredWep;
	int dwStoredGiveWep;
	int dwStoredGiveAmmo;
    char byteWepSlot;
	char byteWepSkills;
    char byteWepAccuracy;
	char byteBodyPart;
	int pPointGunAt;
    CVector vecHitLastPos;
    int dwHitCounter;
    int dwLastHitState;
	char byteFightFlags1;
	char byteFightFlags2;
	char byteFightFlags3;
	char byteBleedCounter;
     int pPedFire;
	int pPedFight;
	int fLookDirection;
	int dwWepModelID;
	int dwLeaveCarTimer;
	int dwGetUpTimer;
	int dwLookTimer;
	int dwStandardTimer;
	int dwAttackTimer;
	int dwLastHitTime;
	int dwHitRecoverTimer;
	int dwObjectiveTimer;
    int dwDuckTimer;
	int dwDuckAndCoverTimer;
	int dwBloodyTimer;
    int dwShotTime;
	int dwShotTimeAdd;
	char bytePanicCounter;
	char byteDeadBleeding;
    char byteBodyPartBleeding;
	char __f0567;
	CPed* pNearPeds[10];
	__int16 nNearPeds;
	__int16 wPedMoney;
    int lastDamageType;
    int pLastDamEntity;
    int pAttachedTo;
	CVector vAtchOff;
	 __int16 wAtchType;
	char _f05AE[2];
	int fAtchRot;
    int dwAtchWepAmmo;
	int dwThreatFlags;
	int dwThreatCheck;
	int dwLastThreatCheck;
    int dwSayType;
	int dwSayTimer;
	int dwTalkTimerLast;
	int dwTalkTimer;
	__int16 wTalkTypeLast;
	__int16 wTalkType;
     char byteCanPedTalk;
	char __f05D9[3];
	int dwPedLastComment;
	CVector vecSeekPosEx;
	int fSeekExAngle;

    bool __thiscall FindBestCoordsFromNodes(float fUnusedX, float fUnusedY, float fUnusedZ, CVector* vecBestCoords);
};
#pragma pack(pop)