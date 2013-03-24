#include "RenderWare.h"

#define FUNC_RwRenderStateSet 0x649BA0
#define FUNC_RwRenderStateGet 0x649BF0
#define FUNC_RwIm2DRenderPrimitive 0x649C10
#define FUNC_RwIm3DTransform 0x65AE90
#define FUNC_RwIm3DRenderIndexedPrimitive 0x65AF90
#define FUNC_SetMaskVertices 0x577D10
#define FUNC_RwTextureCreate 0x64DE60
#define FUNC_RwTextureRead 0x64E110
#define FUNC_RwTextureDestroy 0x64DEC0
#define FUNC_RwTextureRasterGenerateMipmaps 0x64E340
#define FUNC_RwRasterLock  0x655530
#define FUNC_RwRasterUnlock 0x655250
#define FUNC_RwRasterCreate 0x655490
#define FUNC_RwRasterDestroy 0x6552E0
#define FUNC_RwD3D8SetRenderState 0x6582A0
#define FUNC_RwD3D8SetTextureStageState 0x658310
#define FUNC_RwV3dTransformPoints 0x647160

/*****************************************************************************/
/** Renderware functions mapping						                    **/
/*****************************************************************************/

RwRenderStateSet_t				    RwRenderStateSet =				(RwRenderStateSet_t)			    FUNC_RwRenderStateSet;
RwRenderStateGet_t                  RwRenderStateGet =              (RwRenderStateGet_t)                FUNC_RwRenderStateGet;
RwIm2DRenderPrimitive_t			    RwIm2DRenderPrimitive =			(RwIm2DRenderPrimitive_t)		    FUNC_RwIm2DRenderPrimitive;
RwIm3DTransform_t                   RwIm3DTransform =               (RwIm3DTransform_t)                 FUNC_RwIm3DTransform;
RwIm3DRenderIndexedPrimitive_t      RwIm3DRenderIndexedPrimitive =  (RwIm3DRenderIndexedPrimitive_t)    FUNC_RwIm3DRenderIndexedPrimitive;
RwTextureRead_t					    RwTextureRead =					(RwTextureRead_t)				    FUNC_RwTextureRead;
RwTextureRasterGenerateMipmaps_t    RwTextureRasterGenerateMipMaps =(RwTextureRasterGenerateMipmaps_t)  FUNC_RwTextureRasterGenerateMipmaps;
RwRasterLock_t                      RwRasterLock =                  (RwRasterLock_t)                    FUNC_RwRasterLock;
RwRasterUnlock_t                    RwRasterUnlock =                (RwRasterUnlock_t)                  FUNC_RwRasterUnlock;
RwRasterDestroy_t                   RwRasterDestroy =               (RwRasterDestroy_t)                 FUNC_RwRasterDestroy;
RwD3D8SetRenderState_t			    RwD3D8SetRenderState =			(RwD3D8SetRenderState_t)		    FUNC_RwD3D8SetRenderState;
RwD3D8SetTextureStageState_t        RwD3D8SetTextureStageState =    (RwD3D8SetTextureStageState_t)      FUNC_RwD3D8SetTextureStageState;


RwGlobals*& RwEngineInstance=*(RwGlobals**)0x7870C0;

