#ifndef RWDEVICE_H
#define RWDEVICE_H

#include "batkreg.h"
#include "baimmedi.h"

#define rwSTANDARDNASTANDARD 0
#define rwSTANDARDCAMERABEGINUPDATE 1
#define rwSTANDARDRGBTOPIXEL 2
#define rwSTANDARDPIXELTORGB 3
#define rwSTANDARDRASTERCREATE 4
#define rwSTANDARDRASTERDESTROY 5
#define rwSTANDARDIMAGEGETRASTER 6
#define rwSTANDARDRASTERSETIMAGE 7
#define rwSTANDARDTEXTURESETRASTER 8
#define rwSTANDARDIMAGEFINDRASTERFORMAT 9
#define rwSTANDARDCAMERAENDUPDATE 10
#define rwSTANDARDSETRASTERCONTEXT 11
#define rwSTANDARDRASTERSUBRASTER 12
#define rwSTANDARDRASTERCLEARRECT 13
#define rwSTANDARDRASTERCLEAR 14
#define rwSTANDARDRASTERLOCK 15
#define rwSTANDARDRASTERUNLOCK 16
#define rwSTANDARDRASTERRENDER 17
#define rwSTANDARDRASTERRENDERSCALED 18
#define rwSTANDARDRASTERRENDERFAST 19
#define rwSTANDARDRASTERSHOWRASTER 20
#define rwSTANDARDCAMERACLEAR 21
#define rwSTANDARDHINTRENDERF2B 22
#define rwSTANDARDRASTERLOCKPALETTE 23
#define rwSTANDARDRASTERUNLOCKPALETTE 24
#define rwSTANDARDNATIVETEXTUREGETSIZE 25
#define rwSTANDARDNATIVETEXTUREREAD 26
#define rwSTANDARDNATIVETEXTUREWRITE 27
#define rwSTANDARDRASTERGETMIPLEVELS 28
#define rwSTANDARDNUMOFSTANDARD 29

typedef RwBool (*RwStandardFunc)(void *pOut, void *pInOut, RwInt32 nI);

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

typedef struct RwDevice RwDevice;
struct RwDevice
{
    RwReal gammaCorrection;
    RwSystemFunc fpSystem;
    RwReal zBufferNear;
    RwReal zBufferFar;
    RwRenderStateSetFunction fpRenderStateSet;
    RwRenderStateGetFunction fpRenderStateGet;
    RwIm2DRenderLineFunction fpIm2DRenderLine;
    RwIm2DRenderTriangleFunction fpIm2DRenderTriangle;
    RwIm2DRenderPrimitiveFunction fpIm2DRenderPrimitive;
    RwIm2DRenderIndexedPrimitiveFunction fpIm2DRenderIndexedPrimitive;
    RwIm3DRenderLineFunction fpIm3DRenderLine;
    RwIm3DRenderTriangleFunction fpIm3DRenderTriangle;
    RwIm3DRenderPrimitiveFunction fpIm3DRenderPrimitive;
    RwIm3DRenderIndexedPrimitiveFunction fpIm3DRenderIndexedPrimitive;
};

typedef struct RwMetrics RwMetrics;
struct RwMetrics
{
    RwUInt32 numTriangles;
    RwUInt32 numProcTriangles;
    RwUInt32 numVertices;
    RwUInt32 numTextureUploads;
    RwUInt32 sizeTextureUploads;
    RwUInt32 numResourceAllocs;
    void *devSpecificMetrics;
};

enum RwVideoModeFlag
{
    rwVIDEOMODEEXCLUSIVE = 0x0001,
    rwVIDEOMODEINTERLACE = 0x0002,
    rwVIDEOMODEFFINTERLACE = 0x0004,
    rwVIDEOMODE_PS2_FSAASHRINKBLIT = 0x0100,
    rwVIDEOMODE_PS2_FSAAREADCIRCUIT = 0x0200,
    rwVIDEOMODE_XBOX_WIDESCREEN = 0x0100,
    rwVIDEOMODE_XBOX_PROGRESSIVE = 0x0200,
    rwVIDEOMODE_XBOX_FIELD = 0x0400,
    rwVIDEOMODE_XBOX_10X11PIXELASPECT = 0x0800,
    rwVIDEOMODEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwVideoModeFlag RwVideoModeFlag;

typedef struct RwVideoMode RwVideoMode;
struct RwVideoMode
{
    RwInt32 width;
    RwInt32 height;
    RwInt32 depth;
    RwVideoModeFlag flags;
    RwInt32 refRate;
    RwInt32 format;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern RwVideoMode *RwEngineGetVideoModeInfo(RwVideoMode *modeinfo, RwInt32 modeIndex);
extern RwInt32 RwEngineGetCurrentVideoMode(void);

#ifdef __cplusplus
}
#endif

#endif
