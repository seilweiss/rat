#ifndef RWMESH_H
#define RWMESH_H

#include <rwcore.h>
#include "bamateri.h"
#include "bamatlst.h"

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
typedef enum RpMeshHeaderFlags RpMeshHeaderFlags;

typedef struct RpMesh RpMesh;
struct RpMesh
{
    RxVertexIndex *indices;
    RwUInt32 numIndices;
    RpMaterial *material;
};

struct RpMeshHeader
{
    RwUInt32 flags;
    RwUInt16 numMeshes;
    RwUInt16 serialNum;
    RwUInt32 totalIndicesInMesh;
    RwUInt32 firstMeshOffset;
};

#endif
