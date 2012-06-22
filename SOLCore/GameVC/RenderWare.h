
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
/*****************************************************************************/
/** RenderWare rendering types                                              **/
/*****************************************************************************/

// RenderWare definitions
#define RW_STRUCT_ALIGN           ((int)((~((unsigned int)0))>>1))
#define RW_TEXTURE_NAME_LENGTH    32
#define RW_MAX_TEXTURE_COORDS     8

#define RWFORCEENUMSIZEINT ((int)((~((unsigned int)0))>>1))

typedef struct RwV2d RwV2d;
typedef struct RwV3d RwV3d;
typedef struct RwPlane RwPlane;
typedef struct RwBBox RwBBox;
typedef struct RpGeometry RpGeometry;
typedef void   RpWorld;
typedef struct RpClump RpClump;
typedef struct RwRaster RwRaster;
typedef struct RpMaterialLighting RpMaterialLighting;
typedef struct RpMaterialList RpMaterialList;
typedef struct RpMaterial RpMaterial;
typedef struct RpTriangle RpTriangle;
typedef struct RwTextureCoordinates RwTextureCoordinates;
typedef struct RwColor      RwColor;
typedef struct RwColorFloat RwColorFloat;
typedef struct RwObjectFrame RwObjectFrame;
typedef struct RpAtomic RpAtomic;
typedef struct RwCamera RwCamera;
typedef struct RpLight RpLight;

typedef RwCamera *(*RwCameraPreCallback) (RwCamera * camera);
typedef RwCamera *(*RwCameraPostCallback) (RwCamera * camera);
typedef RpAtomic *(*RpAtomicCallback) (RpAtomic * atomic);
typedef RpClump  *(*RpClumpCallback) (RpClump * clump, void *data);

// RenderWare primitive types

struct RwColorFloat {
    float r, g, b, a;
};

struct RwRGBA {
    unsigned char r, g, b, a;
};

#define RWRGBALONG(r,g,b,a)                                             \
    ((__uint32_t) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

//An efficient CRGBA class :)
class CRGBA {
public:
	unsigned char r,g,b,a;

	CRGBA() : r(0), g(0), b(0), a(0){}
	CRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a){}
};

struct RwV2d {   
    float x,y;
};

struct RwV3d {   
    float x,y,z;
};

