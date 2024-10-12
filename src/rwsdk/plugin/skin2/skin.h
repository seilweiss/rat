#ifndef _SKIN_H
#define _SKIN_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include "rwcore.h"
#include "rpworld.h"

#include "rpplugin.h"
#include "rpdbgerr.h"

#include "rphanim.h"
#include "rpskin.h"

#if (defined(SKY2_DRVMODEL_H))
#include "sky2/skinsky.h"
#elif (defined(XBOX_DRVMODEL_H))
#include "xbox/skinxbox.h"
#elif (defined(GCN_DRVMODEL_H))
#include "gcn/skingcn.h"
#elif (defined(NULLGCN_DRVMODEL_H))
#include "gcn/skingcn.h"
#elif (defined(D3D8_DRVMODEL_H))
#include "d3d8/skind3d8.h"
#elif (defined(D3D9_DRVMODEL_H))
#include "d3d9/skind3d9.h"
#elif (defined(OPENGL_DRVMODEL_H))
#include "opengl/skinopengl.h"
#elif (defined(SOFTRAS_DRVMODEL_H))
#include "softras/skinsoftras.h"
#elif (defined (NULL_DRVMODEL_H)    || \
       defined (NULLSKY_DRVMODEL_H) || \
       defined (NULLXBOX_DRVMODEL_H))
#include "null/skinnull.h"
#else
#include "generic/skingeneric.h"
#endif

/*===========================================================================*
 *--- Private Types ---------------------------------------------------------*
 *===========================================================================*/
enum SkinPipeline
{
    rpNASKINPIPELINE          = 0,
    rpSKINPIPELINESKINGENERIC = 0x01,
    rpSKINPIPELINESKINMATFX   = 0x02,
    rpSKINPIPELINESKINTOON    = 0x04,
    rpSKINPIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum SkinPipeline SkinPipeline;

typedef void * SkinUnaligned;

typedef struct SkinPlatformData         SkinPlatformData;
#if defined(SKIN_ATOMIC_PLATFORM_DATA)
typedef struct SkinAtomicPlatformData   SkinAtomicPlatformData;
#endif /* defined(SKIN_ATOMIC_PLATFORM_DATA) */
typedef struct SkinGlobalPlatform       SkinGlobalPlatform;

typedef struct SkinSplitData SkinSplitData;
struct SkinSplitData
{
    RwUInt32            boneLimit;
    RwUInt32            numMeshes;
    RwUInt32            numRLE;
    RwUInt8             *matrixRemapIndices;
    RwUInt8             *meshRLECount;
    RwUInt8             *meshRLE;
};

typedef struct SkinBoneData SkinBoneData;
struct SkinBoneData
{
    RwUInt32            numBones;
    RwUInt32            numUsedBones;
    RwUInt8             *usedBoneList;
    RwMatrix            *invBoneToSkinMat;
};

typedef struct SkinVertexMaps SkinVertexMaps;
struct SkinVertexMaps
{
    RwUInt32            maxWeights;
    RwUInt32            *matrixIndices;
    RwMatrixWeights     *matrixWeights;
};

struct RpSkin
{
    SkinBoneData        boneData;
    SkinVertexMaps      vertexMaps;
    SkinPlatformData    platformData;
    SkinSplitData       skinSplitData;
    SkinUnaligned       *unaligned;
};

typedef struct SkinAtomicData SkinAtomicData;
struct SkinAtomicData
{
    RpHAnimHierarchy *hierarchy;
#if defined(SKIN_ATOMIC_PLATFORM_DATA)
    SkinAtomicPlatformData    platformData;
#endif /* defined(SKIN_ATOMIC_PLATFORM_DATA) */
};

typedef struct SkinMatrixCache SkinMatrixCache;
struct SkinMatrixCache
{
    RwMatrix      *aligned;
    SkinUnaligned  unaligned;
};

typedef struct SkinGlobals SkinGlobals;
struct SkinGlobals
{
    /* Offsets. */
    RwInt32 engineOffset;
    RwInt32 atomicOffset;
    RwInt32 geometryOffset;

    /* Matrix Cache. */
    SkinMatrixCache     matrixCache;
    RwUInt32            numMatrices;

    /* Plugin data. */
    RwFreeList         *freeList;
    RwModuleInfo        module;

    /* Platform global data. */
    SkinGlobalPlatform  platform;

    /* Skin split data */
    SkinSplitData       *skinSplitData;
};

/*===========================================================================*
 *--- Private Global Variables ----------------------------------------------*
 *===========================================================================*/
extern SkinGlobals _rpSkinGlobals;

/*===========================================================================*
 *--- Private Defines -------------------------------------------------------*
 *===========================================================================*/
#define RPSKINENGINEGETDATA(engineInstance)     \
     ((_rpSkinLinkCallBack *)                   \
      (((RwUInt8 *)engineInstance) +            \
       _rpSkinGlobals.engineOffset))

#define RPSKINENGINEGETCONSTDATA(engineInstance)        \
     ((const _rpSkinLinkCallBack *)                     \
      (((const RwUInt8 *)engineInstance) +              \
       _rpSkinGlobals.engineOffset))

#define RPSKINATOMICGETDATA(atomicInstance)     \
     ((SkinAtomicData *)                        \
      (((RwUInt8 *)atomicInstance) +            \
       _rpSkinGlobals.atomicOffset))

#define RPSKINATOMICGETCONSTDATA(atomicInstance)        \
     ((const SkinAtomicData *)                          \
      (((const RwUInt8 *)atomicInstance) +              \
       _rpSkinGlobals.atomicOffset))

#define RPSKINGEOMETRYGETDATA(geometryInstance) \
     ((RpSkin **)                               \
      (((RwUInt8 *)geometryInstance) +          \
       _rpSkinGlobals.geometryOffset))

#define RPSKINGEOMETRYGETCONSTDATA(geometryInstance)    \
     ((const RpSkin * const *)                          \
      (((const RwUInt8 *)geometryInstance) +            \
       _rpSkinGlobals.geometryOffset))

/*===========================================================================*
 *--- Private Functions -----------------------------------------------------*
 *===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RwBool
_rpSkinPipelinesCreate(RwUInt32 pipes);

extern RwBool
_rpSkinPipelinesDestroy(void);

extern RpAtomic *
_rpSkinPipelinesAttach( RpAtomic *atomic,
                        RpSkinType type );

extern RwMatrix *
_rpSkinGetAlignedMatrixCache(void);

/* Native Serialization Functions */
extern RwInt32
_rpSkinGeometryNativeSize(const RpGeometry *geometry);

extern RwStream *
_rpSkinGeometryNativeWrite(RwStream *stream, const RpGeometry *geometry);

extern RwStream *
_rpSkinGeometryNativeRead(RwStream *stream, RpGeometry *geometry);

#ifdef SKIN_ATOMIC_PLATFORM_STREAM_SIZE
extern RwInt32
_rpSkinAtomicNativeSize(const RpAtomic *atomic);
#endif /* SKIN_ATOMIC_PLATFORM_STREAM_SIZE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* (defined(_SKIN_H)) */
