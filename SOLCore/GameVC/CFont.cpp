#include "../StdInc.h"

DWORD dwFunc_CFont__PrintString       = 0x551040;
DWORD dwFunc_CFont__SetBackgroundOff  = 0x5500D0;
DWORD dwFunc_CFont__SetBackgroundOn   = 0x5500E0;
DWORD dwFunc_CFont__SetBackgroundOnlyTextOff = 0x550080;
DWORD dwFunc_CFont__SetCentreOff      = 0x550110;
DWORD dwFunc_CFont__SetCentreOn       = 0x550120;
DWORD dwFunc_CFont__SetCentreSize     = 0x5500F0;
DWORD dwFunc_CFont__SetColor          = 0x550170;
DWORD dwFunc_CFont__SetDropShadowPosition =0x54FF20;
DWORD dwFunc_CFont__SetDropColor      = 0x54FF30;
DWORD dwFunc_CFont__SetFontStyle      = 0x54FFE0;
DWORD dwFunc_CFont__SetJustifyOff     = 0x550140;
DWORD dwFunc_CFont__SetJustifyOn      = 0x550150;
DWORD dwFunc_CFont__SetPropOff        = 0x550030;
DWORD dwFunc_CFont__SetPropOn         = 0x550020;
DWORD dwFunc_CFont__SetRightJustifyOff= 0x550040;
DWORD dwFunc_CFont__SetRightJustifyOn = 0x550060; 
DWORD dwFunc_CFont__SetRightJustifyWrap = 0x54FFD0;
DWORD dwFunc_CFont__SetScale          = 0x550230;
DWORD dwFunc_CFont__AsciiToUnicode    = 0x552500;


_declspec(naked) void CFont::PrintString(float x, float y, wchar_t* text) {
	_asm jmp dwFunc_CFont__PrintString
}

_declspec(naked) void CFont::SetBackgroundOff() {
	_asm jmp dwFunc_CFont__SetBackgroundOff
}

_declspec(naked) void CFont::SetBackgroundOn() {
    _asm jmp dwFunc_CFont__SetBackgroundOn
}

_declspec(naked) void CFont::SetBackGroundOnlyTextOff() {
	_asm jmp dwFunc_CFont__SetBackgroundOnlyTextOff
}

_declspec(naked) void CFont::SetCentreOff() {
	_asm jmp dwFunc_CFont__SetCentreOff
}

_declspec(naked) void CFont::SetCentreOn() {
	_asm jmp dwFunc_CFont__SetCentreOn
}

_declspec(naked) void CFont::SetCentreSize(float v) {
	_asm jmp dwFunc_CFont__SetCentreSize
}

_declspec(naked) void CFont::SetColor(CRGBA *colour)
{
	_asm jmp dwFunc_CFont__SetColor
}

_declspec(naked) void CFont::SetDropShadowPosition(short pos) {
	_asm jmp dwFunc_CFont__SetDropShadowPosition
}

_declspec(naked) void CFont::SetDropColor(CRGBA *colour) {
	_asm jmp dwFunc_CFont__SetDropColor
}

_declspec(naked) void CFont::SetFontStyle(short style) {
	_asm jmp dwFunc_CFont__SetFontStyle
}

_declspec(naked) void CFont::SetJustifyOff() {
	_asm jmp dwFunc_CFont__SetJustifyOff
}

_declspec(naked) void CFont::SetJustifyOn() {
	_asm jmp dwFunc_CFont__SetJustifyOn
}

_declspec(naked) void CFont::SetPropOff() {
	_asm jmp dwFunc_CFont__SetPropOff
}

_declspec(naked) void CFont::SetPropOn() {
	_asm jmp dwFunc_CFont__SetPropOn
}

_declspec(naked) void CFont::SetRightJustifyWrap(float wrap) {
	_asm jmp dwFunc_CFont__SetRightJustifyWrap
}

_declspec(naked) void CFont::SetRightJustifyOff() {
	_asm jmp dwFunc_CFont__SetRightJustifyOff
}

_declspec(naked) void CFont::SetRightJustifyOn() {
	_asm jmp dwFunc_CFont__SetRightJustifyOn
}

_declspec(naked) void CFont::SetScale(float x, float y) {
	_asm jmp dwFunc_CFont__SetScale
}

_declspec(naked) void CFont::AsciiToUnicode(char* src, wchar_t* dest) {
	_asm jmp dwFunc_CFont__AsciiToUnicode
}