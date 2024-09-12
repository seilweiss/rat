#ifndef RWRASTER_H
#define RWRASTER_H

#include "bamemory.h"
#include "batkreg.h"

enum RwRasterLockMode
{
    rwRASTERLOCKWRITE = 0x01,
    rwRASTERLOCKREAD = 0x02,
    rwRASTERLOCKNOFETCH = 0x04,
    rwRASTERLOCKRAW = 0x08,
    rwRASTERLOCKMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
#define rwRASTERLOCKREADWRITE (rwRASTERLOCKREAD|rwRASTERLOCKWRITE)
typedef enum RwRasterLockMode RwRasterLockMode;

enum RwRasterFlipMode
{
    rwRASTERFLIPDONTWAIT = 0,
    rwRASTERFLIPWAITVSYNC = 1,
    rwRASTERFLIPMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFlipMode RwRasterFlipMode;

enum RwRasterType
{
    rwRASTERTYPENORMAL = 0x00,
    rwRASTERTYPEZBUFFER = 0x01,
    rwRASTERTYPECAMERA = 0x02,
    rwRASTERTYPETEXTURE = 0x04,
    rwRASTERTYPECAMERATEXTURE = 0x05,
    rwRASTERTYPEMASK = 0x07,
    rwRASTERPALETTEVOLATILE = 0x40,
    rwRASTERDONTALLOCATE = 0x80,
    rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterType RwRasterType;

enum RwRasterFormat
{
    rwRASTERFORMATDEFAULT = 0x0000,
    rwRASTERFORMAT1555 = 0x0100,
    rwRASTERFORMAT565 = 0x0200,
    rwRASTERFORMAT4444 = 0x0300,
    rwRASTERFORMATLUM8 = 0x0400,
    rwRASTERFORMAT8888 = 0x0500,
    rwRASTERFORMAT888 = 0x0600,
    rwRASTERFORMAT16 = 0x0700,
    rwRASTERFORMAT24 = 0x0800,
    rwRASTERFORMAT32 = 0x0900,
    rwRASTERFORMAT555 = 0x0a00,
    rwRASTERFORMATAUTOMIPMAP = 0x1000,
    rwRASTERFORMATPAL8 = 0x2000,
    rwRASTERFORMATPAL4 = 0x4000,
    rwRASTERFORMATMIPMAP = 0x8000,
    rwRASTERFORMATPIXELFORMATMASK = 0x0f00,
    rwRASTERFORMATMASK = 0xff00,
    rwRASTERFORMATFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterFormat RwRasterFormat;

enum RwRasterPrivateFlag
{
    rwRASTERGAMMACORRECTED = 0x01,
    rwRASTERPIXELLOCKEDREAD = 0x02,
    rwRASTERPIXELLOCKEDWRITE = 0x04,
    rwRASTERPALETTELOCKEDREAD = 0x08,
    rwRASTERPALETTELOCKEDWRITE = 0x10,
    rwRASTERPIXELLOCKEDRAW = 0x20,
    rwRASTERPRIVATEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterPrivateFlag RwRasterPrivateFlag;

#define rwRASTERPIXELLOCKED (rwRASTERPIXELLOCKEDREAD | rwRASTERPIXELLOCKEDWRITE)
#define rwRASTERPALETTELOCKED (rwRASTERPALETTELOCKEDREAD | rwRASTERPALETTELOCKEDWRITE)
#define rwRASTERLOCKED (rwRASTERPIXELLOCKED|rwRASTERPALETTELOCKED)

typedef struct RwRaster RwRaster;
struct RwRaster
{
    RwRaster *parent;
    RwUInt8 *cpPixels;
    RwUInt8 *palette;
    RwInt32 width, height, depth;
    RwInt32 stride;
    RwInt16 nOffsetX, nOffsetY;
    RwUInt8 cType;
    RwUInt8 cFlags;
    RwUInt8 privateFlags;
    RwUInt8 cFormat;
    RwUInt8 *originalPixels;
    RwInt32 originalWidth;
    RwInt32 originalHeight;
    RwInt32 originalStride;
};

#define RwRasterGetWidthMacro(_raster) ((_raster)->width)
#define RwRasterGetHeightMacro(_raster) ((_raster)->height)
#define RwRasterGetStrideMacro(_raster) ((_raster)->stride)
#define RwRasterGetDepthMacro(_raster) ((_raster)->depth)
#define RwRasterGetFormatMacro(_raster) ((((_raster)->cFormat) & (rwRASTERFORMATMASK >> 8)) << 8)
#define RwRasterGetTypeMacro(_raster) (((_raster)->cType) & rwRASTERTYPEMASK)
#define RwRasterGetParentMacro(_raster) ((_raster)->parent)

#ifndef RWDEBUG
#define RwRasterGetWidth(_raster) RwRasterGetWidthMacro(_raster)
#define RwRasterGetHeight(_raster) RwRasterGetHeightMacro(_raster)
#define RwRasterGetStride(_raster) RwRasterGetStrideMacro(_raster)
#define RwRasterGetDepth(_raster) RwRasterGetDepthMacro(_raster)
#define RwRasterGetFormat(_raster) RwRasterGetFormatMacro(_raster)
#define RwRasterGetType(_raster) RwRasterGetTypeMacro(_raster)
#define RwRasterGetParent(_raster) RwRasterGetParentMacro(_raster)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

extern RwRaster *RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
extern RwBool RwRasterDestroy(RwRaster *raster);

#ifdef RWDEBUG
extern RwInt32 RwRasterGetWidth(const RwRaster *raster);
extern RwInt32 RwRasterGetHeight(const RwRaster *raster);
extern RwInt32 RwRasterGetStride(const RwRaster *raster);
extern RwInt32 RwRasterGetDepth(const RwRaster *raster);
extern RwInt32 RwRasterGetFormat(const RwRaster *raster);
extern RwInt32 RwRasterGetType(const RwRaster *raster);
extern RwRaster *RwRasterGetParent(const RwRaster *raster);
#endif

extern RwInt32 RwRasterGetNumLevels(RwRaster *raster);
extern RwRaster *RwRasterSubRaster(RwRaster *subRaster, RwRaster *raster, RwRect *rect);
extern RwRaster *RwRasterRenderFast(RwRaster *raster, RwInt32 x, RwInt32 y);
extern RwRaster *RwRasterRender(RwRaster *raster, RwInt32 x, RwInt32 y);
extern RwRaster *RwRasterPushContext(RwRaster *raster);
extern RwRaster *RwRasterPopContext(void);
extern RwBool RwRasterClear(RwInt32 pixelValue);
extern RwRaster *RwRasterShowRaster(RwRaster *raster, void *dev, RwUInt32 flags);
extern RwUInt8 *RwRasterLock(RwRaster *raster, RwUInt8 level, RwInt32 lockMode);
extern RwRaster *RwRasterUnlock(RwRaster *raster);
extern RwUInt8 *RwRasterLockPalette(RwRaster *raster, RwInt32 lockMode);
extern RwRaster *RwRasterUnlockPalette(RwRaster *raster);
extern RwInt32 RwRasterRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB, RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);

#ifdef __cplusplus
}
#endif

#endif
