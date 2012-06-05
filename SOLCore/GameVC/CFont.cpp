//###########################################################
//#	CFont.cpp:												#
//#															#
//#		A proxy between this DLL and VC's CFont class.		#
//#															#
//###########################################################

#include <Windows.h>
#include "CFont.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~	Proxies to VC functions.								~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DWORD   dwFunc_CFont__PrintString       = 0x00551040;
DWORD   dwFunc_CFont__SetBackgroundOff  = 0x005500D0;
DWORD   dwFunc_CFont__SetBackgroundOn   = 0x005500E0;
DWORD	dwFunc_CFont__SetBackgroundOnlyTextOff = 0x00550080;
DWORD	dwFunc_CFont__SetCentreOff      = 0x00550110;
DWORD   dwFunc_CFont__SetCentreOn       = 0x00550120;
DWORD	dwFunc_CFont__SetCentreSize     = 0x005500F0;
DWORD	dwFunc_CFont__SetColor          = 0x00550170;
DWORD	dwFunc_CFont__SetDropShadowPosition =0x0054FF20;
DWORD	dwFunc_CFont__SetDropColor      = 0x0054FF30;
DWORD	dwFunc_CFont__SetFontStyle      = 0x0054FFE0;
DWORD	dwFunc_CFont__SetJustifyOff     = 0x00550140;
DWORD	dwFunc_CFont__SetJustifyOn      = 0x00550150;
DWORD	dwFunc_CFont__SetPropOff        = 0x00550030;
DWORD	dwFunc_CFont__SetPropOn         = 0x00550020;
DWORD	dwFunc_CFont__SetRightJustifyOff= 0x00550040;
DWORD	dwFunc_CFont__SetRightJustifyOn = 0x00550060; 
DWORD	dwFunc_CFont__SetRightJustifyWrap = 0x0054FFD0;
DWORD	dwFunc_CFont__SetScale          = 0x00550230;
DWORD   dwFunc_CFont__AsciiToUnicode    = 0x00552500;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

__declspec(naked) void CFont::PrintString(float x, float y, wchar_t* text)
{
	__asm jmp dwFunc_CFont__PrintString
}

__declspec(naked) void CFont::SetBackgroundOff()
{
	__asm jmp dwFunc_CFont__SetBackgroundOff
}

__declspec(naked) void CFont::SetBackgroundOn()
{
    __asm jmp dwFunc_CFont__SetBackgroundOn
}

__declspec(naked) void CFont::SetBackGroundOnlyTextOff()
{
	__asm jmp dwFunc_CFont__SetBackgroundOnlyTextOff
}

__declspec(naked) void CFont::SetCentreOff()
{
	__asm jmp dwFunc_CFont__SetCentreOff
}

__declspec(naked) void CFont::SetCentreOn()
{
	__asm jmp dwFunc_CFont__SetCentreOn
}

__declspec(naked) void CFont::SetCentreSize(float v)
{
	__asm jmp dwFunc_CFont__SetCentreSize
}

__declspec(naked) void CFont::SetColor(CRGBA *colour)
{
	__asm jmp dwFunc_CFont__SetColor
}

__declspec(naked) void CFont::SetDropShadowPosition(short pos)
{
	__asm jmp dwFunc_CFont__SetDropShadowPosition
}

__declspec(naked) void CFont::SetDropColor(CRGBA *colour)
{
	__asm jmp dwFunc_CFont__SetDropColor
}

__declspec(naked) void CFont::SetFontStyle(short style)
{
	__asm jmp dwFunc_CFont__SetFontStyle
}

__declspec(naked) void CFont::SetJustifyOff()
{
	__asm jmp dwFunc_CFont__SetJustifyOff
}

__declspec(naked) void CFont::SetJustifyOn()
{
	__asm jmp dwFunc_CFont__SetJustifyOn
}

__declspec(naked) void CFont::SetPropOff()
{
	__asm jmp dwFunc_CFont__SetPropOff
}

__declspec(naked) void CFont::SetPropOn()
{
	__asm jmp dwFunc_CFont__SetPropOn
}

__declspec(naked) void CFont::SetRightJustifyWrap(float wrap)
{
	__asm jmp dwFunc_CFont__SetRightJustifyWrap
}

__declspec(naked) void CFont::SetRightJustifyOff()
{
	__asm jmp dwFunc_CFont__SetRightJustifyOff
}

__declspec(naked) void CFont::SetRightJustifyOn()
{
	__asm jmp dwFunc_CFont__SetRightJustifyOn
}

__declspec(naked) void CFont::SetScale(float x, float y)
{
	__asm jmp dwFunc_CFont__SetScale
}

__declspec(naked) void CFont::AsciiToUnicode(char* src, wchar_t* dest)
{
	__asm jmp dwFunc_CFont__AsciiToUnicode
}