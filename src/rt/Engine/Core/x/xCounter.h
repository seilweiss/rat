#ifndef XCOUNTER_H
#define XCOUNTER_H

#include "xBase.h"
#include "xCounterAsset.h"

typedef struct _xCounter : xBase
{
    xCounterAsset* asset;
    S16 count;
    U8 state;
    U8 pad;
#ifdef DEBUGRELEASE
    char stats[72];
#endif
} xCounter;

void xCounterInit();
void xCounterInit(void* b, void* asset);
void xCounterInit(xBase* b, xCounterAsset* asset);
void xCounterReset(xBase* b);
void xCounterSave(xCounter* ent, xSerial* s);
void xCounterLoad(xCounter* ent, xSerial* s);
void xCounterEventCB(xBase*, xBase* to, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32);

#endif
