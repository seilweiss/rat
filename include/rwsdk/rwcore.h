#ifndef RWCORE_H
#define RWCORE_H

#define rwBIGENDIAN

typedef long RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;
typedef char RwChar;
typedef float RwReal;
typedef RwInt32 RwBool;

#ifndef MACRO_START
#define MACRO_START do
#endif

#ifndef MACRO_STOP
#define MACRO_STOP while(0)
#endif

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE !FALSE

typedef struct RwV3d RwV3d;
struct RwV3d
{
    RwReal x;
    RwReal y;
    RwReal z;
};

typedef struct RwRGBA RwRGBA;
struct RwRGBA
{
    RwUInt8 red;
    RwUInt8 green;
    RwUInt8 blue;
    RwUInt8 alpha;
};

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

#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)           \
MACRO_START                                                             \
{                                                                       \
    ((vert)->r = (red));                                                \
    ((vert)->g = (green));                                              \
    ((vert)->b = (blue));                                               \
    ((vert)->a = (alpha));                                              \
}                                                                       \
MACRO_STOP


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
typedef RxObjSpace3DVertex RwIm3DVertex;

#endif
