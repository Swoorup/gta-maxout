
/*****************************************************************************
*
*  PROJECT:     State Of Liberty
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        sdk/game/RenderWare.h
*  PURPOSE:     RenderWare-compatible definitions for
*               Grand Theft Auto: Vice City
*
*  RenderWare is © Criterion Software
*
*****************************************************************************/

#ifndef __RENDERWARE_COMPAT
#define __RENDERWARE_COMPAT

#include <Windows.h>
#include <stdint.h>
// Include d3d8 structures, enums and macros
#include <d3d8.h>
#include <d3dx8.h>

#include "renderwaretypes.h"

// RenderWare primitive types




//An efficient CRGBA class :)
class CRGBA {
public:
	unsigned char r,g,b,a;

	CRGBA() : r(0), g(0), b(0), a(0){}
	CRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a){}
};





//Very efficient Class :)
class CRect {
public:
	float left;
	float bottom;
	float right;
	float top;

	CRect() {}
	CRect(float left, float bottom, float right, float top) : left(left), bottom(bottom), right(right), top(top) {}
};


/*****************************************************************************/
/** Renderware function definations and forward declarations                **/
/*****************************************************************************/

typedef bool (__cdecl *RwRenderStateSet_t)(RwRenderState state, void* value);
typedef bool (__cdecl *RwRenderStateGet_t)(RwRenderState state, void* value);
typedef int (__cdecl *RwIm2DRenderPrimitive_t)(RwPrimitiveType primType,RwIm2DVertex *vertices,int numVertices);  
typedef void *(*RwIm3DTransform_t)(RwIm3DVertex *pVerts, int numVerts, void *ltm, int flags);
typedef bool (*RwIm3DRenderIndexedPrimitive_t)(int primType, RwImVertexIndex *indices, int numIndices);
typedef RwRaster*(__cdecl *RwRasterUnlock_t)(RwRaster *raster);
//Returns pointer to the raster's pixel data if successful or NULL if there is an error.
typedef unsigned int*(__cdecl *RwRasterLock_t)(RwRaster *raster, unsigned __int8 level, int lockmode);
typedef RwRaster*(__cdecl *RwRasterCreate_t)(int width, int height, int depth, int flags);
typedef bool (__cdecl *RwRasterDestroy_t)(RwRaster *raster);
typedef RwTexture* (__cdecl *RwTextureRead_t)(char* _name,char* _maskName);
typedef int (__cdecl *RwTextureDestroy_t)(RwTexture*);
typedef RwTexture* (__cdecl *RwTextureCreate_t)(RwRaster* raster);
typedef bool (__cdecl *RwTextureRasterGenerateMipmaps_t)(RwRaster* raster,RwImage* image);
typedef signed int (__cdecl *RwD3D8SetRenderState_t)(D3DRENDERSTATETYPE state, DWORD value);
typedef signed int (__cdecl *RwD3D8SetTextureStageState_t)(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
typedef RwV3d* (__cdecl *RwV3dTransformPoints_t)(RwV3d* pointOut, const RwV3d* pointIn, int numPoints, const RwMatrix* matrix);


extern RwRenderStateSet_t RwRenderStateSet;
extern RwRenderStateGet_t RwRenderStateGet;
extern RwIm2DRenderPrimitive_t RwIm2DRenderPrimitive;
extern RwIm3DTransform_t RwIm3DTransform;
extern RwIm3DRenderIndexedPrimitive_t RwIm3DRenderIndexedPrimitive;
extern RwRasterLock_t   RwRasterLock;
extern RwRasterUnlock_t RwRasterUnlock;
extern RwRasterDestroy_t RwRasterDestroy;
extern RwTextureRead_t RwTextureRead;
extern RwTextureRasterGenerateMipmaps_t RwTextureRasterGenerateMipMaps;
extern RwD3D8SetRenderState_t RwD3D8SetRenderState;
extern RwD3D8SetTextureStageState_t RwD3D8SetTextureStageState;




#pragma pack(push, 1)

extern RwGlobals*& RwEngineInstance;

extern RwGlobals*& RwEngineInstance;
extern RwObjectCallBack SetVehicleAtomicVisibilityCB;
extern RwPluginRegistry& textureTKList;

RwChar* GetFrameNodeName(RwFrame* pFrame); //580600h

RwBool RpClumpIsSkinned(RpClump* pClump); //57F580h
RpHAnimHierarchy* RpClumpGetSkinHAnimHierarchy(RpClump* pRpClump); //57F250h
RwObject* RwFrameGetFirstObject(RwFrame* pFrame); //57F940h

void RwFreeAlign(void* pBuffer); //5805C0h

RwTexDictionary* RwTexDictionaryStreamRead(RwStream* pStream); //61E710h

extern RwPluginRegistry& clumpTKList;
extern RwPluginRegistry& atomicTKList;
extern RwUInt32& clumpModule;
extern RwUInt32& _rpClumpLightExtOffset;
extern RwUInt32& _rpClumpCameraExtOffset;
extern RwUInt32& lastSeenRightsPluginId;
extern RwUInt32& lastSeenExtraData;
RpClump* RpClumpRender(RpClump* pClump); //640CB0h
RpClump* RpClumpForAllAtomics(RpClump* pClump, RpAtomicCallBack pfnCallback, void* pData); //640D00h
RpClump* RpClumpForAllCameras(RpClump* pClump, RwCameraCallBack pCallBack, void *pData); //640D40h
RpClump* RpClumpForAllLights(RpClump* pClump, RpLightCallBack pCallBack, void *pData); //640D90h
RpAtomic* RpAtomicCreate(void); //640DE0h
RpAtomic* RpAtomicSetGeometry(RpAtomic* pAtomic, RpGeometry* pGeometry, RwUInt32 uFlags); //640ED0h*
RwBool RpAtomicDestroy(RpAtomic* pAtomic); //640F50h*
RpAtomic* RpAtomicClone(RpAtomic* pAtomic); //640FD0h
RpClump* RpClumpClone(RpClump* pClump); //6410E0h
RpLight* DestroyClumpLight(RpLight* pLight, void *pData); //641330h
RwCamera* DestroyClumpCamera(RwCamera* pCamera, void *pData); //641370h
RpClump* RpClumpCreate(void); //6413C0h
RwBool RpClumpDestroy(RpClump* pClump); //641430h
RpClump* RpClumpAddAtomic(RpClump* pClump, RpAtomic* pAtomic); //6415B0h
RpClump* RpClumpRemoveAtomic(RpClump* pClump, RpAtomic* pAtomic); //6415E0h*
RpAtomic* ClumpAtomicStreamRead(RwStream* pStream, rwFrameList* pFrameList, rpGeometryList* pGeometryList); //641640h*
RpClump* RpClumpStreamRead(RwStream* pStream); //641A10h*
RwFrame* RpClumpGetFirstFrame(RpClump* pClump); //INLINE*
RpClumpLightExt* RpClumpLightExtGet(RpLight* pLight); //INLINE*
RpClumpCameraExt* RpClumpCameraExtGet(RwCamera* pCamera); //INLINE*
RwFrame* RpClumpGetFrame(RpClump* pClump); //INLINE*
RpClump* RpClumpSetFrame(RpClump* pClump, RwFrame* pFrame); //INLINE*
RpClumpGlobals* RpClumpGlobalsGet(void); //INLINE*
RpAtomic* RpAtomicSetFrame(RpAtomic* pAtomic, RwFrame* pFrame); //6423C0h*
RwFrame* RpAtomicGetFrame(RpAtomic* pAtomic); //INLINE*
RwFrame* RpClumpGetFrame(RpClump* pClump); //INLINE*
RpAtomic* RpAtomicSetFlags(RpAtomic* pAtomic, RwUInt8 uFlags); //INLINE*
RwUInt32 RpAtomicGetVisibilityFlags(RpAtomic* pAtomic); //INLINE*
void RpAtomicSetVisibilityFlags(RpAtomic* pAtomic, RwUInt32 uFlags); //INLINE*
RwFrame* RwFrameGetParent(RwFrame* pFrame); //INLINE*

void RwMatrixUpdate(RwMatrix* pRwMatrix); //6437B0h*
RwMatrix* RwMatrixInvert(RwMatrix* pMatrixDst, RwMatrix* pMatrixSrc); //643F40h
RwMatrix* RwMatrixScale(RwMatrix* pMatrix, RwV3d vecScale, RwOpCombineType eCombineType); //644190h
RwMatrix* RwMatrixTransform(RwMatrix* pOne, RwMatrix* pTwo, RwOpCombineType eCombineType); //644470h
RwBool RwMatrixDestroy(RwMatrix* pMatrix); //6445F0h
RwMatrix* RwMatrixCreate(void); //644620h

RwFrame* RwFrameCreate(void); //644AA0h
RwBool RwFrameDestroy(RwFrame* pFrame); //644AD0h
RwBool RwFrameDestroyHierarchy(RwFrame* pFrame); //644C90h
void RwFrameUpdateObjects(RwFrame* pRwFrame); //644D00h
RwFrame* RwFrameAddChild(RwFrame* pParent, RwFrame* pChild); //644DA0h
RwFrame* RwFrameForAllChildren(RwFrame* pFrame, RwFrameCallBack callBack, void* pData); //645060
RwFrame* RwFrameForAllObjects(RwFrame* pFrame, RwObjectCallBack callBack, void* pData); //6453B0h

RwUInt32 RwStreamRead(RwStream* pStream,void* pBuffer,RwUInt32 uLength); //6454B0h
RwBool RwStreamClose(RwStream* pStream, void* pData); //6458F0h
RwStream* RwStreamOpen(RwStreamType eType, RwStreamAccessType eAccessType, const void* pData); //6459C0h

RwMatrix* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* pHAnimHierarchy); //646370h
RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* pHAnimHierarchy, RwInt32 nNodeId); //646390h

