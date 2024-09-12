#ifndef P2HEAP_H
#define P2HEAP_H

typedef struct rxHeapFreeBlock rxHeapFreeBlock;
typedef struct rxHeapSuperBlockDescriptor rxHeapSuperBlockDescriptor;
typedef struct RxHeap RxHeap;
typedef struct rxHeapBlockHeader rxHeapBlockHeader;

struct rxHeapFreeBlock
{
    RwUInt32 size;
    rxHeapBlockHeader *ptr;
};

struct rxHeapSuperBlockDescriptor
{
    void *start;
    RwUInt32 size;
    rxHeapSuperBlockDescriptor *next;
};

struct RxHeap
{
    RwUInt32 superBlockSize;
    rxHeapSuperBlockDescriptor *head;
    rxHeapBlockHeader *headBlock;
    rxHeapFreeBlock *freeBlocks;
    RwUInt32 entriesAlloced;
    RwUInt32 entriesUsed;
    RwBool dirty;
};

struct rxHeapBlockHeader
{
    rxHeapBlockHeader *prev;
    rxHeapBlockHeader *next;
    RwUInt32 size;
    rxHeapFreeBlock *freeEntry;
    RwUInt32 pad[4];
};

#endif
