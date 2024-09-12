#ifndef RWFRAME_H
#define RWFRAME_H

#include "batype.h"
#include "bamemory.h"
#include "bamatrix.h"
#include "batkreg.h"

struct RwFrame
{
    RwObject object;
    RwLLLink inDirtyListLink;
    RwMatrix modelling;
    RwMatrix ltm;
    RwLinkList objectList;
    struct RwFrame *child;
    struct RwFrame *next;
    struct RwFrame *root;
};
typedef struct RwFrame RWALIGN(RwFrame, rwFRAMEALIGNMENT);

typedef RwFrame *(*RwFrameCallBack)(RwFrame *frame, void *data);

#define RwFrameGetMatrixMacro(_f) (&(_f)->modelling)
#ifndef RWDEBUG
#define RwFrameGetMatrix(_f) RwFrameGetMatrixMacro(_f)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

extern RwFrame *RwFrameTransform(RwFrame *frame, const RwMatrix *m, RwOpCombineType combine);
extern RwFrame *RwFrameOrthoNormalize(RwFrame *frame);

extern RwMatrix *RwFrameGetLTM(RwFrame *frame);

#ifdef RWDEBUG
extern RwMatrix *RwFrameGetMatrix(RwFrame *frame);
#endif

extern RwFrame *RwFrameUpdateObjects(RwFrame *frame);

extern RwFrame *RwFrameCreate(void);
extern RwBool RwFrameDestroy(RwFrame *frame);

#ifdef __cplusplus
}
#endif

#endif
