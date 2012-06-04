#ifndef D3D8HOOKINIT_H
#define D3D8HOOKINIT_H

#include "IDirect3D8Hook.h"
#include "IDirect3DDevice8Hook.h"
#include "StdInc.h"

typedef IDirect3D8* (WINAPI *Direct3DCreate8_t)(UINT SDKVersion);

void D3D8HookInit(bool bWindowed);
extern IDirect3DDevice8 *pD3DDevice;

#endif