#ifndef GCN_DRVMODEL_H
#define GCN_DRVMODEL_H

#include "batypes.h"

#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)
#define RwIm2DVertexSetU(vert, texU, recipz) ((vert)->u = (texU))
#define RwIm2DVertexSetV(vert, texV, recipz) ((vert)->v = (texV))
#define RwIm2DVertexGetU(vert) ((vert)->u)
#define RwIm2DVertexGetV(vert) ((vert)->v)

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)           \
MACRO_START                                                             \
{                                                                       \
    ((vert)->r = (red));                                                \
    ((vert)->g = (green));                                              \
    ((vert)->b = (blue));                                               \
    ((vert)->a = (alpha));                                              \
}                                                                       \
MACRO_STOP

typedef struct rwGameCube2DVertex rwGameCube2DVertex;
struct rwGameCube2DVertex
{
    RwReal x;
    RwReal y;
    RwReal z;
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
    RwReal u;
    RwReal v;
};
typedef rwGameCube2DVertex RwIm2DVertex;

typedef RwUInt16 RxVertexIndex;
typedef RxVertexIndex RwImVertexIndex;

#endif
