#ifndef RWLIGHT_H
#define RWLIGHT_H

#include <rwcore.h>
#include "basector.h"

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
    RpLight *light;
    RwLLLink WorldSectorInLight;
    RpWorldSector *sect;
};

#define RpLightSetFrameMacro(_light, _frame) (rwObjectHasFrameSetFrame((_light), (_frame)), (_light))
#define RpLightGetFrameMacro(_light) ((RwFrame *)rwObjectGetParent((_light)))

#ifndef RWDEBUG
#define RpLightSetFrame(_light, _frame) RpLightSetFrameMacro(_light, _frame)
#define RpLightGetFrame(_light) RpLightGetFrameMacro(_light)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef RWDEBUG
extern RpLight *RpLightSetFrame(RpLight *light, RwFrame *frame);
extern RwFrame *RpLightGetFrame(const RpLight *light);
#endif

extern RpLight *RpLightCreate(RwInt32 type);
extern RwBool RpLightDestroy(RpLight *light);
extern RpLight *RpLightSetRadius(RpLight *light, RwReal radius);
extern RpLight *RpLightSetColor(RpLight *light, const RwRGBAReal *color);
extern RpLight *RpLightSetConeAngle(RpLight *ight, RwReal angle);

#ifdef __cplusplus
}
#endif

#endif
