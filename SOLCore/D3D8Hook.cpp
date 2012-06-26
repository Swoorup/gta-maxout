#include "StdInc.h"

bool bWindowedMode;

IDirect3D8Hook D3D8Hook;
IDirect3D8 *pD3D;
IDirect3D8Hook *pD3DHook;
IDirect3DDevice8 *pD3DDevice;
IDirect3DDevice8Hook *pD3DDeviceHook;


DWORD OldDirect3DCreate8 = 0x66355C;
IDirect3D8* WINAPI NewDirect3DCreate8(UINT SDKVersion)
{
	//pD3D = OldDirect3DCreate8(SDKVersion);	// Create a real IDirect3D8 interface for us.
    __asm{
        push SDKVersion
        call OldDirect3DCreate8
        mov pD3D, eax
    }
	pD3DHook = &D3D8Hook;	// Get a pointer to our IDirect3D8Hook interface.
	return pD3DHook;		// Give Vice City our fake IDirect3D8 interface pointer.
}

void D3D8HookInit(bool bWindowed)
{
    CMemory::InstallCallHook(0x600FC0, &NewDirect3DCreate8, ASM_CALL);
    CMemory::InstallCallHook(0x65B857, &NewDirect3DCreate8, ASM_CALL);
    bWindowedMode = bWindowed;
}