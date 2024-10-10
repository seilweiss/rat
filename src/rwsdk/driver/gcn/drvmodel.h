#ifndef GCN_DRVMODEL_H
#define GCN_DRVMODEL_H

#include "batypes.h"

#define RwIm2DVertexSetScreenX(vert, scrnx) ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny) ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz) ((vert)->z = (scrnz))
#define RwIm2DVertexGetScreenX(vert) ((vert)->x)
#define RwIm2DVertexGetScreenY(vert) ((vert)->y)
#define RwIm2DVertexGetScreenZ(vert) ((vert)->z)
#define RwIm2DVertexSetU(vert, texU, recipz) ((vert)->u = (texU))
#define RwIm2DVertexSetV(vert, texV, recipz) ((vert)->v = (texV))
#define RwIm2DVertexGetU(vert) ((vert)->u)
#define RwIm2DVertexGetV(vert) ((vert)->v)

#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)           \
MACRO_START                                                             \
{                                                                       \
    ((vert)->r = (red));                                                \
    ((vert)->g = (green));                                              \
    ((vert)->b = (blue));                                               \
    ((vert)->a = (alpha));                                              \
}                                                                       \
MACRO_STOP

typedef struct rwGameCube2DVertex rwGameCube2DVertex;
struct rwGameCube2DVertex
{
    RwReal x;
    RwReal y;
    RwReal z;
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
    RwReal u;
    RwReal v;
};
typedef rwGameCube2DVertex RwIm2DVertex;

typedef RwUInt16 RxVertexIndex;
typedef RxVertexIndex RwImVertexIndex;

#define RwV3dTransformPointMacro(_pntsOut, _pntsIn, _matrix)                \
MACRO_START                                                                 \
{                                                                           \
    register RwV3d *__pntsOut = (_pntsOut);                                 \
    register const RwV3d *__pntsIn = (_pntsIn);                             \
    register const RwMatrix *__matrix = (_matrix);                          \
    asm {                                                                   \
        psq_l f8, 0x0(__pntsIn), 0, 0;                                      \
        psq_l f9, 0x8(__pntsIn), 1, 0;                                      \
        psq_l f0, 0x0(__matrix), 0, 0;                                      \
        psq_l f1, 0x8(__matrix), 1, 0;                                      \
        psq_l f6, 0x30(__matrix), 0, 0;                                     \
        psq_l f7, 0x38(__matrix), 1, 0;                                     \
        psq_l f2, 0x10(__matrix), 0, 0;                                     \
        psq_l f3, 0x18(__matrix), 1, 0;                                     \
        ps_madds0 f10, f0, f8, f6;                                          \
        ps_madds0 f11, f1, f8, f7;                                          \
        psq_l f4, 0x20(__matrix), 0, 0;                                     \
        psq_l f5, 0x28(__matrix), 1, 0;                                     \
        ps_madds1 f10, f2, f8, f10;                                         \
        ps_madds1 f11, f3, f8, f11;                                         \
        ps_madds0 f10, f4, f9, f10;                                         \
        ps_madds0 f11, f5, f9, f11;                                         \
        psq_st f10, 0x0(__pntsOut), 0, 0;                                   \
        psq_st f11, 0x8(__pntsOut), 1, 0;                                   \
    }                                                                       \
}                                                                           \
MACRO_STOP

#define RwV3dTransformPointsMacro(_pntsOut, _pntsIn, _count, _matrix)       \
MACRO_START                                                                 \
{                                                                           \
    register RwV3d *__pntsOut = (_pntsOut);                                 \
    register const RwV3d *__pntsIn = (_pntsIn);                             \
    register RwInt32 __count = (_count);                                    \
    register const RwMatrix *__matrix = (_matrix);                          \
    asm {                                                                   \
        mtctr __count;                                                      \
        psq_l f0, 0x0(__matrix), 0, 0;                                      \
        psq_l f1, 0x8(__matrix), 1, 0;                                      \
        addi __pntsOut, __pntsOut, -4;                                      \
        psq_l f6, 0x30(__matrix), 0, 0;                                     \
        psq_l f7, 0x38(__matrix), 1, 0;                                     \
        psq_l f8, 0x0(__pntsIn), 0, 0;                                      \
        psq_lu f9, 0x8(__pntsIn), 1, 0;                                     \
        psq_l f2, 0x10(__matrix), 0, 0;                                     \
        psq_l f3, 0x18(__matrix), 1, 0;                                     \
        psq_l f4, 0x20(__matrix), 0, 0;                                     \
        psq_l f5, 0x28(__matrix), 1, 0;                                     \
    loop:                                                                   \
        ps_madds0 f10, f0, f8, f6;                                          \
        ps_madds0 f11, f1, f8, f7;                                          \
        ps_madds1 f10, f2, f8, f10;                                         \
        ps_madds1 f11, f3, f8, f11;                                         \
        psq_lu f8, 0x4(__pntsIn), 0, 0;                                     \
        ps_madds0 f10, f4, f9, f10;                                         \
        ps_madds0 f11, f5, f9, f11;                                         \
        psq_lu f9, 0x8(__pntsIn), 1, 0;                                     \
        psq_stu f10, 0x4(__pntsOut), 0, 0;                                  \
        psq_stu f11, 0x8(__pntsOut), 1, 0;                                  \
        bdnz loop;                                                          \
    }                                                                       \
}                                                                           \
MACRO_STOP

