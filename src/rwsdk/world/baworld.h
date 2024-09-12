#ifndef RWWORLD_H
#define RWWORLD_H

#include <rwcore.h>
#include "baclump.h"
#include "balight.h"
#include "bamatlst.h"
#include "basector.h"

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

typedef RpWorldSector *(*RpWorldSectorCallBackRender)(RpWorldSector *worldSector);

typedef struct RpWorld RpWorld;
struct RpWorld
{
    RwObject object;
    RwUInt32 flags;
    RpWorldRenderOrder renderOrder;
    RpMaterialList matList;
    RpSector *rootSector;
    RwInt32 numTexCoordSets;
    RwInt32 numClumpsInWorld;
    RwLLLink *currentClumpLink;
    RwLinkList clumpList;
    RwLinkList lightList;
    RwLinkList directionalLightList;
    RwV3d worldOrigin;
    RwBBox boundingBox;
    RpWorldSectorCallBackRender renderCallBack;
    RxPipeline *pipeline;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern RwBool RpWorldDestroy(RpWorld *world);
extern RpWorld *RpWorldCreate(RwBBox *boundingBox);

#ifdef __cplusplus
}
#endif

#endif
