#ifndef XMATH3_H
#define XMATH3_H

#include "xVec3.h"

struct xMat3x3
{
    xVec3 right;
    S32 flags;
    xVec3 up;
    U32 pad1;
    xVec3 at;
    U32 pad2;
};

struct xMat4x3 : xMat3x3
{
    xVec3 pos;
    U32 pad3;
};

extern xMat4x3 g_I3;

inline void xMat3x3Copy(xMat3x3* o, const xMat3x3* m)
{
    *o = *m;
}

inline void xMat3x3Identity(xMat3x3* m)
{
    xMat3x3Copy(m, &g_I3);
}

#endif