#ifndef RWCLUMP_H
#define RWCLUMP_H

#include <rwcore.h>
#include "bageomet.h"
#include "basector.h"
#include "balight.h"

enum RpInterpolatorFlag
{
    rpINTERPOLATORDIRTYINSTANCE = 0x01,
    rpINTERPOLATORDIRTYSPHERE = 0x02,
    rpINTERPOLATORNOFRAMEDIRTY = 0x04,
    rpINTERPOLATORFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpInterpolatorFlag rpInterpolatorFlag;

enum RpAtomicFlag
{
    rpATOMICCOLLISIONTEST = 0x01,
    rpATOMICRENDER = 0x04,
    rpATOMICFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicFlag RpAtomicFlag;

enum RpAtomicSetGeomFlag
{
    rpATOMICSAMEBOUNDINGSPHERE = 0x01,
    rpATOMICSETGEOMFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicSetGeomFlag RpAtomicSetGeomFlag;

enum RpAtomicPrivateFlag
{
    rpATOMICPRIVATEWORLDBOUNDDIRTY = 0x01,
    rpATOMICPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicPrivateFlag rpAtomicPrivateFlag;

typedef struct RpAtomic RpAtomic;

typedef struct RpInterpolator RpInterpolator;
struct RpInterpolator
{
    RwInt32 flags;
    RwInt16 startMorphTarget;
    RwInt16 endMorphTarget;
    RwReal time;
    RwReal recipTime;
    RwReal position;
};

typedef struct RpClump RpClump;

typedef RpClump *(*RpClumpCallBack)(RpClump *clump, void *data);

struct RpClump
{
    RwObject object;
    RwLinkList atomicList;
    RwLinkList lightList;
    RwLinkList cameraList;
    RwLLLink inWorldLink;
    RpClumpCallBack callback;
};

typedef RpAtomic *(*RpAtomicCallBackRender)(RpAtomic *atomic);
struct RpAtomic
{
    RwObjectHasFrame object;
    RwResEntry *repEntry;
    RpGeometry *geometry;
    RwSphere boundingSphere;
    RwSphere worldBoundingSphere;
    RpClump *clump;
    RwLLLink inClumpLink;
    RpAtomicCallBackRender renderCallBack;
    RpInterpolator interpolator;
    RwUInt16 renderFrame;
    RwUInt16 pad;
    RwLinkList llWorldSectorsInAtomic;
    RxPipeline *pipeline;
};

typedef struct RpTie RpTie;
struct RpTie
{
    RwLLLink lAtomicInWorldSector;
    RpAtomic *apAtom;
    RwLLLink lWorldSectorInAtomic;
    RpWorldSector *worldSector;
};

#define RpAtomicGetGeometryMacro(_atomic) ((_atomic)->geometry)

#define RpAtomicSetRenderCallBackMacro(_atomic, _callback)              \
MACRO_START                                                             \
{                                                                       \
    (_atomic)->renderCallBack = (_callback);                            \
    if (!(_atomic)->renderCallBack)                                     \
    {                                                                   \
        (_atomic)->renderCallBack = AtomicDefaultRenderCallBack;        \
    }                                                                   \
}                                                                       \
MACRO_STOP

#define RpAtomicGetRenderCallBackMacro(_atomic) ((_atomic)->renderCallBack)

#ifndef RWDEBUG
#define RpAtomicGetGeometry(_atomic) RpAtomicGetGeometryMacro(_atomic)
#define RpAtomicSetRenderCallBack(_atomic, _callback) RpAtomicSetRenderCallBackMacro(_atomic, _callback)
#define RpAtomicGetRenderCallBack(_atomic) RpAtomicGetRenderCallBackMacro(_atomic)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

extern RpAtomic *AtomicDefaultRenderCallBack(RpAtomic *atomic);

#ifdef RWDEBUG
extern RpGeometry *RpAtomicGetGeometry(const RpAtomic *atomic);
extern void RpAtomicSetRenderCallBack(RpAtomic *atomic, RpAtomicCallBackRender callback);
extern RpAtomicCallBackRender RpAtomicGetRenderCallBack(const RpAtomic *atomic);
#endif

#ifdef __cplusplus
}
#endif

#endif
