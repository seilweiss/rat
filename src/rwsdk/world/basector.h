#ifndef RWSECTOR_H
#define RWSECTOR_H

#include <rwcore.h>
#include "bamateri.h"
#include "bamatlst.h"
#include "bamesh.h"
#include "bageomet.h"

typedef struct RpVertexNormal RpVertexNormal;
struct RpVertexNormal
{
    RwInt8 x;
    RwInt8 y;
    RwInt8 z;
    RwUInt8 pad;
};

typedef struct RpWorldSector RpWorldSector;
struct RpWorldSector
{
    RwInt32 type;
    RpTriangle *triangles;
    RwV3d *vertices;
    RpVertexNormal *normals;
    RwTexCoords *texCoords[rwMAXTEXTURECOORDS];
    RwRGBA *preLitLum;
    RwResEntry *repEntry;
    RwLinkList collAtomicsInWorldSector;
    RwLinkList lightsInWorldSector;
    RwBBox boundingBox;
    RwBBox tightBoundingBox;
    RpMeshHeader *mesh;
    RxPipeline *pipeline;
    RwUInt16 matListWindowBase;
    RwUInt16 numVertices;
    RwUInt16 numTriangles;
    RwUInt16 pad;
};

typedef struct RpSector RpSector;
struct RpSector
{
    RwInt32 type;
};

#endif
