//-----------------------------------------------------------------------------
// File: D3DFont.h
//
// Desc: Texture-based font class
//-----------------------------------------------------------------------------
/*
#ifndef CCUSTOMFONT_H
#define CCUSTOMFONT_H
#include <tchar.h>
#include <Windows.h>
#include "GameVC\RenderWare.h"
#include "main.h"


// Font creation flags
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define D3DFONT_CENTERED_X  0x0001
#define D3DFONT_CENTERED_Y  0x0002
#define D3DFONT_TWOSIDED    0x0004
#define D3DFONT_FILTERED    0x0008

struct RenderStateBlock
{
    RwTextureFilterMode textureFilterMode;
    RwBlendFunction blendSourceFunction;
    RwBlendFunction blendDestFunction;
    bool vertexAlphaEnable;
};


//-----------------------------------------------------------------------------
// Name: class CD3DFont
// Desc: Texture-based font class for doing text in a 3D scene.
//-----------------------------------------------------------------------------
class CCustomFont
{
    RwIm2DVertex *pVertices;
    TCHAR   m_strFontName[80];            // Font properties
    DWORD   m_dwFontHeight;
    DWORD   m_dwFontFlags;

    //LPDIRECT3DVERTEXBUFFER8 m_pVB;
    DWORD   m_dwTexWidth;                 // Texture dimensions
    DWORD   m_dwTexHeight;
    FLOAT   m_fTextScale;
    FLOAT   m_fTexCoords[128-32][4];
    DWORD   m_dwSpacing;                  // Character pixel spacing per side

    // Stateblocks for setting and restoring render states
    RenderStateBlock m_pStateBlockSaved;
    //LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText;

public:
    // 2D and 3D text drawing functions
    RwRaster*      m_pRaster;   // The Renderware raster for this font
    HRESULT DrawText( FLOAT sx, FLOAT sy, DWORD dwColor,
                            const TCHAR* strText, DWORD dwFlags);
    HRESULT DrawTextScaled( FLOAT x, FLOAT y, FLOAT z, 
                            FLOAT fXScale, FLOAT fYScale, DWORD dwColor, 
                            const TCHAR* strText, DWORD dwFlags=0L );
    HRESULT Render3DText( const TCHAR* strText, DWORD dwFlags=0L );
    
    // Function to get extent of text
    HRESULT GetTextExtent( const TCHAR* strText, SIZE* pSize );

    // Initializing and destroying device-dependent objects
    HRESULT InitObjects();
    HRESULT RestoreDeviceObjects();
    //HRESULT InvalidateDeviceObjects();
    //HRESULT DeleteDeviceObjects();

    // Constructor / destructor
    CCustomFont( const TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
    ~CCustomFont();
};




#endif

*/