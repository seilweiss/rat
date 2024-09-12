#ifndef PIP2MODEL_H
#define PIP2MODEL_H

#include "batypes.h"
#include "bacolor.h"
#include "drvmodel.h"

#define RXHEAPPLATFORMDEFAULTSIZE  (1 << 12) /* 4k */

typedef struct RxObjSpace3DVertex RxObjSpace3DVertex;
struct RxObjSpace3DVertex
{
    RwReal x;
    RwReal y;
    RwReal z;
    RwReal nx;
    RwReal ny;
    RwReal nz;
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
    RwReal u;
    RwReal v;
};

typedef RxObjSpace3DVertex RxObjSpace3DLitVertex;

typedef RxObjSpace3DLitVertex RwIm3DVertex;

typedef RwIm2DVertex RxScrSpace2DVertex;

#define RwIm3DVertexSetPos(_vert, _imx, _imy, _imz)                                               \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->x = _imx;                                                                            \
    (_vert)->y = _imy;                                                                            \
    (_vert)->z = _imz;                                                                            \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetNormal(_vert, _imx, _imy, _imz)                                            \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->nx = _imx;                                                                           \
    (_vert)->ny = _imy;                                                                           \
    (_vert)->nz = _imz;                                                                           \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetRGBA(_vert, _r, _g, _b, _a)                                                \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->r = _r;                                                                              \
    (_vert)->g = _g;                                                                              \
    (_vert)->b = _b;                                                                              \
    (_vert)->a = _a;                                                                              \
}                                                                                                 \
MACRO_STOP

#define RwIm3DVertexSetUV(_vert, _u, _v)                                                          \
MACRO_START                                                                                       \
{                                                                                                 \
    (_vert)->u = _u;                                                                              \
    (_vert)->v = _v;                                                                              \
}                                                                                                 \
MACRO_STOP

#endif
