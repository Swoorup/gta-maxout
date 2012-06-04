/*
	file:
		IDirect3D8Hook.cpp
	desc:
		This is the code for wrapping the IDirect3D8 interface.
*/

// Includes
#include "IDirect3D8Hook.h"

// Externals
extern bool bWindowedMode;
extern IDirect3D8 *pD3D;
extern IDirect3DDevice8 *pD3DDevice;
extern IDirect3DDevice8Hook *pD3DDeviceHook;

// Globals
D3DDISPLAYMODE D3DDisplayMode;

// Functions
HRESULT __stdcall IDirect3D8Hook::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice8** ppReturnedDeviceInterface)
{
    static HANDLE IconHandle = 0;
    if ( IconHandle == 0) 
        IconHandle = LoadImage((HINSTANCE)GetWindowLong(pPresentationParameters->hDeviceWindow,GWL_HINSTANCE), "Icons//SOL.ico",IMAGE_ICON, 0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
    SetClassLong(pPresentationParameters->hDeviceWindow, GCL_HICON, (LONG)IconHandle);
	if (bWindowedMode)
	{
		pPresentationParameters->Windowed = TRUE;
		pPresentationParameters->Flags = 0;
		pPresentationParameters->FullScreen_RefreshRateInHz = 0;
		pPresentationParameters->FullScreen_PresentationInterval = 0;

		GetAdapterDisplayMode(Adapter, &D3DDisplayMode);
		pPresentationParameters->BackBufferFormat = D3DDisplayMode.Format;

        RECT R = { 0, 0, pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight};
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		AdjustWindowRect(&R, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, false);

        int RectWidth = R.right - R.left;
        int RectHeight = R.bottom - R.top;

        R.left   += screenWidth/2 - RectWidth/2;
        R.top    += screenHeight/2 - RectHeight/2;
        R.right  = R.left + RectWidth;
        R.bottom = R.top + RectHeight;

        if (RectWidth < screenWidth && RectHeight < screenHeight)
        SetWindowLong(pPresentationParameters->hDeviceWindow, GWL_STYLE, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
        SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_TOP, R.left, R.top, RectWidth, RectHeight, SWP_SHOWWINDOW|SWP_NOZORDER);
	}

	HRESULT hr = pD3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	pD3DDevice = *ppReturnedDeviceInterface;
	pD3DDeviceHook = &D3DDevice8Hook;
	//CustomInitialize(pD3DDevice, pPresentationParameters);
	*ppReturnedDeviceInterface = pD3DDeviceHook;
	return hr;
}

ULONG __stdcall IDirect3D8Hook::AddRef(void)
{
	if (++m_iRef > 0)
	{
		return pD3D->AddRef();
	} else {
		return 0;
	}
}

ULONG __stdcall IDirect3D8Hook::Release(void)
{
	if (--m_iRef > 0)
	{
		return pD3D->Release();
	} else {
		return 0;
	}
}

//################################################################################

HRESULT __stdcall IDirect3D8Hook::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pD3D->QueryInterface(iid, ppvObject);
}

HRESULT __stdcall IDirect3D8Hook::RegisterSoftwareDevice(void *pInitializeFunction)
{
	return pD3D->RegisterSoftwareDevice(pInitializeFunction);
}

UINT __stdcall IDirect3D8Hook::GetAdapterCount(void)
{
	return pD3D->GetAdapterCount();
}

HRESULT __stdcall IDirect3D8Hook::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER8* pIdentifier)
{
	return pD3D->GetAdapterIdentifier(Adapter, Flags , pIdentifier);;
}

UINT __stdcall IDirect3D8Hook::GetAdapterModeCount(UINT Adapter)
{
	return pD3D->GetAdapterModeCount(Adapter);
}

HRESULT __stdcall IDirect3D8Hook::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return pD3D->EnumAdapterModes(Adapter, Mode, pMode);
}

HRESULT __stdcall IDirect3D8Hook::GetAdapterDisplayMode(UINT Adapter,D3DDISPLAYMODE *pMode)
{
	return pD3D->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT __stdcall IDirect3D8Hook::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed)
{
	return pD3D->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

HRESULT __stdcall IDirect3D8Hook::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return pD3D->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT __stdcall IDirect3D8Hook::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType)
{
	return pD3D->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType);
}

HRESULT __stdcall IDirect3D8Hook::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return pD3D->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT __stdcall IDirect3D8Hook::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps)
{
	return pD3D->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR __stdcall IDirect3D8Hook::GetAdapterMonitor(UINT Adapter)
{
	return pD3D->GetAdapterMonitor(Adapter);
}
