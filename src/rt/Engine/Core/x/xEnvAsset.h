#ifndef XENVASSET_H
#define XENVASSET_H

#include "xBaseAsset.h"
#include "xVec3.h"

struct xEnvAsset : xBaseAsset
{
    U32 bspAssetID;
    U32 startCameraAssetID;
    U32 climateFlags;
    F32 climateStrengthMin;
    F32 climateStrengthMax;
    U32 bspLightKit;
    U32 objectLightKit;
    U32 flags;
    U32 bspCollisionAssetID;
    U32 bspFXAssetID;
    U32 bspCameraAssetID;
    U32 bspMapperID;
    U32 bspMapperCollisionID;
    U32 bspMapperFXID;
    F32 loldHeight;
    xVec3 minBounds;
    xVec3 maxBounds;
};

#endif
