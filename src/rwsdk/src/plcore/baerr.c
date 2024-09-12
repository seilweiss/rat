#include <stdlib.h>
#include <string.h>

#include "batypes.h"

#include "balibtyp.h"

#include "baerr.h"
#include "badebug.h"

#define RWERRORGLOBAL(var) \
    (RWPLUGINOFFSET(rwErrorGlobals, RwEngineInstance, \
    errorModule.globalsOffset)->var)

static RwModuleInfo errorModule;

void *
_rwErrorOpen(void *object, RwInt32 offset, RwInt32 __RWUNUSED__ size )
{
    RWFUNCTION(RWSTRING("_rwErrorOpen"));

    /* Cache the globals offset */
    errorModule.globalsOffset = offset;

    /* One more module instance */
    errorModule.numInstances++;

    /* Initialise the variables */
    RWERRORGLOBAL(errorCode).pluginID = 0;
    RWERRORGLOBAL(errorCode).errorCode = (RwInt32) E_RW_NOERROR;

    /* All done */
    RWRETURN(object);
}

void *
_rwErrorClose(void *object,
              RwInt32 __RWUNUSED__ offset ,
              RwInt32 __RWUNUSED__ size)
{
    RWFUNCTION(RWSTRING("_rwErrorClose"));

    /* One less module instance */
    errorModule.numInstances--;

    RWRETURN(object);
}

RwError *
RwErrorSet(RwError *code)
{
    RWAPIFUNCTION(RWSTRING("RwErrorSet"));
    RWASSERT(150, code);

    if ((RWERRORGLOBAL(errorCode).pluginID == 0x0) &&
        (RWERRORGLOBAL(errorCode).errorCode == (RwInt32) E_RW_NOERROR))
    {
        if (code->errorCode & 0x80000000)
        {
            /* common error */
            RWERRORGLOBAL(errorCode).pluginID = 0x0;
        }
        else
        {
            /* plugin error */
            RWERRORGLOBAL(errorCode).pluginID = code->pluginID;
        }
        /* No current error status */
        RWERRORGLOBAL(errorCode).errorCode = code->errorCode;
    }
    RWRETURN(code);
}

RwError *
RwErrorGet(RwError *code)
{
    RWAPIFUNCTION(RWSTRING("RwErrorGet"));
    RWASSERT(196, code);

    *code = RWERRORGLOBAL(errorCode);
    RWERRORGLOBAL(errorCode).pluginID = 0x0;
    RWERRORGLOBAL(errorCode).errorCode = (RwInt32) E_RW_NOERROR;

    RWRETURN(code);
}

RwInt32
_rwerror(RwInt32 code, ...)
{
    va_list             ap;
    va_start(ap, code);
    va_end(ap);
    return (code);
}
