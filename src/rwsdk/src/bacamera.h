#ifndef RWCAMERA_H
#define RWCAMERA_H

#include "bamemory.h"
#include "batypehf.h"
#include "bamatrix.h"
#include "baraster.h"
#include "babbox.h"
#include "baframe.h"
#include "bacolor.h"

#define RwCameraGetViewOffsetMacro(_camera) (&((_camera)->viewOffset))
#define RwCameraSetRasterMacro(_camera, _raster) (((_camera)->frameBuffer = (_raster)), (_camera))
#define RwCameraGetRasterMacro(_camera) ((_camera)->frameBuffer)
#define RwCameraSetZRasterMacro(_camera, _raster) (((_camera)->zBuffer = (_raster)), (_camera))
#define RwCameraGetZRasterMacro(_camera) ((_camera)->zBuffer)
#define RwCameraGetNearClipPlaneMacro(_camera) ((_camera)->nearPlane)
#define RwCameraGetFarClipPlaneMacro(_camera) ((_camera)->farPlane)
#define RwCameraSetFogDistanceMacro(_camera, _distance) (((_camera)->fogPlane = (_distance)), (_camera))
#define RwCameraGetFogDistanceMacro(_camera) ((_camera)->fogPlane)
#define RwCameraGetCurrentCameraMacro() ((RwCamera*)RWSRCGLOBAL(curCamera))
#define RwCameraGetProjectionMacro(_camera) ((_camera)->projectionType)
#define RwCameraGetViewWindowMacro(_camera) (&((_camera)->viewWindow))
#define RwCameraGetViewMatrixMacro(_camera) (&((_camera)->viewMatrix))
#define RwCameraSetFrameMacro(_camera, _frame) (_rwObjectHasFrameSetFrame((_camera), (_frame)), (_camera))
#define RwCameraGetFrameMacro(_camera) ((RwFrame *)rwObjectGetParent((_camera)))

#ifndef RWDEBUG
#define RwCameraGetViewOffset(_camera) RwCameraGetViewOffsetMacro(_camera)
#define RwCameraSetRaster(_camera, _raster) RwCameraSetRasterMacro(_camera, _raster)
#define RwCameraGetRaster(_camera) RwCameraGetRasterMacro(_camera)
#define RwCameraSetZRaster(_camera, _raster) RwCameraSetZRasterMacro(_camera, _raster)
#define RwCameraGetZRaster(_camera) RwCameraGetZRasterMacro(_camera)
#define RwCameraGetNearClipPlane(_camera) RwCameraGetNearClipPlaneMacro(_camera)
#define RwCameraGetFarClipPlane(_camera) RwCameraGetFarClipPlaneMacro(_camera)
#define RwCameraSetFogDistance(_camera, _distance) RwCameraSetFogDistanceMacro(_camera, _distance)
#define RwCameraGetFogDistance(_camera) RwCameraGetFogDistanceMacro(_camera)
#define RwCameraGetCurrentCamera() RwCameraGetCurrentCameraMacro()
#define RwCameraGetProjection(_camera) RwCameraGetProjectionMacro(_camera)
#define RwCameraGetViewWindow(_camera) RwCameraGetViewWindowMacro(_camera)
#define RwCameraGetViewMatrix(_camera) RwCameraGetViewMatrixMacro(_camera)
#define RwCameraSetFrame(_camera, _frame) RwCameraSetFrameMacro(_camera, _frame)
#define RwCameraGetFrame(_camera) RwCameraGetFrameMacro(_camera)
#endif

