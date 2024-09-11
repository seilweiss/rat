#ifndef XQUICKCULL_H
#define XQUICKCULL_H

#include "xMath3.h"

struct xQCControl
{
    F32 world_xmin;
    F32 world_ymin;
    F32 world_zmin;
    F32 world_xmax;
    F32 world_ymax;
    F32 world_zmax;
    F32 world_xsz;
    F32 world_ysz;
    F32 world_zsz;
    F32 scale_x;
    F32 scale_y;
    F32 scale_z;
    F32 center_x;
    F32 center_y;
    F32 center_z;
};

struct xQCData
{
    S8 xmin;
    S8 ymin;
    S8 zmin;
    S8 zmin_dup;
    S8 xmax;
    S8 ymax;
    S8 zmax;
    S8 zmax_dup;
    xVec3 min;
    xVec3 max;
};

extern xQCControl xqc_def_ctrl;

struct xBound;

void xQuickCullInit(xQCControl* ctrl, F32 xmin, F32 ymin, F32 zmin, F32 xmax, F32 ymax, F32 zmax);
void xQuickCullInit(xQCControl* ctrl, const xBox* box);
S32 xQuickCullIsects(const xQCData* a, const xQCData* b);
void xQuickCullForBound(xQCControl* ctrl, xQCData* q, const xBound* b);
void xQuickCullForLine(xQCControl* ctrl, xQCData* q, const xLine3* ln);
void xQuickCullForRay(xQCControl* ctrl, xQCData* q, const xRay3* r);
void xQuickCullForSphere(xQCControl* ctrl, xQCData* q, const xSphere* s);
void xQuickCullForBox(xQCControl* ctrl, xQCData* q, const xBox* box);
void xQuickCullForOBB(xQCControl* ctrl, xQCData* q, const xBox* b, const xMat4x3* m);
void xQuickCullForEverything(xQCData* q);

#ifdef DEBUG
void xQuickCullDebugCB();
void xQuickCullDebugUpdate();
void xQuickCullDebugRegister(const xQCData* q);
#endif

#endif
