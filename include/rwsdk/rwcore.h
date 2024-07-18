#ifndef RWCORE_H
#define RWCORE_H

#include <stddef.h>
#include <stdarg.h>

#define rwBIGENDIAN

typedef long RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;
typedef char RwChar;
typedef float RwReal;
typedef RwInt32 RwBool;

#define RwInt32MAXVAL 0x7FFFFFFF
#define RwInt32MINVAL 0x80000000
#define RwUInt32MAXVAL 0xFFFFFFFF
#define RwUInt32MINVAL 0x00000000
#define RwRealMAXVAL (RwReal)(3.40282347e+38)
#define RwRealMINVAL (RwReal)(1.17549435e-38)
#define RwInt16MAXVAL 0x7FFF
#define RwInt16MINVAL 0x8000
#define RwUInt16MAXVAL 0xFFFF
#define RwUInt16MINVAL 0x0000

#define RWALIGN(type, x) type
#define rwMATRIXALIGNMENT sizeof(RwUInt32)
#define rwFRAMEALIGNMENT sizeof(RwUInt32)
#define rwV4DALIGNMENT sizeof(RwUInt32)

#define RWFORCEENUMSIZEINT ((RwInt32)((~((RwUInt32)0))>>1))

#ifndef MACRO_START
#define MACRO_START do
#endif

#ifndef MACRO_STOP
#define MACRO_STOP while(0)
#endif

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE !FALSE

typedef struct RwV2d RwV2d;
struct RwV2d
{
    RwReal x;
    RwReal y;
};

typedef struct RwV3d RwV3d;
struct RwV3d
{
    RwReal x;
    RwReal y;
    RwReal z;
};

typedef struct RwRect RwRect;
struct RwRect
{
    RwInt32 x;
    RwInt32 y;
    RwInt32 w;
    RwInt32 h;
};

typedef struct RwSphere RwSphere;
struct RwSphere
{
    RwV3d center;
    RwReal radius;
};

#define rwMAXTEXTURECOORDS 8

