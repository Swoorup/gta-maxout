#include "SJLIB/stdinc.h"


/* 4A55E0h
 * This function is used for getting the inverse of tan
 * by specify x and y coordinates
 */

double CGeneral::GetATanOfXY(CVector2D v2dToCalc) {
	double result;
	
	_asm {
		mov eax, 4A55E0h
		push v2dToCalc.fY
		push v2dToCalc.fX
		call eax
        add esp, 8
		fstp result
	}
	return result;
}