//typedef RwV3d CVector;
class CVector{
public:
    float x, y, z;
    CVector(){}
    CVector(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct RwRect {
	float x, y, w, h;
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
//typedef struct RwRect CRect;

struct RwPlane {
    RwV3d normal;
    float length;
};

struct RwBBox {
    RwV3d max;
    RwV3d min;
};

struct RwSphere {
    RwV3d position;
    float radius;
};

#pragma pack(push, 1)
struct RwMatrix
{
  RwV3d vLookRight;
  uint32_t dwFlags;
  RwV3d vLookAt;
  uint32_t dwPad01;
  RwV3d vLookUp;
  uint32_t dwPad02;
  RwV3d vPos;
  uint32_t dwPad03;
};
#pragma pack(pop)


// RenderWare enumerations
enum RsEventStatus
{
	rsEVENTERROR = 0,
	rsEVENTPROCESSED = 1,
	rsEVENTNOTPROCESSED = 2
};

/**
 * \ingroup rwrenderstate
 * RwRenderState represents the global state variables that control
 * rendering. These may be set and queried using the
 * \ref RwRenderStateSet and \ref RwRenderStateGet functions respectively.
 *
 * Refer to the \ref rwrenderstateoverview for an overview of this system.
 *
 * \note The texture render states (raster, address & filter modes) would
 * normally just be used when rendering in immediate mode and should be
 * specificied completely every time a texture is used. Retained mode
 * pipelines will frequently set theses states internally, usually based on
 * \ref RwTexture objects.
 */

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
typedef enum RwRenderState RwRenderState;

enum RwTextureAddressMode
{
    rwTEXTUREADDRESSNATEXTUREADDRESS = 0,
    rwTEXTUREADDRESSWRAP,      /**<UV wraps (tiles) */
    rwTEXTUREADDRESSMIRROR,    /**<Alternate UV is flipped */
    rwTEXTUREADDRESSCLAMP,     /**<UV is clamped to 0-1 */
    rwTEXTUREADDRESSBORDER,    /**<Border color takes effect outside of 0-1 */
    rwTEXTUREADDRESSMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureAddressMode RwTextureAddressMode;

/**
 * \ingroup immediatemodedatatypes
 * RwPrimitiveType
 *  This type represents the different types of indexed
 * line and indexed triangle primitives that are available when rendering 2D
 * and 3D immediate mode objects (see API functions \ref RwIm2DRenderIndexedPrimitive,
 * \ref RwIm2DRenderPrimitive, \ref RwIm3DRenderIndexedPrimitive and \ref RwIm3DRenderPrimitive).
 * Indices are into a vertex list and must be defined in a counter-clockwise order
 * (as seen from the camera) to be visible.*/

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
typedef enum RwPrimitiveType RwPrimitiveType;

enum RwCameraType
{
    RW_CAMERA_NULL = 0,
    RW_CAMERA_PERSPECTIVE = 1,
    RW_CAMERA_ORTHOGRAPHIC = 2,
    RW_CAMERA_LAST = RW_STRUCT_ALIGN
};
enum RpAtomicFlags
{
    ATOMIC_COLLISION = 1,
    ATOMIC_VISIBLE = 4,
    ATOMIC_LAST = RW_STRUCT_ALIGN
};

/**
 * \ingroup rwrenderstate
 * RwBlendFunction represents the options available when changing the
 * \ref RwRenderState setting for \ref rwRENDERSTATESRCBLEND and 
 * \ref rwRENDERSTATEDESTBLEND. The values are factors used to modulate
 * either the source or destination pixel color when blending to
 * the frame buffer. Note the some  combinations are not allowed on
 * certain platforms (see platform specific restrictions).
 *
 * In the following list, the factors applied to each color component are 
 * listed explicitly. A subscript s refers to a source value while a subscript 
 * d refers to a destination value. Note that blending in the alpha channel is 
 * only applicable when the frame buffer actually contains alpha, and that
 * the precise operation is platform specific. For instance, the
 * source alpha value might simply be written to the alpha channel with
 * no blending.
 */

enum RwBlendFunction
{
    rwBLENDNABLEND = 0,
    rwBLENDZERO,            /**<(0,    0,    0,    0   ) */
    rwBLENDONE,             /**<(1,    1,    1,    1   ) */
    rwBLENDSRCCOLOR,        /**<(Rs,   Gs,   Bs,   As  ) */
    rwBLENDINVSRCCOLOR,     /**<(1-Rs, 1-Gs, 1-Bs, 1-As) */
    rwBLENDSRCALPHA,        /**<(As,   As,   As,   As  ) */
    rwBLENDINVSRCALPHA,     /**<(1-As, 1-As, 1-As, 1-As) */
    rwBLENDDESTALPHA,       /**<(Ad,   Ad,   Ad,   Ad  ) */
    rwBLENDINVDESTALPHA,    /**<(1-Ad, 1-Ad, 1-Ad, 1-Ad) */
    rwBLENDDESTCOLOR,       /**<(Rd,   Gd,   Bd,   Ad  ) */
    rwBLENDINVDESTCOLOR,    /**<(1-Rd, 1-Gd, 1-Bd, 1-Ad) */
    rwBLENDSRCALPHASAT,     /**<(f,    f,    f,    1   )  f = min (As, 1-Ad) */
    rwBLENDFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwBlendFunction RwBlendFunction;
/**
 * \ingroup rwrenderstate
 * RwTextureFilterMode represents the texture filtering modes that may
 * be set using the \ref RwRenderState \ref rwRENDERSTATETEXTUREFILTER in
 * immediate mode, or \ref RwTextureSetFilterMode in retained mode.
 */
enum RwTextureFilterMode
{
    rwFILTERNAFILTERMODE = 0,
    rwFILTERNEAREST,                /**<Point sampled */
    rwFILTERLINEAR,                 /**<Bilinear */
    rwFILTERMIPNEAREST,             /**<Point sampled per pixel mip map */
    rwFILTERMIPLINEAR,              /**<Bilinear per pixel mipmap */
    rwFILTERLINEARMIPNEAREST,       /**<MipMap interp point sampled */
    rwFILTERLINEARMIPLINEAR,        /**<Trilinear */
    rwTEXTUREFILTERMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureFilterMode RwTextureFilterMode;

/**
 * \ingroup rwraster
 *  RwRasterType 
 *  This type represents the options available for creating a new 
 * raster (se API function \ref RwRasterCreate)*/
enum RwRasterType
{
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
typedef enum RwRasterType RwRasterType;

/**
 * \ingroup rwraster
 * \ref RwRasterFormat is a set of values and flags which may be combined to
 * specify a raster format. The format chosen for a particular raster depends
 * on the hardware device and the raster type specified at creation time
 * (see API function \ref RwRasterCreate). The format may be retrieved using
 * API function \ref RwRasterGetFormat.
 *
 * The raster format is a packed set of bits which contains the following
 * four pieces of information (these may be combined with bitwise OR):
 *
 * <ol>
 * <li> The pixel color format corresponding to one of the following values:
 *      <ul>
 *      <li> rwRASTERFORMAT1555
 *      <li> rwRASTERFORMAT565
 *      <li> rwRASTERFORMAT4444
 *      <li> rwRASTERFORMATLUM8
 *      <li> rwRASTERFORMAT8888
 *      <li> rwRASTERFORMAT888
 *      <li> rwRASTERFORMAT16
 *      <li> rwRASTERFORMAT24
 *      <li> rwRASTERFORMAT32
 *      <li> rwRASTERFORMAT555
 *      </ul>
 *      This value may be masked out of the raster format using
 *      rwRASTERFORMATPIXELFORMATMASK.
 * <li> The palette depth if the raster is palettized:
 *      <ul> 
 *      <li> rwRASTERFORMATPAL4
 *      <li> rwRASTERFORMATPAL8
 *      </ul>
 *      In these cases, the color format refers to that of the palette.
 * <li> Flag rwRASTERFORMATMIPMAP. Set if the raster contains mipmap levels.
 * <li> Flag rwRASTERFORMATAUTOMIPMAP. Set if the mipmap levels were generated
 *      automatically by RenderWare.
 * </ol>
 */
enum RwRasterFormat
{
    rwRASTERFORMATDEFAULT = 0x0000, /* Whatever the hardware likes best */

    rwRASTERFORMAT1555 = 0x0100,    /**<16 bits - 1 bit alpha, 5 bits red, green and blue */
    rwRASTERFORMAT565 = 0x0200,     /**<16 bits - 5 bits red and blue, 6 bits green */
    rwRASTERFORMAT4444 = 0x0300,    /**<16 bits - 4 bits per component */
    rwRASTERFORMATLUM8 = 0x0400,    /**<Gray scale */
    rwRASTERFORMAT8888 = 0x0500,    /**<32 bits - 8 bits per component */
    rwRASTERFORMAT888 = 0x0600,     /**<24 bits - 8 bits per component */
    rwRASTERFORMAT16 = 0x0700,      /**<16 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT24 = 0x0800,      /**<24 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT32 = 0x0900,      /**<32 bits - undefined: useful for things like Z buffers */
    rwRASTERFORMAT555 = 0x0a00,     /**<16 bits - 5 bits red, green and blue */

    rwRASTERFORMATAUTOMIPMAP = 0x1000, /**<RenderWare generated the mip levels */

    rwRASTERFORMATPAL8 = 0x2000,    /**<8 bit palettised */
    rwRASTERFORMATPAL4 = 0x4000,    /**<4 bit palettised */

    rwRASTERFORMATMIPMAP = 0x8000,  /**<Mip mapping on */

    rwRASTERFORMATPIXELFORMATMASK = 0x0f00, /**<The pixel color format 
                                             *  (excluding palettised bits) */
    rwRASTERFORMATMASK = 0xff00     /**<The whole format */ ,
    rwRASTERFORMATFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFormat RwRasterFormat;

/**
 * \ingroup rwraster
 * \ref RwRasterLockMode represents the options available for locking 
 * a raster so that it may be modified (see API function \ref RwRasterLock). An 
 * application may wish to write to the raster, read from the raster or
 * simultaneously write and read a raster (rwRASTERLOCKWRITE | rwRASTERLOCKREAD).
 */
enum RwRasterLockMode
{
    rwRASTERLOCKWRITE = 0x01,   /**<Lock for writing */
    rwRASTERLOCKREAD = 0x02,    /**<Lock for reading */
    rwRASTERLOCKNOFETCH = 0x04, /**<When used in combination with
                                 *  rwRASTERLOCKWRITE, asks the driver not to
                                 *  fetch the pixel data. This is only useful
                                 *  if it is known that ALL the raster data is
                                 *  going to be overwritten before the raster
                                 *  is unlocked, i.e. from an 
                                 *  \ref RwRasterSetFromImage call. This flag
                                 *  is not supported by all drivers. */
    rwRASTERLOCKRAW = 0x08,    /**<When used in combination with
                                   rwRASTERLOCKWRITE or rwRASTERLOCKREAD
                                   allows access to the raw platform specific
                                   pixel format */
    rwRASTERLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RwTransformOrder
{
    TRANSFORM_INITIAL = 0,
    TRANSFORM_BEFORE = 1,
    TRANSFORM_AFTER = 2,
    TRANSFORM_LAST = RW_STRUCT_ALIGN
};
enum RpLightType
{
    LIGHT_TYPE_NULL = 0,
    
    LIGHT_TYPE_DIRECTIONAL = 1,
    LIGHT_TYPE_AMBIENT = 2,
    
    LIGHT_TYPE_POINT = 0x80,
    LIGHT_TYPE_SPOT_1 = 0x81,
    LIGHT_TYPE_SPOT_2 = 0x82,

    LIGHT_TYPE_LAST = RW_STRUCT_ALIGN
};
enum RpLightFlags
{
    LIGHT_ILLUMINATES_ATOMICS = 1,
    LIGHT_ILLUMINATES_GEOMETRY = 2,
    LIGHT_FLAGS_LAST = RW_STRUCT_ALIGN
};

// RenderWare/plugin base types
struct RwObject
{
    unsigned char type;
    unsigned char subtype;
    unsigned char flags;
    unsigned char privateFlags;
    void *parent;                // should be RwFrame with RpClump
};
struct RwVertex
{
    RwV3d        position;
    unsigned int fogplane;
    unsigned int color;
    float        u,v;
};
struct RwListEntry
{
    RwListEntry *next,*prev;
};
struct RwList
{
    RwListEntry root;
};
struct RwFrame
{
    RwObject         object;            // 0
    void             *pad1,*pad2;       // 8
    RwMatrix         modelling;         // 16
    RwMatrix         ltm;               // 32
    RwList           objects;           // 48
    struct RwFrame   *child;            // 56
    struct RwFrame   *next;             // 60
    struct RwFrame   *root;             // 64

    // Rockstar Frame extension (0x253F2FE) (24 bytes)
    unsigned char    pluginData[8];     // padding
    char             szName[16];        // name (as stored in the frame extension)
};
struct RwTexDictionary
{
    RwObject     object;
    RwList       textures;
    RwListEntry  globalTXDs;
};

struct RwImage
{
        int             flags;

        int             width;  /* Device may have different ideas */
        int             height; /* internally !! */

        int             depth;  /* Of referenced image */
        int             stride;

        int            *cpPixels;
        RwRGBA         *palette;
};

struct RwTexture
{
    RwRaster           *raster; /** pointer to RwRaster with data */
    RwTexDictionary    *dict;   /* Dictionary this texture is in */
    RwListEntry         lInDictionary; /* List of textures in this dictionary */

    char                name[RW_TEXTURE_NAME_LENGTH];  /* Name of the texture */
    char                mask[RW_TEXTURE_NAME_LENGTH];  /* Name of the textures mask */

    /* 31 [xxxxxxxx xxxxxxxx vvvvuuuu ffffffff] 0 */
    unsigned int        filterAddressing; /* Filtering & addressing mode flags */

    int                 refCount; /* Reference count, surprisingly enough */
};

struct RwTextureCoordinates
{
    float u,v;
};

struct RwRaster
{
    RwRaster        *parent;               // Top level raster if a sub raster
    unsigned char   *cpPixels;             // Pixel pointer when locked
    unsigned char   *palette;              // Raster palette
    int             width, height, depth;  // Dimensions of raster
    int             stride;                // pitch/Lines bytes of raster
    short           nOffsetX, nOffsetY;    // Sub raster Offset
    unsigned char   cType;                 // Type of raster
    unsigned char   cFlags;                // Raster flags
    unsigned char   privateFlags;          // Raster Private flags
    unsigned char   cFormat;               // Raster format

    unsigned char   *origPixels;
    int             origWidth, origHeight, origDepth;
    void*           renderResource;
};

struct RwObjectFrame
{
    RwObject     object;
    RwListEntry  lFrame;
    void         *callback;
};

struct RwCameraFrustum
{
    RwPlane       plane;
    unsigned char x,y,z;
    unsigned char unknown1;
};

struct RwCamera
{
    RwObjectFrame        object;
    RwCameraType         type;
    RwCameraPreCallback  preCallback;
    RwCameraPostCallback postCallback;
    RwMatrix             matrix;
    RwRaster             *bufferColor;
    RwRaster             *bufferDepth;
    RwV2d                screen;
    RwV2d                screenInverse;
    RwV2d                screenOffset;
    float                nearplane;
    float                farplane;
    float                fog;
    float                unknown1;
    float                unknown2;
    RwCameraFrustum      frustum4D[6];
    RwBBox               viewBBox;
    RwV3d                frustum3D[8];
};

struct RpInterpolation
{
    unsigned int     unknown1;
    unsigned int     unknown2;
    float            unknown3;
    float            unknown4;
    float            unknown5;
};

struct RpAtomic
{
    RwObjectFrame    object;
    void             *info;
    RpGeometry       *geometry;
    RwSphere         bsphereLocal;
    RwSphere         bsphereWorld;
    RpClump          *clump;
    RwListEntry      globalClumps;
    RpAtomicCallback renderCallback;
    RpInterpolation  interpolation;
    unsigned short   frame;
    unsigned short   unknown7;
    RwList           sectors;
    void             *render;
};

struct RpAtomicContainer {
    RpAtomic    *atomic;
    char        szName[17];
};

struct RpLight
{
    RwObjectFrame   object;
    float           radius;
    RwColorFloat    color;
    float           unknown1;
    RwList          sectors;
    RwListEntry     globalLights;
    unsigned short  frame;
    unsigned short  unknown2;
};
struct RpClump
{   // RenderWare (plugin) Clump (used by GTA)
    RwObject        object;
    RwList          atomics;
    RwList          lights;
    RwList          cameras;
    RwListEntry     globalClumps;
    RpClumpCallback callback;
};
struct RpMaterialLighting
{
    float ambient, specular, diffuse;
};
struct RpMaterial
{
    RwTexture*          texture;
    RwRGBA              color;
    void                *render;
    RpMaterialLighting  lighting;
    short               refs;
    short               id;
};
struct RpMaterials
{
    RpMaterial **materials;
    int        entries;
    int        unknown;
};
struct RpTriangle
{
    unsigned short v1, v2, v3;
    unsigned short materialId;
};
struct RpGeometry
{
    RwObject             object;
    unsigned int         flags;
    unsigned short       unknown1;
    short                refs;

    int                  triangles_size;
    int                  vertices_size;
    int                  unknown_size;
    int                  texcoords_size;

    RpMaterials          materials;
    RpTriangle           *triangles;
    RwColor              *colors;
    RwTextureCoordinates *texcoords[RW_MAX_TEXTURE_COORDS];
    void                 *unknown2;
    void                 *info;
    void                 *unknown3;
};

/*****************************************************************************/
/** RenderWare I/O                                                          **/
/*****************************************************************************/

// RenderWare type definitions
typedef int          (* RwIOCallbackClose) (void *data);
typedef unsigned int (* RwIOCallbackRead)  (void *data, void *buffer, unsigned int length);
typedef int          (* RwIOCallbackWrite) (void *data, const void *buffer, unsigned int length);
typedef int          (* RwIOCallbackOther) (void *data, unsigned int offset);

// RenderWare enumerations
enum RwStreamType
{
    STREAM_TYPE_NULL = 0,
    STREAM_TYPE_FILE = 1,
    STREAM_TYPE_FILENAME = 2,
    STREAM_TYPE_BUFFER = 3,
    STREAM_TYPE_CALLBACK = 4,
    STREAM_TYPE_LAST = RW_STRUCT_ALIGN
};
enum RwStreamMode
{
    STREAM_MODE_NULL = 0,
    STREAM_MODE_READ = 1,
    STREAM_MODE_WRITE = 2,
    STREAM_MODE_APPEND = 3,
    STREAM_MODE_LAST = RW_STRUCT_ALIGN
};

// RenderWare base types
struct RwBuffer
{
    void            *ptr;
    unsigned int    size;
};
union RwStreamTypeData
{
    struct {
        unsigned int      position;
        unsigned int      size;
        void              *ptr_file;
    };
    struct {
        void              *file;
    };
    struct {
        RwIOCallbackClose callbackClose;
        RwIOCallbackRead  callbackRead;
        RwIOCallbackWrite callbackWrite;
        RwIOCallbackOther callbackOther;
        void              *ptr_callback;
    };
};

struct RwStream
{
    RwStreamType        type;
    RwStreamMode        mode;
    int                 pos;
    RwStreamTypeData    data;
    int                 id;
};

struct RwError
{
    int err1,err2;
};

struct RwD3D8Vertex
{
    float      x;              /**< Screen X */
    float      y;              /**< Screen Y */
    float      z;              /**< Screen Z */
    float      rhw;            /**< Reciprocal of homogeneous W */

    unsigned int    emissiveColor;  /**< Vertex color */

    float      u;              /**< Texture coordinate U */
    float      v;              /**< Texture coordinate V */
};


/**
 * \ingroup rwim2dvertex
 * \ref RwIm2DVertex
 * Typedef for a RenderWare Graphics Immediate Mode 2D Vertex
 */
typedef RwD3D8Vertex    RwIm2DVertex;

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
extern RwRasterCreate_t RwRasterCreate;
extern RwRasterDestroy_t RwRasterDestroy;
extern RwTextureRead_t RwTextureRead;
extern RwTextureDestroy_t RwTextureDestroy;
extern RwTextureCreate_t RwTextureCreate;
extern RwTextureRasterGenerateMipmaps_t RwTextureRasterGenerateMipMaps;
extern RwD3D8SetRenderState_t RwD3D8SetRenderState;
extern RwD3D8SetTextureStageState_t RwD3D8SetTextureStageState;
extern RwV3dTransformPoints_t RwV3dTransformPoints;

#endif