RwV3d* RwV3dTransformPoints(RwV3d* pPointsOut, RwV3d* pPointsIn, RwInt32 nNumPoints, RwMatrix* pTransform); //647160h
RwV3d* RwV3dTransformVectors(RwV3d* pVectorsOut, RwV3d* pVectorsIn, RwInt32 nNumVectors, RwMatrix* pTransform); //647170h

RwCamera* RwCameraSetFrame(RwCamera* pCamera, RwFrame* pFrame); //INLINE*

RpMorphTarget* RpMorphTargetCalcBoundingSphere(RpMorphTarget* pMorphTarget, RwSphere* pBoundingSphere); //64C920h
RwInt32 RpGeometryAddMorphTargets(RpGeometry* pGeometry, RwInt32 nMtCount); //64CA30h
RwInt32 RpGeometryAddMorphTarget(RpGeometry* pGeometry); //64CBF0h*
RpGeometry* RpGeometryTriangleSetVertexIndices(RpGeometry* pGeometry, RpTriangle* pTriangle, RwUInt16 uVert1, RwUInt16 uVert2, RwUInt16 uVert3);//64CC00h*
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* pGeometry, RpTriangle* pTriangle, RpMaterial* pMaterial); //64CC30h
RpGeometry* RpGeometryForAllMaterials(RpGeometry* pGeometry, RpMaterialCallBack fpCallBack, void* pData); //64CC90h
RpGeometry* RpGeometryLock(RpGeometry* pGeometry, RwInt32 nLockMode); //64CCD0h
RpGeometry* RpGeometryUnlock(RpGeometry* pGeometry); //64CD00h
RpGeometry* RpGeometryCreate(RwInt32 nNumVerts, RwInt32 nNumTriangles, RwUInt32 uFormat); //64CDB0h
RpGeometry* RpGeometryAddRef(RpGeometry* pGeometry); //64CFD0h*
RwBool RpGeometryDestroy(RpGeometry* pGeometry); //64CFE0h
RwInt32 RpGeometryRegisterPlugin(RwInt32 nSize, RwUInt32 uPluginID, RwPluginObjectConstructor pConstructCB, RwPluginObjectDestructor pDestructCB, RwPluginObjectCopy pCopyCB); //64D080h
RwInt32 RpGeometryRegisterPluginStream(RwInt32 nSize, RwUInt32 uPluginID, RwPluginDataChunkReadCallBack pReadCB, RwPluginDataChunkWriteCallBack pWriteCB, RwPluginDataChunkGetSizeCallBack pGetSizeCB); //64D0B0h
RpGeometry* RpGeometryStreamRead(RwStream* pStream); //64D0E0h*
RwBool GeometryAnnihilate(RpGeometry* pGeometry); //64D7C0h

