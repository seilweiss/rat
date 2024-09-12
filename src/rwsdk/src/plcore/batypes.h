#ifndef RWTYPES_H
#define RWTYPES_H

#include <stdlib.h>
#include <stddef.h>
#include "ostypes.h"

#include "rwversion.h"

#if (!defined(RWFORCEENUMSIZEINT))
#define RWFORCEENUMSIZEINT ((RwInt32)((~((RwUInt32)0))>>1))
#endif

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

typedef struct RwV2d RwV2d;
struct RwV2d
{
    RwReal x;
    RwReal y;
};

typedef struct RwV3d RwV3d;
struct RwV3d
{
    RwReal x;
    RwReal y;
    RwReal z;
};

typedef struct RwRect RwRect;
struct RwRect
{
    RwInt32 x;
    RwInt32 y;
    RwInt32 w;
    RwInt32 h;
};

typedef struct RwSphere RwSphere;
struct RwSphere
{
    RwV3d center;
    RwReal radius;
};

#define rwMAXTEXTURECOORDS 8

enum RwTextureCoordinateIndex
{
    rwNARWTEXTURECOORDINATEINDEX = 0,
    rwTEXTURECOORDINATEINDEX0,
    rwTEXTURECOORDINATEINDEX1,
    rwTEXTURECOORDINATEINDEX2,
    rwTEXTURECOORDINATEINDEX3,
    rwTEXTURECOORDINATEINDEX4,
    rwTEXTURECOORDINATEINDEX5,
    rwTEXTURECOORDINATEINDEX6,
    rwTEXTURECOORDINATEINDEX7,
    rwTEXTURECOORDINATEINDEXFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureCoordinateIndex RwTextureCoordinateIndex;

typedef struct RwTexCoords RwTexCoords;
struct RwTexCoords
{
    RwReal u;
    RwReal v;
};

typedef struct RwLLLink RwLLLink;
struct RwLLLink
{
    RwLLLink *next;
    RwLLLink *prev;
};

typedef struct RwLinkList RwLinkList;
struct RwLinkList
{
    RwLLLink link;
};

typedef struct RwSurfaceProperties RwSurfaceProperties;
struct RwSurfaceProperties
{
    RwReal ambient;
    RwReal specular;
    RwReal diffuse;
};

#define RWRGBALONG(r,g,b,a) ((RwUInt32) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

typedef struct RwPlane RwPlane;
struct RwPlane
{
    RwV3d normal;
    RwReal distance;
};

#endif
