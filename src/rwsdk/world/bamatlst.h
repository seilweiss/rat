#ifndef RWMATLST_H
#define RWMATLST_H

#include <rwcore.h>
#include "bamateri.h"

typedef struct RpMaterialList RpMaterialList;
struct RpMaterialList
{
    RpMaterial **materials;
    RwInt32 numMaterials;
    RwInt32 space;
};

#endif
