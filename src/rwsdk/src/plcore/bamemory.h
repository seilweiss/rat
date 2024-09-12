#ifndef RWMEMORY_H
#define RWMEMORY_H

#include <stdlib.h>
#include "batypes.h"

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
    void *(*rwmalloc)(size_t size, RwUInt32 hint);
    void (*rwfree)(void *mem);
    void *(*rwrealloc)(void *mem, size_t newSize, RwUInt32 hint);
    void *(*rwcalloc)(size_t numObj, size_t sizeObj, RwUInt32 hint);
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
    const RwChar *fileCreate;
    RwUInt32 lineCreate;
#endif
};

typedef void *(*RwMemoryAllocFn)(RwFreeList *fl, RwUInt32 hint);
typedef RwFreeList *(*RwMemoryFreeFn)(RwFreeList *fl, void *pData);

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef RWDEBUG
extern const RwChar *_rwMemoryLastAllocFile;
extern RwUInt32 _rwMemoryLastAllocLine;
#endif

#ifdef __cplusplus
}
#endif

#endif
