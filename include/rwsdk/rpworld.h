#ifndef RPWORLD_H
#define RPWORLD_H

#include <rwcore.h>

typedef struct RpMaterial RpMaterial;
struct RpMaterial
{
    RwTexture* texture;
    RwRGBA color;           
    RxPipeline* pipeline;  
    RwSurfaceProperties surfaceProps;
    RwInt16 refCount;
    RwInt16 pad;
};

typedef struct RpMaterialList RpMaterialList;
struct RpMaterialList
{
    RpMaterial** materials;
    RwInt32 numMaterials;
    RwInt32 space;
};

typedef struct RpMeshHeader RpMeshHeader;
enum RpMeshHeaderFlags
{
    rpMESHHEADERTRISTRIP = 0x0001,
    rpMESHHEADERTRIFAN = 0x0002,
    rpMESHHEADERLINELIST = 0x0004,
    rpMESHHEADERPOLYLINE = 0x0008,
    rpMESHHEADERPOINTLIST = 0x0010,
    rpMESHHEADERPRIMMASK = 0x00FF,
    rpMESHHEADERUNINDEXED = 0x0100,
    rpMESHHEADERFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef struct RpMesh RpMesh;
struct RpMesh
{
    RxVertexIndex* indices;
    RwUInt32 numIndices;
    RpMaterial* material;
};

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
    RpGeometry* parentGeom;
    RwSphere boundingSphere;
    RwV3d* verts;
    RwV3d* normals;
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
    RpTriangle* triangles;
    RwRGBA* preLitLum;
    RwTexCoords* texCoords[rwMAXTEXTURECOORDS];
    RpMeshHeader* mesh;
    RwResEntry* repEntry;
    RpMorphTarget* morphTarget;
};

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
    RpTriangle* triangles;
    RwV3d* vertices;
    RpVertexNormal* normals;
    RwTexCoords* texCoords[rwMAXTEXTURECOORDS];
    RwRGBA* preLitLum;
    RwResEntry* repEntry;
    RwLinkList collAtomicsInWorldSector;
    RwLinkList lightsInWorldSector;
    RwBBox boundingBox;
    RwBBox tightBoundingBox;
    RpMeshHeader* mesh;
    RxPipeline* pipeline;
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

typedef struct RpLight RpLight;
struct RpLight
{
    RwObjectHasFrame object;
    RwReal radius;
    RwRGBAReal color;
    RwReal minusCosAngle; 
    RwLinkList WorldSectorsInLight;
    RwLLLink inWorld;
    RwUInt16 lightFrame;
    RwUInt16 pad;
};

enum RpInterpolatorFlag
{
    rpINTERPOLATORDIRTYINSTANCE = 0x01,
    rpINTERPOLATORDIRTYSPHERE = 0x02,
    rpINTERPOLATORNOFRAMEDIRTY = 0x04,
    rpINTERPOLATORFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpInterpolatorFlag rpInterpolatorFlag;

enum RpAtomicFlag
{
    rpATOMICCOLLISIONTEST = 0x01,
    rpATOMICRENDER = 0x04,
    rpATOMICFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicFlag RpAtomicFlag;

enum RpAtomicSetGeomFlag
{
    rpATOMICSAMEBOUNDINGSPHERE = 0x01,
    rpATOMICSETGEOMFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicSetGeomFlag RpAtomicSetGeomFlag;

enum RpAtomicPrivateFlag
{
    rpATOMICPRIVATEWORLDBOUNDDIRTY = 0x01,
    rpATOMICPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpAtomicPrivateFlag rpAtomicPrivateFlag;

typedef struct RpAtomic RpAtomic;

typedef struct RpInterpolator RpInterpolator;
struct RpInterpolator
{
    RwInt32 flags;
    RwInt16 startMorphTarget;
    RwInt16 endMorphTarget;
    RwReal time;
    RwReal recipTime;
    RwReal position;
};

typedef struct RpClump RpClump;
typedef RpClump*(*RpClumpCallBack)(RpClump* clump, void *data);
struct RpClump
{
    RwObject object;
    RwLinkList atomicList;
    RwLinkList lightList;
    RwLinkList cameraList;
    RwLLLink inWorldLink;
    RpClumpCallBack callback;
};

typedef RpAtomic*(*RpAtomicCallBackRender)(RpAtomic* atomic);
struct RpAtomic
{
    RwObjectHasFrame object;
    RwResEntry* repEntry;
    RpGeometry* geometry;
    RwSphere boundingSphere;
    RwSphere worldBoundingSphere;
    RpClump* clump;
    RwLLLink inClumpLink;
    RpAtomicCallBackRender renderCallBack;
    RpInterpolator interpolator;
    RwUInt16 renderFrame;
    RwUInt16 pad;
    RwLinkList llWorldSectorsInAtomic;
    RxPipeline* pipeline;
};

enum RpWorldRenderOrder
{
    rpWORLDRENDERNARENDERORDER = 0,
    rpWORLDRENDERFRONT2BACK,
    rpWORLDRENDERBACK2FRONT,
    rpWORLDRENDERORDERFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpWorldRenderOrder RpWorldRenderOrder;

typedef RpWorldSector*(*RpWorldSectorCallBackRender)(RpWorldSector* worldSector);

typedef struct RpWorld RpWorld;
struct RpWorld
{
    RwObject object;
    RwUInt32 flags;
    RpWorldRenderOrder renderOrder;
    RpMaterialList matList;
    RpSector* rootSector;
    RwInt32 numTexCoordSets;
    RwInt32 numClumpsInWorld;
    RwLLLink* currentClumpLink;
    RwLinkList clumpList;
    RwLinkList lightList;
    RwLinkList directionalLightList;
    RwV3d worldOrigin;
    RwBBox boundingBox;
    RpWorldSectorCallBackRender renderCallBack;
    RxPipeline* pipeline;
};

#endif
