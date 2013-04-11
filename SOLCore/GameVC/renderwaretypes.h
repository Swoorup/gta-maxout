//#include "../StdInc.h"
#define _pad(a, size) char a[size]

#pragma once
#pragma pack(push, 1)

struct RwV3d {   
    float x,y,z;
};



typedef unsigned int RwUInt32;
typedef unsigned int RwBool;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef int RwInt32;
typedef short RwInt16;
typedef char RwInt8;
typedef char RwChar;
typedef float RwReal;
//typedef CVector RwV3d;

#define RWFORCEENUMSIZEINT ((RwInt32)((~((RwUInt32)0))>>1))

struct RpAtomic;
struct RwObjectHasFrame;
struct RwResEntry;
struct RpGeometry;
struct RpClump;
struct RxPipeline;
struct RwRaster;
struct RwStream;
struct RpMaterial;
struct RwTexture;

struct RpAnimBlendClump;

enum RpGeometryLockMode {
    rpGEOMETRYLOCKPOLYGONS   =   0x01, /**<Lock the polygons (triangle list) */
    rpGEOMETRYLOCKVERTICES   =   0x02, /**<Lock the vertex positional data */
    rpGEOMETRYLOCKNORMALS    =   0x04, /**<Lock the vertex normal data */
    rpGEOMETRYLOCKPRELIGHT   =   0x08, /**<Lock the pre-light values */
    rpGEOMETRYLOCKTEXCOORDS  =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS1 =   0x10, /**<Lock the texture coordinates set 1*/
    rpGEOMETRYLOCKTEXCOORDS2 =   0x20, /**<Lock the texture coordinates set 2*/
    rpGEOMETRYLOCKTEXCOORDS3 =   0x40, /**<Lock the texture coordinates set 3*/
    rpGEOMETRYLOCKTEXCOORDS4 =   0x80, /**<Lock the texture coordinates set 4*/
    rpGEOMETRYLOCKTEXCOORDS5 = 0x0100, /**<Lock the texture coordinates set 5*/
    rpGEOMETRYLOCKTEXCOORDS6 = 0x0200, /**<Lock the texture coordinates set 6*/
    rpGEOMETRYLOCKTEXCOORDS7 = 0x0400, /**<Lock the texture coordinates set 7*/
    rpGEOMETRYLOCKTEXCOORDS8 = 0x0800, /**<Lock the texture coordinates set 8*/
    rpGEOMETRYLOCKTEXCOORDSALL = 0x0ff0, /**<Lock all texture coordinate sets*/
    rpGEOMETRYLOCKALL        = 0x0fff, /**<Combination of all the above */

    rpGEOMETRYLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef RpMaterial*(*RpMaterialCallBack)(RpMaterial *pMaterial, void *pData);
typedef RwTexture *(*RwTextureCallBack)(RwTexture *texture, void *pData);

typedef void*(*RwPluginObjectConstructor)(void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);
typedef void*(*RwPluginObjectCopy)(void *pDstObject, const void *pSrcObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);
typedef void*(*RwPluginObjectDestructor)(void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);

typedef RwStream*(*RwPluginDataChunkReadCallBack)(RwStream *pStream, RwInt32 nBinaryLength, void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);
typedef RwBool(*RwPluginDataChunkRightsCallBack)(void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject, RwUInt32 uExtraData);
typedef RwStream*(*RwPluginDataChunkWriteCallBack)(RwStream *pStream, RwInt32 nBinaryLength, const void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);
typedef RwInt32(*RwPluginDataChunkGetSizeCallBack)(const void *pObject, RwInt32 nOffsetInObject, RwInt32 nSizeInObject);

typedef RpClump*(*RpClumpCallBackRender)(RpClump* pClump);

struct RwObject;
struct RwFrame;

typedef RpAtomic*(*RpAtomicCallBackRender)(RpAtomic* pAtomic);
typedef RpAtomic*(*RpAtomicCallBack)(RpAtomic* pAtomic, void *pData);
typedef RwObject *(*RwObjectCallBack)(RwObject *pObject, void *pData);
typedef RwFrame *(*RwFrameCallBack)(RwFrame *pFrame, void *pData);

#define rwID_DATABASE 0x64617462     /* datb */

#define MAKECHUNKID(vendorID, chunkID) (((vendorID & 0xFFFFFF) << 8) | (chunkID & 0xFF))
#define GETOBJECTID(chunkID) (chunkID & 0xFF)
#define GETVENDORID(chunkID) ((chunkID >> 8) & 0xFFFFFF)

enum RwOpCombineType {
    rwCOMBINEREPLACE = 0,   //replace - all previous transformations are lost
    rwCOMBINEPRECONCAT,     //pre-concatenation - the given transformation is applied before all others
    rwCOMBINEPOSTCONCAT,    //post-concatenation - the given transformation is applied after all others
    rwOPCOMBINETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwRGBA {
    RwUInt8 cRed; // 0-1
	//red component
    RwUInt8 cGreen; // 1-2
	//green component
    RwUInt8 cBlue; // 2-3
	//blue component
    RwUInt8 cAlpha; // 3-4
	//alpha component
};

enum RwPluginVendor {
    rwVENDORID_CORE             = 0x000000L,
    rwVENDORID_CRITERIONTK      = 0x000001L,
    rwVENDORID_REDLINERACER     = 0x000002L,
    rwVENDORID_CSLRD            = 0x000003L,
    rwVENDORID_CRITERIONINT     = 0x000004L,
    rwVENDORID_CRITERIONWORLD   = 0x000005L,
    rwVENDORID_BETA             = 0x000006L,
    rwVENDORID_CRITERIONRM      = 0x000007L,
    rwVENDORID_CRITERIONRWA     = 0x000008L, /* RenderWare Audio */
    rwVENDORID_CRITERIONRWP     = 0x000009L, /* RenderWare Physics */
    rwPLUGINVENDORFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwError {
    RwInt32 nPluginID; // 0-4
	//plugin ID
    RwInt32 nErrorCode; // 4-8
	//error code
};

#define RWECODE(a,b) a,

enum RwErrorCodeCommon {
    E_RW_NOERROR = (int)0x80000000L,
	RWECODE(E_RW_BADENGINESTATE,
			"Engine in incorrect state for this operation")
	RWECODE(E_RW_BADOPEN,
			"Error opening the file %s")
	RWECODE(E_RW_BADPARAM,
			"Invalid Parameter passed. %s")
	RWECODE(E_RW_BADVERSION,
			"The binary file format version is incompatible with this library")
	RWECODE(E_RW_DEBUGSTACK,
			"Debug Library has Stack Depth mismatch")
	RWECODE(E_RW_DEFAULTPIPELINECREATION,
			"Creation of a default pipeline (%s) failed")
	RWECODE(E_RW_FRAMENOMATRIX,
			"The frame does not have an associated matrix")
	RWECODE(E_RW_INVIMAGEDEPTH,
			"Invalid Image Depth")
	RWECODE(E_RW_INVIMAGEFORMAT,
			"Image has no pixel memory allocated")
	RWECODE(E_RW_INVIMAGEMASK,
			"The mask and image are not the same size")
	RWECODE(E_RW_INVIMAGESIZE,
			"Destination and source images are of differing sizes")
	RWECODE(E_RW_INVRASTERDEPTH,
			"Invalid Raster depth")
	RWECODE(E_RW_INVRASTERFORMAT,
			"Unrecognized raster format")
	RWECODE(E_RW_INVRASTERLOCKREQ,
			"Invalid Raster lock request")
	RWECODE(E_RW_INVRASTERMIPLEVEL,
			"Invalid Raster mipmap level")
	RWECODE(E_RW_INVRASTERSIZE,
			"Invalid Raster size")
	RWECODE(E_RW_INVRASTERUNLOCKREQ,
			"Invalid Raster unlock request")
	RWECODE(E_RW_NOFRAME,
			"Unable to find Frame")
	RWECODE(E_RW_NOMEM,
			"Unable to allocate %d bytes of memory")
	RWECODE(E_RW_NOMIPMAPGENERATIONCALLBACK,
			"No Mipmap generation callback set - use RtMipmapUseDefaultMipmapGenerationCallback")
	RWECODE(E_RW_NOTSSEENABLEDCPU,
			"Not SSE enabled CPU")
	RWECODE(E_RW_NULLP,
			"NULL pointer passed to library routine")
	RWECODE(E_RW_PLUGININIT,
			"Plugin has already been initialized")
	RWECODE(E_RW_PLUGINNOTINIT,
			"Plugin not initialized")
	RWECODE(E_RW_RANGE,
			"A supplied parameter was outside the expected range")
	RWECODE(E_RW_READ,
			"Read error on stream")
	RWECODE(E_RW_REDUNDANT_FUNCTION,
			"Call to redundant function - scheduled to be dropped from future releases")
	RWECODE(E_RW_WRITE,
			"Write error on stream")
	RWECODE(E_RX_MESHES_RANGES_OVERLAP,
		"\n    Geometry is in an invalid format for RxPipeline rendering.\n    There may be visible artifacts and/or decreased performance.\n    Use RpGeometrySortByMaterial.\n    [stream %p type %s]")
	RWECODE(E_RW_STRING_TRUNCATION,
			"strlen(%s) >= %d; truncating at character #%d  == %c")
    E_RW_LASTERROR = RWFORCEENUMSIZEINT
};

typedef RwBool(*RwPluginDataChunkAlwaysCallBack)(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void *(*RwPluginObjectDestructor)(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void *(*RwPluginErrorStrCallBack)(void *);

struct RwPluginRegistry;

struct RwPluginRegEntry {
    RwInt32         offset;
    RwInt32         size;
    RwUInt32        pluginID;
    RwPluginDataChunkReadCallBack readCB;
    RwPluginDataChunkWriteCallBack writeCB;
    RwPluginDataChunkGetSizeCallBack getSizeCB;
    RwPluginDataChunkAlwaysCallBack alwaysCB;
    RwPluginDataChunkRightsCallBack rightsCB;
    RwPluginObjectConstructor constructCB;
    RwPluginObjectDestructor destructCB;
    RwPluginObjectCopy copyCB;
    RwPluginErrorStrCallBack errStrCB;
    RwPluginRegEntry *nextRegEntry;
    RwPluginRegEntry *prevRegEntry;
    RwPluginRegistry *parentRegistry;
};

struct RwPluginRegistry {
    RwInt32          sizeOfStruct;
    RwInt32          origSizeOfStruct;
    RwInt32          maxSizeOfStruct;
    RwInt32          staticAlloc;
    RwPluginRegEntry *firstRegEntry;
    RwPluginRegEntry *lastRegEntry;
};

enum RwCorePluginID {
    rwID_NAOBJECT               = MAKECHUNKID(rwVENDORID_CORE, 0x00),
    rwID_STRUCT                 = MAKECHUNKID(rwVENDORID_CORE, 0x01),
    rwID_STRING                 = MAKECHUNKID(rwVENDORID_CORE, 0x02),
    rwID_EXTENSION              = MAKECHUNKID(rwVENDORID_CORE, 0x03),

    rwID_CAMERA                 = MAKECHUNKID(rwVENDORID_CORE, 0x05),
/**< RwCamera chunk. See \ref RwCameraStreamRead */

    rwID_TEXTURE                = MAKECHUNKID(rwVENDORID_CORE, 0x06),
/**< RwTexture chunk. See \ref RwTextureStreamRead */

    rwID_MATERIAL               = MAKECHUNKID(rwVENDORID_CORE, 0x07),
/**< RpMaterial chunk. See \ref RpMaterialStreamRead. */

    rwID_MATLIST                = MAKECHUNKID(rwVENDORID_CORE, 0x08),
    rwID_ATOMICSECT             = MAKECHUNKID(rwVENDORID_CORE, 0x09),
    rwID_PLANESECT              = MAKECHUNKID(rwVENDORID_CORE, 0x0A),

    rwID_WORLD                  = MAKECHUNKID(rwVENDORID_CORE, 0x0B),
/**< RpWorld chunk. See \ref RpWorldStreamRead. */

    rwID_SPLINE                 = MAKECHUNKID(rwVENDORID_CORE, 0x0C),
/**< RpSpline chunk. See \ref RpSplineStreamRead */

    rwID_MATRIX                 = MAKECHUNKID(rwVENDORID_CORE, 0x0D),
/**< RwMatrix chunk. See \ref RwMatrixStreamRead */

    rwID_FRAMELIST              = MAKECHUNKID(rwVENDORID_CORE, 0x0E),

    rwID_GEOMETRY               = MAKECHUNKID(rwVENDORID_CORE, 0x0F),
/**< RpGeometry chunk. See \ref RpGeometryStreamRead. */

    rwID_CLUMP                  = MAKECHUNKID(rwVENDORID_CORE, 0x10),
/**< RpClump chunk. See \ref RpClumpStreamRead. */

    rwID_LIGHT                  = MAKECHUNKID(rwVENDORID_CORE, 0x12),
/**< RpLight chunk. See \ref RpLightStreamRead. */

    rwID_UNICODESTRING          = MAKECHUNKID(rwVENDORID_CORE, 0x13),

    rwID_ATOMIC                 = MAKECHUNKID(rwVENDORID_CORE, 0x14),
/**< RpAtomic chunk. See \ref RpAtomicStreamRead */

    rwID_TEXTURENATIVE          = MAKECHUNKID(rwVENDORID_CORE, 0x15),

    rwID_TEXDICTIONARY          = MAKECHUNKID(rwVENDORID_CORE, 0x16),
/**< RwTexDictionary - platform specific texture dictionary.
 * See \ref RwTexDictionaryStreamRead. */

    rwID_ANIMDATABASE           = MAKECHUNKID(rwVENDORID_CORE, 0x17),

    rwID_IMAGE                  = MAKECHUNKID(rwVENDORID_CORE, 0x18),
/**< RwImage chunk. See \ref RwImageStreamRead */

    rwID_SKINANIMATION          = MAKECHUNKID(rwVENDORID_CORE, 0x19),
    rwID_GEOMETRYLIST           = MAKECHUNKID(rwVENDORID_CORE, 0x1A),

    rwID_ANIMANIMATION          = MAKECHUNKID(rwVENDORID_CORE, 0x1B),
/**< RtAnimAnimation chunk. See \ref RtAnimAnimationStreamRead. */
    rwID_HANIMANIMATION         = MAKECHUNKID(rwVENDORID_CORE, 0x1B),
/**< RtAnimAnimation chunk. For backwards compatibility. See \ref rwID_ANIMANIMATION. */

    rwID_TEAM                   = MAKECHUNKID(rwVENDORID_CORE, 0x1C),
/**< \ref RpTeam chunk. See \ref RpTeamStreamRead */
    rwID_CROWD                  = MAKECHUNKID(rwVENDORID_CORE, 0x1D),

    rwID_DMORPHANIMATION        = MAKECHUNKID(rwVENDORID_CORE, 0x1E),
/**< RpDMorphAnimation - delta morph animation chunk. See \ref RpDMorphAnimationStreamRead */

    rwID_RIGHTTORENDER          = MAKECHUNKID(rwVENDORID_CORE, 0x1f),

    rwID_MTEFFECTNATIVE         = MAKECHUNKID(rwVENDORID_CORE, 0x20),
/**< \if xbox RpMTEffect - multi-texture effect chunk. See \ref RpMTEffectStreamRead \endif */
/**< \if gcn  RpMTEffect - multi-texture effect chunk. See \ref RpMTEffectStreamRead \endif */

    rwID_MTEFFECTDICT           = MAKECHUNKID(rwVENDORID_CORE, 0x21),
/**< \if xbox RpMTEffectDict - multi-texture effect dictionary chunk. See \ref RpMTEffectDictStreamRead \endif */
/**< \if gcn  RpMTEffectDict - multi-texture effect dictionary chunk. See \ref RpMTEffectDictStreamRead \endif */

    rwID_TEAMDICTIONARY         = MAKECHUNKID(rwVENDORID_CORE, 0x22),
/**< \ref RpTeamDictionary chunk. See \ref RpTeamDictionaryStreamRead */

    rwID_PITEXDICTIONARY        = MAKECHUNKID(rwVENDORID_CORE, 0x23),
/**< RwTexDictionary - platform independent texture dictionary. See \ref RtPITexDictionaryStreamRead. */

    rwID_TOC                    = MAKECHUNKID(rwVENDORID_CORE, 0x24),
/**< RtTOC chunk. See \ref RtTOCStreamRead */

    rwID_PRTSTDGLOBALDATA       = MAKECHUNKID(rwVENDORID_CORE, 0x25),
/**< RpPrtStdEmitterClass, RpPrtStdParticleClass and RpPrtStdPropertyTable chunks.
 *   See \ref RpPrtStdEClassStreamRead, \ref RpPrtStdPClassStreamRead
 *   \ref RpPrtStdPropTabStreamRead and \ref RpPrtStdGlobalDataStreamRead */

    rwID_ALTPIPE                = MAKECHUNKID(rwVENDORID_CORE, 0x26),
    rwID_PIPEDS                 = MAKECHUNKID(rwVENDORID_CORE, 0x27),
    rwID_PATCHMESH              = MAKECHUNKID(rwVENDORID_CORE, 0x28),
/**< RpPatchMesh chunk. See \ref RpPatchMeshStreamRead */

    rwID_CHUNKGROUPSTART        = MAKECHUNKID(rwVENDORID_CORE, 0x29),
    rwID_CHUNKGROUPEND          = MAKECHUNKID(rwVENDORID_CORE, 0x2A),

    rwID_UVANIMDICT             = MAKECHUNKID(rwVENDORID_CORE, 0x2B),
/**< UV anim dictionary chunk. See \ref RpUVAnimGetDictSchema */

    rwID_COLLTREE               = MAKECHUNKID(rwVENDORID_CORE, 0x2C),

    rwID_ENVIRONMENT            = MAKECHUNKID(rwVENDORID_CORE, 0x2D),
/**< RpEnvironment chunk is used internally to convey art package background
   < settings to the Visualizer.*/    

/* Insert before MAX and increment MAX */
    rwID_COREPLUGINIDMAX        = MAKECHUNKID(rwVENDORID_CORE, 0x2E),
    rwCOREPLUGINIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwStreamType {
    rwNASTREAM = 0,     //invalid stream type
    rwSTREAMFILE,       //file
    rwSTREAMFILENAME,   //file name
    rwSTREAMMEMORY,     //memory
    rwSTREAMCUSTOM,     //custom
    rwSTREAMTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwStreamAccessType {
    rwNASTREAMACCESS = 0, //invalid stream access
    rwSTREAMREAD,         //read
    rwSTREAMWRITE,        //write
    rwSTREAMAPPEND,       //append
    rwSTREAMACCESSTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwStreamMemory {
    RwUInt32 dwPosition; // 0-4
	//current 'memory' position 0 is first byte
    RwUInt32 nSize; // 4-8
	//space allocated currently
    RwUInt8 *pMemBlock; // 8-9
	//current memory block pointer
};

union RwStreamFile {
    void *fpFile; // 0-4
	//file pointer
    const void *pConstfpFile; // 4-8
	//const file pointer
};

typedef RwBool(*rwCustomStreamFnClose) (void *data);
typedef RwUInt32(*rwCustomStreamFnRead) (void *data, void *buffer, RwUInt32 length);
typedef RwBool(*rwCustomStreamFnWrite) (void *data, const void *buffer, RwUInt32 length);
typedef RwBool(*rwCustomStreamFnSkip) (void *data, RwUInt32 offset);

struct RwStreamCustom {
    rwCustomStreamFnClose sfnclose; // 0-4
    rwCustomStreamFnRead sfnread; // 4-8
    rwCustomStreamFnWrite sfnwrite; // 8-12
    rwCustomStreamFnSkip sfnskip; // 12-16
    void *pData; // 16-20
};

union RwStreamUnion {
    RwStreamMemory stMemory; // 0-9
	//memory
    RwStreamFile stFile; // 0-8
	//file
    RwStreamCustom stCustom; // 0-20
	//custom
};

struct RwStream {
    RwStreamType eType; // 0-4
    RwStreamAccessType eAccessType; // 4-8
    RwInt32 dwPosition; // 8-12
    RwStreamUnion unType; // 12-32
    RwBool rwOwned; // 32-36
};

struct RtQuat {
	RwV3d vecImag;
	//imaginary parts
	RwReal fReal;
	//the real part
};

struct RwObject {
	RwUInt8 cType; // 0-1
	//internal use
	RwUInt8 cSubType; // 1-2
	//internal use
	RwUInt8 cFlags; // 2-3
	//internal use
	RwUInt8 cPrivateFlags; // 3-4
	//internal use
	void* pParent; // 4-8
	//internal use
};

struct RwLLLink {
    RwLLLink *pNext; // 0-4
	//next link
    RwLLLink *pPrev; // 4-8
	//previous link
};

struct RwLinkList {
    RwLLLink stLink; // 0-8
	//first link
};

typedef RwObjectHasFrame* (*RwObjectHasFrameSyncFunction)(RwObjectHasFrame *object);

struct RwObjectHasFrame {
	RwObject stObject; // 0-8
	//base object structure
	RwLLLink lFrame; // 8-16
	//frame linked list
	RwObjectHasFrameSyncFunction fnSync; // 16-20
	//sync function
};

struct RwMatrix {
	RwV3d vLookRight; // 0-12
	//rotation vector 1
	RwUInt32 dwFlags; // 12-16
	//matrix flags
	RwV3d vLookAt; // 16-28
	//rotation vector 2
	RwUInt32 dwPad01; // 28-32
	//padding
	RwV3d vLookUp; // 32-44
	//rotation vector 3
	RwUInt32 dwPad02; // 44-48
	//padding
	RwV3d vPos; // 48-60
	//position vector
	RwUInt32 dwPad03; // 60-64
	//padding
};

struct RwSphere {
    RwV3d vecCenter; // 0-12
	//sphere center
    RwReal fRadius; // 12-16
	//sphere radius
};

struct RwFrame {
	RwObject stObject; // 0-8
	//object structure for this frame
	RwLLLink lInDirtyListLink; // 8-16
	//dirty link list element
	RwMatrix matFrameRelative; // 16-80
	//matrix relative to parent (if root, then absolute)
	RwMatrix matFrameAbsolute; // 80-144
	//absolute matrix of the frame
	RwLinkList pObjectList; // 144-152
	//list of objects connected to a frame
	RwFrame* pFirstChild; // 152-156
	//first child of the frame
	RwFrame* pNext; // 156-160
	//next frame
	RwFrame* pRoot; // 160-164
	//root frame
	_pad(__pad3a,8); // 164-172
	RwChar szFrameName[24]; // 172-196
	//name of the frame
	RwUInt32 dwFrameHierarchyId; // 196-200
	//hierarchy id of the frame
};

enum RpInterpolatorFlag {
    rpINTERPOLATORDIRTYINSTANCE = 0x01,
    rpINTERPOLATORDIRTYSPHERE = 0x02,
    rpINTERPOLATORNOFRAMEDIRTY = 0x04,
    rpINTERPOLATORFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RpInterpolator {
	RwInt32 nFlags; // 0-4
	//animation interpolator flags
	RwInt16 nStartMorphTarget; // 4-6
	//startMorphTarget
	RwInt16 nEndMorphTarget; // 6-8
	//endMorphTarget
	RwReal fTime; // 8-12
	//time
	RwReal fRecipTime; // 12-16
	//recipTime
	RwReal fPosition; // 16-20
	//current position
};

enum RxClusterForcePresent {
    rxCLALLOWABSENT  = FALSE, //the cluster is allowed to be absent if no prior nodes create it and no subsequent nodes require it
    rxCLFORCEPRESENT = TRUE , //the cluster must be present even if no prior nodes create it and no subsequent nodes require it
    rxCLUSTERFORCEPRESENTFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxClusterDefinition {
    RwChar* pName; // 0-4
	//name
    RwUInt32 dwDefaultStride; // 4-8
	//default stride
    RwUInt32 dwDefaultAttributes; // 8-12
	//default attributes
    const RwChar* pAttributeSet; // 12-16
	//attribute set
};

struct RxClusterRef {
    RxClusterDefinition* pClusterDef; // 0-4
	//cluster definition
    RxClusterForcePresent stForcePresent; // 4-8
	//specifies whether the cluster should be forced present
    RwUInt32 dwReserved; // 8-12
	//omit or initialize to zero
};

enum RxClusterValid {
    rxCLVALID_NOCHANGE = 0, //the cluster and its data will not change in validity on passing through this node
    rxCLVALID_VALID    = 1, //the cluster and its data will be valid on exit from this node
    rxCLVALID_INVALID  = 2, //the cluster's data will be invalid on exit from this node
    rxCLUSTERVALIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxOutputSpec {
	RwChar* pName; // 0-4
	//name
	RxClusterValid* pOutputClusters; // 4-8
	//states of clusters of interest on output
	RxClusterValid eAllOtherClusters; // 8-12
	//states of clusters not of interest on output
};

enum RxClusterValidityReq {
    rxCLREQ_DONTWANT = 0, //the cluster is required but any data within it is not wanted and will be overwritten
    rxCLREQ_REQUIRED = 1, //the cluster is required and it must contain valid data
    rxCLREQ_OPTIONAL = 2, //the cluster will be used if it is present and contains valid data, otherwise the node will make do without it
    rxCLUSTERVALIDITYREQFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxIoSpec {
	RwUInt32 dwNumClustersOfInterest; // 0-4
	//number of clusters of interest
	RxClusterRef* pClustersOfInterest; // 4-8
	//clusters of interest array
	RxClusterValidityReq *pInputRequirements; // 8-12
	//requirements of the clusters of interest on input to the node
	RwUInt32 dwNumOutputs; // 12-16
	//number of outputs from the node
	RxOutputSpec* pOutputs; // 16-20
	//output specification array
};

struct rxHeapFreeBlock;

struct rxHeapBlockHeader {
    rxHeapBlockHeader* pPrev; // 0-4
	//previous block
	rxHeapBlockHeader* pNext; // 4-8
	//next block
    RwUInt32 dwSize; // 8-12
	//block size
    rxHeapFreeBlock* pFreeEntry; // 12-16
	//(or null)
    RwUInt32 dwPad[4]; // 16-32
	//alignment padding to 32 bytes
};

struct rxHeapFreeBlock {
    RwUInt32 dwSize; // 0-4
	//block size
    rxHeapBlockHeader* pPtr; // 4-8
	//block header pointer
};

struct rxHeapSuperBlockDescriptor {
    void *pStart; // 0-4
	//start pointer
    RwUInt32 dwSize; // 4-8
	//superblock size
    rxHeapSuperBlockDescriptor* pNext; // 8-12
	//next descriptor
};

struct RxHeap {
    RwUInt32 dwSuperBlockSize; // 0-4
	//granularity of heap growth
    rxHeapSuperBlockDescriptor* pHead; // 4-8
	//internally used superblock pointer
    rxHeapBlockHeader* pHeadBlock; // 8-12
	//internally used block pointer
    rxHeapFreeBlock* pFreeBlocks; // 12-16
	//internally used free blocks pointer
    RwUInt32 dwEntriesAlloced; // 16-20
	//number of entries allocated
    RwUInt32 dwEntriesUsed; // 20-24
	//number of entries used
    RwBool bDirty; // 24-28
	//internally used boolean, flags whether the heap needs resetting or not
};

struct RwFreeList {
    RwUInt32 uEntrySize; // 0-4
	//size of an entry in the free list
    RwUInt32 uEntriesPerBlock; // 4-8
	//number of entries per free list block
    RwUInt32 uHeapSize; // 8-12
	//size of the heap
    RwUInt32 uAlignment; // 12-16
	//alignment of a free list entry
    RwLinkList llBlockList; // 16-24
	//list of data blocks
    RwUInt32 uFlags; // 24-28
	//flags which affect the behavior of the free list. rwFREELISTFLAG_FREEBLOCKS
    RwLLLink llLink; // 28-36
	//link to the free list linked list
};

enum RwShadeMode {
    rwSHADEMODENASHADEMODE = 0,
    rwSHADEMODEFLAT,                //flat shading
    rwSHADEMODEGOURAUD,             //Gouraud shading
    rwSHADEMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwBlendFunction {
    rwBLENDNABLEND = 0,
    rwBLENDZERO,            // (0,    0,    0,    0   )
    rwBLENDONE,             // (1,    1,    1,    1   )
    rwBLENDSRCCOLOR,        // (Rs,   Gs,   Bs,   As  )
    rwBLENDINVSRCCOLOR,     // (1-Rs, 1-Gs, 1-Bs, 1-As)
    rwBLENDSRCALPHA,        // (As,   As,   As,   As  )
    rwBLENDINVSRCALPHA,     // (1-As, 1-As, 1-As, 1-As)
    rwBLENDDESTALPHA,       // (Ad,   Ad,   Ad,   Ad  )
    rwBLENDINVDESTALPHA,    // (1-Ad, 1-Ad, 1-Ad, 1-Ad)
    rwBLENDDESTCOLOR,       // (Rd,   Gd,   Bd,   Ad  )
    rwBLENDINVDESTCOLOR,    // (1-Rd, 1-Gd, 1-Bd, 1-Ad)
    rwBLENDSRCALPHASAT,     // (f,    f,    f,    1   )  f = min (As, 1-Ad)
    rwBLENDFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwTextureAddressMode {
    rwTEXTUREADDRESSNATEXTUREADDRESS = 0,
    rwTEXTUREADDRESSWRAP,      //UV wraps (tiles)
    rwTEXTUREADDRESSMIRROR,    //alternate UV is flipped
    rwTEXTUREADDRESSCLAMP,     //UV is clamped to 0-1
    rwTEXTUREADDRESSBORDER,    //border color takes effect outside of 0-1
    rwTEXTUREADDRESSMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwTextureFilterMode {
    rwFILTERNAFILTERMODE = 0,
    rwFILTERNEAREST,                //point sampled
    rwFILTERLINEAR,                 //bilinear
    rwFILTERMIPNEAREST,             //point sampled per pixel mip map
    rwFILTERMIPLINEAR,              //bilinear per pixel mipmap
    rwFILTERLINEARMIPNEAREST,       //MipMap interp point sampled
    rwFILTERLINEARMIPLINEAR,        //trilinear
    rwTEXTUREFILTERMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwFogType {
    rwFOGTYPENAFOGTYPE = 0,
    rwFOGTYPELINEAR,            //linear fog
    rwFOGTYPEEXPONENTIAL,       //exponential fog
    rwFOGTYPEEXPONENTIAL2,      //exponential^2 fog
    rwFOGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxRenderStateVector {
    RwUInt32 uFlags; // 0-4
	//a load of the boolean renderstate options
    RwShadeMode eShadeMode; // 4-8
	//flat or Gouraud currently
    RwBlendFunction eSrcBlend; // 8-12
	//src  alpha, 1-src  alpha, etc
    RwBlendFunction eDestBlend; // 12-16
	//dest alpha, 1-dest alpha, etc
    RwRaster* pTextureRaster; // 16-20
	//texture raster
    RwTextureAddressMode eAddressModeU; // 20-24
	//U addressing mode - WRAP, MIRROR, CLAMP, BORDER
    RwTextureAddressMode eAddressModeV; // 24-28
	//V addressing mode - WRAP, MIRROR, CLAMP, BORDER
    RwTextureFilterMode eFilterMode; // 28-32
	//filtering mode - combos of NEAREST LINEAR MIP
    RwRGBA rgbBorderColor; // 32-36
	//border color for texturing address mode border
    RwFogType eFogType; // 36-40
	//select the type of fogging to use
    RwRGBA rgbFogColor; // 40-44
	//color used for fogging
};

struct rwPipeGlobals {
    RwFreeList *pPipesFreeList; // 0-4
	//save mallocs, use a freelist
    RxRenderStateVector  defaultRenderState; // 4-48
	//default render state
    RwLinkList llAllPipelines; // 48-56
	//unused as of yet, meant to be used to keep track of all created pipelines (for CBs and maybe cleanup)
    RwUInt32 uMaxNodesPerPipe; // 56-60
	//initialised from _rxPipelineMaxNodes at startup. Used to allow conservative, single allocations during pipelock

    /* NOTE: Rw and RpWorld PowerPipe globals kept together for simplicity */

    /* The current default pipelines (used if pipe == NULL for an object) */
    RxPipeline          *currentAtomicPipeline; // 60-64
    RxPipeline          *currentWorldSectorPipeline; // 64-68
    RxPipeline          *currentMaterialPipeline; // 68-72
    /* Generic C-based pipes that run on all platforms
     * - these are set as the current pipes at startup unless
     *   platform-specific pipes (below) are created */
    RxPipeline          *genericAtomicPipeline; // 72-76
    RxPipeline          *genericWorldSectorPipeline; // 76-80
    RxPipeline          *genericMaterialPipeline; // 80-84
    /* Platforms that have their own non-generic pipelines
     * (OPENGL, D3D8, SKY2, KAMUI2, DOLPHIN) put them here: */
    RxPipeline          *platformAtomicPipeline; // 84-88
    RxPipeline          *platformWorldSectorPipeline; // 88-92
    RxPipeline          *platformMaterialPipeline; // 92-96
};

struct RxPipelineNodeParam {
    void* pDataParam; // 0-4
	//the data pointer passed in to \ref RxPipelineExecute
    RxHeap* pHeap; // 4-8
	//the heap associated with the current pipeline exeuction
};

struct RxPipeline;
struct RxPipelineNode;
struct RxNodeDefinition;

typedef RwBool (*RxNodeBodyFn) (RxPipelineNode* self, const RxPipelineNodeParam *pParams);
typedef RwBool (*RxNodeInitFn) (RxNodeDefinition* self);
typedef void   (*RxNodeTermFn) (RxNodeDefinition* self);
typedef RwBool (*RxPipelineNodeInitFn) (RxPipelineNode* self);
typedef void   (*RxPipelineNodeTermFn) (RxPipelineNode* self);
typedef RwBool (*RxPipelineNodeConfigFn) (RxPipelineNode* self, RxPipeline* pPipeline);
typedef RwUInt32 (*RxConfigMsgHandlerFn) (RxPipelineNode* self, RwUInt32 msg, RwUInt32 intparam, void *pParam);

struct RxNodeMethods {
    RxNodeBodyFn fnNodeBody; // 0-4
	//node body function
    RxNodeInitFn fnNodeInit; // 4-8
	//node initialization function
    RxNodeTermFn fnNodeTerm; // 8-12
	//node termination function
    RxPipelineNodeInitFn fnPipelineNodeInit; // 12-16
	//pipeline node initialization function
    RxPipelineNodeTermFn fnPipelineNodeTerm; // 16-20
	//pipeline node termination function
    RxPipelineNodeConfigFn fnPipelineNodeConfig; // 20-24
	//pipeline node configuration function
    RxConfigMsgHandlerFn fnConfigMsgHandler; // 24-28
	//configuration message handler function
};

enum RxNodeDefEditable {
    rxNODEDEFCONST    = FALSE, //this node definition should not be freed
    rxNODEDEFEDITABLE = TRUE , //this node definition is a temporary, modified copy of another and can be freed
    rxNODEDEFEDITABLEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxNodeDefinition {
	RwChar* szName; // 0-4
	//name	
	RxNodeMethods stNodeMethods; // 4-32
	//node methods
	RxIoSpec stIo; // 32-52
	//input/output specification
	RwUInt32 dwPipelineNodePrivateDataSize; // 52-56
	//size in bytes of node's private data
	RxNodeDefEditable stEditable; // 56-60
	//flags whether a node is editable
	RwInt32 dwInputPipesCnt; // 60-64
	//count of the unlocked pipelines containing this node
};

struct RxPipelineCluster {
    RxClusterDefinition* pClusterRef; // 0-4
	//cluster refererence
    RwUInt32 dwCreationAttributes; // 4-8
	//creation attributes
};

struct RxPipelineNodeTopSortData {
    RwUInt32 dwNumIns; // 0-4
	//input count
    RwUInt32 dwNumInsVisited; // 4-8
	//count of inputs visited during dependencies propagation/cluster slot allocation
    void* pReq; // 8-12 (rxReq*, not defined in RW headers?)
	//req used in dependencies propagation/cluster slot allocation
};

struct RxPipelineNode {
	RxNodeDefinition* pNodeDef; // 0-4
	//node definition reference
	RwUInt32 dwNumOutputs; // 4-8
	//output count
	RwUInt32* pOutputs; // 8-12
	//output array, indexing the pipeline's array of pipeline nodes
	RxPipelineCluster **slotClusterRefs; // 12-16
	//for packets passing through this node, SlotClusterRefs[n] identifies the cluster to be found at index n in the packet's
	//Clusters[] array. These assignments are determined at pipeline Unlock() time and are good for the life of the pipeline.
	RwUInt32* pSlotsContinue; // 16-20
	//cluster persistence table for the node's outputs
	void* pPrivateData; // 20-24
	//pointer to the pipeline Node's private data
	RwUInt32* pInputToClusterSlot; // 24-28
	//LUT to locate clusters of interest in packets passing through this pipeline Node
	RxPipelineNodeTopSortData *pTopSortData; // 28-32
	//internal Use
	void* pInitializationData; // 32-36
	//used by the pipeline node initialisation function in setting up the Private data.
	RwUInt32 dwInitializationDataSize; // 36-40
	//present so that if the node is cloned we can copy the initialisation data.
};

struct RxCluster {
    RwUInt16 wFlags; // 0-2
	//bitfield of flags e.g. modification permissions
    RwUInt16 wStride; // 2-4
	//stride in bytes of the cluster's data
    void* pData; // 4-8
	//the cluster's data
    void* pCurrentData; // 8-12
	//a 'cursor', referencing the current element in the data
    RwUInt32 dwNumAlloced; // 12-16
	//allocated count
    RwUInt32 dwNumUsed; // 16-20
	//used count
    RxPipelineCluster* pClusterRef; // 20-24
	//valid after a cluster has been locked for writing, otherwise NULL. Analog of \ref RxPipelineNode and its 'nodeDef' member
    RwUInt32 dwAttributes; // 24-28
	//cluster attributes
};

struct RxPacket {
    RwUInt16 wFlags; // 0-2
	//flags to guide pipeline execution
    RwUInt16 wNumClusters; // 2-4
	//maximum number of clusters simultanesouly present in the current pipeline
    RxPipeline* pPipeline; // 4-8
	//the pipeline in which this packet is embedded (the current pipeline)
    RwUInt32* pInputToClusterSlot; // 8-12
	//LUT to locate clusters of interest in the packet
    RwUInt32* pSlotsContinue; // 12-16
	//bitfields specifying clusters persisting to output node
    RxPipelineCluster **pSlotClusterRefs; // 16-20
	//internal use
    RxCluster stClusters[1]; // 20-??
	//cluster array large enough for widest part of the pipeline
};

struct RxPipelineRequiresCluster {
    RxClusterDefinition* pClusterDef; // 0-4
	//reference to a Cluster definition
    RxClusterValidityReq rqdOrOpt;
	//cluster validity requirement (rxCLREQ_DONTWANT, rxCLREQ_REQUIRED or rxCLREQ_OPTIONAL)
    RwUInt32 dwSlotIndex;
	//index into the packet's cluster array within this pipeline
};

enum rxEmbeddedPacketState {
    rxPKST_PACKETLESS = 0, //packet not created
    rxPKST_UNUSED     = 1, //packet created and then destroyed
    rxPKST_INUSE      = 2, //packet created but not yet destroyed and fetched but not yet dispatched
    rxPKST_PENDING    = 3, //packet created but not destroyed and dispatched but not yet fetched
    rxEMBEDDEDPACKETSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RxPipeline {
	RwBool bLocked; // 0-4
	//flags whether the pipeline is locked for editing
	RwUInt32 dwNumNodes; // 4-8
	//node count
	RxPipelineNode* pNodes; // 8-12
	//topologically sorted array of pipeline nodes
	RwUInt32 dwPacketNumClusterSlots; // 12-16
	//number of slots allocated for clusters
	rxEmbeddedPacketState eEmbeddedPacketState; // 16-20
	//the state of this pipeline's embedded packet
	RxPacket* pEmbeddedPacket; // 20-24
	//this pipeline's embedded packet
	RwUInt32 dwNumInputRequirements; // 24-28
	//input requirements count
	RxPipelineRequiresCluster* pInputRequirements; // 28-32
	//input requirements array
	void* pSuperBlock; // 32-36
	//internally used block of memory
	RwUInt32 dwSuperBlockSize; // 36-40
	//internally used block of memory
	RwUInt32 dwEntryPoint; // 40-44
	//the index of the node which is the entry point of this pipeline
	RwUInt32 dwPluginId; // 44-48
	//if required, the Id of the plugin owning this pipeline, or 0
	RwUInt32 dwPluginData; // 48-52
	//rights callback extra data
};

enum RpAtomicFlag {
    rpATOMICCOLLISIONTEST = 0x01, /**<A generic collision flag to indicate
                                   * that the atomic should be considered
                                   * in collision tests.
                                   */
    rpATOMICRENDER = 0x04,      /**<The atomic is rendered if it is
                                 * in the view frustum.
                                 */

    rpATOMICFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpAtomicSetGeomFlag {
    rpATOMICSAMEBOUNDINGSPHERE = 0x01, /**<The bounding-sphere for the
                                        * new geometry is assumed to be the
                                        * same as the old one, if any, and
                                        * should not be recalculated.
                                        */

    rpATOMICSETGEOMFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpAtomicPrivateFlag {
    rpATOMICPRIVATEWORLDBOUNDDIRTY = 0x01,
    rpATOMICPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RpAtomic {
	RwObjectHasFrame stObject; // 0-20
	//base structure for objects with frame
	RwResEntry* pResEntry; // 20-24
	//information for an instance
	RpGeometry* pGeometry; // 24-28
	//triangles making the object
	RwSphere stBoundingSphere; // 28-44
	//local bounding sphere
	RwSphere stWorldBoundingSphere; // 44-60
	//world bounding sphere
	RpClump* pClump; // 60-64
	//clump it belongs to
	RwLLLink inClumpLink; // 64-72
	//clump atomic linked list entry
	RpAtomicCallBackRender pRenderCallback; // 72-76
	//render callback for this atomic
	RpInterpolator stInterpolator; // 76-96
	//animation interpolator data
	RwUInt16 wRenderFrame; // 96-98
	//counter for checks of "render has occurred already"
	RwUInt16 wPad; // 98-100
	//padding
	RwLinkList llWorldSectorsInAtomic; // 100-108
	//connections to sectors
	_pad(__pad4a,16); // 96-112
};

struct RpClumpChunkInfo {
    RwInt32 nNumAtomics;
    RwInt32 nNumLights;
    RwInt32 nNumCameras;
};

struct RpClump {
	RwObject stObject; // 0-8
	//base object
	RwLinkList llAtomicList; // 8-16
	//list of atomics
	RwLinkList llLightList; // 16-24
	//list of lights
    RwLinkList llCameraList; // 24-32
	//list of cameras
	_pad(__pad0b,28); // 32-60
	RpAnimBlendClump* pAnimBlend; // 60-64
	//pointer to the animation block
	_pad(__pad0c,8); // 64-72
	RpClumpCallBackRender fnRenderCallback; // 72-76
	//render callback
};

enum RwRasterType {
    rwRASTERTYPENORMAL = 0x00,          /**<Normal */
    rwRASTERTYPEZBUFFER = 0x01,         /**<Z Buffer */
    rwRASTERTYPECAMERA = 0x02,          /**<Camera */
    rwRASTERTYPETEXTURE = 0x04,         /**<Texture */
    rwRASTERTYPECAMERATEXTURE = 0x05,   /**<Camera texture */
    rwRASTERTYPEMASK = 0x07,            /**<Mask for finding type */

    rwRASTERPALETTEVOLATILE = 0x40,        /**<If set, hints that the palette will change often */
    rwRASTERDONTALLOCATE = 0x80,        /**<If set the raster is not allocated */
    rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwRaster {
	RwRaster* pParent; // 0-4
	//top level raster if a sub raster
	RwUInt8* pPixels; // 4-8
	//pixel pointer when locked
	RwUInt8* pPalette; // 8-12
	//raster palette
	RwInt32 nWidth; // 12-16
	//raster width
	RwInt32 nHeight; // 16-20
	//raster height
	RwInt32 nDepth; // 20-24
	//raster depth
	RwInt32 nStride; // 24-28
	//lines bytes of raster
	RwInt16 nOffsetX; // 28-30
	//sub raster X offset
	RwInt16 nOffsetY; // 30-32
	//sub raster Y offset
	RwUInt8 cType; // 32-33
	//type of raster
	RwUInt8 cFlags; // 33-34
	//raster flags
	RwUInt8 cPrivateFlags; // 34-35
	//raster private flags
	RwUInt8 cFormat; // 35-36
	//raster format
	RwUInt8* pOriginalPixels; // 36-40
	//original pixels
	RwInt32 nOriginalWidth; // 40-44
	//original width
	RwInt32 nOriginalHeight; // 44-48
	//original height
	RwInt32 nOriginalStride; // 48-52
	//original stride
};

struct RwTexDictionary {
    RwObject stObject; // 0-8
	//homogeneous type
    RwLinkList stTexturesInDict; // 8-16
	//list of textures in dictionary
    RwLLLink lInInstance; // 16-24
	//link list of all dicts in system
};

struct RwImage {
	RwInt32 nFlags; // 0-4
	//image flags
	RwInt32 nWidth; // 4-8
	//image width in pixels
	RwInt32 nHeight; // 8-12
	//image height in pixels
	RwInt32 nDepth; // 12-16
	//bits per pixel
	RwInt32 nStride; // 16-20
	//stride
	RwUInt8* cpPixels; // 20-24
	//pointer to pixels
	RwRGBA* pPalette; // 24-28
	//palette
};

#define rwTEXTUREBASENAMELENGTH 32

struct RwTexture {
    RwRaster* pRaster; // 0-4
	//pointer to RwRaster with data
    RwTexDictionary* pDict; // 4-8
	//dictionary this texture is in
    RwLLLink lInDictionary; // 8-16
	//list of textures in this dictionary
    RwChar szName[rwTEXTUREBASENAMELENGTH]; // 16-48
	//name of the texture
    RwChar szMask[rwTEXTUREBASENAMELENGTH]; // 48-80
	//name of the textures mask
    RwUInt32 dwFilterAddressing; // 80-84
	//filtering & addressing mode flags (31 [xxxxxxxx xxxxxxxx vvvvuuuu ffffffff])
    RwInt32 nRefCount; // 84-88
	//reference count, surprisingly enough
};

struct RwSurfaceProperties {
    RwReal ambient; // 0-4
	//ambient reflection coefficient
    RwReal specular; // 4-8
	//specular reflection coefficient
    RwReal diffuse; // 8-12
	//reflection coefficient
};

enum RpMatFXMaterialFlags {
    rpMATFXEFFECTNULL            = 0, /**<No material effect.           */
    rpMATFXEFFECTBUMPMAP         = 1, /**<Bump mapping                  */
    rpMATFXEFFECTENVMAP          = 2, /**<Environment mapping           */
    rpMATFXEFFECTBUMPENVMAP      = 3, /**<Bump and environment mapping  */
    rpMATFXEFFECTDUAL            = 4, /**<Dual pass                     */
    rpMATFXEFFECTUVTRANSFORM     = 5, /**<Base UV transform             */
    rpMATFXEFFECTDUALUVTRANSFORM = 6, /**<Dual UV transform (2 pass)    */

    rpMATFXEFFECTMAX,
    rpMATFXNUMEFFECTS       = rpMATFXEFFECTMAX - 1,

    rpMATFXFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RpMaterial {
	RwTexture* pTexture; // 0-4
	//material texture
	RwRGBA rgbColor; // 4-8
	//color of the material
	void* pPipeline; // 8-12
	//pipeline for the material
	RwSurfaceProperties stSurfaceProps; // 12-24
	//surface properties
	RwInt16 nRefCount; // 24-26
	//reference count
	RwInt16 nPad; // 26-28
	//padding
};

struct RpMaterialList {
	RpMaterial** ppMaterials; // 0-4
	//material pointers
	RwInt32 nNumMaterials; // 4-8
	//number of materials
	RwInt32 nSpace;  // 8-12
	//space for materials
};

struct RpTriangle {
    RwUInt16 wVertIndex[3]; // 0-6
	//vertex indices
    RwUInt16 wMatIndex; // 6-8
	//index into material list
};

struct RpMeshHeader {
    RwUInt32 dwFlags; // 0-4
	//see RpMeshHeaderFlags
    RwUInt16 wNumMeshes; // 4-6
	//number of meshes in object
    RwUInt16 wSerialNum; // 6-8
	//determine if mesh has changed since last instance
    RwUInt32 dwTotalIndicesInMesh; // 8-12
	//total triangle index count in all meshes
    RwUInt32 dwFirstMeshOffset; // 12-16
	//offset in bytes from end this structure RpMeshHeader to the first mesh
};

typedef void (*RwResEntryDestroyNotify)(RwResEntry * resEntry);

struct RwResEntry {
	RwLLLink lLink; // 0-8
	//node in the list of resource elements
	RwInt32 nSize; // 8-12
	//size of this node
	void* pOwner; // 12-16
	//owner of this node
	RwResEntry** ppOwnerRef; // 16-20
	//pointer to pointer to this (enables de-alloc)
	RwResEntryDestroyNotify destroyNotify; // 20-24
	//this is called right before destruction
};

struct RpMorphTarget {
	RpGeometry* pParentGeom; // 0-4 
	//parent geometry
	RwSphere stBoundingSphere; // 4-20
	//bounding sphere
	RwV3d* pVerts; // 20-24
	//vertices list
	RwV3d* pNormals; // 24-28
	//normals list
};

struct RwTexCoords {
    RwReal u; // 0-4
	//U value
    RwReal v; // 4-8
	//V value
};

#define rwMAXTEXTURECOORDS 8

enum RpGeometryFlag {
    rpGEOMETRYTRISTRIP  = 0x00000001, /**<This geometry's meshes can be
                                          rendered as strips.
                                          \ref RpMeshSetTriStripMethod is
                                          used to change this method.*/
    rpGEOMETRYPOSITIONS = 0x00000002, /**<This geometry has positions */  
    rpGEOMETRYTEXTURED  = 0x00000004, /**<This geometry has only one set of
                                          texture coordinates. Texture
                                          coordinates are specified on a per
                                          vertex basis */
    rpGEOMETRYPRELIT    = 0x00000008, /**<This geometry has pre-light colors */
    rpGEOMETRYNORMALS   = 0x00000010, /**<This geometry has vertex normals */
    rpGEOMETRYLIGHT     = 0x00000020, /**<This geometry will be lit */
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040, /**<Modulate material color 
                                                      with vertex colors
                                                      (pre-lit + lit) */

    rpGEOMETRYTEXTURED2 = 0x00000080, /**<This geometry has at least 2 sets of
                                          texture coordinates. */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpGeometry.
     */

    rpGEOMETRYNATIVE            = 0x01000000,
    rpGEOMETRYNATIVEINSTANCE    = 0x02000000,

    rpGEOMETRYFLAGSMASK         = 0x000000FF,
    rpGEOMETRYNATIVEFLAGSMASK   = 0x0F000000,

    rpGEOMETRYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RpGeometry {
	RwObject stObject; // 0-8
	//generic type
	RwUInt32 dwFlags; // 8-12
	//geometry flags
	RwUInt16 wLockedSinceLastInst; // 12-14
	//what has been locked since we last instanced - for re-instancing
	RwInt16 nRefCount; // 14-16
	//reference count (for keeping track of atomics referencing geometry)
	RwInt32 nNumTriangles; // 16-20
	//quantity of polys (polys, verts and morph targets)
	RwInt32 nNumVertices; // 20-24
	//quantity of vertices
	RwInt32 nNumMorphTargets; // 24-28
	//quantity of morph targets
	RwInt32 nNumTexCoordSets; // 28-32
	//quantity of texture coord sets
	RpMaterialList stMatList; // 32-44
	//material list
	RpTriangle* pTriangles; // 44-48
	//the triangles
	RwRGBA* pPreLitLum; // 48-52
	//the pre-lighting values
	RwTexCoords* pTexCoords[rwMAXTEXTURECOORDS]; // 52-84
	//texture coordinates
	RpMeshHeader* pMesh; // 84-88
	//the mesh - groups polys of the same material
	RwResEntry* pResEntry; // 88-92
	//information for an instance
	RpMorphTarget* pMorphTarget; // 92-96
	//the Morph Target
};

struct RwRGBAReal {
    RwReal fRed; // 0-4
	//red component
    RwReal fGreen; // 4-8
	//green component
    RwReal fBlue; // 8-12
	//blue component
    RwReal fAlpha; // 12-16
	//alpha component
};

struct RpLight {
	RwObjectHasFrame stObject; // 0-20
	//object with frame
	RwReal fRadius; // 20-24
	//light radius
	RwRGBAReal color; // 24-40
	//light color
	RwReal fMinusCosAngle; // 40-44
	//minusCosAngle
	RwLinkList llWorldSectorsInLight; // 44-52
	//WorldSectorsInLight
	RwLLLink inWorld; // 52-60
	//inWorld
	RwUInt16 uLightFrame; // 60-62
	//lightFrame
	RwUInt16 pad; // 62-64
};

typedef RpLight*(*RpLightCallBack) (RpLight * light, void *data);

struct RwV2d {
	RwReal x; // 0-4
	//X value
	RwReal y; // 4-8
	//Y value
};

struct RwPlane {
    RwV3d normal; // 0-12
	//normal to the plane
    RwReal distance; // 12-16
	//distance to plane from origin in normal direction
};

struct RwFrustumPlane {
    RwPlane plane; // 0-16
    RwUInt8 closestX; // 16-17
    RwUInt8 closestY; // 17-18
    RwUInt8 closestZ; // 18-19
    RwUInt8 pad; // 19-20
};

struct RwBBox {
    /* Must be in this order */
    RwV3d sup;
	//supremum vertex.
    RwV3d inf;
	//infimum vertex.
};

enum RwCameraProjection {
    rwNACAMERAPROJECTION = 0,   /**<Invalid projection */
    rwPERSPECTIVE = 1,          /**<Perspective projection */
    rwPARALLEL = 2,             /**<Parallel projection */
    rwCAMERAPROJECTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwCamera;

typedef RwCamera *(*RwCameraCallBack)(RwCamera *camera, void *data);
typedef RwCamera   *(*RwCameraBeginUpdateFunc) (RwCamera * camera);
typedef RwCamera   *(*RwCameraEndUpdateFunc) (RwCamera * camera);

struct RwCamera {
	RwObjectHasFrame    object; // 0-20

	/* Parallel or perspective projection */
	RwCameraProjection  projectionType;

	/* Start/end update functions */
	RwCameraBeginUpdateFunc beginUpdate;
	RwCameraEndUpdateFunc endUpdate;

	/* The view matrix */
	RwMatrix            viewMatrix;

	/* The cameras image buffer */
	RwRaster           *frameBuffer;

	/* The Z buffer */
	RwRaster           *zBuffer;

	/* Cameras mathmatical characteristics */
	RwV2d               viewWindow;
	RwV2d               recipViewWindow;
	RwV2d               viewOffset;
	RwReal              nearPlane;
	RwReal              farPlane;
	RwReal              fogPlane;

	/* Transformation to turn camera z or 1/z into a Z buffer z */
	RwReal              zScale, zShift;

	/* The clip-planes making up the viewing frustum */
	RwFrustumPlane      frustumPlanes[6];
	RwBBox              frustumBoundBox;

	/* Points on the tips of the view frustum */
	RwV3d               frustumCorners[8];
};

enum RwRenderState
{
    rwRENDERSTATENARENDERSTATE = 0,

    rwRENDERSTATETEXTURERASTER,
        /**<Raster used for texturing (normally used in immediate mode). 
         *  The value is a pointer to an \ref RwRaster.
         * Default: NULL.
         */
    rwRENDERSTATETEXTUREADDRESS,
        /**<\ref RwTextureAddressMode: wrap, clamp, mirror or border.
         * Default: rwTEXTUREADDRESSWRAP.
         */
    rwRENDERSTATETEXTUREADDRESSU,
        /**<\ref RwTextureAddressMode in u only.
         * Default: rwTEXTUREADDRESSWRAP.
         */
    rwRENDERSTATETEXTUREADDRESSV,
        /**<\ref RwTextureAddressMode in v only.
         * Default: rwTEXTUREADDRESSWRAP.
         */
    rwRENDERSTATETEXTUREPERSPECTIVE,
        /**<Perspective correction on/off (always enabled on many platforms).
         */
    rwRENDERSTATEZTESTENABLE,
        /**<Z-buffer test on/off.
         * Default: TRUE.
         */
    rwRENDERSTATESHADEMODE,
        /**<\ref RwShadeMode: flat or gouraud shading.
         * Default: rwSHADEMODEGOURAUD.
         */
    rwRENDERSTATEZWRITEENABLE,
        /**<Z-buffer write on/off.
         * Default: TRUE.
         */
    rwRENDERSTATETEXTUREFILTER,
        /**<\ref RwTextureFilterMode: point sample, bilinear, trilinear, etc.
         * Default: rwFILTERLINEAR.
         */
    rwRENDERSTATESRCBLEND,
        /**<\ref RwBlendFunction used to modulate the source pixel color
         *  when blending to the frame buffer.
         * Default: rwBLENDSRCALPHA.
         */
    rwRENDERSTATEDESTBLEND,
        /**<\ref RwBlendFunction used to modulate the destination pixel
         *  color in the frame buffer when blending. The resulting pixel
         *  color is given by the formula 
         *  (SRCBLEND * srcColor + DESTBLEND * destColor) for each RGB
         *  component. For a particular platform, not all combinations
         *  of blend function are allowed (see platform specific
         *  restrictions).
         * Default: rwBLENDINVSRCALPHA.
         */
    rwRENDERSTATEVERTEXALPHAENABLE,
        /**<Alpha blending on/off (always enabled on some platforms). 
         *  This is normally used in immediate mode to enable alpha blending 
         *  when vertex colors or texture rasters have transparency. Retained
         *  mode pipelines will usually set this state based on material colors 
         *  and textures.
         * Default: FALSE.
         */
    rwRENDERSTATEBORDERCOLOR,
        /**<Border color for \ref RwTextureAddressMode 
         *  \ref rwTEXTUREADDRESSBORDER. The value should be a packed 
         *  RwUInt32 in a platform specific format. The macro 
         *  RWRGBALONG(r, g, b, a) may be used to construct this using 
         *  8-bit color components.
         * Default: RWRGBALONG(0, 0, 0, 0).
         */
    rwRENDERSTATEFOGENABLE,
        /**<Fogging on/off (all polygons will be fogged).  
         * Default: FALSE.
         */
    rwRENDERSTATEFOGCOLOR,
        /**<Color used for fogging. The value should be a packed RwUInt32 
         *  in a platform specific format. The macro RWRGBALONG(r, g, b, a)
         *  may be used to construct this using 8-bit color components. 
         * Default: RWRGBALONG(0, 0, 0, 0).
         */
    rwRENDERSTATEFOGTYPE,
        /**<\ref RwFogType, the type of fogging to use. 
         * Default: rwFOGTYPELINEAR.
         */
    rwRENDERSTATEFOGDENSITY,
        /**<Fog density for \ref RwFogType of 
         *  \ref rwFOGTYPEEXPONENTIAL or \ref rwFOGTYPEEXPONENTIAL2. 
         *  The value should be a pointer to an RwReal in the 
         *  range 0 to 1.  
         * Default: 1.
         */
    rwRENDERSTATECULLMODE = 20,
        /**<\ref RwCullMode, for selecting front/back face culling, or
         *  no culling.
         * Default: rwCULLMODECULLBACK.
         */
    rwRENDERSTATESTENCILENABLE,
        /**<Stenciling on/off.
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: FALSE.
         */
    rwRENDERSTATESTENCILFAIL,
        /**<\ref RwStencilOperation used when the stencil test passes.
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: rwSTENCILOPERATIONKEEP.
         */
    rwRENDERSTATESTENCILZFAIL,
        /**<\ref RwStencilOperation used when the stencil test passes and 
         *  the depth test (z-test) fails. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: rwSTENCILOPERATIONKEEP.
         */
    rwRENDERSTATESTENCILPASS,
        /**<\ref RwStencilOperation used when both the stencil and the depth 
         *  (z) tests pass. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: rwSTENCILOPERATIONKEEP.
         */
    rwRENDERSTATESTENCILFUNCTION,
        /**<\ref RwStencilFunction for the stencil test. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: rwSTENCILFUNCTIONALWAYS.
         */
    rwRENDERSTATESTENCILFUNCTIONREF,
        /**<Integer reference value for the stencil test. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: 0.
         */
    rwRENDERSTATESTENCILFUNCTIONMASK,
        /**<Mask applied to the reference value and each stencil buffer 
         *  entry to determine the significant bits for the stencil test. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: 0xffffffff.
         */
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
        /**<Write mask applied to values written into the stencil buffer. 
         *  <i> Supported on Xbox, D3D8, D3D9, and OpenGL only. </i>
         * Default: 0xffffffff.
         */
    rwRENDERSTATEALPHATESTFUNCTION,
        /**<\ref RwAlphaTestFunction for the alpha test. When a pixel fails,
         * neither the frame buffer nor the Z-buffer are updated.
         * Default: rwALPHATESTFUNCTIONGREATER (GameCube, Xbox, D3D8, D3D9
         * and OpenGL). The default PS2 behaviour is to always update the
         * frame buffer and update the Z-buffer only if a greater than or
         * equal test passes.
         */
    rwRENDERSTATEALPHATESTFUNCTIONREF,
        /**<Integer reference value for the alpha test. 
         *  <i> Range is 0 to 255, mapped to the platform's actual range </i>
         * Default: 128 (PS2) 0 (GameCube, Xbox, D3D8, D3D9 and OpenGL).
         */

    rwRENDERSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwPrimitiveType
{
    rwPRIMTYPENAPRIMTYPE = 0,   /**<Invalid primative type */
    rwPRIMTYPELINELIST = 1,     /**<Unconnected line segments, each line is specified by
                                 * both its start and end index, independently of other lines
                                 * (for example, 3 segments specified as 0-1, 2-3, 4-5) */
    rwPRIMTYPEPOLYLINE = 2,     /**<Connected line segments, each line's start index
                                 * (except the first) is specified by the index of the end of
                                 * the previous segment (for example, 3 segments specified as
                                 * 0-1, 1-2, 2-3) */
    rwPRIMTYPETRILIST = 3,      /**<Unconnected triangles: each triangle is specified by
                                 * three indices, independently of other triangles (for example,
                                 * 3 triangles specified as 0-1-2, 3-4-5, 6-7-8) */
    rwPRIMTYPETRISTRIP = 4,     /**<Connected triangles sharing an edge with, at most, one
                                 * other forming a series (for example, 3 triangles specified
                                 * as 0-2-1, 1-2-3-, 2-4-3) */
    rwPRIMTYPETRIFAN = 5 ,      /**<Connected triangles sharing an edge with, at most,
                                 * two others forming a fan (for example, 3 triangles specified
                                 * as 0-2-1, 0-3-2, 0-4-3) */
    rwPRIMTYPEPOINTLIST = 6,    /**<Points 1, 2, 3, etc. This is not
                                 * supported by the default RenderWare
                                 * immediate or retained-mode pipelines
                                 * (except on PlayStation 2), it is intended
                                 * for use by user-created pipelines */
    rwPRIMITIVETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwD3D8Vertex {
    RwReal x; // 0-4
	//screen X
    RwReal y; // 4-8
	//screen Y
    RwReal z; // 8-12
	//screen Z
    RwReal rhw; // 12-16
	//reciprocal of homogeneous W
    RwUInt32 emissiveColor; // 16-20
	//vertex color
    RwReal u; // 20-24
	//texture coordinate U
    RwReal v; // 24-28
	//texture coordinate V
};

typedef RwD3D8Vertex RwIm2DVertex;

typedef RwUInt16 RxVertexIndex;
typedef RxVertexIndex RwImVertexIndex;

typedef RwBool (*RwSystemFunc)(RwInt32 nOption, void *pOut, void *pInOut, RwInt32 nIn);
typedef RwBool (*RwRenderStateSetFunction)(RwRenderState nState, void *pParam);
typedef RwBool (*RwRenderStateGetFunction)(RwRenderState nState, void *pParam);
typedef RwBool (*RwIm2DRenderLineFunction)(RwIm2DVertex *vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2);
typedef RwBool (*RwIm2DRenderTriangleFunction)(RwIm2DVertex *vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool (*RwIm2DRenderPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex *vertices, RwInt32 numVertices);
typedef RwBool (*RwIm2DRenderIndexedPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex *vertices, RwInt32 numVertices, RwImVertexIndex *indices, RwInt32 numIndices);
typedef RwBool (*RwIm3DRenderLineFunction)(RwInt32 vert1, RwInt32 vert2);
typedef RwBool (*RwIm3DRenderTriangleFunction)(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool (*RwIm3DRenderPrimitiveFunction)(RwPrimitiveType primType);
typedef RwBool (*RwIm3DRenderIndexedPrimitiveFunction)(RwPrimitiveType primtype, RwImVertexIndex *indices, RwInt32 numIndices);

struct RwDevice {
     RwReal gammaCorrection; // 0-4
	//gamma correction
    RwSystemFunc fpSystem; // 4-8
	//system handler
    RwReal zBufferNear; // 8-12
	//near Z buffer value
    RwReal zBufferFar; // 12-16
	//far Z buffer value

    /* Immediate mode functions */
    RwRenderStateSetFunction                fpRenderStateSet; // 16-20
    RwRenderStateGetFunction                fpRenderStateGet; // 20-24

    /* Render functions */
    RwIm2DRenderLineFunction                fpIm2DRenderLine; // 24-28
    RwIm2DRenderTriangleFunction            fpIm2DRenderTriangle; // 28-32
    RwIm2DRenderPrimitiveFunction           fpIm2DRenderPrimitive; // 32-36
    RwIm2DRenderIndexedPrimitiveFunction    fpIm2DRenderIndexedPrimitive; // 36-40

    RwIm3DRenderLineFunction                fpIm3DRenderLine; // 40-44
    RwIm3DRenderTriangleFunction            fpIm3DRenderTriangle; // 44-48
    RwIm3DRenderPrimitiveFunction           fpIm3DRenderPrimitive; // 48-52
    RwIm3DRenderIndexedPrimitiveFunction    fpIm3DRenderIndexedPrimitive; // 52-56
};

#define rwSTANDARDNUMOFSTANDARD 29

typedef RwBool (*RwStandardFunc)(void *pOut,void *pInOut,RwInt32 nI);

typedef int (*vecSprintfFunc)(RwChar *buffer, const RwChar *format, ...); 
typedef int (*vecVsprintfFunc)(RwChar *buffer, const RwChar *format, va_list argptr); 
typedef RwChar *(*vecStrcpyFunc)(RwChar *dest, const RwChar *srce);
typedef RwChar *(*vecStrncpyFunc)(RwChar *dest, const RwChar *srce, size_t size);
typedef RwChar *(*vecStrcatFunc)(RwChar *dest, const RwChar *srce);
typedef RwChar *(*vecStrncatFunc)(RwChar *dest, const RwChar *srce, size_t size);
typedef RwChar *(*vecStrrchrFunc)(const RwChar *string, int findThis);
typedef RwChar *(*vecStrchrFunc)(const RwChar *string, int findThis);
typedef RwChar *(*vecStrstrFunc)(const RwChar *string, const RwChar *findThis);
typedef int (*vecStrcmpFunc)(const RwChar *string1, const RwChar *string2);
typedef int (*vec_stricmpFunc)(const RwChar *string1, const RwChar *string2);
typedef size_t (*vecStrlenFunc)(const RwChar *string);
typedef RwChar *(*vecStruprFunc)(RwChar *string);
typedef RwChar *(*vecStrlwrFunc)(RwChar *string);
typedef RwChar *(*vecStrtokFunc)(RwChar *string, const RwChar *delimit);
typedef int (*vecSscanfFunc)(const RwChar *buffer, const RwChar *format, ...);

struct RwStringFunctions {
    vecSprintfFunc vecSprintf; // 0-4
    vecVsprintfFunc vecVsprintf; // 4-8
    vecStrcpyFunc vecStrcpy; // 8-12
    vecStrncpyFunc vecStrncpy; // 12-16
    vecStrcatFunc vecStrcat; // 16-20
    vecStrncatFunc vecStrncat; // 20-24
    vecStrrchrFunc vecStrrchr; // 24-28
    vecStrchrFunc vecStrchr; // 28-32
    vecStrstrFunc vecStrstr; // 32-36
    vecStrcmpFunc vecStrcmp; // 36-40
    vec_stricmpFunc vec_stricmp; // 40-44
    vecStrlenFunc vecStrlen; // 44-48
    vecStruprFunc vecStrupr; // 48-52
    vecStrlwrFunc vecStrlwr; // 52-56
    vecStrtokFunc vecStrtok; // 56-60
    vecSscanfFunc vecSscanf; // 60-64
};

struct RwMemoryFunctions {
    /* c.f.
     * Program Files/Microsoft Visual Studio/VC98/Include/MALLOC.H
     */
    void *(*rwmalloc)(size_t size); // 0-4
        /**< Allocates memory blocks.
         *  \param size Number of bytes to allocate. Should be greater
         *         then zero.
         *  \param hint A RwUInt32 value representing a memory hint.
         *  \return A void pointer to the allocated space, or NULL if
         *          there is insufficient memory available.
         */
    void  (*rwfree)(void *mem); // 4-8
        /**< Deallocates or frees a memory block.
         *  \param mem Previously allocated memory block to be freed.
         *         Shouldn't be NULL pointer.
         */
    void *(*rwrealloc)(void *mem, size_t newSize); // 8-12
        /**< Reallocate memory blocks.
         *  \param mem Pointer to previously allocated memory block.
         *  \param size New size in bytes. Should be greater then zero.
         *  \param hint A RwUInt32 value representing a memory hint.
         *  \return A void pointer to the allocated space, or NULL if
         *          there is insufficient memory available.
         */
    void *(*rwcalloc)(size_t numObj, size_t sizeObj); // 12-16
        /**< Allocates an array in memory with elements initialized to 0.
         *  \param numObj Non-zero number of elements.
         *  \param sizeObj Non-zero length in bytes of each element.
         *  \param hint A RwUInt32 value representing a memory hint.
         *  \return A void pointer to the allocated space, or NULL if
         *          there is insufficient memory available.
         */
};

typedef void        (*RwFreeListCallBack) (void *pMem, void *pData);
typedef void       *(*RwMemoryAllocFn)    (RwFreeList * fl, RwUInt32 hint);
typedef RwFreeList *(*RwMemoryFreeFn)     (RwFreeList * fl, void *pData);

struct RwMetrics {
    RwUInt32    numTriangles;           /**< The number of triangles processed. */
    RwUInt32    numProcTriangles;       /**< The number of mesh triangles processed. */
    RwUInt32    numVertices;            /**< The number of vertices processed. */
    RwUInt32    numTextureUploads;
    /**<
     * \if sky2 The number of textures used. \endif
     * \if d3d8 The number of times RwD3D8SetTexture is called. \endif
     * \if d3d9 The number of times RwD3D9SetTexture is called.  \endif
     * \if opengl The number of times RwOpenGLSetTexture is called. \endif
     * \if xbox The number of textures used. \endif
     * \if gcn The number of textures used. \endif
     * \if softras The number of times the \ref rwRENDERSTATETEXTURERASTER renderstate
     * is set with a valid (non-NULL) texture. \endif
     */
    RwUInt32    sizeTextureUploads;
    /**<
     * \if sky2 The number of bytes uploaded to the GS. \endif
     * \if d3d8 The size of the textures, in bytes, that have been passed to RwD3D8SetTexture. \endif
     * \if d3d9 The size of the textures, in bytes, that have been passed to RwD3D9SetTexture. \endif
     * \if opengl The size of the textures, in bytes, that have been passed to RwOpenGLSetTexture. \endif
     * \if xbox Size of textures swapped. \endif
     * \if gcn Size of textures swapped. \endif
     * \if softras The size of the textures, in bytes, that have been set with
     * the \ref rwRENDERSTATETEXTURERASTER renderstate. \endif
     */
    RwUInt32    numResourceAllocs;      /**< The number of resource blocks swapped. */
    void        *devSpecificMetrics;    /**< Device specific metrics. */
};

enum RwEngineStatus {
    rwENGINESTATUSIDLE = 0,                     /* This needs to be zero */
    rwENGINESTATUSINITED = 1,
    rwENGINESTATUSOPENED = 2,
    rwENGINESTATUSSTARTED = 3,
    rwENGINESTATUSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RwGlobals {
    /* Current entities */
    void *curCamera; // 0-4
	//current camera
    void *curWorld; // 4-8
	//current World

    /* Checking counters */
    RwUInt16 renderFrame; // 8-10
	//camera display count
    RwUInt16 lightFrame; // 10-12
	//used to ensure each light is applied only once.
    RwUInt16 pad[2];  // 12-16
	//longword align it again

    /* For the currently accessed device */
    RwDevice dOpenDevice; // 16-72

    /* Standard renderers and functions */
    RwStandardFunc stdFunc[rwSTANDARDNUMOFSTANDARD]; // 72-188

    /* All of the frames which have been updated */
    RwLinkList dirtyFrameList; // 188-196

	/* Unknown functions */
	_pad(__pad00,44); // 196-240

    /* The string functions */
    RwStringFunctions stringFuncs; // 240-304

    /* The memory allocation functions */
    RwMemoryFunctions memoryFuncs; // 304-320

    /* virtual memory alloc/free functions */
    RwMemoryAllocFn memoryAlloc; // 320-324
    RwMemoryFreeFn memoryFree; // 324-328

    RwMetrics *metrics; // 328-332

    /* Current engine status */
    RwEngineStatus engineStatus; // 332-336

    /* Resource arena init size. */
    RwUInt32 resArenaInitSize; // 336-340
};

struct RpClumpGlobals {
	RwFreeList* pAtomicFreeList; // 0-4
	//atomic free list
	RwFreeList* pClumpFreeList; // 4-8
	//clump free list
};

struct RpMaterialGlobals {
	RwFreeList* pMaterialFreeList; // 4-8
	//material free list
};

struct RwTextureGlobals {
	RwFreeList* pMaterialFreeList; // 4-8
	//material free list
};

struct RpClumpLightExt {
	RpClump* pClump; // 0-4
	//owner clump
	RwLLLink inClumpLink; // 4-12
	//link inside clump
};

struct RpClumpCameraExt {
	RpClump* pClump; // 0-4
	//owner clump
	RwLLLink inClumpLink; // 4-12
	//link inside clump
};

struct rwFrameList {
    RwFrame **frames; // 0-4
    RwInt32 numFrames; // 4-8
};

struct rpGeometryList {
	RpGeometry **pGeometries; // 0-4
	RwInt32 numGeometries; // 4-8
};

struct rpClumpAtomicChunkInfo {
	RwInt32 nFrameID; // 0-4
	//frame id of the atomic
	RwInt32 nGeometryID; // 4-8
	//geometry id of the atomic
	RwUInt8 uFlags; // 8-9
	//atomic flags
	RwUInt8 uPad[3]; // 9-12
	//padding
	RwUInt32 uNull; // 12-16
	//never used (padding?)
};

enum RpWorldPrivateFlag
{
    rpWORLDSINGLEMALLOC = 0x01,
    rpWORLDPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpWorldFlag
{
    rpWORLDTRISTRIP  = 0x01, /**<This world's meshes can be rendered
                                 as tri strips */
    rpWORLDPOSITIONS = 0x02, /**<This world has positions */
    rpWORLDTEXTURED  = 0x04, /**<This world has only one set of texture coordinates */
    rpWORLDPRELIT    = 0x08, /**<This world has luminance values */
    rpWORLDNORMALS   = 0x10, /**<This world has normals */
    rpWORLDLIGHT     = 0x20, /**<This world will be lit */
    rpWORLDMODULATEMATERIALCOLOR = 0x40,
                             /**<Modulate material color with vertex colors
                                 (pre-lit + lit) */
    rpWORLDTEXTURED2 = 0x80, /**<This world has 2 or more sets of texture coordinates */

    /*
     * These above flags were stored in the flags field in an RwObject, they
     * are now stored in the flags file of the RpWorld.
     */

    rpWORLDNATIVE               = 0x01000000,
    rpWORLDNATIVEINSTANCE       = 0x02000000,

    rpWORLDFLAGSMASK            = 0x000000FF,
    rpWORLDNATIVEFLAGSMASK      = 0x0F000000,

    rpWORLDSECTORSOVERLAP       = 0x40000000,

    rpWORLDFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpWorldRenderOrder
{
    rpWORLDRENDERNARENDERORDER = 0,
    rpWORLDRENDERFRONT2BACK,  /**<Renders nearest sectors first */
    rpWORLDRENDERBACK2FRONT, /**<Renders furthest sectors first */
    rpWORLDRENDERORDERFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

struct RpVertexNormal
{
    RwInt8          x;
    RwInt8          y;
    RwInt8          z;
    RwUInt8         pad; /* pad character to force alignment */
};

struct RpSector
{
    RwInt32                 type;
};

struct RpWorldSector
{
    RwInt32                 type;

    RpTriangle              *triangles;             /* Triangles */

    RwV3d                   *vertices;              /* Vertex positions */
    RpVertexNormal          *normals;               /* Vertex normals */

    RwTexCoords             *texCoords[rwMAXTEXTURECOORDS]; /* Texture coordinates */

    RwRGBA                  *preLitLum;             /* Pre lit luminances */

    /* Pointer to memory allocated for vertex and poly pointers */
    RwResEntry              *repEntry;

    /* Atomics in this sectors */
    /* The pointers are frigged so they look like they are pointing to
       Atomics when they are pointing to here */
    RwLinkList              collAtomicsInWorldSector;       /* Coll priority */

    /* Lights in an atomic sector */
    RwLinkList              lightsInWorldSector;

    /* Outer bounding box of sector based on BSP planes */
    RwBBox                  boundingBox;

    /* Bounding box tightly enclosing geometry */
    RwBBox                  tightBoundingBox;

    /* The mesh which groups same material triangles together */
    RpMeshHeader            *mesh;

    /* The WorldSector object pipeline for this WorldSector */
    RxPipeline    *pipeline;

    /* Material list window base
     * (triangles in a given sector can "see"
     * the 256 materials from
     * MatList[matListWindowBase] -> MatList[matListWindowBase + 255])
     */
    RwUInt16                matListWindowBase;

    RwUInt16                numVertices;            /* Num vertices */
    RwUInt16                numTriangles;           /* Num triangles */
    RwUInt16                pad;
};

typedef RpWorldSector *(*RpWorldSectorCallBackRender) (RpWorldSector *
                                                       worldSector);

struct RpWorld {
    RwObject            object;

    RwUInt32            flags;

    RpWorldRenderOrder  renderOrder;

    /* Materials */
    RpMaterialList      matList;

    /* The world stored as a BSP tree */
    RpSector           *rootSector;

    /* The number of texture coordinate sets in each sector */
    RwInt32             numTexCoordSets;

    /* Render frame used when last rendered */
    RwInt32             numClumpsInWorld;
    RwLLLink           *currentClumpLink;

    /* All the clumps in the world */
    RwLinkList          clumpList;

    /* All of the lights in the world */
    RwLinkList          lightList;

    /* Directional lights in the world */
    RwLinkList          directionalLightList;

    /* The worlds origin offset */
    RwV3d               worldOrigin;

    /* Bounding box around the whole world */
    RwBBox              boundingBox;

    /* The callbacks functions */
    RpWorldSectorCallBackRender renderCallBack;

    RxPipeline         *pipeline;
};

struct rwResources {
    RwInt32             maxSize;
    RwInt32             currentSize;
    RwInt32             reusageSize;

    void               *memHeap;

    RwLinkList          entriesA;
    RwLinkList          entriesB;

    RwLinkList         *freeEntries;
    RwLinkList         *usedEntries;
};

struct rwResourcesGlobals {
    rwResources         res;
};

struct RtAnimInterpolator;

typedef void(* RtAnimKeyFrameApplyCallBack)(void *result, void *voidIFrame);
typedef void(* RtAnimKeyFrameBlendCallBack)(void *voidOut, void *voidIn1, void *voidIn2, float alpha);
typedef void(* RtAnimKeyFrameInterpolateCallBack)(void *voidOut, void *voidIn1, void *voidIn2, float time, void *customData);
typedef void(* RtAnimKeyFrameAddCallBack)(void *voidOut, void *voidIn1, void *voidIn2);

typedef RtAnimInterpolator*(* RtAnimCallBack)(RtAnimInterpolator *animInstance, void *data);

struct RtAnimAnimation {
	_pad(__pad0a,24); // 0-24
};

struct RtAnimInterpolator {
	RtAnimAnimation* pCurrentAnim; // 0-4
	//current RtAnimAnimation applied
	float fCurrentTime; // 4-8
	//current animation time
	void* pNextFrame; // 8-12
	//next animation keyframe to be played
	RtAnimCallBack pAnimCallBack; // 12-16
	//animation callback function pointer
	void* pAnimCallBackData; // 16-20
	//animation callback function user data
	float fAnimCallBackTime; // 20-24
	//trigger time for callback function
	RtAnimCallBack pAnimLoopCallBack; // 24-28
	//animation loop callback function pointer
	void* pAnimLoopCallBackData; // 28-32
	//animation loop callback function data
	int nCurrentInterpKeyFrameSize; // 32-36
	//size of interpolated keyframes in the current animation scheme
	int nCurrentAnimKeyFrameSize; // 36-40
	//size of animation keyframes in the current animation scheme
	int nNumNodes; // 40-44
	//number of nodes driven by the animation
	BOOL bIsSubInterpolator; // 44-48
	//internal use
	int nOffsetInParent; // 48-52
	//internal use
	RtAnimInterpolator* pParentAnimation; // 52-56
	//internal use
	RtAnimKeyFrameApplyCallBack pKeyFrameApplyCB; // 56-60
	//internal use
	RtAnimKeyFrameBlendCallBack pKeyFrameBlendCB; // 60-64
	//internal use
	RtAnimKeyFrameInterpolateCallBack pKeyFrameInterpolateCB; // 64-68
	//internal use
	RtAnimKeyFrameAddCallBack pKeyFrameAddCB; // 68-72
	//internal use
};

struct RpHAnimNodeInfo {
	int nNodeId; // 0-4
	//user defined ID for this node
	int nNodeIndex; // 4-8
	//array index of node 
	int nFlags; // 8-12
	//matrix push/pop flags
	RwFrame* pFrame; // 12-16
	//pointer to an attached RwFrame
};

struct RpHAnimHierarchy {
	int nFlags; // 0-4
	//flags for the hierarchy
	int nNumNodes; // 4-8
	//number of nodes in the hierarchy
	RwMatrix* pMatrixArray; // 8-12
	//pointer to node matrices
	void* pMatrixArrayUnaligned; // 12-16
	//pointer to memory used for node matrices from which the aligned pMatrixArray is allocated
	RpHAnimNodeInfo* pNodeInfo; // 16-20
	//array of node information (push/pop flags etc)
	RwFrame* pParentFrame; // 20-24
	//pointer to the root RwFrame of the hierarchy this RpHAnimHierarchy represents 
	RpHAnimHierarchy* pParentHierarchy; // 24-28
	//parent of this hierarchy
	int nRootParentOffset; // 28-32
	//root parent offset
	RtAnimInterpolator* pCurrentAnim; // 32-36
	//animation interpolator for this hierarchy
};

struct RpGeometryChunkInfo {
    RwInt32 nFormat; // 0-4
	// Compression flags and number of texture coord sets
    RwInt32 numTriangles; // 4-8
    RwInt32 numVertices; // 8-12
    RwInt32 numMorphTargets; // 12-16
};

struct RpMorphTargetChunkInfo {
	RwSphere stBoundingSphere; // 0-16
	//bounding sphere
	RwBool bHasVerts; // 16-20
	//vertices list
	RwBool bHasNormals; // 20-24
	//normals list
};

struct RpMaterialChunkInfo
{
    RwInt32             flags;       /* Material flags - unused currently - 
                                      * for future expansion */
    RwRGBA              color;       /* Color of material. */
    RwInt32             unused;      /* Not used */
    RwBool              textured;    /* Are we textured? */
    RwSurfaceProperties surfaceProps;/* Surface properties */
};

struct RwMemory
{
    RwUInt8     *start; /**< Starting address. */
    RwUInt32    length; /**< Length in bytes. */
};

typedef struct _RxObjSpace3DVertex RxObjSpace3DVertex;
struct _RxObjSpace3DVertex
{
        RwV3d          objVertex;              /* Object space vertex */
        RwV3d          objNormal;              /* Object space normal */
        unsigned int    color;
        float         u, v;                   /* Vertex tex coords */
};

/* The 3D immediate mode one is the same */
typedef RxObjSpace3DVertex RxObjSpace3DLitVertex;
typedef RxObjSpace3DLitVertex RwIm3DVertex;
typedef unsigned __int16 RwImVertexIndex;

#pragma pack(pop)