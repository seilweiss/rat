#ifndef RWWOROBJ_H
#define RWWOROBJ_H

#include <rwcore.h>
#include "basector.h"
#include "baclump.h"
#include "balight.h"
#include "baworld.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern RpWorld *RpWorldRemoveCamera(RpWorld *world, RwCamera *camera);
extern RpWorld *RpWorldAddCamera(RpWorld *world, RwCamera *camera);
extern RpWorld *RwCameraGetWorld(const RwCamera *camera);

extern RpWorld *RpWorldAddLight(RpWorld *world, RpLight *light);
extern RpWorld *RpWorldRemoveLight(RpWorld *world, RpLight *light);

#ifdef __cplusplus
}
#endif

#endif
