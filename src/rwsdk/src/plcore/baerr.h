#ifndef RWERR_H
#define RWERR_H

#include "rwdbgerr.h"

typedef struct RwError RwError;
struct RwError
{
    RwInt32 pluginID;
    RwInt32 errorCode;
};

typedef struct rwErrorGlobals rwErrorGlobals;
struct rwErrorGlobals
{
    RwError     errorCode;                      /* Error code for last error */
};

#define RWECODE(a,b) a,

enum RwErrorCodeCommon
{
    E_RW_NOERROR = (int)0x80000000L,
#include "errcom.def"
    E_RW_LASTERROR = RWFORCEENUMSIZEINT
};
typedef enum RwErrorCodeCommon RwErrorCodeCommon;

#undef RWECODE

#ifdef __cplusplus
extern "C"
{
#endif

extern void *_rwErrorOpen(void *object, RwInt32 offset, RwInt32 size);
extern void *_rwErrorClose(void *object, RwInt32 offset, RwInt32 size);

extern RwError *RwErrorGet(RwError *code);
extern RwError *RwErrorSet(RwError *code);
extern RwInt32 _rwerror(RwInt32 code, ...);

#ifdef __cplusplus
}
#endif

#endif
