#ifndef XBASE_H
#define XBASE_H

#include "xBaseAsset.h"
#include "xLinkAsset.h"
#include "xDebug.h"

struct xBase;

typedef void(*xBaseEventCallback)(xBase* from, xBase* to, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);

struct xBase
{
    U32 id;
    U8 baseType;
    U8 linkCount;
    U16 baseFlags;
    const xLinkAsset* link;
    xBaseEventCallback eventFunc;
};

// Guessed based on context
#define k_XBASE_IS_ENABLED ((U16)(1 << 0))
#define k_XBASE_IS_PERSISTENT ((U16)(1 << 1))
#define k_XBASE_IS_VALID ((U16)(1 << 2))
#define k_XBASE_IS_VISIBLE_IN_CUTSCENES ((U16)(1 << 3))
#define k_XBASE_RECEIVES_SHADOWS ((U16)(1 << 4))
#define k_XBASE_UNK_0x80 ((U16)(1 << 7))

// Present in assert strings
#define k_XBASE_IS_ENTITY ((U16)(1 << 5))
#define k_XBASE_IS_NPC ((U16)(1 << 8))

struct xSerial;

void xBaseInit(xBase* xb, const xBaseAsset* asset);
void xBaseSetup(xBase* xb);
void xBaseSave(xBase* ent, xSerial* s);
void xBaseLoad(xBase* ent, xSerial* s);
void xBaseReset(xBase* xb, xBaseAsset* asset);

inline void xBaseEnable(xBase* xb)
{
    xb->baseFlags |= k_XBASE_IS_ENABLED;
}

inline void xBaseDisable(xBase* xb)
{
    xb->baseFlags &= (U16)~k_XBASE_IS_ENABLED;
}

inline bool xBaseIsEnabled(const xBase* xb)
{
    return xb->baseFlags & k_XBASE_IS_ENABLED;
}

inline void xBaseValidate(xBase* xb)
{
    xb->baseFlags |= k_XBASE_IS_VALID;
}

inline bool xBaseIsEntity(const xBase* xb)
{
    xASSERT(130, xb != NULL);
    return xb->baseFlags & k_XBASE_IS_ENTITY;
}

#endif
