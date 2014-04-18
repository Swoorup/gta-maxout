#include "SJLIB/stdinc.h"

float CCurves::CalcSpeedScaleFactor(CVector2D* pv2dSource, CVector2D* pv2dTarget, CVector2D v2dStartDirection, CVector2D v2dDestDirection) {
	CVector2D v2dRespective(pv2dSource->fX - pv2dTarget->fX, pv2dSource->fY - pv2dTarget->fY);
	
	float fDistance = v2dRespective.Length();
	float fDotProduct = v2dStartDirection.DotProduct(v2dDestDirection);
	if(fDotProduct <= 0.9f)
		return (((1.0f - fDotProduct) / 4.0f + 1.0f) * fDistance);
	else 
	{
		float fScaleFactor = pv2dSource->fX * v2dStartDirection.fY - pv2dSource->fY * v2dStartDirection.fX - (pv2dTarget->fX * v2dStartDirection.fY - pv2dTarget->fY * v2dStartDirection.fX);
		fScaleFactor = utl::abs<float>(fScaleFactor);
		return (fDistance + fScaleFactor);
	}
}

//429540h
int _declspec(naked) CCurves::CalcCurvePoint(CVector* pvecCurrentPoint, CVector* pvecNextPoint, CVector2D* pv2dCurrentDirection, CVector2D* pv2dNextDirection, float fTimeDelta, int nTimeFactor, CVector* pvecGotoPoint, CVector* pvecVelocity) {
    _asm 
	{
        mov eax, 429540h
        jmp eax
    }
}