//57F250h
RpHAnimHierarchy* RpClumpGetSkinHAnimHierarchy(RpClump* pRpClump) {
	RpHAnimHierarchy* pReturn;
	_asm {
		push pRpClump
		mov eax,57F250h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//57F580h
RwBool RpClumpIsSkinned(RpClump* pClump) {
	RwBool bReturn;

	_asm {
		push pClump
		mov eax, 57F580h
		call eax
		add esp, 04h
		mov bReturn, eax
	}

	return bReturn;
}

//57F940h
RwObject* RwFrameGetFirstObject(RwFrame* pFrame) {
	RwObject* pReturn;
	_asm {
		push pFrame
		mov eax, 57F940h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//5805C0h
void RwFreeAlign(void* pBuffer) {
	_asm {
		push pBuffer
		mov eax, 5805C0h
		call eax
		add esp, 04h
	}
}

//580600h
RwChar* GetFrameNodeName(RwFrame* pFrame) {
	char* pReturn;
	_asm {
		push pFrame
		mov eax, 580600h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//61E710h
RwTexDictionary* RwTexDictionaryStreamRead(RwStream* pStream) {
	RwTexDictionary* pReturn;
	_asm {
		push pStream
		mov eax, 61E710h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

RwUInt32& materialModule=*(RwUInt32*)0x7876A0;

RwPluginRegistry& clumpTKList=*(RwPluginRegistry*)0x6DD0A8;
RwPluginRegistry& atomicTKList=*(RwPluginRegistry*)0x6DD090;
RwPluginRegistry& textureTKList=*(RwPluginRegistry*)0x6DDB70;
RwUInt32& clumpModule=*(RwUInt32*)0x786E88;
RwUInt32& _rpClumpLightExtOffset=*(RwUInt32*)0x786EB8;
RwUInt32& _rpClumpCameraExtOffset=*(RwUInt32*)0x786EB4;
RwUInt32& lastSeenRightsPluginId=*(RwUInt32*)0x786E84;
RwUInt32& lastSeenExtraData=*(RwUInt32*)0x786E5C;

//640CB0h
RpClump* RpClumpRender(RpClump* pClump) {
	RpClump* pReturn;
	_asm {
		push pClump
		mov eax,640CB0h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//640D00h
RpClump* RpClumpForAllAtomics(RpClump* pClump, RpAtomicCallBack pfnCallback, void* pData) {
	RpClump* pReturn;
	_asm {
		push pData
		push pfnCallback
		push pClump
		mov eax,640D00h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//640D40h
RpClump* RpClumpForAllCameras(RpClump* pClump, RwCameraCallBack pCallBack, void *pData) {
	RpClump* pReturn;
	_asm {
		push pData
		push pCallBack
		push pClump
		mov eax,640D40h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//640D90h
RpClump* RpClumpForAllLights(RpClump* pClump, RpLightCallBack pCallBack, void *pData) {
	RpClump* pReturn;
	_asm {
		push pData
		push pCallBack
		push pClump
		mov eax,640D90h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//640DE0h
RpAtomic* RpAtomicCreate(void) {
	RpAtomic* pReturn;
	_asm {
		mov eax,640DE0h
		call eax
		mov pReturn,eax
	}
	return pReturn;
}

//640ED0h*
RpAtomic* RpAtomicSetGeometry(RpAtomic* pAtomic, RpGeometry* pGeometry, RwUInt32 uFlags) {
	//if atomic already has this geometry, then nothing needs to be done
	if(pAtomic->pGeometry == pGeometry){
		return pAtomic;
	}

	if(pGeometry){
		RpGeometryAddRef(pGeometry);
	}

	if(pAtomic->pGeometry){
		RpGeometryDestroy(pAtomic->pGeometry);
	}

	pAtomic->pGeometry=pGeometry;

	//update atomic bound sphere if requested
	if((uFlags & rpATOMICSAMEBOUNDINGSPHERE) == 0){
		if(pGeometry){
			pAtomic->stBoundingSphere.vecCenter.x=pGeometry->pMorphTarget->stBoundingSphere.vecCenter.x;
			pAtomic->stBoundingSphere.vecCenter.y=pGeometry->pMorphTarget->stBoundingSphere.vecCenter.y;
			pAtomic->stBoundingSphere.vecCenter.z=pGeometry->pMorphTarget->stBoundingSphere.vecCenter.z;
			pAtomic->stBoundingSphere.fRadius=pGeometry->pMorphTarget->stBoundingSphere.fRadius;
		}

		//if atomic has frame and is in world, update
		if(RpAtomicGetFrame(pAtomic) && RpAtomicGetWorld(pAtomic)){
			RwFrameUpdateObjects(RpAtomicGetFrame(pAtomic));
		}
	}

	return pAtomic;
}

#ifdef RWUSEORIGINALS
//640F50h
RwBool RpAtomicDestroy(RpAtomic* pAtomic) {
	RwBool bReturn;
	_asm {
		push pAtomic
		mov eax,640F50h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}
#else
//640F50h*
RwBool RpAtomicDestroy(RpAtomic* pAtomic) {
	_rwPluginRegistryDeInitObject(&atomicTKList,pAtomic);

	if(pAtomic->pResEntry){
		RwResourcesFreeResEntry(pAtomic->pResEntry);
	}

	if(pAtomic->pGeometry){
		RpGeometryDestroy(pAtomic->pGeometry);
		
		pAtomic->pGeometry=NULL;

		if(RpAtomicGetFrame(pAtomic) && RpAtomicGetWorld(pAtomic)){
			RwFrameUpdateObjects(RpAtomicGetFrame(pAtomic));
		}
	}

	_rwObjectHasFrameReleaseFrame(&pAtomic->stObject);

	RwEngineInstance->memoryFree(RpClumpGlobalsGet()->pAtomicFreeList,pAtomic);
	
	return TRUE;
}
#endif

//640FD0h
RpAtomic* RpAtomicClone(RpAtomic* pAtomic) {
	RpAtomic* pReturn;
	_asm {
		push pAtomic
		mov eax,640FD0h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//6410E0h
RpClump* RpClumpClone(RpClump* pClump) {
	RpClump* pReturn;
	_asm {
		push pClump
		mov eax, 6410E0h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//641330h
RpLight* DestroyClumpLight(RpLight* pLight, void *pData) {
	RpLight* pReturn;
	_asm {
		push pData
		push pLight
		mov eax,641330h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//641370h
RwCamera* DestroyClumpCamera(RwCamera* pCamera, void *pData) {
	RwCamera* pReturn;
	_asm {
		push pData
		push pCamera
		mov eax,641370h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//6413C0h
RpClump* RpClumpCreate(void) {
	RpClump* pReturn;
	_asm {
		mov eax,6413C0h
		call eax
		mov pReturn,eax
	}
	return pReturn;
}

//641430h
RwBool RpClumpDestroy(RpClump* pClump) {
	RwBool bReturn;
	_asm {
		push pClump
		mov eax,641430h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//6415B0h
RpClump* RpClumpAddAtomic(RpClump* pClump, RpAtomic* pAtomic) {
	_asm {
		push pAtomic
		push pClump
		mov eax, 6415B0h
		call eax
		add esp, 08h
	}
	return pClump;
}

//6415E0h*
RpClump* RpClumpRemoveAtomic(RpClump* pClump, RpAtomic* pAtomic) {
	pAtomic->inClumpLink.pPrev->pNext=pAtomic->inClumpLink.pNext;
	pAtomic->inClumpLink.pNext->pPrev=pAtomic->inClumpLink.pPrev;

	pAtomic->pClump=NULL;

	return pClump;
}

#define STREAMREAD_READERR 1
#define STREAMREAD_VERERR 2
#define STREAMREAD_MEMERR 3
#define STREAMREAD_CREATEERR 4

#ifdef RWUSEORIGINALS
//641640h
RpAtomic* ClumpAtomicStreamRead(RwStream* pStream, rwFrameList* pFrameList, rpGeometryList* pGeometryList) {
	RpAtomic* pReturn;
	_asm {
		push pGeometryList
		push pFrameList
		push pStream
		mov eax,641640h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}
#else

#define CLATOMICPROG_ATOMIC 1

//641640h*
RpAtomic* ClumpAtomicStreamRead(RwStream* pStream, rwFrameList* pFrameList, rpGeometryList* pGeometryList) {
	RwUInt32 uChunkVer, uChunkLen, uError = 0, uProgress = 0;
	RwError stError;
	rpClumpAtomicChunkInfo stAtomicChunk;
	RpAtomic* pAtomic;
	RpGeometry* pGeometry;

	while(1) {

		//find atomic chunk info
		if(!RwStreamFindChunk(pStream, rwID_STRUCT, &uChunkLen, &uChunkVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uChunkVer < 0x31000 || uChunkVer > 0x36003) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uChunkLen > sizeof(rpClumpAtomicChunkInfo)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(RwStreamRead(pStream, &stAtomicChunk, uChunkLen) != uChunkLen) {
			uError = STREAMREAD_READERR;
			break;
		}

		RwMemNative32(&stAtomicChunk, sizeof(rpClumpAtomicChunkInfo));

		pAtomic = RpAtomicCreate();

		if(!pAtomic) {
			uError = STREAMREAD_CREATEERR;
			break;
		}

		uProgress |= CLATOMICPROG_ATOMIC;

		RpAtomicSetFlags(pAtomic, stAtomicChunk.uFlags);

		if(pFrameList->numFrames > 0) {
			if(stAtomicChunk.nFrameID >= 0 && stAtomicChunk.nFrameID < pFrameList->numFrames) {
				RpAtomicSetFrame(pAtomic, pFrameList->frames[stAtomicChunk.nFrameID]);
			}
		}
	
		//if there's a geometry list, use that, otherwise the geometry must follow in stream
		if(pGeometryList->numGeometries > 0) {
			if(stAtomicChunk.nGeometryID >= 0 && stAtomicChunk.nGeometryID < pGeometryList->numGeometries) {
				RpAtomicSetGeometry(pAtomic, pGeometryList->pGeometries[stAtomicChunk.nGeometryID], 0);
			}
		}
		else {
			if(!RwStreamFindChunk(pStream, rwID_GEOMETRY, NULL, &uChunkVer)) {
				uError = STREAMREAD_READERR;
				break;
			}

			if(uChunkVer < 0x31000  || uChunkVer > 0x36003) {
				uError = STREAMREAD_VERERR;
				break;
			}

			pGeometry = RpGeometryStreamRead(pStream);

			if(!pGeometry) {
				uError = STREAMREAD_READERR;
				break;
			}

			RpAtomicSetGeometry(pAtomic, pGeometry, 0);
		
			RpGeometryDestroy(pGeometry);
		}

		lastSeenRightsPluginId = 0;
		lastSeenExtraData = 0;
	
		//read data for plugins
		if(!_rwPluginRegistryReadDataChunks(&atomicTKList,pStream,pAtomic)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(lastSeenRightsPluginId != 0) {
			_rwPluginRegistryInvokeRights(&atomicTKList, lastSeenRightsPluginId, pAtomic, lastSeenExtraData);
		}

		break;
	}

	if(uError != 0) {
		if(uProgress & CLATOMICPROG_ATOMIC) {
			RpAtomicDestroy(pAtomic);
		}

		if(uError == STREAMREAD_READERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_READ;
			RwErrorSet(&stError);
		}
		else if(uError == STREAMREAD_VERERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_BADVERSION;
			RwErrorSet(&stError);
		}

		return NULL;
	}

	return pAtomic;
}
#endif

#ifdef RWUSEORIGINALS
//641A10h
RpClump* RpClumpStreamRead(RwStream* pStream) {
	RpClump* pReturn;
	_asm {
		push pStream
		mov eax,641A10h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}
#else

#define CLUMPPROG_CLUMP 1
#define CLUMPPROG_FRAMELIST 2
#define CLUMPPROG_GEOMETRY 4

//641A10h*
RpClump* RpClumpStreamRead(RwStream* pStream) {
	RwUInt32 uStructLen, uStructVer, uReadValue, uChunkVer, uChunkLen;
	RpClumpChunkInfo stClumpInfo;
	RpClump* pClump;
	RwUInt32 uError = 0, uProgress = 0;
	rwFrameList stFrameList;
	rpGeometryList stGeometryList;
	RwInt32 i;

	while(1) {
	
		//find header and check version
		if(!RwStreamFindChunk(pStream, rwID_STRUCT, &uStructLen, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		//pre 3.3 versions can only have atomics
		if(uStructVer <= 0x33000){
			if(RwStreamRead(pStream, &uReadValue, sizeof(RwUInt32)) != sizeof(RwUInt32)) {
				uError = STREAMREAD_READERR;
				break;
			}

			RwMemNative32((void*)&uReadValue, sizeof(RwUInt32));

			stClumpInfo.nNumAtomics = uReadValue;
			stClumpInfo.nNumCameras = 0;
			stClumpInfo.nNumLights = 0;
		}
		else {
			if(RwStreamRead(pStream, &stClumpInfo, sizeof(RpClumpChunkInfo)) != sizeof(RpClumpChunkInfo)) {
				uError = STREAMREAD_READERR;
				break;
			}

			RwMemNative32((void*)&stClumpInfo, sizeof(RpClumpChunkInfo));
		}

		//create clump
		pClump = RpClumpCreate();

		if(!pClump) {
			uError = STREAMREAD_CREATEERR;
			break;
		}

		uProgress |= CLUMPPROG_CLUMP;

		//read frame list
		if(!RwStreamFindChunk(pStream, rwID_FRAMELIST, NULL, &uChunkVer)){
			uError = STREAMREAD_READERR;
			break;
		}

		if(!_rwFrameListStreamRead(pStream, &stFrameList)) {
			uError = STREAMREAD_READERR;
			break;
		}

		uProgress |= CLUMPPROG_FRAMELIST;

		//read geometry list info
		if(!RwStreamFindChunk(pStream, rwID_GEOMETRYLIST, NULL, &uChunkVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		RwUInt32 uGeomListSize, uGeomListVer;

		if(!RwStreamFindChunk(pStream, rwID_STRUCT, &uGeomListSize, &uGeomListVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uGeomListVer < 0x31000 || uGeomListVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		RwInt32 nGeometries;

		if(RwStreamRead(pStream, &nGeometries, sizeof(RwInt32)) != sizeof(RwInt32)) {
			uError = STREAMREAD_READERR;
			break;
		}

		RwMemNative32(&nGeometries, sizeof(RwInt32));

		if(nGeometries > 0) {
			stGeometryList.numGeometries = nGeometries;
			stGeometryList.pGeometries = (RpGeometry**)RwEngineInstance->memoryFuncs.rwmalloc(nGeometries * sizeof(RpGeometry*));
			
			memset(stGeometryList.pGeometries, 0, nGeometries * sizeof(RpGeometry*));
		}
		else {
			stGeometryList.numGeometries = 0;
			stGeometryList.pGeometries = NULL;
		}

		uProgress |= CLUMPPROG_GEOMETRY;

		//read geometries if they're separated from atomics
		for(i=0; i<nGeometries; i++) {
			if(!RwStreamFindChunk(pStream, rwID_GEOMETRY, &uChunkLen, &uChunkVer)) {
				uError = STREAMREAD_READERR;
				break;
			}

			if(uChunkVer < 0x31000 || uChunkVer > 0x36003) {
				uError = STREAMREAD_VERERR;
			}

			stGeometryList.pGeometries[i] = RpGeometryStreamRead(pStream);

			if(!stGeometryList.pGeometries[i]) {
				uError = STREAMREAD_READERR;
				break;
			}
		}

		if(uError) {
			break;
		}

		//set root frame
		RpClumpSetFrame(pClump, stFrameList.frames[0]);

		RpAtomic* pAtomic;

		//read clump atomics
		for(i=0; i<stClumpInfo.nNumAtomics; i++) {
			if(!RwStreamFindChunk(pStream, rwID_ATOMIC, NULL, &uChunkVer)) {
				uError = STREAMREAD_READERR;
				break;
			}

			//read atomic and link frames and geometry
			pAtomic = ClumpAtomicStreamRead(pStream, &stFrameList, &stGeometryList);

			if(!pAtomic) {
				uError = STREAMREAD_READERR;
				break;
			}

			//place atomic into the linked list of clump
			pAtomic->inClumpLink.pNext = pClump->llAtomicList.stLink.pNext;
			pAtomic->inClumpLink.pPrev = &pClump->llAtomicList.stLink;

			pClump->llAtomicList.stLink.pNext->pPrev = &pAtomic->inClumpLink;
			pClump->llAtomicList.stLink.pNext = &pAtomic->inClumpLink;

			pAtomic->pClump = pClump;
		}

		if(uError) {
			break;
		}

		RwInt32 nFrameID;
		RpLight* pLight;

		//read clump lights
		for(i=0; i<stClumpInfo.nNumLights; i++) {
			//read frame ID
			if(!RwStreamFindChunk(pStream, rwID_STRUCT, NULL, NULL) || !RwStreamReadInt32(pStream, &nFrameID, sizeof(RwInt32))) {
				uError = STREAMREAD_READERR;
				break;
			}

			if(!RwStreamFindChunk(pStream, rwID_LIGHT, NULL, NULL)) {
				uError = STREAMREAD_READERR;
				break;
			}

			pLight = RpLightStreamRead(pStream);

			if(!pLight) {
				uError = STREAMREAD_READERR;
				break;
			}

			//set light frame
			RpLightSetFrame(pLight, stFrameList.frames[nFrameID]);

			//place light into the linked list of clump
			RpClumpLightExtGet(pLight)->inClumpLink.pNext = pClump->llLightList.stLink.pNext;
			RpClumpLightExtGet(pLight)->inClumpLink.pPrev = &pClump->llLightList.stLink;

			pClump->llLightList.stLink.pNext->pPrev = &RpClumpLightExtGet(pLight)->inClumpLink;
			pClump->llLightList.stLink.pNext = &RpClumpLightExtGet(pLight)->inClumpLink;

			RpClumpLightExtGet(pLight)->pClump = pClump;
		}

		if(uError) {
			break;
		}

		RwCamera* pCamera;

		//read clump cameras
		for(i=0; i<stClumpInfo.nNumCameras; i++) {
			if(!RwStreamFindChunk(pStream, rwID_STRUCT, NULL, NULL) || !RwStreamReadInt32(pStream, &nFrameID, sizeof(RwInt32))) {
				uError = STREAMREAD_READERR;
				break;
			}

			if(!RwStreamFindChunk(pStream, rwID_CAMERA, NULL, NULL)) {
				uError = STREAMREAD_READERR;
				break;
			}

			pCamera = RwCameraStreamRead(pStream);

			if(!pCamera) {
				uError = STREAMREAD_READERR;
				break;
			}

			//set camera frame
			RwCameraSetFrame(pCamera, stFrameList.frames[nFrameID]);

			//place camera into the linked list of clump
			RpClumpCameraExtGet(pCamera)->inClumpLink.pNext = pClump->llCameraList.stLink.pNext;
			RpClumpCameraExtGet(pCamera)->inClumpLink.pPrev = &pClump->llCameraList.stLink;

			pClump->llCameraList.stLink.pNext->pPrev = &RpClumpCameraExtGet(pCamera)->inClumpLink;
			pClump->llCameraList.stLink.pNext = &RpClumpCameraExtGet(pCamera)->inClumpLink;

			RpClumpCameraExtGet(pCamera)->pClump = pClump;
		}

		if(uError) {
			break;
		}

		//remove references to geometries and free geometry list
		if(stGeometryList.pGeometries) {
			for(i=0; i<stGeometryList.numGeometries; i++) {
				RpGeometryDestroy(stGeometryList.pGeometries[i]);
			}
			RwEngineInstance->memoryFuncs.rwfree(stGeometryList.pGeometries);

			stGeometryList.pGeometries = NULL;
		}

		//free frame list
		_rwFrameListDeInitialize(&stFrameList);

		//read data for plugins
		if(!_rwPluginRegistryReadDataChunks(&clumpTKList, pStream, pClump)) {
			uError = STREAMREAD_READERR;
			break;
		}

		//success
		break;
	}

	if(uError) {
		RwError stError;

		if(uProgress & CLUMPPROG_GEOMETRY) {
			if(stGeometryList.pGeometries) {
				for(i=0; i<stGeometryList.numGeometries; i++) {
					if(stGeometryList.pGeometries[i]) {
						RpGeometryDestroy(stGeometryList.pGeometries[i]);
					}
				}
				RwEngineInstance->memoryFuncs.rwfree(stGeometryList.pGeometries);
			}
		}

		if(uProgress & CLUMPPROG_FRAMELIST) {
			_rwFrameListDeInitialize(&stFrameList);
		}

		if(uProgress & CLUMPPROG_CLUMP) {
			_rwPluginRegistryDeInitObject(&clumpTKList, pClump);

			RwLLLink *pCurLink = pClump->llAtomicList.stLink.pNext;
			RpAtomic *pAtomic, *pNullAtomic = NULL;
		
			while(pCurLink != &pClump->llAtomicList.stLink) {
				pAtomic = (RpAtomic*)((RwUInt32)pCurLink-(RwUInt32)&pNullAtomic->inClumpLink);

				RpAtomicDestroy(pAtomic);

				pCurLink = pCurLink->pNext;
			}

			RpClumpForAllLights(pClump, DestroyClumpLight, NULL);

			RpClumpForAllCameras(pClump, DestroyClumpCamera, NULL);

			if(RpClumpGetFrame(pClump)) {
				RwFrameDestroyHierarchy(RpClumpGetFrame(pClump));
			}

			RwEngineInstance->memoryFree(RpClumpGlobalsGet()->pClumpFreeList, pClump);
		}

		if(uError == STREAMREAD_VERERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_BADVERSION;
			RwErrorSet(&stError);
		}
		else if(uError == STREAMREAD_READERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_READ;
			RwErrorSet(&stError);
		}

		return NULL;
	}

	return pClump;
}
#endif

//INLINE*
RwFrame* RpClumpGetFirstFrame(RpClump* pClump) {
	return (RwFrame*)pClump->stObject.pParent;
}

//INLINE*
RpClumpLightExt* RpClumpLightExtGet(RpLight* pLight) {
	return (RpClumpLightExt*)((DWORD)pLight+(DWORD)_rpClumpLightExtOffset);
}

//INLINE*
RpClumpCameraExt* RpClumpCameraExtGet(RwCamera* pCamera) {
	return (RpClumpCameraExt*)((DWORD)pCamera+(DWORD)_rpClumpCameraExtOffset);
}

//INLINE*
RwFrame* RpClumpGetFrame(RpClump* pClump) {
	return (RwFrame*)pClump->stObject.pParent;
}

//INLINE*
RpClump* RpClumpSetFrame(RpClump* pClump, RwFrame* pFrame) {
	pClump->stObject.pParent=(void*)pFrame;
	return pClump;
}

//INLINE*
RpClumpGlobals* RpClumpGlobalsGet(void) {
	return (RpClumpGlobals*)((DWORD)RwEngineInstance+(DWORD)clumpModule);
}

//INLINE*
RpMaterialGlobals* RpMaterialGlobalsGet(void) {
	return (RpMaterialGlobals*)((DWORD)RwEngineInstance+(DWORD)materialModule);
}

//6423C0h*
RpAtomic* RpAtomicSetFrame(RpAtomic* pAtomic, RwFrame* pFrame) {
	_rwObjectHasFrameSetFrame(&pAtomic->stObject,pFrame);

	pAtomic->stObject.stObject.cPrivateFlags|=rpATOMICPRIVATEWORLDBOUNDDIRTY;

	return pAtomic;
}

//INLINE*
RwFrame* RpAtomicGetFrame(RpAtomic* pAtomic) {
	return (RwFrame*)pAtomic->stObject.stObject.pParent;
}

//INLINE*
RpAtomic* RpAtomicSetFlags(RpAtomic* pAtomic, RwUInt8 uFlags) {
	pAtomic->stObject.stObject.cFlags=uFlags;
	return pAtomic;
}

RwUInt32& dwAtomicVisibilityExtOffset = *(RwUInt32*)0x69A1C8;

//INLINE*
RwUInt32 RpAtomicGetVisibilityFlags(RpAtomic* pAtomic) {
	RwUInt32* pdwFlags = (RwUInt32*)((char*)pAtomic + dwAtomicVisibilityExtOffset);
	return *pdwFlags;
}

//INLINE*
void RpAtomicSetVisibilityFlags(RpAtomic* pAtomic, RwUInt32 uFlags) {
	RwUInt32* pdwFlags = (RwUInt32*)((char*)pAtomic + dwAtomicVisibilityExtOffset);
	*pdwFlags = uFlags;
}

//INLINE*
RwFrame* RwFrameGetParent(RwFrame* pFrame) {
	return (RwFrame*)pFrame->stObject.pParent;
}

//6437B0h*
void RwMatrixUpdate(RwMatrix* pRwMatrix) {
	pRwMatrix->dwFlags &= 0xFFFDFFFC;
}

//643F40h
RwMatrix* RwMatrixInvert(RwMatrix* pMatrixDst, RwMatrix* pMatrixSrc) {
	RwMatrix* pReturn;
	_asm {
		push pMatrixSrc
		push pMatrixDst
		mov eax,643F40h
		call eax
		add esp,8
		mov pReturn,eax
	}
	return pReturn;
}

//644190h
RwMatrix* RwMatrixScale(RwMatrix* pMatrix, RwV3d vecScale, RwOpCombineType eCombineType) {
	RwMatrix* pReturn;
	_asm {
		push eCombineType
		push vecScale
		push pMatrix
		mov eax, 644190h
		call eax
		add esp, 0Ch
		mov pReturn, eax
	}
	return pReturn;
}

//644470h
RwMatrix* RwMatrixTransform(RwMatrix* pOne, RwMatrix* pTwo, RwOpCombineType eCombineType) {
	RwMatrix* pReturn;
	_asm {
		push eCombineType
		push pTwo
		push pOne
		mov eax, 644470h
		call eax
		add esp, 0Ch
		mov pReturn, eax
	}
	return pReturn;
}

//6445F0h
RwBool RwMatrixDestroy(RwMatrix* pMatrix) {
	_asm {
		push pMatrix
		mov eax, 6445F0h
		call eax
		add esp, 04h
	}
	return 1;
}

//644620h
RwMatrix* RwMatrixCreate(void) {
	RwMatrix* pReturn;
	_asm {
		mov eax, 644620h
		call eax
		mov pReturn, eax
	}
	return pReturn;
}

//644AA0h
RwFrame* RwFrameCreate(void) {
	RwFrame* pReturn;
	_asm {
		mov eax,644AA0h
		call eax
		mov pReturn,eax
	}
	return pReturn;
}

//644AD0h
RwBool RwFrameDestroy(RwFrame* pFrame) {
	RwBool bReturn;
	_asm {
		push pFrame
		mov eax,644AD0h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//644C90h
RwBool RwFrameDestroyHierarchy(RwFrame* pFrame) {
	RwBool bReturn;
	_asm {
		push pFrame
		mov eax,644C90h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//644D00h
void RwFrameUpdateObjects(RwFrame* pRwFrame) {
	_asm {
		push pRwFrame
		mov eax, 644D00h
		call eax
		add esp, 04h
	}
}

//644DA0h
RwFrame* RwFrameAddChild(RwFrame* pParent, RwFrame* pChild) {
	_asm {
		push pChild
		push pParent
		mov eax, 644DA0h
		call eax
		add esp, 08h
	}
	return pParent;
}

//645060
RwFrame* RwFrameForAllChildren(RwFrame* pFrame, RwFrameCallBack callBack, void* pData) {
	RwFrame* pReturn;
	_asm {
		push pData
		push callBack
		push pFrame
		mov eax, 645060h
		call eax
		add esp, 0Ch
		mov pReturn, eax
	}
	return pReturn;
}

RwObjectCallBack SetVehicleAtomicVisibilityCB = (RwObjectCallBack)0x59F200;

//6453B0h
RwFrame* RwFrameForAllObjects(RwFrame* pFrame, RwObjectCallBack callBack, void* pData) {
	_asm {
		push pData
		push callBack
		push pFrame
		mov eax, 6453B0h
		call eax
		add esp, 0Ch
	}
	return pFrame;
}

//6454B0h
RwUInt32 RwStreamRead(RwStream* pStream,void* pBuffer,RwUInt32 uLength) {
	RwUInt32 uReturn;
	_asm {
		push uLength
		push pBuffer
		push pStream
		mov eax,6454B0h
		call eax
		add esp,0Ch
		mov uReturn,eax
	}
	return uReturn;
}

//6458F0h
RwBool RwStreamClose(RwStream* pStream, void* pData) {
	RwBool bReturn;
	_asm {
		push pData
		push pStream
		mov eax,6458F0h
		call eax
		add esp,08h
		mov bReturn,eax
	}
	return bReturn;
}

//6459C0h
RwStream* RwStreamOpen(RwStreamType eType, RwStreamAccessType eAccessType, const void* pData) {
	RwStream* pReturn;
	_asm {
		push pData
		push eAccessType
		push eType
		mov eax,6459C0h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//646370h
RwMatrix* RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy* pHAnimHierarchy) {
	RwMatrix* pReturn;
	_asm {
		push pHAnimHierarchy
		mov eax,646370h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//646390h
RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy* pHAnimHierarchy, RwInt32 nNodeId) {
	RwInt32 nReturn;
	_asm {
		push nNodeId
		push pHAnimHierarchy
		mov eax,646390h
		call eax
		add esp,08h
		mov nReturn,eax
	}
	return nReturn;
}

//647160h
RwV3d* RwV3dTransformPoints(RwV3d* pPointsOut, RwV3d* pPointsIn, RwInt32 nNumPoints, RwMatrix* pTransform) {
	RwV3d* pReturn;
	__asm {
		push pTransform
		push nNumPoints
		push pPointsIn
		push pPointsOut
		mov eax,647160h
		call eax
		add esp,10h
		mov pReturn,eax
	}
	return pReturn;
}

//647170h
RwV3d* RwV3dTransformVectors(RwV3d* pVectorsOut, RwV3d* pVectorsIn, RwInt32 nNumVectors, RwMatrix* pTransform) {
	RwV3d* pReturn;
	__asm {
		push pTransform
		push nNumVectors
		push pVectorsIn
		push pVectorsOut
		mov eax,647170h
		call eax
		add esp,10h
		mov pReturn,eax
	}
	return pReturn;
}

//INLINE*
RwCamera* RwCameraSetFrame(RwCamera* pCamera, RwFrame* pFrame) {
	_rwObjectHasFrameSetFrame(&pCamera->object,pFrame);
	return pCamera;
}

//64C920h
RpMorphTarget* RpMorphTargetCalcBoundingSphere(RpMorphTarget* pMorphTarget, RwSphere* pBoundingSphere) {
	RpMorphTarget* pReturn;
	_asm {
		push pBoundingSphere
		push pMorphTarget
		mov eax,64C920h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//64CA30h
RwInt32 RpGeometryAddMorphTargets(RpGeometry* pGeometry, RwInt32 nMtCount) {
	RwInt32 nReturn;
	_asm {
		push nMtCount
		push pGeometry
		mov eax,64CA30h
		call eax
		add esp,08h
		mov nReturn,eax
	}
	return nReturn;
}

//64CBF0h*
RwInt32 RpGeometryAddMorphTarget(RpGeometry* pGeometry) {
	return RpGeometryAddMorphTargets(pGeometry,1);
}

//64CC00h*
RpGeometry* RpGeometryTriangleSetVertexIndices(RpGeometry* pGeometry, RpTriangle* pTriangle, RwUInt16 uVert1, RwUInt16 uVert2, RwUInt16 uVert3) {
	pTriangle->wVertIndex[0]=uVert1;
	pTriangle->wVertIndex[1]=uVert2;
	pTriangle->wVertIndex[2]=uVert3;
	return pGeometry;
}

//64CC30h
RpGeometry* RpGeometryTriangleSetMaterial(RpGeometry* pGeometry, RpTriangle* pTriangle, RpMaterial* pMaterial) {
	RpGeometry* pReturn;
	_asm {
		push pMaterial
		push pTriangle
		push pGeometry
		mov eax,64CC30h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//64CC90h
RpGeometry* RpGeometryForAllMaterials(RpGeometry* pGeometry, RpMaterialCallBack fpCallBack, void* pData) {
	RpGeometry* pReturn;
	_asm {
		push pData
		push fpCallBack
		push pGeometry
		mov eax,64CC90h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//64CCD0h
RpGeometry* RpGeometryLock(RpGeometry* pGeometry, RwInt32 nLockMode) {
	RpGeometry* pReturn;
	_asm {
		push nLockMode
		push pGeometry
		mov eax,64CCD0h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//64CD00h
RpGeometry* RpGeometryUnlock(RpGeometry* pGeometry) {
	RpGeometry* pReturn;
	_asm {
		push pGeometry
		mov eax,64CD00h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//64CDB0h
RpGeometry* RpGeometryCreate(RwInt32 nNumVerts, RwInt32 nNumTriangles, RwUInt32 uFormat) {
	RpGeometry* pReturn;
	_asm {
		push uFormat
		push nNumTriangles
		push nNumVerts
		mov eax,64CDB0h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//64CFD0h*
RpGeometry* RpGeometryAddRef(RpGeometry* pGeometry) {
	pGeometry->nRefCount++;
	return pGeometry;
}

//64CFE0h
RwBool RpGeometryDestroy(RpGeometry* pGeometry) {
	RwBool bReturn;
	_asm {
		push pGeometry
		mov eax,64CFE0h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//64D080h
RwInt32 RpGeometryRegisterPlugin(RwInt32 nSize, RwUInt32 uPluginID, RwPluginObjectConstructor pConstructCB, RwPluginObjectDestructor pDestructCB, RwPluginObjectCopy pCopyCB) {
	RwInt32 nReturn;
	_asm {
		push pCopyCB
		push pDestructCB
		push pConstructCB
		push uPluginID
		push nSize
		mov eax,64D080h
		call eax
		add esp,14h
		mov nReturn,eax
	}
	return nReturn;
}

//64D0B0h
RwInt32 RpGeometryRegisterPluginStream(RwInt32 nSize, RwUInt32 uPluginID, RwPluginDataChunkReadCallBack pReadCB, RwPluginDataChunkWriteCallBack pWriteCB, RwPluginDataChunkGetSizeCallBack pGetSizeCB) {
	RwInt32 nReturn;
	_asm {
		push pGetSizeCB
		push pWriteCB
		push pReadCB
		push uPluginID
		push nSize
		mov eax,64D0B0h
		call eax
		add esp,14h
		mov nReturn,eax
	}
	return nReturn;
}

RwPluginRegistry& geometryTKList=*(RwPluginRegistry*)0x6DDB50;

#ifdef RWUSEORIGINALS
//64D0E0h
RpGeometry* RpGeometryStreamRead(RwStream* pStream) {
	RpGeometry* pReturn;
	_asm {
		push pStream
		mov eax, 64D0E0h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}
#else

#define GEOMPROG_GEOMETRY 1
#define GEOMPROG_ANNIHILATE 2

//64D0E0h*
RpGeometry* RpGeometryStreamRead(RwStream* pStream) {
	RwUInt32 uStructVer, uError = 0, uProgress = 0;
	RpGeometryChunkInfo stGeomChunk;
	RpMorphTargetChunkInfo stMorphChunk;
	RwSurfaceProperties stSurfaceProps;
	RpGeometry* pGeometry;
	RwUInt16 uTempVertex;
	RwError stError;
	
	while(1) {
	
		//find header and check version
		if(!RwStreamFindChunk(pStream, rwID_STRUCT, NULL, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}
		
		//only accept versions 3.1 - 3.4
		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}
		
		//get geometry chunk info
		if(RwStreamRead(pStream, &stGeomChunk, sizeof(RpGeometryChunkInfo)) != sizeof(RpGeometryChunkInfo)) {
			uError = STREAMREAD_READERR;
			break;
		}
		
		RwMemNative32(&stGeomChunk, sizeof(RpGeometryChunkInfo));
		
		//versions below 3.4 have a default surface properties structure here
		if(uStructVer < 0x34001) {
			if(RwStreamRead(pStream, &stSurfaceProps, sizeof(RwSurfaceProperties)) != sizeof(RwSurfaceProperties)) {
				uError = STREAMREAD_READERR;
				break;
			}
			
			RwMemNative32(&stSurfaceProps, sizeof(RwSurfaceProperties));
			RwMemRealToFloat32(&stSurfaceProps, sizeof(RwSurfaceProperties));
		}
		
		//create the geometry
		pGeometry = RpGeometryCreate(stGeomChunk.numVertices, stGeomChunk.numTriangles, stGeomChunk.nFormat);

		if(pGeometry == NULL) {
			uError = STREAMREAD_CREATEERR;
			break;
		}

		uProgress = GEOMPROG_GEOMETRY;

		//add any additional morph targets
		if(stGeomChunk.numMorphTargets > 1) {
			if(RpGeometryAddMorphTargets(pGeometry, stGeomChunk.numMorphTargets-1) < 0) {
				uError = STREAMREAD_CREATEERR;
				break;
			}
		}

		if(!(pGeometry->dwFlags & rpGEOMETRYNATIVE) && pGeometry->nNumVertices > 0) {
			//read prelit luminance vertices
			if(stGeomChunk.nFormat & 8) {
				if(RwStreamRead(pStream, pGeometry->pPreLitLum, pGeometry->nNumVertices*sizeof(RwRGBA)) != pGeometry->nNumVertices*sizeof(RwRGBA)) {
					uError = STREAMREAD_READERR;
					break;
				}
			}

			//read tex coord set info
			if(pGeometry->nNumTexCoordSets > 0) {
				for(int i=0; i<pGeometry->nNumTexCoordSets; i++) {
					if(RwStreamReadReal(pStream, (RwReal*)pGeometry->pTexCoords[i], pGeometry->nNumVertices * sizeof(RwTexCoords)) == NULL) {
						uError = STREAMREAD_READERR;
						break;
					}
				}

				if(uError != 0) {
					break;
				}
			}

			//read triangles
			if(pGeometry->nNumTriangles > 0) {
				if(RwStreamRead(pStream, pGeometry->pTriangles, sizeof(RpTriangle) * pGeometry->nNumTriangles) != sizeof(RpTriangle) * pGeometry->nNumTriangles) {
					uError = STREAMREAD_READERR;
					break;
				}

				RwMemNative32(pGeometry->pTriangles, sizeof(RpTriangle) * pGeometry->nNumTriangles);

				for(int i=0; i<pGeometry->nNumTriangles; i++) {
					uTempVertex = pGeometry->pTriangles->wVertIndex[0];
					pGeometry->pTriangles->wVertIndex[0] = pGeometry->pTriangles->wVertIndex[1];
					pGeometry->pTriangles->wVertIndex[1] = pGeometry->pTriangles->wVertIndex[2];
					pGeometry->pTriangles->wVertIndex[2] = pGeometry->pTriangles->wMatIndex;
					pGeometry->pTriangles->wMatIndex = uTempVertex;
				}
			}
		}

		//read morph targets
		for(int i=0; i<pGeometry->nNumMorphTargets; i++) {
			if(RwStreamRead(pStream, &stMorphChunk, sizeof(RpMorphTargetChunkInfo)) != sizeof(RpMorphTargetChunkInfo)) {
				uError = STREAMREAD_READERR;
				break;
			}

			RwMemFloat32ToReal(&stMorphChunk.stBoundingSphere.vecCenter, sizeof(RwSphere));
			RwMemFloat32ToReal(&stMorphChunk.stBoundingSphere.fRadius, sizeof(RwReal));
			RwMemNative32(&stMorphChunk, sizeof(RpMorphTargetChunkInfo));

			memcpy(&pGeometry->pMorphTarget[i].stBoundingSphere, &stMorphChunk.stBoundingSphere, sizeof(RwSphere));

			if(stMorphChunk.bHasVerts) {
				if(RwStreamRead(pStream, pGeometry->pMorphTarget[i].pVerts, sizeof(RwV3d) * pGeometry->nNumVertices) == 0) {
					uError = STREAMREAD_READERR;
					break;
				}
			}

			if(stMorphChunk.bHasNormals) {
				if(RwStreamRead(pStream, pGeometry->pMorphTarget[i].pNormals, sizeof(RwV3d) * pGeometry->nNumVertices) == 0) {
					uError = STREAMREAD_READERR;
					break;
				}
			}
		}

		if(uError != 0) {
			break;
		}

		//process material list
		if(!RwStreamFindChunk(pStream, rwID_MATLIST, NULL, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		if(uStructVer < 0x34001) {
			_rpMaterialSetDefaultSurfaceProperties(&stSurfaceProps);
		}

		if(!_rpMaterialListStreamRead(pStream, &pGeometry->stMatList)) {
			uError = STREAMREAD_READERR;
			break;
		}

		if(uStructVer < 0x34001) {
			_rpMaterialSetDefaultSurfaceProperties(NULL);
		}

		uProgress = GEOMPROG_ANNIHILATE;

		//read plugin data
		if(!_rwPluginRegistryReadDataChunks(&geometryTKList, pStream, pGeometry)) {
			uError = STREAMREAD_READERR;
			break;
		}

		//unlock for others to use
		if(!RpGeometryUnlock(pGeometry)) {
			uError = STREAMREAD_CREATEERR;
			break;
		}

		break;
	}

	if(uError != 0) {
		if(pGeometry->nRefCount > 1) {
			return NULL;
		}

		if(uError & GEOMPROG_GEOMETRY) {
			if(pGeometry->pResEntry != NULL) {
				RwResourcesFreeResEntry(pGeometry->pResEntry);
			}

			RpGeometryLock(pGeometry, rpGEOMETRYLOCKALL);

			_rwPluginRegistryDeInitObject(&geometryTKList, pGeometry);

			if(pGeometry->pMorphTarget != NULL) {
				RwEngineInstance->memoryFuncs.rwfree(pGeometry->pMorphTarget);
				pGeometry->pMorphTarget = NULL;
			}

			_rpMaterialListDeinitialize(&pGeometry->stMatList);

			RwEngineInstance->memoryFuncs.rwfree(pGeometry);
		}
		else if(uError & GEOMPROG_ANNIHILATE) {
			if(pGeometry->pResEntry != NULL) {
				RwResourcesFreeResEntry(pGeometry->pResEntry);
			}

			GeometryAnnihilate(pGeometry);
		}

		if(uError & STREAMREAD_VERERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_BADVERSION;
			RwErrorSet(&stError);
		}

		return NULL;
	}

	return pGeometry;
}

#endif

//64D7C0h
RwBool GeometryAnnihilate(RpGeometry* pGeometry) {
	RwBool bReturn;
	_asm {
		push pGeometry
		mov eax, 64D7C0h
		call eax
		add esp, 04h
		mov bReturn, eax
	}
	return bReturn;
}

//64DD90h
RwBool RwTexDictionaryDestroy(RwTexDictionary* pDict) {
	_asm {
		push pDict
		mov eax, 64DD90h
		call eax
		add esp, 04h
	}
	return TRUE;
}

//64DE20h
RwTexDictionary *RwTexDictionaryForAllTextures(RwTexDictionary* pDict, RwTextureCallBack fpCallBack, void *pData) {
	RwTexDictionary* pReturn;
	_asm {
		push pData
		push fpCallBack
		push pDict
		mov eax, 64DE20h
		call eax
		add esp, 0Ch
		mov pReturn, eax
	}
	return pReturn;
}

//64DE60h
RwTexture* RwTextureCreate(RwRaster* pRaster) {
	RwTexture* pReturn;
	_asm {
		push pRaster
		mov eax,64DE60h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//64DEC0h
RwBool RwTextureDestroy(RwTexture* pTexture) {
	RwBool bReturn;
	_asm {
		push pTexture
		mov eax,64DEC0h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//64E060h
RwTexture* RwTexDictionaryFindNamedTexture(RwTexDictionary* pDict, RwChar* pszName) {
	RwTexture* pReturn;
	_asm {
		push pszName
		push pDict
		mov eax, 64E060h
		call eax
		add esp, 08h
		mov pReturn, eax
	}
	return pReturn;
}

//64E0E0h
RwTexDictionary* RwTexDictionarySetCurrent(RwTexDictionary* pDict) {
	RwTexDictionary* pReturn;
	_asm {
		push pDict
		mov eax, 64E0E0h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//64E100h
RwTexDictionary* RwTexDictionaryGetCurrent(void) {
	RwTexDictionary* pReturn;
	_asm {
		mov eax, 64E100h
		call eax
		mov pReturn, eax
	}
	return pReturn;
}

//64F990h
RwBool _rwStreamReadChunkHeader(RwStream* pStream, RwUInt32* puChunkId, RwUInt32* puChunkLen, RwUInt32* puChunkVersion, RwUInt32* puChunkMajorVersion) {
	RwBool bReturn;
	_asm {
		push puChunkMajorVersion
		push puChunkVersion
		push puChunkLen
		push puChunkId
		push pStream
		mov eax, 64F990h
		call eax
		add esp, 14h
		mov bReturn, eax
	}
	return bReturn;
}

//64FAC0h
RwBool RwStreamFindChunk(RwStream* pStream, RwUInt32 dwType, RwUInt32* dwLengthOut, RwUInt32* dwVersionOut) {
	RwBool bReturn;
	_asm {
		push dwVersionOut
		push dwLengthOut
		push dwType
		push pStream
		mov eax,64FAC0h
		call eax
		add esp,10h
		mov bReturn,eax
	}
	return bReturn;
}

//64FBD0h*
void* RwMemNative32(void* pMem, RwUInt32 uSize) {
	return pMem;
}

//64FBE0h*
void* RwMemRealToFloat32(void* pMem, RwUInt32 uSize) {
	return pMem;
}

//64FC00h*
void* RwMemFloat32ToReal(void* pMem, RwUInt32 uSize) {
	return pMem;
}

//64FCE0h
RwStream* RwStreamReadReal(RwStream* pStream, RwReal* pReals, RwUInt32 numBytes) {
	RwStream* pReturn;
	_asm {
		push numBytes
		push pReals
		push pStream
		mov eax, 64FCE0h
		call eax
		add esp, 0Ch
		mov pReturn, eax
	}
	return pReturn;
}

//64FD50h
RwStream* RwStreamReadInt32(RwStream* pStream, RwInt32* pInts, RwUInt32 numBytes) {
	RwStream* pReturn;
	_asm {
		push numBytes
		push pInts
		push pStream
		mov eax,64FD50h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//6506F0h
RwTexture* RwTextureStreamRead(RwStream* pStream) {
	RwTexture* pReturn;
	_asm {
		push pStream
		mov eax, 6506F0h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//651250h
RwImage* RwImageCreate(RwInt32 nWidth, RwInt32 nHeight, RwInt32 nDepth) {
	RwImage* pReturn;
	_asm {
		push nDepth
		push nHeight
		push nWidth
		mov eax,651250h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//6512B0h
RwBool RwImageDestroy(RwImage* pImage) {
	RwBool bReturn;
	_asm {
		push pImage
		mov eax,6512B0h
		call eax
		add esp,04h
		mov bReturn,eax
	}
	return bReturn;
}

//651310h
RwImage* RwImageAllocatePixels(RwImage* pImage) {
	RwImage* pReturn;
	_asm {
		push pImage
		mov eax,651310h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//6544F0
RpWorld* RpAtomicGetWorld(RpAtomic* pAtomic) {
	RpWorld* pReturn;
	_asm {
		push pAtomic
		mov eax,6544F0h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//655490h
RwRaster* RwRasterCreate(RwInt32 nWidth, RwInt32 nHeight, RwInt32 nDepth, RwInt32 nFlags) {
	RwRaster* pReturn;
	_asm {
		push nFlags
		push nDepth
		push nHeight
		push nWidth
		mov eax,655490h
		call eax
		add esp,10h
		mov pReturn,eax
	}
	return pReturn;
}

RwSurfaceProperties& stDefaultSurfaceProps = *(RwSurfaceProperties*)0x6DDCD8;

//6556C0h*
void _rpMaterialSetDefaultSurfaceProperties(RwSurfaceProperties* pSurfaceProps) {
	if(pSurfaceProps) {
		memcpy(&stDefaultSurfaceProps, pSurfaceProps, sizeof(RwSurfaceProperties));
	}
	else {
		stDefaultSurfaceProps.ambient = 1.0f;
		stDefaultSurfaceProps.diffuse = 1.0f;
		stDefaultSurfaceProps.specular = 1.0f;
	}
}

//6557B0h
RpMaterial* RpMaterialCreate(void) {
	RpMaterial* pReturn;
	_asm {
		mov eax,6557B0h
		call eax
		mov pReturn,eax
	}
	return pReturn;
}

//655830h
RwBool RpMaterialDestroy(RpMaterial* pMaterial) {
	RwBool bReturn;
	_asm {
		push pMaterial
		mov eax, 655830h
		call eax
		add esp, 04h
		mov bReturn, eax
	}
	return bReturn;
}

//655890h
RpMaterial* RpMaterialSetTexture(RpMaterial* pMaterial, RwTexture* pTexture) {
	RpMaterial* pReturn;
	_asm {
		push pTexture
		push pMaterial
		mov eax,655890h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

RwPluginRegistry& materialTKList = *(RwPluginRegistry*)0x6DDCC0;

#ifdef RWUSEORIGINALS
//655920h
RpMaterial* RpMaterialStreamRead(RwStream* pStream) {
	RpMaterial* pReturn;
	_asm {
		push pStream
		mov eax, 655920h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}
#else

#define MATERIALPROG_MATERIAL 1

//655920h*
RpMaterial* RpMaterialStreamRead(RwStream* pStream) {
	RwUInt32 uStructVer, uStructLen, uError = 0, uProgress = 0;
	RwError stError;
	RpMaterial* pMaterial;
	RpMaterialChunkInfo stMatChunk;
	
	while(1) {
	
		//find header and check version
		if(!RwStreamFindChunk(pStream, rwID_STRUCT, &uStructLen, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}
		
		//only accept versions 3.1 - 3.4
		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		if(uStructLen > sizeof(RpMaterialChunkInfo)) {
			uError = STREAMREAD_READERR;
			break;
		}

		//read material chunk info
		if(RwStreamRead(pStream, &stMatChunk, uStructLen) != uStructLen) {
			uError = STREAMREAD_READERR;
			break;
		}

		RwMemNative32(&stMatChunk, sizeof(RpMaterialChunkInfo));

		//create material
		pMaterial = (RpMaterial*)RwEngineInstance->memoryAlloc(RpMaterialGlobalsGet()->pMaterialFreeList, 28);

		if(!pMaterial) {
			uError = STREAMREAD_CREATEERR;
			break;
		}

		pMaterial->pTexture = NULL;
		pMaterial->rgbColor.cAlpha = 0xFF;
		pMaterial->rgbColor.cRed = 0xFF;
		pMaterial->rgbColor.cGreen = 0xFF;
		pMaterial->rgbColor.cBlue = 0xFF;
		pMaterial->pPipeline = NULL;
		pMaterial->nRefCount = 1;

		//set surface properties
		pMaterial->stSurfaceProps.ambient = stMatChunk.surfaceProps.ambient;
		pMaterial->stSurfaceProps.diffuse = stMatChunk.surfaceProps.diffuse;
		pMaterial->stSurfaceProps.specular = stMatChunk.surfaceProps.specular;

		_rwPluginRegistryInitObject(&materialTKList, pMaterial);

		pMaterial->rgbColor = stMatChunk.color;

		uProgress |= MATERIALPROG_MATERIAL;

		if(stMatChunk.textured) {
			//find header and check version
			if(!RwStreamFindChunk(pStream, rwID_TEXTURE, NULL, &uStructVer)) {
				uError = STREAMREAD_READERR;
				break;
			}

			//only accept versions 3.1 - 3.4
			if(uStructVer < 0x31000 || uStructVer > 0x36003) {
				uError = STREAMREAD_VERERR;
				break;
			}
			
			//read texture
			pMaterial->pTexture = RwTextureStreamRead(pStream);

			//allow texture reading to fail, may happen in Vice City
		}

		if(!_rwPluginRegistryReadDataChunks(&materialTKList, pStream, pMaterial)) {
			uError = STREAMREAD_READERR;
			break;
		}

		break;
	}

	if(uError != 0) {
		if(uProgress & MATERIALPROG_MATERIAL) {
			RpMaterialDestroy(pMaterial);
		}

		if(uError & STREAMREAD_VERERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_BADVERSION;
			RwErrorSet(&stError);
		}

		return NULL;
	}

	return pMaterial;
}

#endif

//657020h
RpAtomic* RpMatFXWorldSectorEnableEffects(RpAtomic* pAtomic) {
	RpAtomic* pReturn;

	_asm {
		push pAtomic
		mov eax, 657020h
		call eax
		add esp, 04h
		mov pReturn, eax
	}

	return pReturn;
}

//657050h
RpMaterial* RpMatFXMaterialSetEffects(RpMaterial* pMaterial, RpMatFXMaterialFlags nEffects) {
	RpMaterial* pReturn;

	_asm {
		push nEffects
		push pMaterial
		mov eax, 657050h
		call eax
		add esp, 08h
		mov pReturn, eax
	}
	
	return pReturn;
}

//657180h
RpMaterial* RpMatFXMaterialSetupEnvMap(RpMaterial* pMaterial, RwTexture* pTexture, RwFrame* pFrame, RwBool bUseFrameBufferAlpha, float fCoef) {
	RpMaterial* pReturn;

	_asm {
		push fCoef
		push bUseFrameBufferAlpha
		push pFrame
		push pTexture
		push pMaterial
		mov eax, 657180h
		call eax
		add esp, 14h
		mov pReturn, eax
	}

	return pReturn;
}

//660270h
RwImage* RwImageSetFromRaster(RwImage* pImage, RwRaster* pRaster) {
	RwImage* pReturn;
	_asm {
		push pRaster
		push pImage
		mov eax,660270h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//6602B0h
RwRaster* RwRasterSetFromImage(RwRaster* pRaster, RwImage* pImage) {
	RwRaster* pReturn;
	_asm {
		push pImage
		push pRaster
		mov eax,6602B0h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//660380h
rwFrameList* _rwFrameListDeInitialize(rwFrameList* pFrameList) {
	rwFrameList* pReturn;
	_asm {
		push pFrameList
		mov eax,660380h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//6603B0h
rwFrameList* _rwFrameListStreamRead(RwStream* pStream, rwFrameList* pFrameList) {
	rwFrameList* pReturn;
	_asm {
		push pFrameList
		push pStream
		mov eax,6603B0h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//660940h
RpLight* RpLightStreamRead(RwStream* pStream) {
	RpLight* pReturn;
	_asm {
		push pStream
		mov eax,660940h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//INLINE*
RpLight* RpLightSetFrame(RpLight* pLight, RwFrame* pFrame) {
	_rwObjectHasFrameSetFrame(&pLight->stObject,pFrame);
	return pLight;
}

//660CC0h
void _rwObjectHasFrameSetFrame(RwObjectHasFrame* pObjectHasFrame, RwFrame* pFrame) {
	_asm {
		push pFrame
		push pObjectHasFrame
		mov eax,660CC0h
		call eax
		add esp,08h
	}
}

//660D10h
void _rwObjectHasFrameReleaseFrame(RwObjectHasFrame* pObjectHasFrame) {
	_asm {
		push pObjectHasFrame
		mov eax,660D10h
		call eax
		add esp,04h
	}
}

RwUInt32& resourcesModule=*(RwUInt32*)0x817CE8;

//669240h*
RwBool RwResourcesFreeResEntry(RwResEntry* pEntry) {
	if(pEntry->destroyNotify){
		pEntry->destroyNotify(pEntry);
	}

	if(pEntry->ppOwnerRef){
		*(pEntry->ppOwnerRef)=NULL;
	}

	if(pEntry->lLink.pNext){
		pEntry->lLink.pPrev->pNext=pEntry->lLink.pNext;
		pEntry->lLink.pNext->pPrev=pEntry->lLink.pPrev;

		RwResourcesGlobalsGet()->res.currentSize-=pEntry->nSize;

		_rwResHeapFree(pEntry);
	}

	return TRUE;
}

//INLINE*
rwResourcesGlobals* RwResourcesGlobalsGet() {
	return (rwResourcesGlobals*)((DWORD)RwEngineInstance+(DWORD)resourcesModule);
}


//669790h
RwUInt32 _rwPluginRegistryAddPlugin(RwPluginRegistry* pRegistry, int nSize, RwUInt32 uPluginId, void* pFunc1, void* pFunc2, void* pFunc3) {
	RwUInt32 uReturn;
	_asm {
		push pFunc3
		push pFunc2
		push pFunc1
		push uPluginId
		push nSize
		push pRegistry
		mov eax, 669790h
		call eax
		add esp, 18h
		mov uReturn, eax
	}
	return uReturn;
}

//6699C0h
RwPluginRegistry* _rwPluginRegistryInitObject(RwPluginRegistry* pReg, void *pObject) {
	RwPluginRegistry* pReturn;
	_asm {
		push pObject
		push pReg
		mov eax, 6699C0h
		call eax
		add esp, 08h
		mov pReturn, eax
	}
	return pReturn;
}

//669A20h
RwPluginRegistry* _rwPluginRegistryDeInitObject(RwPluginRegistry* pPluginRegistry, void* pObject) {
	RwPluginRegistry* pReturn;
	_asm {
		push pObject
		push pPluginRegistry
		mov eax,669A20h
		call eax
		add esp,08h
		mov pReturn,eax
	}
	return pReturn;
}

//669AE0h
RwError* RwErrorSet(RwError* pError) {
	RwError* pReturn;
	_asm {
		push pError
		mov eax,669AE0h
		call eax
		add esp,04h
		mov pReturn,eax
	}
	return pReturn;
}

//669BA0h
RwPluginRegistry* _rwPluginRegistryAddPluginStream(RwPluginRegistry* pRegistry, RwUInt32 uPluginId, void* pFunc1, void* pFunc2, void* pFunc3) {
	RwPluginRegistry* uReturn;
	_asm {
		push pFunc3
		push pFunc2
		push pFunc1
		push uPluginId
		push pRegistry
		mov eax, 669BA0h
		call eax
		add esp, 14h
		mov uReturn, eax
	}
	return uReturn;
}

//669C40h
/*RwPluginRegistry* _rwPluginRegistryReadDataChunksX(RwPluginRegistry* pPluginRegistry, RwStream* pStream, void* pObject) {
	RwUInt32 uStructVer, uExtensionsLen, uStructLen, uError = 0, uProgress = 0;
	RwError stError;
	
	while(1) {
	
		//find header and check version
		if(!RwStreamFindChunk(pStream, rwID_EXTENSION, &uExtensionsLen, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}

		//only accept versions 3.1 - 3.4
		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		RwUInt32 uExtId, uExtLen;

		while(uExtensionsLen != 0) {
			if(!_rwStreamReadChunkHeader(pStream, &uExtId, &uExtLen, NULL, NULL)) {
				uError = STREAMREAD_READERR;
				break;
			}

			if(pStream->
		}

		if(uError != 0) {
			break;
		}


	}
}*/

//669C40h
RwPluginRegistry* _rwPluginRegistryReadDataChunks(RwPluginRegistry* pPluginRegistry, RwStream* pStream, void* pObject) {
	RwPluginRegistry* pReturn;
	_asm {
		push pObject
		push pStream
		push pPluginRegistry
		mov eax,669C40h
		call eax
		add esp,0Ch
		mov pReturn,eax
	}
	return pReturn;
}

//669D70h
RwPluginRegistry* _rwPluginRegistryInvokeRights(RwPluginRegistry* pPluginRegistry, RwUInt32 uId, void* pObject, RwUInt32 uExtraData) {
	RwPluginRegistry* pReturn;
	_asm {
		push uExtraData
		push pObject
		push uId
		push pPluginRegistry
		mov eax,669D70h
		call eax
		add esp,10h
		mov pReturn,eax
	}
	return pReturn;
}

//669F50h
RwCamera* RwCameraStreamRead(RwStream* pStream) {
	RwCamera* pReturn;
	_asm {
		push pStream
		mov eax, 669F50h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//66D9B0h
RpMaterialList* _rpMaterialListDeinitialize(RpMaterialList* pMatList) {
	RpMaterialList* pReturn;
	_asm {
		push pMatList
		mov eax, 66D9B0h
		call eax
		add esp, 04h
		mov pReturn, eax
	}
	return pReturn;
}

//66DA30h
RwInt32 _rpMaterialListAppendMaterial(RpMaterialList* pMatList, RpMaterial* pMaterial) {
	RwInt32 nReturn;
	_asm {
		push pMaterial
		push pMatList
		mov eax, 66DA30h
		call eax
		add esp, 08h
		mov nReturn, eax
	}
	return nReturn;
}

#ifdef RWUSEORIGINALS
//66DB20h
RpMaterialList* _rpMaterialListStreamRead(RwStream* pStream, RpMaterialList* pMatList) {
	RpMaterialList* pReturn;
	_asm {
		push pMatList
		push pStream
		mov eax, 66DB20h
		call eax
		add esp, 08h
		mov pReturn, eax
	}
	return pReturn;
}
#else

#define MATLISTPROG_MATLIST 1

//66DB20h*
RpMaterialList* _rpMaterialListStreamRead(RwStream* pStream, RpMaterialList* pMatList) {
	RwUInt32 uStructVer, uStructLen, uError = 0, uProgress = 0;
	RwInt32 nNumMaterials;
	RwError stError;
	
	while(1) {
	
		//find header and check version
		if(!RwStreamFindChunk(pStream, rwID_STRUCT, &uStructLen, &uStructVer)) {
			uError = STREAMREAD_READERR;
			break;
		}
		
		//only accept versions 3.1 - 3.4
		if(uStructVer < 0x31000 || uStructVer > 0x36003) {
			uError = STREAMREAD_VERERR;
			break;
		}

		//get number of materials
		if(!RwStreamReadInt32(pStream, &nNumMaterials, sizeof(RwInt32))) {
			uError = STREAMREAD_READERR;
			break;
		}

		//no materials
		if(nNumMaterials <= 0) {
			pMatList->nNumMaterials = 0;
			pMatList->nSpace = 0;
			pMatList->ppMaterials = NULL;
			return pMatList;
		}

		//allocate memory for material pointers
		pMatList->ppMaterials = (RpMaterial**)RwEngineInstance->memoryFuncs.rwmalloc(sizeof(RpMaterial*) * nNumMaterials);
			
		if(pMatList->ppMaterials == NULL) {
			uError = STREAMREAD_MEMERR;
			break;
		}

		uProgress |= MATLISTPROG_MATLIST;

		pMatList->nSpace = nNumMaterials;
		pMatList->nNumMaterials = 0;

		//get the list that marks duplicates in the material list
		RwInt32* pCopyIds = (RwInt32*)RwEngineInstance->memoryFuncs.rwmalloc(sizeof(RwInt32) * nNumMaterials);

		if(!RwStreamReadInt32(pStream, pCopyIds, sizeof(RwInt32) * nNumMaterials)) {
			RwEngineInstance->memoryFuncs.rwfree(pCopyIds);
			uError = STREAMREAD_READERR;
			break;
		}

		//append materials to the list
		for(int i=0; i<nNumMaterials; i++) {
			RpMaterial* pMaterial;

			if(pCopyIds[i] < 0) {
				if(!RwStreamFindChunk(pStream, rwID_MATERIAL, NULL, &uStructVer)) {
					uError = STREAMREAD_READERR;
					break;
				}

				if(uStructVer < 0x31000 || uStructVer > 0x36003) {
					uError = STREAMREAD_VERERR;
					break;
				}

				pMaterial = RpMaterialStreamRead(pStream);

				if(pMaterial == NULL) {
					uError = STREAMREAD_READERR;
					break;
				}
			}
			else if(pCopyIds[i] >= i) {
				uError = STREAMREAD_READERR;
				break;
			}
			else {
				pMaterial = pMatList->ppMaterials[pCopyIds[i]];
				pMaterial->nRefCount++;
			}

			_rpMaterialListAppendMaterial(pMatList, pMaterial);
			RpMaterialDestroy(pMaterial);
		}

		RwEngineInstance->memoryFuncs.rwfree(pCopyIds);

		break;
	}

	if(uError != 0) {
		if(uProgress & MATLISTPROG_MATLIST) {
			for(int i=0; i<pMatList->nNumMaterials; i++) {
				RpMaterialDestroy(pMatList->ppMaterials[i]);
			}

			RwEngineInstance->memoryFuncs.rwfree(pMatList->ppMaterials);
		}

		if(uError & STREAMREAD_VERERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_BADVERSION;
			RwErrorSet(&stError);
		}
		else if(uError & STREAMREAD_MEMERR) {
			stError.nPluginID = rwID_STRING;
			stError.nErrorCode = E_RW_NOMEM;
			RwErrorSet(&stError);
		}

		pMatList->nNumMaterials = 0;
		pMatList->nSpace = 0;
		pMatList->ppMaterials = NULL;

		return NULL;
	}

	return pMatList;
}

#endif

//6785D0h
void _rwResHeapFree(RwResEntry* pEntry) {
	_asm {
		push pEntry
		mov eax,6785D0h
		call eax
		add esp,04h
	}
}
