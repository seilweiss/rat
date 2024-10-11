#ifndef DLRENDST_H
#define DLRENDST_H

#include "batypes.h"
#include "baimmedi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void _rwDlRenderStateSetZCompLoc(RwBool zBeforeTex);
extern void RwGameCubeSetAlphaCompare(RwInt32 comp0, RwUInt8 ref0, RwInt32 op, RwInt32 comp1, RwUInt8 ref1);

#ifdef __cplusplus
}
#endif

#endif
