#include "../StdInc.h"

DWORD   dwFunc_CSprite2d__SetTexture1Param      = 0x005789E0;
DWORD   dwFunc_CSprite2d__SetTexture2Param    = 0x005789B0;
DWORD   dwFunc_CSprite2d__DrawRect      = 0x00577B00;
DWORD   dwFunc_CSprite2d__Draw1         = 0x005786A0;
DWORD   dwFunc_CSprite2d__SetAddressing = 0x00578970;
DWORD   dwFunc_CSprite2d__DrawTextureRect2Param = 0x00578710;

_declspec(naked) void CSprite2d::DrawRect(CRect& rect, CRGBA& colour) {
	_asm jmp dwFunc_CSprite2d__DrawRect
}

_declspec(naked) void CSprite2d::Draw(CRect *rect, CRGBA *colour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	_asm jmp dwFunc_CSprite2d__Draw1
}

_declspec(naked) void CSprite2d::DrawTextureRect(CRect&, CRGBA&) {
    _asm jmp dwFunc_CSprite2d__DrawTextureRect2Param
}

void CSprite2d::Draw3D(CRect& rect, CRGBA& colour, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) {
	typedef void (*pSetVertices)(CRect&,CRGBA&,CRGBA&,CRGBA&,CRGBA&,float,float,float,float,float,float,float,float);
	pSetVertices SetVertices = (pSetVertices)0x00578010;


	SetVertices(rect, colour, colour, colour, colour, x1, y1, x2, y2, x3, y3, x4, y4);

	RwIm3DVertex *vertices = new RwIm3DVertex[4];
	vertices[0].objVertex.x = x1;
	vertices[0].objVertex.y = y1;
	vertices[0].objVertex.z = z1;
	vertices[1].objVertex.x = x2;
	vertices[1].objVertex.y = y2;
	vertices[1].objVertex.z = z2;
	vertices[2].objVertex.x = x3;
	vertices[2].objVertex.y = y3;
	vertices[2].objVertex.z = z3;
	vertices[3].objVertex.x = x4;
	vertices[3].objVertex.y = y4;
	vertices[3].objVertex.z = z4;


	vertices[0].color = -1;
	vertices[1].color = -1;
	vertices[2].color = -1;
	vertices[3].color = -1;

	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;
	vertices[3].u = 0.0f;
	vertices[3].v = 1.0f;

	vertices[0].objNormal.x = 0.0f;
	vertices[0].objNormal.y = 0.0f;
	vertices[0].objNormal.z = 0.0f;
	vertices[1].objNormal.x = 0.0f;
	vertices[1].objNormal.y = 0.0f;
	vertices[1].objNormal.z = 0.0f;
	vertices[2].objNormal.x = 0.0f;
	vertices[2].objNormal.y = 0.0f;
	vertices[2].objNormal.z = 0.0f;
	vertices[3].objNormal.x = 0.0f;
	vertices[3].objNormal.y = 0.0f;
	vertices[3].objNormal.z = 0.0f;

	WORD indices[6] = { 0, 1, 2, 0, 2, 3 };

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTexture->pRaster);
	RwIm3DTransform(vertices, 4, NULL, 4);
	RwIm3DRenderIndexedPrimitive(3, indices, 6);
}

_declspec(naked) void CSprite2d::SetTexture(char *name, char *maskName) {
	_asm jmp dwFunc_CSprite2d__SetTexture2Param
}

_declspec(naked) void CSprite2d::SetTexture(char* name) {
    _asm jmp dwFunc_CSprite2d__SetTexture1Param
}

_declspec(naked) void CSprite2d::SetAddressing(RwTextureAddressMode _RwTextureAddressMode) {
    _asm jmp dwFunc_CSprite2d__SetAddressing
}