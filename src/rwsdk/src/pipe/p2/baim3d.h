#ifndef BAIM3D_H
#define BAIM3D_H

#include "batypes.h"
#include "baimmedi.h"
#include "bamatrix.h"
#include "drvmodel.h"

#include "p2core.h"
#include "pip2model.h"
#include "p2stdcls.h"
#include "p2renderstate.h"

enum RwIm3DTransformFlags
{
    rwIM3D_VERTEXUV = 1,
    rwIM3D_ALLOPAQUE = 2,
    rwIM3D_NOCLIP = 4,
    rwIM3D_VERTEXXYZ = 8,
    rwIM3D_VERTEXRGBA = 16,
    rwIM3DTRANSFORMFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwIm3DTransformFlags RwIm3DTransformFlags;

#ifdef __cplusplus
extern "C"
{
#endif

extern void *RwIm3DTransform(RwIm3DVertex *pVerts, RwUInt32 numVerts, RwMatrix *ltm, RwUInt32 flags);
extern RwBool RwIm3DEnd(void);
extern RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType);

#ifdef __cplusplus
}
#endif

#endif
