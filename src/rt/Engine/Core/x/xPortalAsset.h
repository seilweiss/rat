#ifndef XPORTALASSET_H
#define XPORTALASSET_H

#include "xBaseAsset.h"

struct xPortalAsset : xBaseAsset
{
    U32 assetCameraID;
    U32 assetMarkerID;
    F32 ang;
    U32 sceneID;
};

#endif
