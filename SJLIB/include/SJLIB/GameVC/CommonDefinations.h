#pragma once
#include "SJLIB/stdinc.h"

typedef class CPathNode CPathNode;
typedef class CMatrix CMatrix;

#pragma pack(push, 1)
#include "CMatrix.h"

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

// just testing
// structure that is assigned to the model 
struct CColModel
{
	CVector center;
	float fRadius;
	CVector minimum;
	CVector maximum; 
	
	WORD nColSpheres; //40
	WORD nColBoxes;	//
	WORD nColFaces;
	char nNumberOfUnknownData; // Unknown Section
	char charUnk;
	char charUnk2;
	char pad[3];
	DWORD rwAllocatedCColSphereBuffer; //52 CColSpheres
	DWORD rwAllocatedUnkPointer;
	DWORD rwAllocatedCColBoxBuffer; // colboxes
	DWORD rwAllocatedVerticesBuffer; // 8 are aligned
	DWORD rwAllocatedFacesBuffer;
	DWORD rwOnTheFlyBuffer20BytesArrayBuff;
	
};
struct CColSphere
{
	CVector position;
	float fRadius;
	char material; //char bSurfaceType;??
	char flag; //char bPieceType;?
};

struct CColBox
{
	CVector minimum;
	CVector maximum;
	char material;
	char flag;
};

struct CColLine
{
	CVector position;
	DWORD padding;
	CVector position2;
};

struct CColPoint
{
	CVector position;
	float fUnknown1;
	CVector Normal;
	float fUnknown2;
	char bSurfaceTypeA;
    char bPieceTypeA;
    char bSurfaceTypeB;
    char bPieceTypeB;
};

/*
class CBaseModelInfo
{
public:
	// vTables
	virtual ~CBaseModelInfo(void);
	virtual void Shutdown(void);
	virtual void DeleteRwObject(void) = 0;
	virtual void CreateInstance(void) = 0;
	virtual void CreateInstance(RwMatrixTag*) = 0;
	virtual RwObject* GetRwObject(void) = 0;
	virtual void SetAnimFileIndex(void);
	virtual void ConvertAnimFileIndex(void);
	virtual int GetAnimFileIndex(void);
	virtual void SetAtomic(int, RpAtomic*) = 0;
	
	// fields
	char bla[19];
	WORD nTxdSlot;
	char bla2[4];
	char modelInfoType; //25
	char c1; //26
	char c2; //27
	CColModel* colmodel; //28
	WORD w2dInfoIndex; //32
	WORD w2; //34
	WORD nTxdSlotsUsed; //36
	WORD indexTxdSlot; //38
}
// assert sizeof(CColPoint) == 36
//*/
#include "CAutoPilot.h"
#include "CPed.h"

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


