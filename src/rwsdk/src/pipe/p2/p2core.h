#ifndef P2CORE_H
#define P2CORE_H

#include "p2macros.h"
#include "p2heap.h"

#include "batypes.h"
#include "bamemory.h"

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
    RwChar *name;
    RwUInt32 defaultStride;
    RwUInt32 defaultAttributes;
    const RwChar *attributeSet;
};

struct RxOutputSpec
{
     RwChar *name;
     RxClusterValid *outputClusters;
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
    RxClusterDefinition *clusterDef;
    RxClusterForcePresent forcePresent;
    RwUInt32 reserved;
};

struct RxIoSpec
{
    RwUInt32 numClustersOfInterest;
    RxClusterRef *clustersOfInterest;
    RxClusterValidityReq *inputRequirements;
    RwUInt32 numOutputs;
    RxOutputSpec *outputs;
};

typedef RwBool (*RxNodeBodyFn)(RxPipelineNode *self, const RxPipelineNodeParam *params);
typedef RwBool (*RxNodeInitFn)(RxNodeDefinition *self);
typedef void (*RxNodeTermFn)(RxNodeDefinition *self);
typedef RwBool (*RxPipelineNodeInitFn)(RxPipelineNode *self);
typedef void (*RxPipelineNodeTermFn)(RxPipelineNode *self);
typedef RwBool (*RxPipelineNodeConfigFn)(RxPipelineNode *self, RxPipeline *pipeline);
typedef RwUInt32 (*RxConfigMsgHandlerFn)(RxPipelineNode *self, RwUInt32 msg, RwUInt32 intparam, void *ptrparam);

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
    RwChar *name;
    RxNodeMethods nodeMethods;
    RxIoSpec io;
    RwUInt32 pipelineNodePrivateDataSize;
    RxNodeDefEditable editable;
    RwInt32 InputPipesCnt;
};

struct RxPipelineCluster
{
    RxClusterDefinition *clusterRef;
    RwUInt32 creationAttributes;
};

struct RxCluster
{
    RwUInt16 flags;
    RwUInt16 stride;
    void *data;
    void *currentData;
    RwUInt32 numAlloced;
    RwUInt32 numUsed;
    RxPipelineCluster *clusterRef;
    RwUInt32 attributes;
};

struct RxPacket
{
    RwUInt16 flags;
    RwUInt16 numClusters;
    RxPipeline *pipeline;
    RwUInt32 *inputToClusterSlot;
    RwUInt32 *slotsContinue;
    RxPipelineCluster **slotClusterRefs;
    RxCluster clusters[1];
};

struct RxPipelineNode
{
    RxNodeDefinition *nodeDef;           
    RwUInt32 numOutputs;        
    RwUInt32 *outputs;           
    RxPipelineCluster **slotClusterRefs;
    RwUInt32 *slotsContinue;     
    void *privateData;       
    RwUInt32 *inputToClusterSlot;
    RxPipelineNodeTopSortData *topSortData;
    void *initializationData;
    RwUInt32 initializationDataSize;
};

struct RxPipelineNodeTopSortData
{
    RwUInt32 numIns;
    RwUInt32 numInsVisited;
    rxReq *req;
};

struct RxPipelineNodeParam
{
    void *dataParam;
    RxHeap *heap;
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
    RxPipeline *pipeline;
    RxPipelineNode *currentNode;
    RwInt32 exitCode;
    RwUInt32 pad;
    RxPipelineNodeParam params;
};

struct RxPipelineRequiresCluster
{
    RxClusterDefinition *clusterDef;
    RxClusterValidityReq rqdOrOpt;
    RwUInt32 slotIndex;
};

typedef struct RxPipeline RxPipeline;
struct RxPipeline
{
    RwBool locked;
    RwUInt32 numNodes;
    RxPipelineNode *nodes;
    RwUInt32 packetNumClusterSlots;
    rxEmbeddedPacketState embeddedPacketState;
    RxPacket *embeddedPacket;
    RwUInt32 numInputRequirements;
    RxPipelineRequiresCluster *inputRequirements;
    void *superBlock;
    RwUInt32 superBlockSize;
    RwUInt32 entryPoint;
    RwUInt32 pluginId;
    RwUInt32 pluginData;
};

#endif
