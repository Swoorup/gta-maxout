//-----------------------------------------------------------------------------
// File: D3DFont.cpp
//
// Desc: Texture-based font class
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <tchar.h>
#include "CCustomFont.h"
#include <math.h>
//-----------------------------------------------------------------------------

typedef RwIm2DVertex FONT2DVERTEX;

//struct FONT2DVERTEX { D3DXVECTOR4 p;   DWORD color;     FLOAT tu, tv; };
//struct FONT3DVERTEX { D3DXVECTOR3 p;   D3DXVECTOR3 n;   FLOAT tu, tv; };

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FONT3DVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

#define MAX_NUM_VERTICES 50*6 //Max number of vertices that can be displayed at a single RwIm2DPrimitive call. This is always a multiple of 6. Default to Directx 8 MAX VERTICES
#define MAX_NUM_CHARS 256

//inline FONT3DVERTEX InitFont3DVertex( const D3DXVECTOR3& p, const D3DXVECTOR3& n,
                                      //FLOAT tu, FLOAT tv )
//{
    //FONT3DVERTEX v;   v.p = p;   v.n = n;   v.tu = tu;   v.tv = tv;
    //return v;
//}
//-----------------------------------------------------------------------------
// Name: CD3DFont()
// Desc: Font class constructor
//-----------------------------------------------------------------------------
CCustomFont::CCustomFont( const TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags )
{
    _tcsncpy( m_strFontName, strFontName, sizeof(m_strFontName) / sizeof(TCHAR) );
    m_strFontName[sizeof(m_strFontName) / sizeof(TCHAR) - 1] = _T('\0');
    m_dwFontHeight         = dwHeight;
    m_dwFontFlags          = dwFlags;
    m_dwSpacing            = 0;

    m_pRaster             = NULL;
    pVertices = new RwIm2DVertex[MAX_NUM_CHARS*6];
    //m_pStateBlockSaved     = NULL;
    //m_pStateBlockDrawText  = NULL;
}


//-----------------------------------------------------------------------------
// Name: ~CD3DFont()
// Desc: Font class destructor
//-----------------------------------------------------------------------------
CCustomFont::~CCustomFont()
{
    if (!(pVertices == NULL))
        delete pVertices;
    pVertices = NULL;
    RwRasterDestroy(m_pRaster);
    
    //InvalidateDeviceObjects();
    //DeleteDeviceObjects();
}



