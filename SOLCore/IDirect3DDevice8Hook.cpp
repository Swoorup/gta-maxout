/*
	file:
		IDirect3DDevice8Hook.cpp
	desc:
		This is the code for wrapping the IDirect3DDevice8 interface.
*/

// Includes
#include "IDirect3DDevice8Hook.h"
#include "IDirect3D8Hook.h"
//#include "Custom.h"

// Externals
extern bool bWindowedMode;
extern IDirect3D8Hook *pD3DHook;
extern IDirect3DDevice8 *pD3DDevice;
extern D3DDISPLAYMODE D3DDisplayMode;

// Functions
HRESULT __stdcall IDirect3DDevice8Hook::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	//CustomRender(pD3DDevice);

	return pD3DDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall IDirect3DDevice8Hook::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    if (bWindowedMode)
	{
		pPresentationParameters->Windowed = TRUE;
		pPresentationParameters->Flags = 0;
		pPresentationParameters->FullScreen_RefreshRateInHz = 0;
		pPresentationParameters->FullScreen_PresentationInterval = 0;

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
        
        SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_TOP, R.left, R.top, RectWidth, RectHeight, SWP_SHOWWINDOW|SWP_NOZORDER);
        if (RectWidth < screenWidth && RectHeight < screenHeight){
        SetWindowLong(pPresentationParameters->hDeviceWindow, GWL_STYLE, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
        }
	}

	//CustomReset();
	HRESULT hr = pD3DDevice->Reset(pPresentationParameters);
	//if (SUCCEEDED(hr)) CustomInitialize(pD3DDevice, pPresentationParameters);
	return hr;
}

ULONG __stdcall IDirect3DDevice8Hook::AddRef()
{
	if (++m_iRef > 0)
	{
		return pD3DDevice->AddRef();
	} else {
		return 0;
	}
}

ULONG __stdcall IDirect3DDevice8Hook::Release()
{
	if (--m_iRef > 0)
	{
		return pD3DDevice->Release();
	} else {
		return 0;
	}
}

HRESULT __stdcall IDirect3DDevice8Hook::GetDirect3D(IDirect3D8** ppD3D)
{
	*ppD3D = pD3DHook;
	return D3D_OK;
}

//################################################################################

HRESULT __stdcall IDirect3DDevice8Hook::BeginScene()
{
	return pD3DDevice->BeginScene();
}