RwBool RwTexDictionaryDestroy(RwTexDictionary* pDict); //64DD90h
RwTexDictionary *RwTexDictionaryForAllTextures(RwTexDictionary* pDict, RwTextureCallBack fpCallBack, void *pData); //64DE20h
RwTexture* RwTextureCreate(RwRaster* pRaster); //64DE60h
RwBool RwTextureDestroy(RwTexture* pTexture); //64DEC0h

RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* pDict, RwChar* pszName); //64E060h
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* pDict); //64E0E0h
RwTexDictionary* RwTexDictionaryGetCurrent(void); //64E100h

RwBool _rwStreamReadChunkHeader(RwStream* pStream, RwUInt32* puChunkId, RwUInt32* puChunkLen, RwUInt32* puChunkVersion, RwUInt32* puChunkMajorVersion); //64F990h
RwBool RwStreamFindChunk(RwStream* pStream, RwUInt32 dwType, RwUInt32* dwLengthOut, RwUInt32* dwVersionOut); //64FAC0h
void* RwMemNative32(void* pMem, RwUInt32 uSize); //64FBD0h*
void* RwMemRealToFloat32(void* pMem, RwUInt32 uSize); //64FBE0h*
void* RwMemFloat32ToReal(void* pMem, RwUInt32 uSize); //64FC00h*
RwStream* RwStreamReadReal(RwStream* pStream, RwReal* pReals, RwUInt32 numBytes); //64FCE0h
RwStream* RwStreamReadInt32(RwStream* pStream, RwInt32* pInts, RwUInt32 numBytes); //64FD50h