enum RwTextureCoordinateIndex
{
    rwNARWTEXTURECOORDINATEINDEX = 0,
    rwTEXTURECOORDINATEINDEX0,
    rwTEXTURECOORDINATEINDEX1,
    rwTEXTURECOORDINATEINDEX2,
    rwTEXTURECOORDINATEINDEX3,
    rwTEXTURECOORDINATEINDEX4,
    rwTEXTURECOORDINATEINDEX5,
    rwTEXTURECOORDINATEINDEX6,
    rwTEXTURECOORDINATEINDEX7,
    rwTEXTURECOORDINATEINDEXFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureCoordinateIndex RwTextureCoordinateIndex;

typedef struct RwTexCoords RwTexCoords;
struct RwTexCoords
{
    RwReal u;
    RwReal v;
};

typedef struct RwLLLink RwLLLink;
struct RwLLLink
{
    RwLLLink* next;
    RwLLLink* prev;
};

typedef struct RwLinkList RwLinkList;
struct RwLinkList
{
    RwLLLink link;
};

typedef struct RwSurfaceProperties RwSurfaceProperties;
struct RwSurfaceProperties
{
    RwReal ambient;
    RwReal specular;
    RwReal diffuse;
};

typedef struct RwPlane RwPlane;
struct RwPlane
{
    RwV3d normal;
    RwReal distance;
};

typedef struct RwObject RwObject;
struct RwObject
{
    RwUInt8 type;
    RwUInt8 subType;
    RwUInt8 flags;
    RwUInt8 privateFlags;
    void* parent;
};

#define rwObjectGetParent(object) (((const RwObject *)(object))->parent)

#ifndef RWDEBUG
#define RwMalloc(_s, _h, line) ((RWSRCGLOBAL(memoryFuncs).rwmalloc)((_s), (_h)))
#else
#define RwMalloc(_s, _h, line)                              \
    (_rwMemoryLastAllocFile = __FILE__,                     \
     _rwMemoryLastAllocLine = (line),                       \
     ((RWSRCGLOBAL(memoryFuncs).rwmalloc)((_s), (_h))))
#endif

#define RwFree(_p) ((RWSRCGLOBAL(memoryFuncs).rwfree)((_p)))

#ifndef RWDEBUG
#define RwCalloc(_n, _s, _h, line) ((RWSRCGLOBAL(memoryFuncs).rwcalloc)((_n), (_s), (_h)))
#else
#define RwCalloc(_n, _s, _h, line)                          \
    (_rwMemoryLastAllocFile = __FILE__,                     \
     _rwMemoryLastAllocLine = (line),                       \
     ((RWSRCGLOBAL(memoryFuncs).rwcalloc)((_n), (_s), (_h))))
#endif

#ifndef RWDEBUG
#define RwRealloc(_p, _s, _h, line) ((RWSRCGLOBAL(memoryFuncs).rwrealloc)((_p),(_s), (_h)))
#else
#define RwRealloc(_p, _s, _h, line)                         \
    (_rwMemoryLastAllocFile = __FILE__,                     \
     _rwMemoryLastAllocLine = (line),                       \
     ((RWSRCGLOBAL(memoryFuncs).rwrealloc)((_p),(_s), (_h))))
#endif

enum RwMemoryHintFlag
{
    rwMEMHINTFLAG_RESIZABLE = 0x01000000,
    rwMEMHINTFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwMemoryHintFlag RwMemoryHintFlag;

#define rwMEMHINTFLAG_MASK      (0xFF000000)

enum RwMemoryHintDuration
{
    rwMEMHINTDUR_NADURATION = 0x00000000,
    rwMEMHINTDUR_FUNCTION = 0x00010000,
    rwMEMHINTDUR_FRAME = 0x00020000,
    rwMEMHINTDUR_EVENT = 0x00030000,
    rwMEMHINTDUR_GLOBAL = 0x00040000,
    rwMEMHINTDUR_MASK = 0x00FF0000,
    rwMEMHINTDURFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwMemoryHintDuration RwMemoryHintDuration;

struct RwMemoryFunctions
{
    void*(*rwmalloc)(size_t size, RwUInt32 hint);
    void(*rwfree)(void* mem);
    void*(*rwrealloc)(void* mem, size_t newSize, RwUInt32 hint);
    void*(*rwcalloc)(size_t numObj, size_t sizeObj, RwUInt32 hint);
};
typedef struct RwMemoryFunctions RwMemoryFunctions;

typedef struct RwFreeList RwFreeList;
struct RwFreeList
{
    RwUInt32 entrySize;
#ifdef RWDEBUG
    RwUInt32 nonAlignedEntrySize;
#endif
    RwUInt32 entriesPerBlock;
    RwUInt32 heapSize;
    RwUInt32 alignment;
    RwLinkList blockList;
    RwUInt32 flags;
    RwLLLink link;
#ifdef RWDEBUG
    const RwChar* fileCreate;
    RwUInt32 lineCreate;
#endif
};

typedef void*(*RwMemoryAllocFn)(RwFreeList* fl, RwUInt32 hint);
typedef RwFreeList*(*RwMemoryFreeFn)(RwFreeList* fl, void* pData);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RWDEBUG
extern const RwChar* _rwMemoryLastAllocFile;
extern RwUInt32 _rwMemoryLastAllocLine;
#endif

#ifdef __cplusplus
}
#endif

typedef int(*vecSprintfFunc)(RwChar* buffer, const RwChar* format, ...);
typedef int(*vecVsprintfFunc)(RwChar* buffer, const RwChar* format, va_list argptr); 
typedef RwChar*(*vecStrcpyFunc)(RwChar* dest, const RwChar* srce);
typedef RwChar*(*vecStrncpyFunc)(RwChar* dest, const RwChar* srce, size_t size);
typedef RwChar*(*vecStrcatFunc)(RwChar* dest, const RwChar* srce);
typedef RwChar*(*vecStrncatFunc)(RwChar* dest, const RwChar* srce, size_t size);
typedef RwChar*(*vecStrrchrFunc)(const RwChar* string, int findThis);
typedef RwChar*(*vecStrchrFunc)(const RwChar* string, int findThis);
typedef RwChar*(*vecStrstrFunc)(const RwChar* string, const RwChar* findThis);
typedef int(*vecStrcmpFunc)(const RwChar* string1, const RwChar* string2);
typedef int(*vecStrncmpFunc)(const RwChar* string1, const RwChar* string2, size_t max_size);
typedef int(*vecStricmpFunc)(const RwChar* string1, const RwChar* string2);
typedef size_t(*vecStrlenFunc)(const RwChar* string);
typedef RwChar*(*vecStruprFunc)(RwChar* string);
typedef RwChar*(*vecStrlwrFunc)(RwChar* string);
typedef RwChar*(*vecStrtokFunc)(RwChar* string, const RwChar* delimit);
typedef int(*vecSscanfFunc)(const RwChar* buffer, const RwChar* format, ...);

typedef struct RwStringFunctions RwStringFunctions;
struct RwStringFunctions
{
    vecSprintfFunc vecSprintf;
    vecVsprintfFunc vecVsprintf;
    vecStrcpyFunc vecStrcpy;
    vecStrncpyFunc vecStrncpy;
    vecStrcatFunc vecStrcat;
    vecStrncatFunc vecStrncat;
    vecStrrchrFunc vecStrrchr;
    vecStrchrFunc vecStrchr;
    vecStrstrFunc vecStrstr;
    vecStrcmpFunc vecStrcmp;
    vecStrncmpFunc vecStrncmp;
    vecStricmpFunc vecStricmp;
    vecStrlenFunc vecStrlen;
    vecStruprFunc vecStrupr;
    vecStrlwrFunc vecStrlwr;
    vecStrtokFunc vecStrtok;
    vecSscanfFunc vecSscanf;
};

enum RwOpCombineType
{
    rwCOMBINEREPLACE = 0,
    rwCOMBINEPRECONCAT,
    rwCOMBINEPOSTCONCAT,
    rwOPCOMBINETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwOpCombineType RwOpCombineType;

struct RwMatrixTag
{
    RwV3d right;
    RwUInt32 flags;
    RwV3d up;
    RwUInt32 pad1;
    RwV3d at;
    RwUInt32 pad2;
    RwV3d pos;
    RwUInt32 pad3;
};
typedef struct RwMatrixTag RWALIGN(RwMatrix, rwMATRIXALIGNMENT);

typedef void*(*RwPluginObjectConstructor)(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void*(*RwPluginObjectCopy)(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void*(*RwPluginObjectDestructor)(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject);

typedef struct rwGameCube2DVertex rwGameCube2DVertex;
struct rwGameCube2DVertex
{
    RwReal x;
    RwReal y;
    RwReal z;
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
    RwReal u;
    RwReal v;
};
typedef rwGameCube2DVertex RwIm2DVertex;

typedef RwUInt16 RxVertexIndex;
typedef RxVertexIndex RwImVertexIndex;

#ifdef __cplusplus
extern "C" {
#endif

extern RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in);

#ifdef __cplusplus
}
#endif

#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)
#define RwIm2DVertexSetU(vert, texU, recipz) ((vert)->u = (texU))
#define RwIm2DVertexSetV(vert, texV, recipz) ((vert)->v = (texV))
#define RwIm2DVertexGetU(vert) ((vert)->u)
#define RwIm2DVertexGetV(vert) ((vert)->v)

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)           \
MACRO_START                                                             \
{                                                                       \
    ((vert)->r = (red));                                                \
    ((vert)->g = (green));                                              \
    ((vert)->b = (blue));                                               \
    ((vert)->a = (alpha));                                              \
}                                                                       \
MACRO_STOP

enum RwRenderState
{
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER,
    rwRENDERSTATETEXTUREADDRESS,
    rwRENDERSTATETEXTUREADDRESSU,
    rwRENDERSTATETEXTUREADDRESSV,
    rwRENDERSTATETEXTUREPERSPECTIVE,
    rwRENDERSTATEZTESTENABLE,
    rwRENDERSTATESHADEMODE,
    rwRENDERSTATEZWRITEENABLE,
    rwRENDERSTATETEXTUREFILTER,
    rwRENDERSTATESRCBLEND,
    rwRENDERSTATEDESTBLEND,
    rwRENDERSTATEVERTEXALPHAENABLE,
    rwRENDERSTATEBORDERCOLOR,
    rwRENDERSTATEFOGENABLE,
    rwRENDERSTATEFOGCOLOR,
    rwRENDERSTATEFOGTYPE,
    rwRENDERSTATEFOGDENSITY,
    rwRENDERSTATECULLMODE = 20,
    rwRENDERSTATESTENCILENABLE,
    rwRENDERSTATESTENCILFAIL,
    rwRENDERSTATESTENCILZFAIL,
    rwRENDERSTATESTENCILPASS,
    rwRENDERSTATESTENCILFUNCTION,
    rwRENDERSTATESTENCILFUNCTIONREF,
    rwRENDERSTATESTENCILFUNCTIONMASK,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
    rwRENDERSTATEALPHATESTFUNCTION,
    rwRENDERSTATEALPHATESTFUNCTIONREF,
    rwRENDERSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRenderState RwRenderState;

enum RwFogType
{
    rwFOGTYPENAFOGTYPE = 0,
    rwFOGTYPELINEAR,
    rwFOGTYPEEXPONENTIAL,
    rwFOGTYPEEXPONENTIAL2,
    rwFOGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwFogType RwFogType;

enum RwPrimitiveType
{
    rwPRIMTYPENAPRIMTYPE = 0,
    rwPRIMTYPELINELIST = 1,
    rwPRIMTYPEPOLYLINE = 2,
    rwPRIMTYPETRILIST = 3,
    rwPRIMTYPETRISTRIP = 4,
    rwPRIMTYPETRIFAN = 5,
    rwPRIMTYPEPOINTLIST = 6,
    rwPRIMITIVETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwPrimitiveType RwPrimitiveType;

#define RwIm2DGetNearScreenZMacro() (RWSRCGLOBAL(dOpenDevice).zBufferNear)
#define RwRenderStateGetMacro(_state, _value) (RWSRCGLOBAL(dOpenDevice).fpRenderStateGet(_state, _value))
#define RwRenderStateSetMacro(_state, _value) (RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(_state, _value))
#define RwIm2DRenderPrimitiveMacro(_primType, _vertices, _numVertices) (RWSRCGLOBAL(dOpenDevice).fpIm2DRenderPrimitive(_primType, _vertices, _numVertices))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RWDEBUG
#define RwIm2DGetNearScreenZ() RwIm2DGetNearScreenZMacro()
#define RwRenderStateGet(_state, _value) RwRenderStateGetMacro(_state, _value)
#define RwRenderStateSet(_state, _value) RwRenderStateSetMacro(_state, _value)
#define RwIm2DRenderPrimitive(_primType, _vertices, _numVertices) RwIm2DRenderPrimitiveMacro(_primType, _vertices, _numVertices)
#else
extern RwReal RwIm2DGetNearScreenZ(void);
extern RwBool RwRenderStateGet(RwRenderState state, void* value);
extern RwBool RwRenderStateSet(RwRenderState state, void* value);
extern RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);
#endif

#ifdef __cplusplus
}
#endif

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

typedef RwBool(*RwStandardFunc)(void* pOut,void* pInOut, RwInt32 nI);

typedef RwBool(*RwSystemFunc)(RwInt32 nOption, void* pOut, void* pInOut, RwInt32 nIn);
typedef RwBool(*RwRenderStateSetFunction)(RwRenderState nState, void* pParam);
typedef RwBool(*RwRenderStateGetFunction)(RwRenderState nState, void* pParam);
typedef RwBool(*RwIm2DRenderLineFunction)(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2);
typedef RwBool(*RwIm2DRenderTriangleFunction)(RwIm2DVertex* vertices, RwInt32 numVertices, RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool(*RwIm2DRenderPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);
typedef RwBool(*RwIm2DRenderIndexedPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices, RwImVertexIndex* indices, RwInt32 numIndices);
typedef RwBool(*RwIm3DRenderLineFunction)(RwInt32 vert1, RwInt32 vert2);
typedef RwBool(*RwIm3DRenderTriangleFunction)(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool(*RwIm3DRenderPrimitiveFunction)(RwPrimitiveType primType);
typedef RwBool(*RwIm3DRenderIndexedPrimitiveFunction)(RwPrimitiveType primtype, RwImVertexIndex* indices, RwInt32 numIndices);

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
    void* devSpecificMetrics;
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
extern "C" {
#endif

extern RwVideoMode* RwEngineGetVideoModeInfo(RwVideoMode* modeinfo, RwInt32 modeIndex);
extern RwInt32 RwEngineGetCurrentVideoMode(void);

#ifdef __cplusplus
}
#endif

enum RwDebugType
{
    rwNADEBUGTYPE = 0,
    rwDEBUGASSERT,
    rwDEBUGERROR,
    rwDEBUGMESSAGE,
    rwDEBUGTRACE,
    rwDEBUGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwDebugType RwDebugType;

typedef void(*RwDebugHandler)(RwDebugType type, const RwChar* string);

#define RWSRCGLOBAL(variable) (((RwGlobals*)RwEngineInstance)->variable)

enum RwEngineStatus
{
    rwENGINESTATUSIDLE = 0,
    rwENGINESTATUSINITED = 1,
    rwENGINESTATUSOPENED = 2,
    rwENGINESTATUSSTARTED = 3,
    rwENGINESTATUSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwEngineStatus RwEngineStatus;

typedef struct RwGlobals RwGlobals;
struct RwGlobals
{
#ifdef RWDEBUG
    RwDebugHandler debugFunction;
    RwInt32 debugStackDepth;
    RwBool debugTrace;
#endif
    void* curCamera;
    void* curWorld;
    RwUInt16 renderFrame;
    RwUInt16 lightFrame;
    RwUInt16 pad[2];
    RwDevice dOpenDevice;
    RwStandardFunc stdFunc[rwSTANDARDNUMOFSTANDARD];
    RwLinkList dirtyFrameList;
    RwStringFunctions stringFuncs;
    RwMemoryFunctions memoryFuncs;
#ifdef RWDEBUG
    RwBool freeListExtraDebug;
#endif
    RwMemoryAllocFn memoryAlloc;
    RwMemoryFreeFn memoryFree;
    RwMetrics* metrics;
    RwEngineStatus engineStatus;
    RwUInt32 resArenaInitSize;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void* RwEngineInstance;

#ifdef __cplusplus
}
#endif

typedef struct RwResEntry RwResEntry;
typedef void(*RwResEntryDestroyNotify)(RwResEntry* resEntry);
struct RwResEntry
{
    RwLLLink link;
    RwInt32 size;
    void* owner;
    RwResEntry** ownerRef;
    RwResEntryDestroyNotify destroyNotify;
};

typedef struct RwRGBAReal RwRGBAReal;
struct RwRGBAReal
{
    RwReal red;
    RwReal green;
    RwReal blue;
    RwReal alpha;
};

typedef struct RwRGBA RwRGBA;
struct RwRGBA
{
    RwUInt8 red;
    RwUInt8 green;
    RwUInt8 blue;
    RwUInt8 alpha;
};

typedef struct rxHeapFreeBlock rxHeapFreeBlock;
typedef struct rxHeapSuperBlockDescriptor rxHeapSuperBlockDescriptor;
typedef struct RxHeap RxHeap;
typedef struct rxHeapBlockHeader rxHeapBlockHeader;

struct rxHeapFreeBlock
{
    RwUInt32 size;
    rxHeapBlockHeader* ptr;
};

struct rxHeapSuperBlockDescriptor
{
    void* start;
    RwUInt32 size;
    rxHeapSuperBlockDescriptor* next;
};

struct RxHeap
{
    RwUInt32 superBlockSize;
    rxHeapSuperBlockDescriptor* head;
    rxHeapBlockHeader* headBlock;
    rxHeapFreeBlock* freeBlocks;
    RwUInt32 entriesAlloced;
    RwUInt32 entriesUsed;
    RwBool dirty;
};

struct rxHeapBlockHeader
{
    rxHeapBlockHeader* prev;
    rxHeapBlockHeader* next;
    RwUInt32 size;
    rxHeapFreeBlock* freeEntry;
    RwUInt32 pad[4];
};

enum RxClusterValidityReq
{
    rxCLREQ_DONTWANT = 0,
    rxCLREQ_REQUIRED = 1,
    rxCLREQ_OPTIONAL = 2,
    rxCLUSTERVALIDITYREQFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RxClusterValid
{
    rxCLVALID_NOCHANGE = 0,
    rxCLVALID_VALID = 1,
    rxCLVALID_INVALID = 2,
    rxCLUSTERVALIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef struct RxClusterDefinition RxClusterDefinition;
typedef struct rxReq rxReq;
typedef enum RxClusterValidityReq RxClusterValidityReq;
typedef enum RxClusterValid RxClusterValid;
typedef struct RxOutputSpec RxOutputSpec;
typedef struct RxClusterRef RxClusterRef;
typedef struct RxIoSpec RxIoSpec;
typedef struct RxNodeMethods RxNodeMethods;
typedef struct RxNodeDefinition RxNodeDefinition;
typedef struct RxCluster RxCluster;
typedef struct RxPipelineCluster RxPipelineCluster;
typedef struct RxPacket RxPacket;
typedef struct RxPipelineNode RxPipelineNode;
typedef struct RxPipelineNodeTopSortData RxPipelineNodeTopSortData;
typedef struct RxPipelineNode RxPipelineNodeInstance;
typedef struct RxPipelineNodeParam RxPipelineNodeParam;
typedef struct RxExecutionContext RxExecutionContext;
typedef struct RxPipelineRequiresCluster RxPipelineRequiresCluster;
typedef struct RxPipeline RxPipeline;

struct RxClusterDefinition
{
    RwChar* name;
    RwUInt32 defaultStride;
    RwUInt32 defaultAttributes;
    const RwChar* attributeSet;
};

struct RxOutputSpec
{
     RwChar* name;
     RxClusterValid* outputClusters;
     RxClusterValid allOtherClusters;
};

enum RxClusterForcePresent
{
    rxCLALLOWABSENT = FALSE,
    rxCLFORCEPRESENT = TRUE,
    rxCLUSTERFORCEPRESENTFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxClusterForcePresent RxClusterForcePresent;

struct RxClusterRef
{
    RxClusterDefinition* clusterDef;
    RxClusterForcePresent forcePresent;
    RwUInt32 reserved;
};

struct RxIoSpec
{
    RwUInt32 numClustersOfInterest;
    RxClusterRef* clustersOfInterest;
    RxClusterValidityReq* inputRequirements;
    RwUInt32 numOutputs;
    RxOutputSpec* outputs;
};

typedef RwBool(*RxNodeBodyFn)(RxPipelineNode* self, const RxPipelineNodeParam* params);
typedef RwBool(*RxNodeInitFn)(RxNodeDefinition* self);
typedef void(*RxNodeTermFn)(RxNodeDefinition* self);
typedef RwBool(*RxPipelineNodeInitFn)(RxPipelineNode* self);
typedef void(*RxPipelineNodeTermFn)(RxPipelineNode* self);
typedef RwBool(*RxPipelineNodeConfigFn)(RxPipelineNode* self, RxPipeline* pipeline);
typedef RwUInt32(*RxConfigMsgHandlerFn)(RxPipelineNode* self, RwUInt32 msg, RwUInt32 intparam, void* ptrparam);

struct RxNodeMethods
{
    RxNodeBodyFn nodeBody;
    RxNodeInitFn nodeInit;
    RxNodeTermFn nodeTerm;
    RxPipelineNodeInitFn pipelineNodeInit;
    RxPipelineNodeTermFn pipelineNodeTerm;
    RxPipelineNodeConfigFn pipelineNodeConfig;
    RxConfigMsgHandlerFn configMsgHandler;
};

enum RxNodeDefEditable
{
    rxNODEDEFCONST = FALSE,
    rxNODEDEFEDITABLE = TRUE,
    rxNODEDEFEDITABLEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RxNodeDefEditable RxNodeDefEditable;

struct RxNodeDefinition
{
    RwChar* name;
    RxNodeMethods nodeMethods;
    RxIoSpec io;
    RwUInt32 pipelineNodePrivateDataSize;
    RxNodeDefEditable editable;
    RwInt32 InputPipesCnt;
};

struct RxPipelineCluster
{
    RxClusterDefinition* clusterRef;
    RwUInt32 creationAttributes;
};

struct RxCluster
{
    RwUInt16 flags;
    RwUInt16 stride;
    void* data;
    void* currentData;
    RwUInt32 numAlloced;
    RwUInt32 numUsed;
    RxPipelineCluster* clusterRef;
    RwUInt32 attributes;
};

struct RxPacket
{
    RwUInt16 flags;
    RwUInt16 numClusters;
    RxPipeline* pipeline;
    RwUInt32* inputToClusterSlot;
    RwUInt32* slotsContinue;
    RxPipelineCluster** slotClusterRefs;
    RxCluster clusters[1];
};

struct RxPipelineNode
{
    RxNodeDefinition* nodeDef;           
    RwUInt32 numOutputs;        
    RwUInt32* outputs;           
    RxPipelineCluster** slotClusterRefs;
    RwUInt32* slotsContinue;     
    void* privateData;       
    RwUInt32* inputToClusterSlot;
    RxPipelineNodeTopSortData* topSortData;
    void* initializationData;
    RwUInt32 initializationDataSize;
};

struct RxPipelineNodeTopSortData
{
    RwUInt32 numIns;
    RwUInt32 numInsVisited;
    rxReq* req;
};

struct RxPipelineNodeParam
{
    void* dataParam;
    RxHeap* heap;
};

enum rxEmbeddedPacketState
{
    rxPKST_PACKETLESS = 0,
    rxPKST_UNUSED = 1,
    rxPKST_INUSE = 2,
    rxPKST_PENDING = 3,
    rxEMBEDDEDPACKETSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum rxEmbeddedPacketState rxEmbeddedPacketState;

struct RxExecutionContext
{
    RxPipeline* pipeline;
    RxPipelineNode* currentNode;
    RwInt32 exitCode;
    RwUInt32 pad;
    RxPipelineNodeParam params;
};

struct RxPipelineRequiresCluster
{
    RxClusterDefinition* clusterDef;
    RxClusterValidityReq rqdOrOpt;
    RwUInt32 slotIndex;
};

typedef struct RxPipeline RxPipeline;
struct RxPipeline
{
    RwBool locked;
    RwUInt32 numNodes;
    RxPipelineNode* nodes;
    RwUInt32 packetNumClusterSlots;
    rxEmbeddedPacketState embeddedPacketState;
    RxPacket* embeddedPacket;
    RwUInt32 numInputRequirements;
    RxPipelineRequiresCluster* inputRequirements;
    void* superBlock;
    RwUInt32 superBlockSize;
    RwUInt32 entryPoint;
    RwUInt32 pluginId;
    RwUInt32 pluginData;
};

enum RwRasterLockMode
{
    rwRASTERLOCKWRITE = 0x01,
    rwRASTERLOCKREAD = 0x02,
    rwRASTERLOCKNOFETCH = 0x04,
    rwRASTERLOCKRAW = 0x08,
    rwRASTERLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

#define rwRASTERLOCKREADWRITE (rwRASTERLOCKREAD|rwRASTERLOCKWRITE)
typedef enum RwRasterLockMode RwRasterLockMode;

enum RwRasterFlipMode
{
    rwRASTERFLIPDONTWAIT = 0,
    rwRASTERFLIPWAITVSYNC = 1,
    rwRASTERFLIPMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFlipMode RwRasterFlipMode;

enum RwRasterType
{
    rwRASTERTYPENORMAL = 0x00,
    rwRASTERTYPEZBUFFER = 0x01,
    rwRASTERTYPECAMERA = 0x02,
    rwRASTERTYPETEXTURE = 0x04,
    rwRASTERTYPECAMERATEXTURE = 0x05,
    rwRASTERTYPEMASK = 0x07,
    rwRASTERPALETTEVOLATILE = 0x40,
    rwRASTERDONTALLOCATE = 0x80,
    rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterType RwRasterType;

enum RwRasterFormat
{
    rwRASTERFORMATDEFAULT = 0x0000,
    rwRASTERFORMAT1555 = 0x0100,
    rwRASTERFORMAT565 = 0x0200,
    rwRASTERFORMAT4444 = 0x0300,
    rwRASTERFORMATLUM8 = 0x0400,
    rwRASTERFORMAT8888 = 0x0500,
    rwRASTERFORMAT888 = 0x0600,
    rwRASTERFORMAT16 = 0x0700,
    rwRASTERFORMAT24 = 0x0800,
    rwRASTERFORMAT32 = 0x0900,
    rwRASTERFORMAT555 = 0x0a00,
    rwRASTERFORMATAUTOMIPMAP = 0x1000,
    rwRASTERFORMATPAL8 = 0x2000,
    rwRASTERFORMATPAL4 = 0x4000,
    rwRASTERFORMATMIPMAP = 0x8000,
    rwRASTERFORMATPIXELFORMATMASK = 0x0f00,
    rwRASTERFORMATMASK = 0xff00,
    rwRASTERFORMATFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFormat RwRasterFormat;

enum RwRasterPrivateFlag
{
    rwRASTERGAMMACORRECTED = 0x01,
    rwRASTERPIXELLOCKEDREAD = 0x02,
    rwRASTERPIXELLOCKEDWRITE = 0x04,
    rwRASTERPALETTELOCKEDREAD = 0x08,
    rwRASTERPALETTELOCKEDWRITE = 0x10,
    rwRASTERPIXELLOCKEDRAW = 0x20,
    rwRASTERPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterPrivateFlag RwRasterPrivateFlag;

#define rwRASTERPIXELLOCKED (rwRASTERPIXELLOCKEDREAD | rwRASTERPIXELLOCKEDWRITE)
#define rwRASTERPALETTELOCKED (rwRASTERPALETTELOCKEDREAD | rwRASTERPALETTELOCKEDWRITE)
#define rwRASTERLOCKED (rwRASTERPIXELLOCKED|rwRASTERPALETTELOCKED)

typedef struct RwRaster RwRaster;
struct RwRaster
{
    RwRaster* parent;
    RwUInt8* cpPixels;
    RwUInt8* palette;
    RwInt32 width, height, depth;
    RwInt32 stride;
    RwInt16 nOffsetX, nOffsetY;
    RwUInt8 cType;
    RwUInt8 cFlags;
    RwUInt8 privateFlags;
    RwUInt8 cFormat;
    RwUInt8* originalPixels;
    RwInt32 originalWidth;
    RwInt32 originalHeight;
    RwInt32 originalStride;
};

#define RwRasterGetWidthMacro(_raster) ((_raster)->width)
#define RwRasterGetHeightMacro(_raster) ((_raster)->height)
#define RwRasterGetStrideMacro(_raster) ((_raster)->stride)
#define RwRasterGetDepthMacro(_raster) ((_raster)->depth)
#define RwRasterGetFormatMacro(_raster) ((((_raster)->cFormat) & (rwRASTERFORMATMASK >> 8)) << 8)
#define RwRasterGetTypeMacro(_raster) (((_raster)->cType) & rwRASTERTYPEMASK)
#define RwRasterGetParentMacro(_raster) ((_raster)->parent)

#ifndef RWDEBUG
#define RwRasterGetWidth(_raster) RwRasterGetWidthMacro(_raster)
#define RwRasterGetHeight(_raster) RwRasterGetHeightMacro(_raster)
#define RwRasterGetStride(_raster) RwRasterGetStrideMacro(_raster)
#define RwRasterGetDepth(_raster) RwRasterGetDepthMacro(_raster)
#define RwRasterGetFormat(_raster) RwRasterGetFormatMacro(_raster)
#define RwRasterGetType(_raster) RwRasterGetTypeMacro(_raster)
#define RwRasterGetParent(_raster) RwRasterGetParentMacro(_raster)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern RwRaster* RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
extern RwBool RwRasterDestroy(RwRaster* raster);

#ifdef RWDEBUG
extern RwInt32 RwRasterGetWidth(const RwRaster* raster);
extern RwInt32 RwRasterGetHeight(const RwRaster* raster);
extern RwInt32 RwRasterGetStride(const RwRaster* raster);
extern RwInt32 RwRasterGetDepth(const RwRaster* raster);
extern RwInt32 RwRasterGetFormat(const RwRaster* raster);
extern RwInt32 RwRasterGetType(const RwRaster* raster);
extern RwRaster* RwRasterGetParent(const RwRaster* raster);
#endif

extern RwInt32 RwRasterGetNumLevels(RwRaster* raster);
extern RwRaster* RwRasterSubRaster(RwRaster* subRaster, RwRaster* raster, RwRect* rect);
extern RwRaster* RwRasterRenderFast(RwRaster* raster, RwInt32 x, RwInt32 y);
extern RwRaster* RwRasterRender(RwRaster* raster, RwInt32 x, RwInt32 y);
extern RwRaster* RwRasterPushContext(RwRaster* raster);
extern RwRaster* RwRasterPopContext(void);
extern RwBool RwRasterClear(RwInt32 pixelValue);
extern RwRaster* RwRasterShowRaster(RwRaster* raster, void* dev, RwUInt32 flags);
extern RwUInt8* RwRasterLock(RwRaster* raster, RwUInt8 level, RwInt32 lockMode);
extern RwRaster* RwRasterUnlock(RwRaster* raster);
extern RwUInt8* RwRasterLockPalette(RwRaster* raster, RwInt32 lockMode);
extern RwRaster* RwRasterUnlockPalette(RwRaster* raster);
extern RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);

#ifdef __cplusplus
}
#endif

typedef struct RxObjSpace3DVertex RxObjSpace3DVertex;
struct RxObjSpace3DVertex
{
    RwReal x;
    RwReal y;
    RwReal z;
    RwReal nx;
    RwReal ny;
    RwReal nz;
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
    RwReal u;
    RwReal v;
};
typedef RxObjSpace3DVertex RwIm3DVertex;

#define RwIm3DVertexSetPos(_vert, _imx, _imy, _imz)                                               \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->x = _imx;                                                                            \
    (_vert)->y = _imy;                                                                            \
    (_vert)->z = _imz;                                                                            \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetNormal(_vert, _imx, _imy, _imz)                                            \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->nx = _imx;                                                                           \
    (_vert)->ny = _imy;                                                                           \
    (_vert)->nz = _imz;                                                                           \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetRGBA(_vert, _r, _g, _b, _a)                                                \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->r = _r;                                                                              \
    (_vert)->g = _g;                                                                              \
    (_vert)->b = _b;                                                                              \
    (_vert)->a = _a;                                                                              \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetUV(_vert, _u, _v)                                                          \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->u = _u;                                                                              \
    (_vert)->v = _v;                                                                              \
}                                                                                                 \
MACRO_STOP

#define rwTEXTUREBASENAMELENGTH 32

typedef struct RwTexDictionary RwTexDictionary;
struct RwTexDictionary
{
    RwObject object;
    RwLinkList texturesInDict;
    RwLLLink lInInstance;
};

typedef struct RwTexture RwTexture;
struct RwTexture
{
    RwRaster* raster;
    RwTexDictionary* dict; 
    RwLLLink lInDictionary;
    RwChar name[rwTEXTUREBASENAMELENGTH];
    RwChar mask[rwTEXTUREBASENAMELENGTH];
    RwUInt32 filterAddressing;
    RwInt32 refCount;
};

#define RwTextureGetRasterMacro(_tex) ((_tex)->raster)

#ifndef RWDEBUG
#define RwTextureGetRaster(_tex) RwTextureGetRasterMacro(_tex)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RWDEBUG
extern RwRaster* RwTextureGetRaster(const RwTexture* texture);
#endif

#ifdef __cplusplus
}
#endif

enum RwIm3DTransformFlags
{
    rwIM3D_VERTEXUV = 1,
    rwIM3D_ALLOPAQUE = 2,
    rwIM3D_NOCLIP = 4,
    rwIM3D_VERTEXXYZ = 8,
    rwIM3D_VERTEXRGBA = 16,
    rwIM3DTRANSFORMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwIm3DTransformFlags RwIm3DTransformFlags;

#ifdef __cplusplus
extern "C" {
#endif

extern void* RwIm3DTransform(RwIm3DVertex* pVerts, RwUInt32 numVerts, RwMatrix* ltm, RwUInt32 flags);
extern RwBool RwIm3DEnd(void);
extern RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType);

#ifdef __cplusplus
}
#endif

struct RwFrame
{
    RwObject object;
    RwLLLink inDirtyListLink;
    RwMatrix modelling;
    RwMatrix ltm;
    RwLinkList objectList;
    struct RwFrame* child;
    struct RwFrame* next;
    struct RwFrame* root;
};
typedef struct RwFrame RWALIGN(RwFrame, rwFRAMEALIGNMENT);
typedef RwFrame*(*RwFrameCallBack)(RwFrame* frame, void* data);

#define RwFrameGetMatrixMacro(_f) (&(_f)->modelling)

#ifndef RWDEBUG
#define RwFrameGetMatrix(_f) RwFrameGetMatrixMacro(_f)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern RwFrame* RwFrameTransform(RwFrame* frame, const RwMatrix* m, RwOpCombineType combine);

#ifdef RWDEBUG
extern RwMatrix* RwFrameGetMatrix(RwFrame* frame);
#endif

extern RwFrame* RwFrameCreate(void);
extern RwBool RwFrameDestroy(RwFrame* frame);

#ifdef __cplusplus
}
#endif

typedef struct RwObjectHasFrame RwObjectHasFrame;
typedef RwObjectHasFrame*(*RwObjectHasFrameSyncFunction)(RwObjectHasFrame* object);
struct RwObjectHasFrame
{
    RwObject object;
    RwLLLink lFrame;
    RwObjectHasFrameSyncFunction sync;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void _rwObjectHasFrameSetFrame(void* object, RwFrame* frame);

#ifdef __cplusplus
}
#endif

#define rwObjectHasFrameSetFrame(object, frame) _rwObjectHasFrameSetFrame(object, frame)

#ifdef __cplusplus
extern "C" {
#endif

extern RwBool _rwFrameSyncDirty(void);

#ifdef __cplusplus
}
#endif

typedef struct RwBBox RwBBox;
struct RwBBox
{
    RwV3d sup;
    RwV3d inf;
};

#define RwCameraGetNearClipPlaneMacro(_camera) ((_camera)->nearPlane)
#define RwCameraGetFarClipPlaneMacro(_camera) ((_camera)->farPlane)
#define RwCameraGetCurrentCameraMacro() ((RwCamera*)RWSRCGLOBAL(curCamera))
#define RwCameraGetFrameMacro(_camera) ((RwFrame *)rwObjectGetParent((_camera)))

#ifndef RWDEBUG
#define RwCameraGetNearClipPlane(_camera) RwCameraGetNearClipPlaneMacro(_camera)
#define RwCameraGetFarClipPlane(_camera) RwCameraGetFarClipPlaneMacro(_camera)
#define RwCameraGetCurrentCamera() RwCameraGetCurrentCameraMacro()
#define RwCameraGetFrame(_camera) RwCameraGetFrameMacro(_camera)
#endif

enum RwCameraClearMode
{
    rwCAMERACLEARIMAGE = 0x1,
    rwCAMERACLEARZ = 0x2,
    rwCAMERACLEARSTENCIL = 0x4,
    rwCAMERACLEARMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraClearMode RwCameraClearMode;

enum RwCameraProjection
{
    rwNACAMERAPROJECTION = 0,
    rwPERSPECTIVE = 1,
    rwPARALLEL = 2,
    rwCAMERAPROJECTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraProjection RwCameraProjection;

typedef struct RwCamera RWALIGN(RwCamera, rwMATRIXALIGNMENT);
typedef RwCamera*(*RwCameraBeginUpdateFunc)(RwCamera* camera);
typedef RwCamera*(*RwCameraEndUpdateFunc)(RwCamera* camera);

typedef struct RwFrustumPlane RwFrustumPlane;
struct RwFrustumPlane
{
    RwPlane plane;
    RwUInt8 closestX;
    RwUInt8 closestY;
    RwUInt8 closestZ;
    RwUInt8 pad;
};

struct RwCamera
{
    RwObjectHasFrame object;
    RwCameraProjection projectionType;
    RwCameraBeginUpdateFunc beginUpdate;
    RwCameraEndUpdateFunc endUpdate;
    RwMatrix viewMatrix;
    RwRaster* frameBuffer;
    RwRaster* zBuffer;
    RwV2d viewWindow;
    RwV2d recipViewWindow;
    RwV2d viewOffset;
    RwReal nearPlane;
    RwReal farPlane;
    RwReal fogPlane;
    RwReal zScale;
    RwReal zShift;
    RwFrustumPlane frustumPlanes[6];
    RwBBox frustumBoundBox;
    RwV3d frustumCorners[8];
};

#ifdef __cplusplus
extern "C" {
#endif

extern RwCamera* RwCameraEndUpdate(RwCamera* camera);
extern RwCamera* RwCameraClear(RwCamera* camera, RwRGBA* colour, RwInt32 clearMode);
extern RwCamera* RwCameraSetFarClipPlane(RwCamera* camera, RwReal farClip);

#ifdef RWDEBUG
extern RwReal RwCameraGetNearClipPlane(const RwCamera* camera);
extern RwReal RwCameraGetFarClipPlane(const RwCamera* camera);
extern RwCamera* RwCameraGetCurrentCamera(void);
extern RwFrame* RwCameraGetFrame(const RwCamera* camera);
#endif

#ifdef __cplusplus
}
#endif

#endif
