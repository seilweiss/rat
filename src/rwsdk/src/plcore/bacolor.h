#ifndef RWCOLOR_H
#define RWCOLOR_H

#include "batypes.h"

typedef struct RwRGBAReal RwRGBAReal;
struct RwRGBAReal
{
    RwReal red;
    RwReal green;
    RwReal blue;
    RwReal alpha;
};

typedef struct RwRGBA RwRGBA;
struct RwRGBA
{
    RwUInt8 red;
    RwUInt8 green;
    RwUInt8 blue;
    RwUInt8 alpha;
};

#endif
