#ifndef RWBBOX_H
#define RWBBOX_H

#include "batype.h"
#include "balibtyp.h"

typedef struct RwBBox RwBBox;
struct RwBBox
{
    RwV3d sup;
    RwV3d inf;
};

#endif
