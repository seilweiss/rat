#ifndef RWMATERI_H
#define RWMATERI_H

#include <rwcore.h>

typedef struct RpMaterial RpMaterial;
struct RpMaterial
{
    RwTexture *texture;
    RwRGBA color;           
    RxPipeline *pipeline;  
    RwSurfaceProperties surfaceProps;
    RwInt16 refCount;
    RwInt16 pad;
};

#ifdef __cplusplus
extern "C"
{
#endif

extern RpMaterial *RpMaterialSetTexture(RpMaterial *material, RwTexture *texture);

#ifdef __cplusplus
}
#endif

#endif