RwTexture* RwTextureStreamRead(RwStream* pStream); //6506F0h

RwImage* RwImageCreate(RwInt32 nWidth, RwInt32 nHeight, RwInt32 nDepth); //651250h
RwBool RwImageDestroy(RwImage* pImage); //6512B0h
RwImage* RwImageAllocatePixels(RwImage* pImage); //651310h

RpWorld* RpAtomicGetWorld(RpAtomic* pAtomic); //6544F0

RwRaster* RwRasterCreate(RwInt32 nWidth, RwInt32 nHeight, RwInt32 nDepth, RwInt32 nFlags); //655490h

void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties* pSurfaceProps); //6556C0h*
RpMaterial* RpMaterialCreate(void); //6557B0h
RwBool RpMaterialDestroy(RpMaterial* pMaterial); //655830h
RpMaterial* RpMaterialSetTexture(RpMaterial* pMaterial, RwTexture* pTexture); //655890h
RpMaterial* RpMaterialStreamRead(RwStream* pStream); //655920h

RpAtomic* RpMatFXWorldSectorEnableEffects(RpAtomic* pAtomic); //657020h
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* pMaterial, RpMatFXMaterialFlags nEffects); //657050h
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* pMaterial, RwTexture* pTexture, RwFrame* pFrame, RwBool bUseFrameBufferAlpha, float fCoef); //657180h

RwImage* RwImageSetFromRaster(RwImage* pImage, RwRaster* pRaster); //660270h
RwRaster* RwRasterSetFromImage(RwRaster* pRaster, RwImage* pImage); //6602B0h

rwFrameList* _rwFrameListDeInitialize(rwFrameList* pFrameList); //660380h
rwFrameList* _rwFrameListStreamRead(RwStream* pStream, rwFrameList* pFrameList); //6603B0h

RpLight* RpLightStreamRead(RwStream* pStream); //660940h
RpLight* RpLightSetFrame(RpLight* pLight, RwFrame* pFrame); //INLINE*

void _rwObjectHasFrameSetFrame(RwObjectHasFrame* pObjectHasFrame, RwFrame* pFrame); //660CC0h
void _rwObjectHasFrameReleaseFrame(RwObjectHasFrame* pObjectHasFrame); //660D10h

extern RwUInt32& resourcesModule;
RwBool RwResourcesFreeResEntry(RwResEntry* pEntry); //669240h*
rwResourcesGlobals* RwResourcesGlobalsGet(); //INLINE*

RwUInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* pRegistry, int nSize, RwUInt32 uPluginId, void* pFunc1, void* pFunc2, void* pFunc3); //669790h
RwPluginRegistry* _rwPluginRegistryInitObject(RwPluginRegistry* pReg, void *pObject); //6699C0h
RwPluginRegistry* _rwPluginRegistryDeInitObject(RwPluginRegistry* pPluginRegistry, void* pObject); //669A20h

RwError* RwErrorSet(RwError* pError); //669AE0h

RwPluginRegistry* _rwPluginRegistryAddPluginStream(RwPluginRegistry* pRegistry, RwUInt32 uPluginId, void* pFunc1, void* pFunc2, void* pFunc3); //669BA0h

RwPluginRegistry* _rwPluginRegistryReadDataChunks(RwPluginRegistry* pPluginRegistry, RwStream* pStream, void* pObject); //669C40h
RwPluginRegistry* _rwPluginRegistryInvokeRights(RwPluginRegistry* pPluginRegistry, RwUInt32 uId, void* pObject, RwUInt32 uExtraData); //669D70h

RwCamera* RwCameraStreamRead(RwStream* pStream); //669F50h

RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* pMatList); //66D9B0h
RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* pMatList, RpMaterial* pMaterial); //66DA30h
RpMaterialList* _rpMaterialListStreamRead(RwStream* pStream, RpMaterialList* pMatList); //66DB20h

void _rwResHeapFree(RwResEntry* pEntry); //6785D0h

#pragma pack(pop)

#endif