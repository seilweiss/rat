#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "babinary.h"
#include "batypes.h"
#include "balibtyp.h"
#include "bastream.h"
#include "osintf.h"
#include "bamemory.h"

#include "rwgrp.h"

#define RWCHUNKGROUPGLOBAL(var) (RWPLUGINOFFSET(rwChunkGroupGlobals, RwEngineInstance, chunkGroupModule.globalsOffset)->var)

static RwModuleInfo chunkGroupModule;

static RwInt32 _rwChunkGroupFListBlockSize = 16;
static RwInt32 _rwChunkGroupFListPreallocBlocks = 1;
static RwFreeList _rwChunkGroupFList;

void  *
_rwChunkGroupOpen(void *instance,
             RwInt32 __RWUNUSED__ offset ,
             RwInt32 __RWUNUSED__ size )
{
    RWFUNCTION(RWSTRING("_rwChunkGroupOpen"));
    RWASSERT(95, instance);

    /* Store the globals offset (same for all instances) */
    chunkGroupModule.globalsOffset = offset;

    /* Get on with the initialization */
    RWCHUNKGROUPGLOBAL(groupFList) =
        RwFreeListCreateAndPreallocateSpace(sizeof(RwChunkGroup), _rwChunkGroupFListBlockSize, sizeof(RwUInt32),
        _rwChunkGroupFListPreallocBlocks, &_rwChunkGroupFList, rwID_CHUNKGROUPMODULE | rwMEMHINTDUR_GLOBAL);
    if (!RWCHUNKGROUPGLOBAL(groupFList))
    {
        /* Failure */
        RWRETURN(NULL);
    }

    /* One more module instance */
    chunkGroupModule.numInstances++;

    RWRETURN(instance);
}

void *
_rwChunkGroupClose(void *instance, RwInt32 offset, RwInt32 size)
{
    RWFUNCTION(RWSTRING("_rwChunkGroupClose"));
    RWASSERT(126, instance);

    if (RWCHUNKGROUPGLOBAL(groupFList))
    {
        RwFreeListDestroy(RWCHUNKGROUPGLOBAL(groupFList));
    }

    /* One less module instance */
    chunkGroupModule.numInstances--;

    /* All done */
    RWRETURN(instance);
}
