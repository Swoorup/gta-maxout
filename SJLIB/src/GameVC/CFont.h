//###########################################################
//#	CFont.h													#
//#															#
//###########################################################

#pragma once

#include "RenderWare.h"



class CFont
{
public:
	static void DrawFonts();
	static void GetNumberOfLines(float x, float y, unsigned short *text);
	static void GetTextRect(CRect *rectOut, float x, float y, wchar_t *text);
	static void Initialise();
	static void PrintString(float x, float y, wchar_t *text);
	static void SetAlphaFade(float alpha);
	static void SetBackGroundOnlyTextOff();
	static void SetBackGroundOnlyTextOn();
	static void SetBackgroundColor(CRGBA *color);
	static void SetBackgroundOff();
	static void SetBackgroundOn();
	static void SetCentreOff();
	static void SetCentreOn();
	static void SetCentreSize(float size);
	static void SetColor(CRGBA *color);
	static void SetDropColor(CRGBA *color);
	static void SetDropShadowPosition(short pos);
	static void SetFontStyle(short style);
	static void SetJustifyOff();
	static void SetJustifyOn();
	static void SetPropOff();
	static void SetPropOn();
	static void SetRightJustifyOff();
	static void SetRightJustifyOn();
	static void SetRightJustifyWrap(float wrap);
	static void SetScale(float x, float y);
	static void SetWrapx(float wrapx);
    static void AsciiToUnicode(char* src, wchar_t* dest);
};