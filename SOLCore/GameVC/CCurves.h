#include "../stdinc.h"
#pragma once

class CCurves {
public:
	static float CalcSpeedScaleFactor(CVector2D* pv2dSource, CVector2D* pv2dTarget, CVector2D v2dStartDirection, CVector2D v2dDestDirection);
};