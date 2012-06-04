#include "RenderWare.h"

#define FUNC_RwRenderStateSet 0x00649BA0
#define FUNC_RwRenderStateGet 0x00649BF0

#define FUNC_RwIm2DRenderPrimitive 0x649C10
#define FUNC_SetMaskVertices 0x577D10

#define FUNC_RwTextureCreate 0x0064DE60
#define FUNC_RwTextureRead 0x64E110
#define FUNC_RwTextureDestroy 0x64DEC0
#define FUNC_RwTextureRasterGenerateMipmaps 0x0064E340

#define FUNC_RwRasterLock  0x00655530
#define FUNC_RwRasterUnlock 0x00655250
#define FUNC_RwRasterCreate 0x00655490
#define FUNC_RwRasterDestroy 0x006552E0

#define FUNC_RwD3D8SetRenderState 0x006582A0
#define FUNC_RwD3D8SetTextureStageState 0x00658310

/*****************************************************************************/
/** Renderware functions mapping						                    **/
/*****************************************************************************/

RwRenderStateSet_t				    RwRenderStateSet =				(RwRenderStateSet_t)			    FUNC_RwRenderStateSet;
RwRenderStateGet_t                  RwRenderStateGet =              (RwRenderStateGet_t)                FUNC_RwRenderStateGet;

RwIm2DRenderPrimitive_t			    RwIm2DRenderPrimitive =			(RwIm2DRenderPrimitive_t)		    FUNC_RwIm2DRenderPrimitive;
RwIm3DTransform_t                   RwIm3DTransform =               (RwIm3DTransform_t)                 0x0065AE90;
RwIm3DRenderIndexedPrimitive_t      RwIm3DRenderIndexedPrimitive =  (RwIm3DRenderIndexedPrimitive_t)    0x0065AF90;

RwTextureCreate_t                   RwTextureCreate =               (RwTextureCreate_t)                 FUNC_RwTextureCreate;
RwTextureRead_t					    RwTextureRead =					(RwTextureRead_t)				    FUNC_RwTextureRead;
RwTextureDestroy_t                  RwTextureDestroy =              (RwTextureDestroy_t)                FUNC_RwTextureDestroy;
RwTextureRasterGenerateMipmaps_t    RwTextureRasterGenerateMipMaps =(RwTextureRasterGenerateMipmaps_t)  FUNC_RwTextureRasterGenerateMipmaps;

RwRasterLock_t                      RwRasterLock =                  (RwRasterLock_t)                    FUNC_RwRasterLock;
RwRasterUnlock_t                    RwRasterUnlock =                (RwRasterUnlock_t)                  FUNC_RwRasterUnlock;
RwRasterCreate_t                    RwRasterCreate =                (RwRasterCreate_t)                  FUNC_RwRasterCreate;
RwRasterDestroy_t                   RwRasterDestroy =               (RwRasterDestroy_t)                 FUNC_RwRasterDestroy;

RwD3D8SetRenderState_t			    RwD3D8SetRenderState =			(RwD3D8SetRenderState_t)		    FUNC_RwD3D8SetRenderState;
RwD3D8SetTextureStageState_t        RwD3D8SetTextureStageState =    (RwD3D8SetTextureStageState_t)      FUNC_RwD3D8SetTextureStageState;