enum RwCameraClearMode
{
    rwCAMERACLEARIMAGE = 0x1,
    rwCAMERACLEARZ = 0x2,
    rwCAMERACLEARSTENCIL = 0x4,
    rwCAMERACLEARMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraClearMode RwCameraClearMode;

enum RwCameraProjection
{
    rwNACAMERAPROJECTION = 0,
    rwPERSPECTIVE = 1,
    rwPARALLEL = 2,
    rwCAMERAPROJECTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraProjection RwCameraProjection;

typedef struct RwCamera RWALIGN(RwCamera, rwMATRIXALIGNMENT);

typedef RwCamera *(*RwCameraBeginUpdateFunc)(RwCamera *camera);
typedef RwCamera *(*RwCameraEndUpdateFunc)(RwCamera *camera);

typedef struct RwFrustumPlane RwFrustumPlane;
struct RwFrustumPlane
{
    RwPlane plane;
    RwUInt8 closestX;
    RwUInt8 closestY;
    RwUInt8 closestZ;
    RwUInt8 pad;
};

struct RwCamera
{
    RwObjectHasFrame object;
    RwCameraProjection projectionType;
    RwCameraBeginUpdateFunc beginUpdate;
    RwCameraEndUpdateFunc endUpdate;
    RwMatrix viewMatrix;
    RwRaster *frameBuffer;
    RwRaster *zBuffer;
    RwV2d viewWindow;
    RwV2d recipViewWindow;
    RwV2d viewOffset;
    RwReal nearPlane;
    RwReal farPlane;
    RwReal fogPlane;
    RwReal zScale;
    RwReal zShift;
    RwFrustumPlane frustumPlanes[6];
    RwBBox frustumBoundBox;
    RwV3d frustumCorners[8];
};

#ifdef __cplusplus
extern "C"
{
#endif

extern RwCamera *RwCameraBeginUpdate(RwCamera *camera);
extern RwCamera *RwCameraEndUpdate(RwCamera *camera);
extern RwCamera *RwCameraClear(RwCamera *camera, RwRGBA *colour, RwInt32 clearMode);
extern RwCamera *RwCameraShowRaster(RwCamera *camera, void *pDev, RwUInt32 flags);
extern RwBool RwCameraDestroy(RwCamera *camera);
extern RwCamera *RwCameraCreate(void);
extern RwCamera *RwCameraSetViewOffset(RwCamera *camera, const RwV2d *offset);
extern RwCamera *RwCameraSetViewWindow(RwCamera *camera, const RwV2d *viewWindow);
extern RwCamera *RwCameraSetProjection(RwCamera *camera, RwCameraProjection projection);
extern RwCamera *RwCameraSetNearClipPlane(RwCamera *camera, RwReal nearClip);
extern RwCamera *RwCameraSetFarClipPlane(RwCamera *camera, RwReal farClip);
extern RwInt32 RwCameraGetPluginOffset(RwUInt32 pluginID);

#ifdef RWDEBUG
extern const RwV2d *RwCameraGetViewOffset(const RwCamera *camera);
extern RwCamera *RwCameraSetRaster(RwCamera *camera, RwRaster *raster);
extern RwRaster *RwCameraGetRaster(const RwCamera *camera);
extern RwCamera *RwCameraSetZRaster(RwCamera *camera, RwRaster *zRaster);
extern RwRaster *RwCameraGetZRaster(const RwCamera *camera);
extern RwReal RwCameraGetNearClipPlane(const RwCamera *camera);
extern RwReal RwCameraGetFarClipPlane(const RwCamera *camera);
extern RwCamera *RwCameraSetFogDistance(RwCamera *camera, RwReal fogDistance);
extern RwReal RwCameraGetFogDistance(const RwCamera *camera);
extern RwCamera *RwCameraGetCurrentCamera(void);
extern RwCameraProjection RwCameraGetProjection(const RwCamera *camera);
extern const RwV2d *RwCameraGetViewWindow(const RwCamera *camera);
extern RwMatrix *RwCameraGetViewMatrix(RwCamera *camera);
extern RwCamera *RwCameraSetFrame(RwCamera *camera, RwFrame *frame);
extern RwFrame *RwCameraGetFrame(const RwCamera *camera);
#endif

#ifdef __cplusplus
}
#endif

#endif
