#ifndef RWBRP_H // Yes, this is misspelled...
#define RWGRP_H

#include "batypes.h"
#include "bastream.h"
#include "bamemory.h"

#define rwCHUNKGROUPMAXNAME 32

#define rwCHUNKGROUPVERSION 0x01

typedef struct RwChunkGroup RwChunkGroup;
struct RwChunkGroup
{
    RwChar      name[rwCHUNKGROUPMAXNAME + 1];  /**< Name identifier for the group. */
};

typedef struct rwChunkGroupGlobals rwChunkGroupGlobals;
struct rwChunkGroupGlobals
{
    RwFreeList         *groupFList;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern void  *
_rwChunkGroupOpen(void *instance,
             RwInt32 __RWUNUSED__ offset ,
             RwInt32 __RWUNUSED__ size );

extern void  *
_rwChunkGroupClose(void *instance,
             RwInt32 __RWUNUSED__ offset ,
             RwInt32 __RWUNUSED__ size );

#ifdef __cplusplus
}
#endif

#endif