#define RwV3dTransformVectorMacro(_vecsOut, _vecsIn, _matrix)               \
MACRO_START                                                                 \
{                                                                           \
    register RwV3d *__vecsOut = (_vecsOut);                                 \
    register const RwV3d *__vecsIn = (_vecsIn);                             \
    register const RwMatrix *__matrix = (_matrix);                          \
    asm {                                                                   \
        psq_l f6, 0x0(__vecsIn), 0, 0;                                      \
        psq_l f7, 0x8(__vecsIn), 1, 0;                                      \
        psq_l f0, 0x0(__matrix), 0, 0;                                      \
        psq_l f1, 0x8(__matrix), 1, 0;                                      \
        psq_l f2, 0x10(__matrix), 0, 0;                                     \
        psq_l f3, 0x18(__matrix), 1, 0;                                     \
        ps_muls0 f10, f0, f6;                                               \
        ps_muls0 f11, f1, f6;                                               \
        psq_l f4, 0x20(__matrix), 0, 0;                                     \
        psq_l f5, 0x28(__matrix), 1, 0;                                     \
        ps_madds1 f10, f2, f6, f10;                                         \
        ps_madds1 f11, f3, f6, f11;                                         \
        ps_madds0 f10, f4, f7, f10;                                         \
        ps_madds0 f11, f5, f7, f11;                                         \
        psq_st f10, 0x0(__vecsOut), 0, 0;                                   \
        psq_st f11, 0x8(__vecsOut), 1, 0;                                   \
    }                                                                       \
}                                                                           \
MACRO_STOP

// UNIMPLEMENTED
#define RwV3dTransformVectorsMacro(_vecsOut, _vecsIn, _count, _matrix)      \
MACRO_START                                                                 \
{                                                                           \
}                                                                           \
MACRO_STOP

#define RwMatrixMultiplyMacro(_matrix, _matrixIn1, _matrixIn2)               \
MACRO_START                                                                  \
{                                                                            \
    register RwMatrix *_dst = (_matrix);                                     \
    register const RwMatrix *_matA = (_matrixIn1);                           \
    register const RwMatrix *_matB = (_matrixIn2);                           \
    asm {                                                                    \
        psq_l f8, 0x0(_matB), 0, 0;                                          \
        psq_l f0, 0x0(_matA), 0, 0;                                          \
        psq_l f2, 0x10(_matA), 0, 0;                                         \
        psq_l f4, 0x20(_matA), 0, 0;                                         \
        ps_muls0 f12, f8, f0;                                                \
        psq_l f6, 0x30(_matA), 0, 0;                                         \
        ps_muls0 f13, f8, f2;                                                \
        psq_l f11, 0x30(_matB), 0, 0;                                        \
        ps_muls0 f30, f8, f4;                                                \
        psq_l f9, 0x10(_matB), 0, 0;                                         \
        ps_madds0 f31, f8, f6, f11;                                          \
        psq_l f10, 0x20(_matB), 0, 0;                                        \
        ps_madds1 f12, f9, f0, f12;                                          \
        psq_l f1, 0x8(_matA), 1, 0;                                          \
        ps_madds1 f13, f9, f2, f13;                                          \
        psq_l f3, 0x18(_matA), 1, 0;                                         \
        ps_madds1 f30, f9, f4, f30;                                          \
        psq_l f5, 0x28(_matA), 1, 0;                                         \
        ps_madds1 f31, f9, f6, f31;                                          \
        psq_l f7, 0x38(_matA), 1, 0;                                         \
        ps_madds0 f12, f10, f1, f12;                                         \
        psq_l f8, 0x8(_matB), 1, 0;                                          \
        ps_madds0 f13, f10, f3, f13;                                         \
        psq_l f11, 0x38(_matB), 1, 0;                                        \
        ps_madds0 f30, f10, f5, f30;                                         \
        psq_l f9, 0x18(_matB), 1, 0;                                         \
        ps_madds0 f31, f10, f7, f31;                                         \
        psq_l f10, 0x28(_matB), 1, 0;                                        \
        psq_st f12, 0(_dst), 0, 0;                                           \
        psq_st f13, 0x10(_dst), 0, 0;                                        \
        psq_st f30, 0x20(_dst), 0, 0;                                        \
        ps_muls0 f12, f8, f0;                                                \
        psq_st f31, 0x30(_dst), 0, 0;                                        \
        ps_muls0 f13, f8, f2;                                                \
        ps_muls0 f30, f8, f4;                                                \
        lwz _matA, 0xC(_matA);                                               \
        lwz _matB, 0xC(_matB);                                               \
        ps_madds0 f11, f8, f6, f11;                                          \
        ps_madds1 f12, f9, f0, f12;                                          \
        ps_madds1 f13, f9, f2, f13;                                          \
        ps_madds1 f8, f9, f4, f30;                                           \
        ps_madds1 f11, f9, f6, f11;                                          \
        ps_madds0 f12, f10, f1, f12;                                         \
        ps_madds0 f13, f10, f3, f13;                                         \
        and _matB, _matA, _matB;                                             \
        ps_madds0 f8, f10, f5, f8;                                           \
        stw _matB, 0xC(_dst);                                                \
        ps_madds0 f11, f10, f7, f11;                                         \
        psq_st f12, 0x8(_dst), 1, 0;                                         \
        psq_st f13, 0x18(_dst), 1, 0;                                        \
        psq_st f8, 0x28(_dst), 1, 0;                                         \
        psq_st f11, 0x38(_dst), 1, 0;                                        \
    }                                                                        \
}                                                                            \
MACRO_STOP

#endif
