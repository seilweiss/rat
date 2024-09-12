#ifndef RWIMMEDI_H
#define RWIMMEDI_H

#include "batypes.h"
#include "drvmodel.h"

enum RwRenderState
{
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER,
    rwRENDERSTATETEXTUREADDRESS,
    rwRENDERSTATETEXTUREADDRESSU,
    rwRENDERSTATETEXTUREADDRESSV,
    rwRENDERSTATETEXTUREPERSPECTIVE,
    rwRENDERSTATEZTESTENABLE,
    rwRENDERSTATESHADEMODE,
    rwRENDERSTATEZWRITEENABLE,
    rwRENDERSTATETEXTUREFILTER,
    rwRENDERSTATESRCBLEND,
    rwRENDERSTATEDESTBLEND,
    rwRENDERSTATEVERTEXALPHAENABLE,
    rwRENDERSTATEBORDERCOLOR,
    rwRENDERSTATEFOGENABLE,
    rwRENDERSTATEFOGCOLOR,
    rwRENDERSTATEFOGTYPE,
    rwRENDERSTATEFOGDENSITY,
    rwRENDERSTATECULLMODE = 20,
    rwRENDERSTATESTENCILENABLE,
    rwRENDERSTATESTENCILFAIL,
    rwRENDERSTATESTENCILZFAIL,
    rwRENDERSTATESTENCILPASS,
    rwRENDERSTATESTENCILFUNCTION,
    rwRENDERSTATESTENCILFUNCTIONREF,
    rwRENDERSTATESTENCILFUNCTIONMASK,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
    rwRENDERSTATEALPHATESTFUNCTION,
    rwRENDERSTATEALPHATESTFUNCTIONREF,
    rwRENDERSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRenderState RwRenderState;

enum RwTextureFilterMode
{
    rwFILTERNAFILTERMODE = 0,
    rwFILTERNEAREST,
    rwFILTERLINEAR,
    rwFILTERMIPNEAREST,
    rwFILTERMIPLINEAR,
    rwFILTERLINEARMIPNEAREST,
    rwFILTERLINEARMIPLINEAR,
    rwTEXTUREFILTERMODEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwTextureFilterMode RwTextureFilterMode;

enum RwFogType
{
    rwFOGTYPENAFOGTYPE = 0,
    rwFOGTYPELINEAR,
    rwFOGTYPEEXPONENTIAL,
    rwFOGTYPEEXPONENTIAL2,
    rwFOGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwFogType RwFogType;

enum RwBlendFunction
{
    rwBLENDNABLEND = 0,
    rwBLENDZERO,
    rwBLENDONE,
    rwBLENDSRCCOLOR,
    rwBLENDINVSRCCOLOR,
    rwBLENDSRCALPHA,
    rwBLENDINVSRCALPHA,
    rwBLENDDESTALPHA,
    rwBLENDINVDESTALPHA,
    rwBLENDDESTCOLOR,
    rwBLENDINVDESTCOLOR,
    rwBLENDSRCALPHASAT,
    rwBLENDFUNCTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwBlendFunction RwBlendFunction;

enum RwPrimitiveType
{
    rwPRIMTYPENAPRIMTYPE = 0,
    rwPRIMTYPELINELIST = 1,
    rwPRIMTYPEPOLYLINE = 2,
    rwPRIMTYPETRILIST = 3,
    rwPRIMTYPETRISTRIP = 4,
    rwPRIMTYPETRIFAN = 5,
    rwPRIMTYPEPOINTLIST = 6,
    rwPRIMITIVETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwPrimitiveType RwPrimitiveType;

#define RwIm2DGetNearScreenZMacro() (RWSRCGLOBAL(dOpenDevice).zBufferNear)
#define RwRenderStateGetMacro(_state, _value) (RWSRCGLOBAL(dOpenDevice).fpRenderStateGet(_state, _value))
#define RwRenderStateSetMacro(_state, _value) (RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(_state, _value))
#define RwIm2DRenderPrimitiveMacro(_primType, _vertices, _numVertices) (RWSRCGLOBAL(dOpenDevice).fpIm2DRenderPrimitive(_primType, _vertices, _numVertices))

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef RWDEBUG
#define RwIm2DGetNearScreenZ() RwIm2DGetNearScreenZMacro()
#define RwRenderStateGet(_state, _value) RwRenderStateGetMacro(_state, _value)
#define RwRenderStateSet(_state, _value) RwRenderStateSetMacro(_state, _value)
#define RwIm2DRenderPrimitive(_primType, _vertices, _numVertices) RwIm2DRenderPrimitiveMacro(_primType, _vertices, _numVertices)
#else
extern RwReal RwIm2DGetNearScreenZ(void);
extern RwBool RwRenderStateGet(RwRenderState state, void *value);
extern RwBool RwRenderStateSet(RwRenderState state, void *value);
extern RwBool RwIm2DRenderPrimitive(RwPrimitiveType primType, RwIm2DVertex *vertices, RwInt32 numVertices);
#endif

#ifdef __cplusplus
}
#endif

#endif
