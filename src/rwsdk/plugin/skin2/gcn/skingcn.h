#ifndef _SKINGCN_H
#define _SKINGCN_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include <rwcore.h>
#include <rpworld.h>

#include "rpskin.h"

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/
struct SkinPlatformData
{
    void        *vertices;
    void        *normals;
    RwUInt8     *weights;
    RwUInt8     *indices;
    RwUInt32    skinType;
};

#define SKIN_ATOMIC_PLATFORM_DATA
struct SkinAtomicPlatformData
{
    void        *vertices;
    void        *normals;
};

struct SkinGlobalPlatform
{
    RxPipeline  *pipelines[5];
};

/*===========================================================================*
 *--- Private Global Variables ----------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- Private Defines -------------------------------------------------------*
 *===========================================================================*/
#define rpSKINMAXNUMBEROFMATRICES 256

#define _rpSkinPipeline(pipeline)                                       \
    (_rpSkinGlobals.platform.pipelines[pipeline - 1])

#if (defined(__VECTORC__) && !(defined(RWDEBUG) || defined(RWSUPPRESSINLINE)))
#define  ATOMICGETDEFAULTINSTANCEPIPELINE()                              \
    (((rwPipeGlobals *)                                                  \
     (((RwUInt8 *)(RwEngineInstance)) +                                  \
      (_rxPipelineGlobalsOffset)))->currentAtomicPipeline)
#endif /* (defined(__VECTORC__) .... */

#if (!defined(ATOMICGETDEFAULTINSTANCEPIPELINE))
#define  ATOMICGETDEFAULTINSTANCEPIPELINE()           \
    (RpAtomicGetDefaultPipeline())
#endif /* (!defined(ATOMICGETDEFAULTINSTANCEPIPELINE)) */

#define SKIN_ATOMIC_PLATFORM_STREAM_SIZE

/*===========================================================================*
 *--- Private Types ---------------------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- Private Functions -----------------------------------------------------*
 *===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SKIND3D9_H */