//-----------------------------------------------------------------------------
// Name: InitObjects()
// Desc: Initializes the raster map which stores the font image.
//-----------------------------------------------------------------------------
HRESULT CCustomFont::InitObjects()
{
    //HRESULT hr;

    // Establish the font and texture size
    m_fTextScale  = 1.0f; // Draw fonts into texture without scaling

    // Large fonts need larger textures
    if( m_dwFontHeight > 60 )
        m_dwTexWidth = m_dwTexHeight = 2048;
    else if( m_dwFontHeight > 30 )
        m_dwTexWidth = m_dwTexHeight = 1024;
    else if( m_dwFontHeight > 15 )
        m_dwTexWidth = m_dwTexHeight = 512;
    else
        m_dwTexWidth  = m_dwTexHeight = 256;


    // Prepare to create a bitmap
    DWORD*      pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory( &bmi.bmiHeader,  sizeof(BITMAPINFOHEADER) );
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       =  (int)m_dwTexWidth;
    bmi.bmiHeader.biHeight      = -(int)m_dwTexHeight;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // Create a DC and a bitmap for the font
    HDC     hDC       = CreateCompatibleDC( NULL );
    HBITMAP hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS,
                                          (void**)&pBitmapBits, NULL, 0 );
    SetMapMode( hDC, MM_TEXT );

    // Create a font.  By specifying ANTIALIASED_QUALITY, we might get an
    // antialiased font, but this is not guaranteed.
    INT nHeight    = -MulDiv( m_dwFontHeight, 
        (INT)(GetDeviceCaps(hDC, LOGPIXELSY) * m_fTextScale), 72 );
    DWORD dwBold   = (m_dwFontFlags&D3DFONT_BOLD)   ? FW_BOLD : FW_NORMAL;
    DWORD dwItalic = (m_dwFontFlags&D3DFONT_ITALIC) ? TRUE    : FALSE;
    HFONT hFont    = CreateFont( nHeight, 0, 0, 0, dwBold, dwItalic,
                        FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                        VARIABLE_PITCH, m_strFontName );
    if( NULL==hFont )
        return E_FAIL;

    HGDIOBJ hbmOld = SelectObject( hDC, hbmBitmap );
    HGDIOBJ hFontOld = SelectObject( hDC, hFont );

    // Set text properties
    SetTextColor( hDC, RGB(255,255,255) );
    SetBkColor(   hDC, 0x00000000 );
    SetTextAlign( hDC, TA_TOP );

    // Loop through all printable character and output them to the bitmap..
    // Meanwhile, keep track of the corresponding tex coords for each character.
    DWORD x = 0;
    DWORD y = 0;
    TCHAR str[2] = _T("x");
    SIZE size;

    // Calculate the spacing between characters based on line height
    GetTextExtentPoint32( hDC, TEXT(" "), 1, &size );
    x = m_dwSpacing = (DWORD) ceil(size.cy * 0.3f);

    for( TCHAR c=32; c<127; c++ )
    {
        str[0] = c;
        GetTextExtentPoint32( hDC, str, 1, &size );

        if( (DWORD)(x + size.cx + m_dwSpacing) > m_dwTexWidth )
        {
            x  = m_dwSpacing;
            y += size.cy+1;
        }

        ExtTextOut( hDC, x+0, y+0, ETO_OPAQUE, NULL, str, 1, NULL );

        m_fTexCoords[c-32][0] = ((FLOAT)(x + 0       - m_dwSpacing))/m_dwTexWidth;
        m_fTexCoords[c-32][1] = ((FLOAT)(y + 0       + 0          ))/m_dwTexHeight;
        m_fTexCoords[c-32][2] = ((FLOAT)(x + size.cx + m_dwSpacing))/m_dwTexWidth;
        m_fTexCoords[c-32][3] = ((FLOAT)(y + size.cy + 0          ))/m_dwTexHeight;

        x += size.cx + (2 * m_dwSpacing);
    }

    // Create a new texture for the font
    //m_pRaster = RwRasterCreate(m_dwTexWidth, m_dwTexHeight,NULL,rwRASTERTYPETEXTURE|rwRASTERFORMAT4444); //Put here 8888 to have 8888 sized

    // Lock the surface and write the alpha values for the set pixels
    //RwRasterLock(m_pRaster,0,rwRASTERLOCKWRITE);
    BYTE* pDstRow = (BYTE*)m_pRaster->pPixels;
    WORD* pDst16;
    BYTE bAlpha; // 4-bit measure of pixel intensity

   //8888 Raster Palette version
    /*
    for (long Index = 0; Index < m_dwTexHeight * m_dwTexWidth * 4; Index += 4)   
    {   
        BYTE Value = (BYTE)*((BYTE *)pBitmapBits + Index);   
        *((BYTE *)m_pRaster->cpPixels + Index + 0) = Value;   
        *((BYTE *)m_pRaster->cpPixels + Index + 1) = Value;   
        *((BYTE *)m_pRaster->cpPixels + Index + 2) = Value;   
        *((BYTE *)m_pRaster->cpPixels + Index + 3) = Value;   
    }   
    */
    //4444 Raster palette version
    
    for( y=0; y < m_dwTexHeight; y++ )
    {
        pDst16 = (WORD*)pDstRow;
        for( x=0; x < m_dwTexWidth; x++ )
        {
            bAlpha = (BYTE)((pBitmapBits[m_dwTexWidth*y + x] & 0xff) >> 4);
            if (bAlpha > 0)
            {
                *pDst16++ = (WORD) ((bAlpha << 12) | 0x0fff);
            }
            else
            {
                *pDst16++ = 0x0000;
            }
        }
        pDstRow += m_pRaster->nStride;
    }
    
    // Done updating texture, so clean up used objects
    RwRasterUnlock(m_pRaster);
    SelectObject( hDC, hbmOld );
    SelectObject( hDC, hFontOld );
    DeleteObject( hbmBitmap );
    DeleteObject( hFont );
    DeleteDC( hDC );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: GetTextExtent()
