#ifndef D3D8HOOKINIT_H
#define D3D8HOOKINIT_H

#include "SJLIB/stdinc.h"

//#define CEGUI_STATIC
//
/*/
#pragma comment(lib,"CEGUIFalagardWRBase_Static.lib")
#pragma comment(lib,"CEGUISILLYImageCodec_Static.lib")
#pragma comment(lib, "CEGUIExpatParser_Static.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"pcre.lib")
#pragma comment(lib,"SILLY.lib")
#pragma comment(lib,"libjpeg.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "libexpat.lib")
#pragma comment(lib, "zlib.lib")*/

typedef IDirect3D8* (WINAPI *Direct3DCreate8_t)(UINT SDKVersion);

void D3D8HookInit(bool bWindowed);
extern IDirect3DDevice8 *pD3DDevice;

#endif