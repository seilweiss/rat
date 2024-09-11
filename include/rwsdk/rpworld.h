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

#ifdef __cplusplus
extern "C" {
#endif

extern RpMaterial* RpMaterialSetTexture(RpMaterial* material, RwTexture* texture);

#ifdef __cplusplus
}
#endif

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
extern "C" {
#endif

#ifdef RWDEBUG
extern RpMorphTarget* RpGeometryGetMorphTarget(const RpGeometry* geometry, RwInt32 morphTarget);
extern RwTexCoords* RpGeometryGetVertexTexCoords(const RpGeometry* geometry, RwTextureCoordinateIndex uvIndex);
extern RwInt32 RpGeometryGetNumVertices(const RpGeometry* geometry);
extern RwV3d* RpMorphTargetGetVertices(const RpMorphTarget* morphTarget);
extern RwV3d* RpMorphTargetGetVertexNormals(const RpMorphTarget* morphTarget);
extern RpMaterial* RpGeometryGetMaterial(const RpGeometry* geometry, RwInt32 matNum);
#endif

#ifdef RWDEBUG
extern RwInt32 RpGeometryGetNumMaterials(const RpGeometry* geometry);
#endif

extern RpGeometry* RpGeometryLock(RpGeometry* geometry, RwInt32 lockMode);
extern RpGeometry* RpGeometryUnlock(RpGeometry* geometry);

#ifdef __cplusplus
}
#endif

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

#define rpLIGHTPOSITIONINGSTART 0x80

enum RpLightType
{
    rpNALIGHTTYPE = 0,
    rpLIGHTDIRECTIONAL,
    rpLIGHTAMBIENT,
    rpLIGHTPOINT = rpLIGHTPOSITIONINGSTART,
    rpLIGHTSPOT,
    rpLIGHTSPOTSOFT,
    rpLIGHTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpLightType RpLightType;

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

typedef struct RpLightTie RpLightTie;
struct RpLightTie
{
    RwLLLink lightInWorldSector;
    RpLight* light;
    RwLLLink WorldSectorInLight;
    RpWorldSector* sect;
};

#define RpLightSetFrameMacro(_light, _frame) (rwObjectHasFrameSetFrame((_light), (_frame)), (_light))
#define RpLightGetFrameMacro(_light) ((RwFrame *)rwObjectGetParent((_light)))

#ifndef RWDEBUG
#define RpLightSetFrame(_light, _frame) RpLightSetFrameMacro(_light, _frame)
#define RpLightGetFrame(_light) RpLightGetFrameMacro(_light)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RWDEBUG
extern RpLight* RpLightSetFrame(RpLight* light, RwFrame* frame);
extern RwFrame* RpLightGetFrame(const RpLight* light);
#endif

extern RpLight* RpLightCreate(RwInt32 type);
extern RwBool RpLightDestroy(RpLight* light);
extern RpLight* RpLightSetRadius(RpLight* light, RwReal radius);
extern RpLight* RpLightSetColor(RpLight* light, const RwRGBAReal* color);
extern RpLight* RpLightSetConeAngle(RpLight* ight, RwReal angle);

#ifdef __cplusplus
}
#endif

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

typedef struct RpTie RpTie;
struct RpTie
{
    RwLLLink lAtomicInWorldSector;
    RpAtomic* apAtom;
    RwLLLink lWorldSectorInAtomic;
    RpWorldSector* worldSector;
};

#define RpAtomicGetGeometryMacro(_atomic) ((_atomic)->geometry)

#define RpAtomicSetRenderCallBackMacro(_atomic, _callback)              \
MACRO_START                                                             \
{                                                                       \
    (_atomic)->renderCallBack = (_callback);                            \
    if (!(_atomic)->renderCallBack)                                     \
    {                                                                   \
        (_atomic)->renderCallBack = AtomicDefaultRenderCallBack;        \
    }                                                                   \
}                                                                       \
MACRO_STOP

#define RpAtomicGetRenderCallBackMacro(_atomic) ((_atomic)->renderCallBack)

#ifndef RWDEBUG
#define RpAtomicGetGeometry(_atomic) RpAtomicGetGeometryMacro(_atomic)
#define RpAtomicSetRenderCallBack(_atomic, _callback) RpAtomicSetRenderCallBackMacro(_atomic, _callback)
#define RpAtomicGetRenderCallBack(_atomic) RpAtomicGetRenderCallBackMacro(_atomic)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern RpAtomic* AtomicDefaultRenderCallBack(RpAtomic* atomic);

#ifdef RWDEBUG
extern RpGeometry* RpAtomicGetGeometry(const RpAtomic* atomic);
extern void RpAtomicSetRenderCallBack(RpAtomic* atomic, RpAtomicCallBackRender callback);
extern RpAtomicCallBackRender RpAtomicGetRenderCallBack(const RpAtomic* atomic);
#endif

#ifdef __cplusplus
}
#endif

enum RwCriterionWorldID
{
    rwID_NAWORLDID = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x00),
    rwID_MATERIALMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x01),
    rwID_MESHMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x02),
    rwID_GEOMETRYMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x03),
    rwID_CLUMPMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x04),
    rwID_LIGHTMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x05),
    rwID_COLLISIONMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x06),
    rwID_WORLDMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x07),
    rwID_RANDOMMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x08),
    rwID_WORLDOBJMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x09),
    rwID_SECTORMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0A),
    rwID_BINWORLDMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0B),
    rwID_WORLDPIPEMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0D),
    rwID_BINMESHPLUGIN = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0E),
    rwID_RXWORLDDEVICEMODULE = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x0F),
    rwID_NATIVEDATAPLUGIN = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x10),
    rwID_VERTEXFMTPLUGIN = MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x11),
    rwCRITERIONWORLDIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCriterionWorldID RwCriterionWorldID;

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

#ifdef __cplusplus
extern "C" {
#endif

extern RwBool RpWorldDestroy(RpWorld* world);
extern RpWorld* RpWorldCreate(RwBBox* boundingBox);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern RpWorld* RpWorldRemoveCamera(RpWorld* world, RwCamera* camera);
extern RpWorld* RpWorldAddCamera(RpWorld* world, RwCamera* camera);
extern RpWorld* RwCameraGetWorld(const RwCamera* camera);

extern RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light);
extern RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light);

#ifdef __cplusplus
}
#endif

#endif
