#pragma once
#include "SJLIB/stdinc.h"

#pragma pack(push, 1)

class CMatrix 
{
public:
	CVector vLookRight;
	int __fxpad01;
	CVector vLookAt;
	int __fxpad02;
	CVector vLookUp;
	int __fxpad03;
	CVector vPos;
	int __fxpad04;
	RwMatrix* pRwAttached;
	int bDeleteOnDetach;

	void UpdateRW()
	{
		if ( pRwAttached )
		{
			pRwAttached->vLookRight.x = vLookRight.fX;
			pRwAttached->vLookRight.y = vLookRight.fY;
			pRwAttached->vLookRight.z = vLookRight.fZ;
			pRwAttached->vLookAt.x = vLookAt.fX;
			pRwAttached->vLookAt.y = vLookAt.fY;
			pRwAttached->vLookAt.z = vLookAt.fZ;
			pRwAttached->vLookUp.x = vLookUp.fX;
			pRwAttached->vLookUp.y = vLookUp.fY;
			pRwAttached->vLookUp.z = vLookUp.fZ;
			pRwAttached->vPos.x = vPos.fX;
			pRwAttached->vPos.y = vPos.fY;
			pRwAttached->vPos.z = vPos.fZ;
			RwMatrixUpdate(pRwAttached);
		}
	}

	CVector operator * (CVector const& vecRight) const
	{
		CVector result;
		result.fX = vLookAt.fX * vecRight.fY + vLookRight.fX * vecRight.fX + vLookUp.fX * vecRight.fZ + vPos.fX;
		result.fY = vLookAt.fY * vecRight.fY + vLookRight.fY * vecRight.fX + vLookUp.fY * vecRight.fZ + vPos.fY;
		result.fZ = vLookAt.fZ * vecRight.fY + vLookRight.fZ * vecRight.fX + vLookUp.fZ * vecRight.fZ + vPos.fZ;

		return result;
	}

	CMatrix operator * (CMatrix const& matRight) const
	{
		CMatrix result;
		result.bDeleteOnDetach = 0;
		result.pRwAttached = NULL;
		
		result.vLookRight = vLookRight * matRight.vLookRight.fX + vLookAt * matRight.vLookRight.fY  + vLookUp * matRight.vLookRight.fZ;
		result.vLookAt = vLookRight * matRight.vLookAt.fX + vLookAt * matRight.vLookAt.fY + vLookUp * matRight.vLookAt.fZ;
		result.vLookUp = vLookRight * matRight.vLookUp.fX + vLookAt * matRight.vLookUp.fY + vLookUp * matRight.vLookUp.fZ;
		result.vPos = vLookRight * matRight.vPos.fX + vLookAt * matRight.vPos.fY + vLookUp * matRight.vPos.fZ + vPos;
	

		if ( result.pRwAttached )
			result.UpdateRW();
		if ( result.bDeleteOnDetach && result.pRwAttached )
			RwMatrixDestroy(result.pRwAttached);
		return result;
	}
};

#pragma pack(pop)