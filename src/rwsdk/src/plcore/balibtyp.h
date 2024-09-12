#ifndef RWLIBTYP_H
#define RWLIBTYP_H

#include "badebug.h"
#include "batkreg.h"
#include "badevice.h"
#include "bamemory.h"
#include "rwstring.h"
#include "drvmodel.h"

#define RWPLUGINOFFSET(_type, _base, _offset) ((_type *)((RwUInt8 *)(_base) + (_offset)))

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
    void *curCamera;
    void *curWorld;
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
    RwMetrics *metrics;
    RwEngineStatus engineStatus;
    RwUInt32 resArenaInitSize;
};

typedef struct RwModuleInfo RwModuleInfo;
struct RwModuleInfo
{
    RwInt32 globalsOffset;
    RwInt32 numInstances;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern void *RwEngineInstance;

#ifdef __cplusplus
}
#endif

#endif
