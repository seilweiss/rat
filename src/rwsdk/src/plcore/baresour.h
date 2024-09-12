#ifndef RWRESOUR_H
#define RWRESOUR_H

#include "balibtyp.h"
#include "batypes.h"

typedef struct RwResEntry RwResEntry;
typedef void (*RwResEntryDestroyNotify)(RwResEntry *resEntry);
struct RwResEntry
{
    RwLLLink link;
    RwInt32 size;
    void *owner;
    RwResEntry **ownerRef;
    RwResEntryDestroyNotify destroyNotify;
};

#endif