// Desc: Get the dimensions of a text string
//-----------------------------------------------------------------------------
HRESULT CCustomFont::GetTextExtent( const TCHAR* strText, SIZE* pSize )
{
    if( NULL==strText || NULL==pSize )
        return E_FAIL;

    FLOAT fRowWidth  = 0.0f;
    FLOAT fRowHeight = (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight;
    FLOAT fWidth     = 0.0f;
    FLOAT fHeight    = fRowHeight;

    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            fRowWidth = 0.0f;
            fHeight  += fRowHeight;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        FLOAT tx1 = m_fTexCoords[c-32][0];
        FLOAT tx2 = m_fTexCoords[c-32][2];

        fRowWidth += (tx2-tx1)*m_dwTexWidth - 2*m_dwSpacing;

        if( fRowWidth > fWidth )
            fWidth = fRowWidth;
    }

    pSize->cx = (int)fWidth;
    pSize->cy = (int)fHeight;

    return S_OK;
}

/*

//-----------------------------------------------------------------------------
// Name: DrawTextScaled()
// Desc: Draws scaled 2D text.  Note that x and y are in viewport coordinates
//       (ranging from -1 to +1).  fXScale and fYScale are the size fraction 
//       relative to the entire viewport.  For example, a fXScale of 0.25 is
//       1/8th of the screen width.  This allows you to output text at a fixed
//       fraction of the viewport, even if the screen or window size changes.
//-----------------------------------------------------------------------------
HRESULT CCustomFont::DrawTextScaled( FLOAT x, FLOAT y, FLOAT z,
                                  FLOAT fXScale, FLOAT fYScale, DWORD dwColor,
                                  const TCHAR* strText, DWORD dwFlags )
{

    // Set up renderstate
    m_pStateBlockSaved->Capture();
    m_pStateBlockDrawText->Apply();
    m_pd3dDevice->SetFVF( D3DFVF_FONT2DVERTEX );
    m_pd3dDevice->SetPixelShader( NULL );
    m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT2DVERTEX) );

    // Set filter states
    if( dwFlags & D3DFONT_FILTERED )
    {
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    D3DVIEWPORT9 vp;
    m_pd3dDevice->GetViewport( &vp );
    FLOAT fLineHeight = ( m_fTexCoords[0][3] - m_fTexCoords[0][1] ) * m_dwTexHeight;

    // Center the text block in the viewport
    if( dwFlags & D3DFONT_CENTERED_X )
    {
        const TCHAR* strTextTmp = strText;
        float xFinal = 0.0f;

        while( *strTextTmp )
        {
            TCHAR c = *strTextTmp++;
    
            if( c == _T('\n') )
                break;  // Isn't supported.  
            if( (c-32) < 0 || (c-32) >= 128-32 )
                continue;

            FLOAT tx1 = m_fTexCoords[c-32][0];
            FLOAT tx2 = m_fTexCoords[c-32][2];

            FLOAT w = (tx2-tx1)*m_dwTexWidth;

            w *= (fXScale*vp.Height)/fLineHeight;

            xFinal += w - (2 * m_dwSpacing) * (fXScale*vp.Height)/fLineHeight;
        }

        x = -xFinal/vp.Width;
    }
    if( dwFlags & D3DFONT_CENTERED_Y )
    {
        y = -fLineHeight/vp.Height;
    }

    FLOAT sx  = (x+1.0f)*vp.Width/2;
    FLOAT sy  = (y+1.0f)*vp.Height/2;
    FLOAT sz  = z;
    FLOAT rhw = 1.0f;

    // Adjust for character spacing
    sx -= m_dwSpacing * (fXScale*vp.Height)/fLineHeight;
    FLOAT fStartX = sx;

    // Fill vertex buffer
    FONT2DVERTEX* pVertices;
    DWORD         dwNumTriangles = 0L;
    m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            sx  = fStartX;
            sy += fYScale*vp.Height;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        FLOAT tx1 = m_fTexCoords[c-32][0];
        FLOAT ty1 = m_fTexCoords[c-32][1];
        FLOAT tx2 = m_fTexCoords[c-32][2];
        FLOAT ty2 = m_fTexCoords[c-32][3];

        FLOAT w = (tx2-tx1)*m_dwTexWidth;
        FLOAT h = (ty2-ty1)*m_dwTexHeight;

        w *= (fXScale*vp.Height)/fLineHeight;
        h *= (fYScale*vp.Height)/fLineHeight;

        if( c != _T(' ') )
        {
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+0-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx1, ty2 );
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+0-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx1, ty1 );
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+w-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+w-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx2, ty1 );
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+w-0.5f,sy+h-0.5f,sz,rhw), dwColor, tx2, ty2 );
            *pVertices++ = InitFont2DVertex( D3DXVECTOR4(sx+0-0.5f,sy+0-0.5f,sz,rhw), dwColor, tx1, ty1 );
            dwNumTriangles += 2;

            if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
            {
                // Unlock, render, and relock the vertex buffer
                m_pVB->Unlock();
                m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
                m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
                dwNumTriangles = 0L;
            }
        }

        sx += w - (2 * m_dwSpacing) * (fXScale*vp.Height)/fLineHeight;
    }

    // Unlock and render the vertex buffer
    m_pVB->Unlock();
    if( dwNumTriangles > 0 )
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );

    // Restore the modified renderstates
    m_pStateBlockSaved->Apply();

    return S_OK;
}
*/