HRESULT __stdcall IDirect3DDevice8Hook::EndScene()
{
	return pD3DDevice->EndScene();
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return pD3DDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	return pD3DDevice->DrawIndexedPrimitive(Type, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture)
{
	return pD3DDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetTexture(DWORD Stage, IDirect3DBaseTexture8* pTexture)
{
	return pD3DDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer)
{
	return pD3DDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer)
{
	return pD3DDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride)
{
	return pD3DDevice->SetStreamSource(StreamNumber, pStreamData, Stride);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pD3DDevice->SetTransform(State, pMatrix);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return pD3DDevice->SetRenderState(State, Value);
}

void __stdcall IDirect3DDevice8Hook::SetGammaRamp(DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	pD3DDevice->SetGammaRamp(Flags, pRamp);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetViewport(CONST D3DVIEWPORT8* pViewport)
{
	return pD3DDevice->SetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture)
{
	return pD3DDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture)
{
	return pD3DDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::QueryInterface(REFIID iid, void **ppvObject)
{
	return pD3DDevice->QueryInterface(iid, ppvObject);
}

HRESULT __stdcall IDirect3DDevice8Hook::TestCooperativeLevel()
{
	return pD3DDevice->TestCooperativeLevel();
}

UINT __stdcall IDirect3DDevice8Hook::GetAvailableTextureMem()
{
	return pD3DDevice->GetAvailableTextureMem();
}

HRESULT __stdcall IDirect3DDevice8Hook::ResourceManagerDiscardBytes(DWORD Bytes)
{
	return pD3DDevice->ResourceManagerDiscardBytes(Bytes);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetDeviceCaps(D3DCAPS8* pCaps)
{
	return pD3DDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
	return pD3DDevice->GetDisplayMode(pMode);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return pD3DDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap)
{
	return pD3DDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall IDirect3DDevice8Hook::SetCursorPosition(int X, int Y, DWORD Flags)
{
	pD3DDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall IDirect3DDevice8Hook::ShowCursor(BOOL bShow)
{
	return pD3DDevice->ShowCursor(bShow);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** ppSwapChain)
{
	return pD3DDevice->CreateAdditionalSwapChain(pPresentationParameters, ppSwapChain);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{
	return pD3DDevice->GetBackBuffer(BackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
	return pD3DDevice->GetRasterStatus(pRasterStatus);
}

void __stdcall IDirect3DDevice8Hook::GetGammaRamp(D3DGAMMARAMP* pRamp)
{
	pD3DDevice->GetGammaRamp(pRamp);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice->CreateRenderTarget(Width, Height, Format, MultiSample, Lockable, ppSurface);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, ppSurface);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface)
{
	return pD3DDevice->CreateImageSurface(Width, Height, Format, ppSurface);
}

HRESULT __stdcall IDirect3DDevice8Hook::CopyRects(IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray)
{
	return pD3DDevice->CopyRects(pSourceSurface, pSourceRectsArray, cRects, pDestinationSurface, pDestPointsArray);
}

HRESULT __stdcall IDirect3DDevice8Hook::UpdateTexture(IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture)
{
	return pD3DDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetFrontBuffer(IDirect3DSurface8* pDestSurface)
{
	return pD3DDevice->GetFrontBuffer(pDestSurface);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetRenderTarget(IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil)
{
	return pD3DDevice->SetRenderTarget(pRenderTarget, pNewZStencil);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetRenderTarget(IDirect3DSurface8** ppRenderTarget)
{
	return pD3DDevice->GetRenderTarget(ppRenderTarget);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetDepthStencilSurface(IDirect3DSurface8** ppZStencilSurface)
{
	return pD3DDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall IDirect3DDevice8Hook::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return pD3DDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return pD3DDevice->GetTransform(State, pMatrix);
}

HRESULT __stdcall IDirect3DDevice8Hook::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pD3DDevice->MultiplyTransform(State, pMatrix);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetViewport(D3DVIEWPORT8* pViewport )
{
	return pD3DDevice->GetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetMaterial(CONST D3DMATERIAL8* pMaterial)
{
	return pD3DDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetMaterial(D3DMATERIAL8* pMaterial)
{
	return pD3DDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetLight(DWORD Index, CONST D3DLIGHT8* pLight)
{
	return pD3DDevice->SetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetLight(DWORD Index, D3DLIGHT8* pLight)
{
	return pD3DDevice->GetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice8Hook::LightEnable(DWORD LightIndex, BOOL bEnable)
{
	return pD3DDevice->LightEnable(LightIndex, bEnable);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return pD3DDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetClipPlane(DWORD Index, CONST float* pPlane )
{
	return pD3DDevice->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetClipPlane(DWORD Index, float* pPlane)
{
	return pD3DDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return pD3DDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall IDirect3DDevice8Hook::BeginStateBlock()
{
	return pD3DDevice->BeginStateBlock();
}

HRESULT __stdcall IDirect3DDevice8Hook::EndStateBlock(DWORD* pToken)
{
	return pD3DDevice->EndStateBlock(pToken);
}

HRESULT __stdcall IDirect3DDevice8Hook::ApplyStateBlock(DWORD Token)
{
	return pD3DDevice->ApplyStateBlock(Token);
}

HRESULT __stdcall IDirect3DDevice8Hook::CaptureStateBlock(DWORD Token)
{
	return pD3DDevice->CaptureStateBlock(Token);
}

HRESULT __stdcall IDirect3DDevice8Hook::DeleteStateBlock(DWORD Token)
{
	return pD3DDevice->DeleteStateBlock(Token);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
	return pD3DDevice->CreateStateBlock(Type, pToken);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetClipStatus(CONST D3DCLIPSTATUS8* pClipStatus)
{
	return pD3DDevice->SetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetClipStatus(D3DCLIPSTATUS8* pClipStatus)
{
	return pD3DDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetTexture(DWORD Stage, IDirect3DBaseTexture8** ppTexture)
{
	return pD3DDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return pD3DDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
	return pD3DDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall IDirect3DDevice8Hook::ValidateDevice(DWORD* pNumPasses)
{
	return pD3DDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetInfo(DWORD DevInfoID, VOID* pDevInfoStruct, DWORD DevInfoStructSize)
{
	return pD3DDevice->GetInfo(DevInfoID, pDevInfoStruct, DevInfoStructSize);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return pD3DDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return pD3DDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return pD3DDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetCurrentTexturePalette(UINT* pPaletteNumber)
{
	return pD3DDevice->GetCurrentTexturePalette(pPaletteNumber);
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pD3DDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pD3DDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice8Hook::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags)
{
	return pD3DDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, Flags);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreateVertexShader(CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage)
{
	return pD3DDevice->CreateVertexShader(pDeclaration, pFunction, pHandle, Usage);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetVertexShader(DWORD Handle)
{
	return pD3DDevice->SetVertexShader(Handle);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetVertexShader(DWORD* pHandle)
{
	return pD3DDevice->GetVertexShader(pHandle);
}

HRESULT __stdcall IDirect3DDevice8Hook::DeleteVertexShader(DWORD Handle)
{
	return pD3DDevice->DeleteVertexShader(Handle);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetVertexShaderConstant(DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice->SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetVertexShaderConstant(DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice->GetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetVertexShaderDeclaration(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice->GetVertexShaderDeclaration(Handle, pData, pSizeOfData);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetVertexShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice->GetVertexShaderFunction(Handle, pData, pSizeOfData);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride)
{
	return pD3DDevice->GetStreamSource(StreamNumber, ppStreamData, pStride);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetIndices(IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex)
{
	return pD3DDevice->SetIndices(pIndexData, BaseVertexIndex);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetIndices(IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex)
{
	return pD3DDevice->GetIndices(ppIndexData, pBaseVertexIndex);
}

HRESULT __stdcall IDirect3DDevice8Hook::CreatePixelShader(CONST DWORD* pFunction, DWORD* pHandle)
{
	return pD3DDevice->CreatePixelShader(pFunction, pHandle);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetPixelShader(DWORD Handle)
{
	return pD3DDevice->SetPixelShader(Handle);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetPixelShader(DWORD* pHandle)
{
	return pD3DDevice->GetPixelShader(pHandle);
}

HRESULT __stdcall IDirect3DDevice8Hook::DeletePixelShader(DWORD Handle)
{
	return pD3DDevice->DeletePixelShader(Handle);
}

HRESULT __stdcall IDirect3DDevice8Hook::SetPixelShaderConstant(DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice->SetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetPixelShaderConstant(DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return pD3DDevice->GetPixelShaderConstant(Register, pConstantData, ConstantCount);
}

HRESULT __stdcall IDirect3DDevice8Hook::GetPixelShaderFunction(DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return pD3DDevice->GetPixelShaderFunction(Handle, pData, pSizeOfData);
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return pD3DDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall IDirect3DDevice8Hook::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return pD3DDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall IDirect3DDevice8Hook::DeletePatch(UINT Handle)
{
	return pD3DDevice->DeletePatch(Handle);
}
