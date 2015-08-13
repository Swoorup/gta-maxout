#pragma once
#include "SJLIB/stdinc.h"
#include "CMatrix.h"

#pragma pack(push,1)
class CEntity
{
public:
	virtual void Add(void); // 00h
	virtual void Remove(void); // 04h
	virtual ~CEntity(void); // 08h
	virtual void SetModelIndex(int nModelIndex); // 0Ch
	virtual void SetModelIndexNoCreate(int nModelIndex); // 10h
	virtual void CreateRwObject(void); // 14h
	virtual void DeleteRwObject(void); // 18h
	virtual CRect* GetBoundRect(CRect* pRect); // 1Ch
	virtual void ProcessControl(void); // 20h
	virtual void ProcessCollision(void); // 24h
	virtual void ProcessShift(void); // 28h
	virtual void Teleport(float fX, float fY, float fZ); // 2Ch
	virtual void PreRender(void); // 30h
	virtual void Render(void); // 34h
	virtual bool SetupLighting(void); // 38h
	virtual void RemoveLighting(bool bSet); // 3Ch
	virtual void FlagToDestroyWhenNextProcessed(void); // 40h

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

	void AttachToRwObject(RwObject *);
};
#pragma pack(pop)