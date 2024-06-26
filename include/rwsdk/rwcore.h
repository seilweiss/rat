#ifndef RWCORE_H
#define RWCORE_H

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

typedef struct RwV3d RwV3d;
struct RwV3d
{
    RwReal x;
    RwReal y;
    RwReal z;
};

typedef struct RwSphere RwSphere;
struct RwSphere
{
    RwV3d center;
    RwReal radius;
};

#define rwMAXTEXTURECOORDS 8

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

typedef struct RwObject RwObject;
struct RwObject
{
    RwUInt8 type;
    RwUInt8 subType;
    RwUInt8 flags;
    RwUInt8 privateFlags;
    void* parent;
};

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

#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)           \
MACRO_START                                                             \
{                                                                       \
    ((vert)->r = (red));                                                \
    ((vert)->g = (green));                                              \
    ((vert)->b = (blue));                                               \
    ((vert)->a = (alpha));                                              \
}                                                                       \
MACRO_STOP

enum RwFogType
{
    rwFOGTYPENAFOGTYPE = 0,
    rwFOGTYPELINEAR,
    rwFOGTYPEEXPONENTIAL,
    rwFOGTYPEEXPONENTIAL2,
    rwFOGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwFogType RwFogType;

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

typedef struct RwObjectHasFrame RwObjectHasFrame;
typedef RwObjectHasFrame*(*RwObjectHasFrameSyncFunction)(RwObjectHasFrame* object);
struct RwObjectHasFrame
{
    RwObject object;
    RwLLLink lFrame;
    RwObjectHasFrameSyncFunction sync;
};

typedef struct RwBBox RwBBox;
struct RwBBox
{
    RwV3d sup;
    RwV3d inf;
};

#endif
