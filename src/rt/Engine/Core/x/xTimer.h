#ifndef XTIMER_H
#define XTIMER_H

#include "xBase.h"
#include "xTimerAsset.h"

struct xTimer : xBase
{
    xTimerAsset* tasset;
    U8 state;
    U8 runsInPause;
    U16 flags;
    F32 secondsLeft;
};

struct xScene;

void xTimerInit(void* b, void* tasset);
void xTimerInit(xBase* b, xTimerAsset* tasset);
void xTimerReset(xTimer* t);
void xTimerSave(xTimer* ent, xSerial* s);
void xTimerLoad(xTimer* ent, xSerial* s);
void xTimerEventCB(xBase*, xBase* to, U32 toEvent, const F32* toParam, xBase*, U32);
void xTimerUpdate(xBase* to, xScene* sc, F32 dt);

#endif