//-----------------------------------------------------------------------------
// Name: DrawText()
// Desc: Draws 2D text. Note that sx and sy are in pixels
//-----------------------------------------------------------------------------
#define gtaZbufferNear *(float*)0x97F05C
#define gtafogPlane *(float*)0x94DB54
HRESULT CCustomFont::DrawText( FLOAT sx, FLOAT sy, DWORD dwColor,
                            const TCHAR* strText, DWORD dwFlags )
{
    if (strText == NULL) //Check if pointer is not NULL
        return S_FALSE;
    // Setup renderstate
    //m_pStateBlockSaved->Capture();
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &m_pStateBlockSaved.textureFilterMode);
    RwRenderStateGet(rwRENDERSTATESRCBLEND ,&m_pStateBlockSaved.blendSourceFunction);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &m_pStateBlockSaved.blendDestFunction);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &m_pStateBlockSaved.vertexAlphaEnable);

    ///m_pStateBlockDrawText->Apply();
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)m_pRaster);

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATESRCBLEND ,(void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    
    //char jptbuf[100];
    //sprintf(jptbuf,"filter: %d\nSRCBLEND: %d\nDESTBLEND: %d\nVertexAlpha: %d",m_pStateBlockSaved.textureFilterMode,m_pStateBlockSaved.blendSourceFunction,m_pStateBlockSaved.blendDestFunction,m_pStateBlockSaved.vertexAlphaEnable);
    //MessageBoxA(NULL,jptbuf,NULL,NULL);
    //m_pd3dDevice->SetPixelShader( NULL );

    // Set filter states
    //if( dwFlags & D3DFONT_FILTERED )
    //{
        //m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        //m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    //}

    // Center the text block in the viewport
    if( dwFlags & D3DFONT_CENTERED_X )
    {
        
        const TCHAR* strTextTmp = strText;
        float xFinal = 0.0f;

        while( *strTextTmp )
        {
            TCHAR c = *strTextTmp++;
    
            if( c == _T('\n') )
                break;  // Isn't supported.  
            if( (c-32) < 0 || (c-32) >= 128-32 )
                continue;

            FLOAT tx1 = m_fTexCoords[c-32][0];
            FLOAT tx2 = m_fTexCoords[c-32][2];
    
            FLOAT w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
    
            xFinal += w - (2 * m_dwSpacing);
        }

        sx = (ResolutionX-xFinal)/2.0f;
    }
    if( dwFlags & D3DFONT_CENTERED_Y )
    {
        float fLineHeight = ((m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight);
        sy = (ResolutionY-fLineHeight)/2;
    }

    // Adjust for character spacing
    sx -= m_dwSpacing;
    FLOAT fStartX = sx;

    // Fill vertex buffer
    DWORD        dwNumTriangles = 0;
    DWORD        dwVertexCount = 0;
    DWORD        dwRenderCount = 0;
    
    
    while( *strText )
    {
        TCHAR c = *strText++;

        if( c == _T('\n') )
        {
            sx = fStartX;
            sy += (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        FLOAT tx1 = m_fTexCoords[c-32][0];
        FLOAT ty1 = m_fTexCoords[c-32][1];
        FLOAT tx2 = m_fTexCoords[c-32][2];
        FLOAT ty2 = m_fTexCoords[c-32][3];

        FLOAT w = (tx2-tx1) *  m_dwTexWidth / m_fTextScale;
        FLOAT h = (ty2-ty1) * m_dwTexHeight / m_fTextScale;

        if( c != _T(' ') )
        {
            pVertices[0+dwVertexCount*6].x = sx+0-0.5f;
            pVertices[0+dwVertexCount*6].y = sy+h-0.5f;
            pVertices[0+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[0+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[0+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[0+dwVertexCount*6].u = tx1;
            pVertices[0+dwVertexCount*6].v = ty2;

            pVertices[1+dwVertexCount*6].x = sx+0-0.5f;
            pVertices[1+dwVertexCount*6].y = sy+0-0.5f;
            pVertices[1+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[1+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[1+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[1+dwVertexCount*6].u = tx1;
            pVertices[1+dwVertexCount*6].v = ty1;

            pVertices[2+dwVertexCount*6].x = sx+w-0.5f;
            pVertices[2+dwVertexCount*6].y = sy+h-0.5f;
            pVertices[2+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[2+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[2+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[2+dwVertexCount*6].u = tx2;
            pVertices[2+dwVertexCount*6].v = ty2;

            pVertices[3+dwVertexCount*6].x = sx+w-0.5f;
            pVertices[3+dwVertexCount*6].y = sy+0-0.5f;
            pVertices[3+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[3+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[3+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[3+dwVertexCount*6].u = tx2;
            pVertices[3+dwVertexCount*6].v = ty1;

            pVertices[4+dwVertexCount*6].x = sx+w-0.5f;
            pVertices[4+dwVertexCount*6].y = sy+h-0.5f;
            pVertices[4+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[4+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[4+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[4+dwVertexCount*6].u = tx2;
            pVertices[4+dwVertexCount*6].v = ty2;

            pVertices[5+dwVertexCount*6].x = sx+0-0.5f;
            pVertices[5+dwVertexCount*6].y = sy+0-0.5f;
            pVertices[5+dwVertexCount*6].z = gtaZbufferNear;
            pVertices[5+dwVertexCount*6].rhw = gtafogPlane;
            pVertices[5+dwVertexCount*6].emissiveColor = dwColor;
            pVertices[5+dwVertexCount*6].u = tx1;
            pVertices[5+dwVertexCount*6].v = ty1;
      
            dwNumTriangles += 2;
            dwVertexCount++;

            if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
            {
                // Render the vertex buffer at maximum vertices
                RwIm2DRenderPrimitive(rwPRIMTYPETRILIST,&pVertices[dwRenderCount*dwNumTriangles*3], dwNumTriangles*3);
                
                dwNumTriangles = 0L;
                dwRenderCount++;
            }
        }

        sx += w - (2 * m_dwSpacing);
    }

    // Render the vertices if present
    if( dwNumTriangles > 0 )
        RwIm2DRenderPrimitive(rwPRIMTYPETRILIST,&pVertices[(dwRenderCount)*MAX_NUM_VERTICES], dwNumTriangles*3);

    // Restore the modified renderstates
    //m_pStateBlockSaved->Apply();
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)m_pStateBlockSaved.textureFilterMode);
    RwRenderStateSet(rwRENDERSTATESRCBLEND ,(void*)m_pStateBlockSaved.blendSourceFunction);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)m_pStateBlockSaved.blendDestFunction);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)m_pStateBlockSaved.vertexAlphaEnable);

    return S_OK;
}



/*
//-----------------------------------------------------------------------------
// Name: Render3DText()
// Desc: Renders 3D text
//-----------------------------------------------------------------------------
HRESULT CD3DFont::Render3DText( const TCHAR* strText, DWORD dwFlags )
{
    if( m_pd3dDevice == NULL )
        return E_FAIL;

    // Setup renderstate
    m_pStateBlockSaved->Capture();
    m_pStateBlockDrawText->Apply();
    m_pd3dDevice->SetFVF( D3DFVF_FONT3DVERTEX );
    m_pd3dDevice->SetPixelShader( NULL );
    m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(FONT3DVERTEX) );

    // Set filter states
    if( dwFlags & D3DFONT_FILTERED )
    {
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    }

    // Position for each text element
    FLOAT x = 0.0f;
    FLOAT y = 0.0f;

    // Center the text block at the origin (not the viewport)
    if( dwFlags & D3DFONT_CENTERED_X )
    {
        SIZE sz;
        GetTextExtent( strText, &sz );
        x = -(((FLOAT)sz.cx)/10.0f)/2.0f;
    }
    if( dwFlags & D3DFONT_CENTERED_Y )
    {
        SIZE sz;
        GetTextExtent( strText, &sz );
        y = -(((FLOAT)sz.cy)/10.0f)/2.0f;
    }

    // Turn off culling for two-sided text
    if( dwFlags & D3DFONT_TWOSIDED )
        m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Adjust for character spacing
    x -= m_dwSpacing / 10.0f;
    FLOAT fStartX = x;
    TCHAR c;

    // Fill vertex buffer
    FONT3DVERTEX* pVertices;
    DWORD         dwNumTriangles = 0L;
    m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );

    while( (c = *strText++) != 0 )
    {
        if( c == '\n' )
        {
            x = fStartX;
            y -= (m_fTexCoords[0][3]-m_fTexCoords[0][1])*m_dwTexHeight/10.0f;
        }

        if( (c-32) < 0 || (c-32) >= 128-32 )
            continue;

        FLOAT tx1 = m_fTexCoords[c-32][0];
        FLOAT ty1 = m_fTexCoords[c-32][1];
        FLOAT tx2 = m_fTexCoords[c-32][2];
        FLOAT ty2 = m_fTexCoords[c-32][3];

        FLOAT w = (tx2-tx1) * m_dwTexWidth  / ( 10.0f * m_fTextScale );
        FLOAT h = (ty2-ty1) * m_dwTexHeight / ( 10.0f * m_fTextScale );

        if( c != _T(' ') )
        {
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+0,y+0,0), D3DXVECTOR3(0,0,-1), tx1, ty2 );
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+0,y+h,0), D3DXVECTOR3(0,0,-1), tx1, ty1 );
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+w,y+0,0), D3DXVECTOR3(0,0,-1), tx2, ty2 );
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+w,y+h,0), D3DXVECTOR3(0,0,-1), tx2, ty1 );
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+w,y+0,0), D3DXVECTOR3(0,0,-1), tx2, ty2 );
            *pVertices++ = InitFont3DVertex( D3DXVECTOR3(x+0,y+h,0), D3DXVECTOR3(0,0,-1), tx1, ty1 );
            dwNumTriangles += 2;

            if( dwNumTriangles*3 > (MAX_NUM_VERTICES-6) )
            {
                // Unlock, render, and relock the vertex buffer
                m_pVB->Unlock();
                m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );
                m_pVB->Lock( 0, 0, (void**)&pVertices, D3DLOCK_DISCARD );
                dwNumTriangles = 0L;
            }
        }

        x += w - (2 * m_dwSpacing) / 10.0f;
    }

    // Unlock and render the vertex buffer
    m_pVB->Unlock();
    if( dwNumTriangles > 0 )
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, dwNumTriangles );

    // Restore the modified renderstates
    m_pStateBlockSaved->Apply();

    return S_OK;
}



*/