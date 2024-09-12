#ifndef RWTEXTUR_H
#define RWTEXTUR_H

#include "batype.h"
#include "bamemory.h"
#include "baraster.h"
#include "baimmedi.h"
#include "baimage.h"

#define rwTEXTUREBASENAMELENGTH 32

#define rwTEXTUREFILTERMODEMASK 0x000000FF
#define rwTEXTUREADDRESSINGUMASK 0x00000F00
#define rwTEXTUREADDRESSINGVMASK 0x0000F000
#define rwTEXTUREADDRESSINGMASK (rwTEXTUREADDRESSINGUMASK | rwTEXTUREADDRESSINGVMASK)

typedef struct RwTexDictionary RwTexDictionary;
struct RwTexDictionary
{
    RwObject object;
    RwLinkList texturesInDict;
    RwLLLink lInInstance;
};

typedef struct RwTexture RwTexture;
struct RwTexture
{
    RwRaster *raster;
    RwTexDictionary *dict; 
    RwLLLink lInDictionary;
    RwChar name[rwTEXTUREBASENAMELENGTH];
    RwChar mask[rwTEXTUREBASENAMELENGTH];
    RwUInt32 filterAddressing;
    RwInt32 refCount;
};

#define RwTextureGetRasterMacro(_tex) ((_tex)->raster)

#define RwTextureSetFilterModeMacro(_tex, _filtering)                       \
    (((_tex)->filterAddressing =                                            \
      ((_tex)->filterAddressing & ~rwTEXTUREFILTERMODEMASK) |               \
      (((RwUInt32)(_filtering)) &  rwTEXTUREFILTERMODEMASK)),               \
     (_tex))

#ifndef RWDEBUG
#define RwTextureGetRaster(_tex) RwTextureGetRasterMacro(_tex)
#define RwTextureSetFilterMode(_tex, _filtering) RwTextureSetFilterModeMacro(_tex, _filtering)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

extern RwTexture *RwTextureCreate(RwRaster *raster);
extern RwBool RwTextureDestroy(RwTexture *texture);

#ifdef RWDEBUG
extern RwRaster *RwTextureGetRaster(const RwTexture *texture);
extern RwTexture *RwTextureSetFilterMode(RwTexture *texture, RwTextureFilterMode filtering);
#endif

#ifdef __cplusplus
}
#endif

#endif
