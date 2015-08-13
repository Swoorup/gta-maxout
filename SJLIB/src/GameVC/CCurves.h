#pragma once
#include "SJLIB/stdinc.h"


class CCurves 
{
public:
	static float CalcSpeedScaleFactor(CVector2D* pv2dSource, CVector2D* pv2dTarget, CVector2D v2dStartDirection, CVector2D v2dDestDirection);
    static int CalcCurvePoint(CVector* pvecCurrentPoint, CVector* pvecNextPoint, CVector2D* pv2dCurrentDirection, CVector2D* pv2dNextDirection, float fTimeDelta, int nTimeFactor, CVector* pvecGotoPoint, CVector* pvecVelocity);
};