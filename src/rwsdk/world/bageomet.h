#ifndef RWGEOMET_H
#define RWGEOMET_H

#include <rwcore.h>
#include "bamateri.h"
#include "bamatlst.h"
#include "bamesh.h"

enum RpGeometryFlag
{
    rpGEOMETRYTRISTRIP = 0x00000001,
    rpGEOMETRYPOSITIONS = 0x00000002,
    rpGEOMETRYTEXTURED = 0x00000004,
    rpGEOMETRYPRELIT = 0x00000008,
    rpGEOMETRYNORMALS = 0x00000010,
    rpGEOMETRYLIGHT = 0x00000020,
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040,
    rpGEOMETRYTEXTURED2 = 0x00000080,
    rpGEOMETRYNATIVE = 0x01000000,
    rpGEOMETRYNATIVEINSTANCE = 0x02000000,
    rpGEOMETRYFLAGSMASK = 0x000000FF,
    rpGEOMETRYNATIVEFLAGSMASK = 0x0F000000,
    rpGEOMETRYFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryFlag RpGeometryFlag;

#define rpGEOMETRYTEXCOORDSETS(_num) ((_num & 0xff) << 16)

enum RpGeometryLockMode
{
    rpGEOMETRYLOCKPOLYGONS = 0x01,
    rpGEOMETRYLOCKVERTICES = 0x02,
    rpGEOMETRYLOCKNORMALS = 0x04,
    rpGEOMETRYLOCKPRELIGHT = 0x08,
    rpGEOMETRYLOCKTEXCOORDS = 0x10,
    rpGEOMETRYLOCKTEXCOORDS1 = 0x10,
    rpGEOMETRYLOCKTEXCOORDS2 = 0x20,
    rpGEOMETRYLOCKTEXCOORDS3 = 0x40,
    rpGEOMETRYLOCKTEXCOORDS4 = 0x80,
    rpGEOMETRYLOCKTEXCOORDS5 = 0x0100,
    rpGEOMETRYLOCKTEXCOORDS6 = 0x0200,
    rpGEOMETRYLOCKTEXCOORDS7 = 0x0400,
    rpGEOMETRYLOCKTEXCOORDS8 = 0x0800,
    rpGEOMETRYLOCKTEXCOORDSALL = 0x0ff0,
    rpGEOMETRYLOCKALL = 0x0fff,
    rpGEOMETRYLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpGeometryLockMode RpGeometryLockMode;

#define rpGEOMETRYLOCKTEXCOORDSIDX(_idx) (rpGEOMETRYLOCKTEXCOORDS1 << (_idx))

typedef struct RpGeometry RpGeometry;

typedef struct RpMorphTarget RpMorphTarget;
struct RpMorphTarget
{
    RpGeometry *parentGeom;
    RwSphere boundingSphere;
    RwV3d *verts;
    RwV3d *normals;
};

typedef struct RpTriangle RpTriangle;
struct RpTriangle
{
    RwUInt16 vertIndex[3];
    RwUInt16 matIndex;
};

struct RpGeometry
{
    RwObject object;
    RwUInt32 flags;
    RwUInt16 lockedSinceLastInst;
    RwInt16 refCount;
    RwInt32 numTriangles;
    RwInt32 numVertices;
    RwInt32 numMorphTargets;
    RwInt32 numTexCoordSets;
    RpMaterialList matList;
    RpTriangle *triangles;
    RwRGBA *preLitLum;
    RwTexCoords *texCoords[rwMAXTEXTURECOORDS];
    RpMeshHeader *mesh;
    RwResEntry *repEntry;
    RpMorphTarget *morphTarget;
};

#define RpGeometryGetMorphTargetMacro(_geometry, _index) (&((_geometry)->morphTarget[(_index)]))
#define RpGeometryGetVertexTexCoordsMacro(_geometry, _uvIndex) ((_geometry)->texCoords[(_uvIndex) - 1])
#define RpGeometryGetNumVerticesMacro(_geometry) ((_geometry)->numVertices)
#define RpMorphTargetGetVerticesMacro(_mt) ((_mt)->verts)
#define RpMorphTargetGetVertexNormalsMacro(_mt) ((_mt)->normals)
#define RpGeometryGetMaterialMacro(_geometry, _num) (((_geometry)->matList.materials)[(_num)])
#define RpGeometryGetNumMaterialsMacro(_geometry) ((_geometry)->matList.numMaterials)

#ifndef RWDEBUG
#define RpGeometryGetMorphTarget(_geometry, _index) RpGeometryGetMorphTargetMacro(_geometry, _index)
#define RpGeometryGetVertexTexCoords(_geometry, _uvIndex) RpGeometryGetVertexTexCoordsMacro(_geometry, _uvIndex)
#define RpGeometryGetNumVertices(_geometry) RpGeometryGetNumVerticesMacro(_geometry)
#define RpMorphTargetGetVertices(_mt) RpMorphTargetGetVerticesMacro(_mt)
#define RpMorphTargetGetVertexNormals(_mt) RpMorphTargetGetVertexNormalsMacro(_mt)
#define RpGeometryGetMaterial(_geometry, _num) RpGeometryGetMaterialMacro(_geometry, _num)
#define RpGeometryGetNumMaterials(_geometry) RpGeometryGetNumMaterialsMacro(_geometry)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef RWDEBUG
extern RpMorphTarget *RpGeometryGetMorphTarget(const RpGeometry *geometry, RwInt32 morphTarget);
extern RwTexCoords *RpGeometryGetVertexTexCoords(const RpGeometry *geometry, RwTextureCoordinateIndex uvIndex);
extern RwInt32 RpGeometryGetNumVertices(const RpGeometry *geometry);
extern RwV3d *RpMorphTargetGetVertices(const RpMorphTarget *morphTarget);
extern RwV3d *RpMorphTargetGetVertexNormals(const RpMorphTarget *morphTarget);
extern RpMaterial *RpGeometryGetMaterial(const RpGeometry *geometry, RwInt32 matNum);
#endif

#ifdef RWDEBUG
extern RwInt32 RpGeometryGetNumMaterials(const RpGeometry *geometry);
#endif

extern RpGeometry *RpGeometryLock(RpGeometry *geometry, RwInt32 lockMode);
extern RpGeometry *RpGeometryUnlock(RpGeometry *geometry);

#ifdef __cplusplus
}
#endif

#endif
