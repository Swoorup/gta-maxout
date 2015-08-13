//###########################################################
//#	CSprite2d.h:											#
//#															#
//###########################################################

//To-do
//Create Destructor
#pragma once
#include "RenderWare.h"

class CSprite2d
{
public:
	RwTexture* RwTexture;

	CSprite2d():RwTexture(NULL){}
	~CSprite2d(){}
	void Draw(CRect *rect, CRGBA *colour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void Draw3D(CRect& rect, CRGBA& colour, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
	static void DrawRect(CRect& rect, CRGBA& colour);

    void DrawTextureRect(CRect&, CRGBA&);
	void SetTexture(char *name, char *maskName);
    void SetTexture(char *name);
    void SetAddressing(RwTextureAddressMode _RwTextureAddressMode);
};