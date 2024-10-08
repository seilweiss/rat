#ifndef XMATH3_H
#define XMATH3_H

#include "iMath3.h"
#include "xVec3.h"
#include "xDebug.h"

struct xVec4
{
    F32 x, y, z, w;
};

struct xFRect
{
    F32 x, y, w, h;
};

struct xLine3
{
    xVec3 p1;
    xVec3 p2;
};

struct xBox
{
    xVec3 upper;
    xVec3 lower;
};

struct xBBox
{
    xVec3 center;
    xBox box;
};

struct xSphere
{
    xVec3 center;
    F32 r;
};

struct xCylinder
{
    xVec3 center;
    F32 r;
    F32 h;
};

#define XRAY3_USE_MIN (1<<10)
#define XRAY3_USE_MAX (1<<11)

struct xRay3
{
    xVec3 origin;
    xVec3 dir;
    F32 min_t;
    F32 max_t;
    S32 flags;
};

struct xIsect
{
    U32 flags;
    F32 penned;
    F32 contained;
    F32 lapped;
    xVec3 point;
    xVec3 norm;
    F32 dist;
};

struct xMat3x3
{
    xVec3 right;
    S32 flags;
    xVec3 up;
    U32 pad1;
    xVec3 at;
    U32 pad2;
} ALIGN(16);

struct xMat4x3 : xMat3x3
{
    xVec3 pos;
    U32 pad3;
} ALIGN(16);

struct xQuat
{
    xVec3 v;
    F32 s;
};

struct xRot
{
    xVec3 axis;
    F32 angle;
};

class xPlane
{
public:
    xVec3 norm;
    F32 d;
};

extern xMat4x3 g_I3;

void xBoxInitBoundOBB(xBox* o, const xBox* b, const xMat4x3* m);

inline void xMat3x3Copy(xMat3x3* o, const xMat3x3* m)
{
    *o = *m;
}

inline void xMat3x3Identity(xMat3x3* m)
{
    xMat3x3Copy(m, &g_I3);
}

void xMat3x3Rot(xMat3x3* m, const xVec3* a, F32 t);

static inline void xMat3x3RMulVec(xVec3* o, const xMat3x3* m, const xVec3* v)
{
    F32 x = m->right.x * v->x + m->up.x * v->y + m->at.x * v->z;
    F32 y = m->right.y * v->x + m->up.y * v->y + m->at.y * v->z;
    F32 z = m->right.z * v->x + m->up.z * v->y + m->at.z * v->z;
    o->x = x, o->y = y, o->z = z;
}

inline void xMat3x3MulScaleC(xMat3x3* o, const xMat3x3* m, F32 x, F32 y, F32 z)
{
    xASSERT(2996, (o != 0) && (m != 0));
    o->right.assign(m->right.x * x, m->right.y * x, m->right.z * x);
    o->up.assign(m->up.x * y, m->up.y * y, m->up.z * y);
    o->at.assign(m->at.x * z, m->at.y * z, m->at.z * z);
}

inline void xMat3x3MulScale(xMat3x3* o, const xMat3x3* m, xVec3* s)
{
    xASSERT(3021, (o != 0) && (m != 0) && (s != 0));
    return xMat3x3MulScaleC(o, m, s->x, s->y, s->z);
}

void xMat4x3Copy(xMat4x3* o, const xMat4x3* m);

#endif
