#ifndef RWTYPEHF_H
#define RWTYPEHF_H

#include "batype.h"
#include "baframe.h"

typedef struct RwObjectHasFrame RwObjectHasFrame;
typedef RwObjectHasFrame *(*RwObjectHasFrameSyncFunction)(RwObjectHasFrame *object);
struct RwObjectHasFrame
{
    RwObject object;
    RwLLLink lFrame;
    RwObjectHasFrameSyncFunction sync;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern void _rwObjectHasFrameSetFrame(void *object, RwFrame *frame);

#ifdef __cplusplus
}
#endif

#define rwObjectHasFrameSetFrame(object, frame) _rwObjectHasFrameSetFrame(object, frame)

#endif
