#ifndef RWDEBUG_H
#define RWDEBUG_H

#include "baerr.h"
#include "batype.h"

enum RwDebugType
{
    rwNADEBUGTYPE = 0,
    rwDEBUGASSERT,
    rwDEBUGERROR,
    rwDEBUGMESSAGE,
    rwDEBUGTRACE,
    rwDEBUGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwDebugType RwDebugType;

typedef void (*RwDebugHandler)(RwDebugType type, const RwChar *string);

#endif
