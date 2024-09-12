#ifndef RWDEBUG_H
#define RWDEBUG_H

#include "baerr.h"
#include "batype.h"

#define RWASSERTE(_condition)
#define RWPENTER(_func)
#define RWPEXIT(_func)

#ifdef RWDEBUG

#define RWSTACKDEPTHCHECKONENTRY()
#define RWSTACKDEPTHCHECKONRETURN()

#define RWAPIFUNCTION(function)                                         \
static const RwChar __dbFunctionName[] = function;                      \
do { } while (__dbFunctionName != __dbFunctionName);                    \
RWSTACKDEPTHCHECKONENTRY();                                             \
RWPENTER(__dbFunctionName);

#define RWFUNCTION(function) RWAPIFUNCTION(function)

#define RWRETURN(result)                                                \
MACRO_START                                                             \
{                                                                       \
    RWSTACKDEPTHCHECKONRETURN();                                        \
    RWPEXIT(__dbFunctionName);                                          \
    return (result);                                                    \
}                                                                       \
MACRO_STOP

#define RWRETURNVOID()                                                  \
MACRO_START                                                             \
{                                                                       \
    RWSTACKDEPTHCHECKONRETURN();                                        \
    RWPEXIT(__dbFunctionName);                                          \
    return;                                                             \
}                                                                       \
MACRO_STOP

#define RWERROR(line, ecode)                    \
MACRO_START                                     \
{                                               \
    RwError _rwErrorCode;                       \
                                                \
    _rwErrorCode.pluginID = rwID_COREPLUGIN;    \
    _rwErrorCode.errorCode = _rwerror ecode;    \
                                                \
    RwErrorSet(&_rwErrorCode);                  \
                                                \
    if (_rwErrorCode.errorCode & 0x80000000)    \
    {                                           \
        RwDebugSendMessage(rwDEBUGERROR,        \
                         __dbFunctionName,      \
                         line,                  \
                         _rwdberrcommon ecode); \
    }                                           \
    else                                        \
    {                                           \
        RwDebugSendMessage(rwDEBUGERROR,        \
                         __dbFunctionName,      \
                         line,                  \
                         _rwdb_errcore ecode);  \
    }                                           \
}                                               \
MACRO_STOP

#define RWMESSAGE(line, args)                                         \
MACRO_START                                                     \
{                                                               \
    RwDebugSendMessage(rwDEBUGMESSAGE,                          \
                         __dbFunctionName, line, _rwdbsprintf args);  \
}                                                               \
MACRO_STOP

#define RWASSERT(line, condition)                             \
MACRO_START                                             \
{                                                       \
    if (!(condition))                                   \
    {                                                   \
        RwDebugSendMessage(rwDEBUGASSERT,               \
                           __dbFunctionName,            \
                           line,                        \
                           RWSTRING(#condition));       \
    }                                                   \
    RWASSERTE(condition);                               \
}                                                       \
MACRO_STOP

#define RWASSERTM(line, condition, messageArgs)               \
MACRO_START                                             \
{                                                       \
    if (!(condition))                                   \
    {                                                   \
        RwDebugSendMessage(rwDEBUGASSERT,               \
                           __dbFunctionName,            \
                           line,                        \
                           RWSTRING(#condition));       \
        RwDebugSendMessage(rwDEBUGMESSAGE,              \
                           __dbFunctionName,            \
                           line,                        \
                           _rwdbsprintf messageArgs);   \
    }                                                   \
    RWASSERTE(condition);                               \
}                                                       \
MACRO_STOP

#else

#define RWRETURN(value) return(value)
#define RWRETURNVOID() return
#define RWERROR(line, errorcode)                              \
MACRO_START                                             \
{                                                       \
    RwError _rwErrorCode;                               \
                                                        \
    _rwErrorCode.pluginID = rwID_COREPLUGIN;            \
    _rwErrorCode.errorCode = _rwerror errorcode;        \
                                                        \
    RwErrorSet(&_rwErrorCode);                          \
}                                                       \
MACRO_STOP

#define RWFUNCTION(name)
#define RWAPIFUNCTION(name)
#define RWASSERT(line, condition)
#define RWASSERTM(line, condition, messageArgs)
#define RWMESSAGE(line, args)

#endif

enum RwDebugType
{
    rwNADEBUGTYPE = 0,
    rwDEBUGASSERT,
    rwDEBUGERROR,
    rwDEBUGMESSAGE,
    rwDEBUGTRACE,
    rwDEBUGTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwDebugType RwDebugType;

typedef void (*RwDebugHandler)(RwDebugType type, const RwChar *string);

#ifdef RWDEBUG

#define RwDebugSendMessage(type, funcName, line, message)     \
        _rwDebugSendMessage(type,                       \
                            RWSTRING(__FILE__),         \
                            line,                       \
                            funcName,                   \
                            message)

#ifdef __cplusplus
extern "C"
{
#endif

extern void _rwDebugSendMessage(RwDebugType type, const RwChar *file, const RwInt32 line, const RwChar *funcName, const RwChar *message);

#ifdef    __cplusplus
}
#endif

#else

#define RwDebugSendMessage(type, funcName, line, message)

#endif

#endif
