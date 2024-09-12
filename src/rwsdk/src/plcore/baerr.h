#ifndef RWERR_H
#define RWERR_H

#include "rwdbgerr.h"

typedef struct RwError RwError;
struct RwError
{
    RwInt32 pluginID;
    RwInt32 errorCode;
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

extern RwError *RwErrorGet(RwError *code);
extern RwError *RwErrorSet(RwError *code);

#ifdef __cplusplus
}
#endif

#endif
