#ifndef RTFSGCN_H
#define RTFSGCN_H

#include "rtfsyst.h"

/* RWPUBLIC */

#include <dolphin.h>
#include <stdio.h>

#define RTFS_INITIALIZE_INTERRUPT_HANDLING
#define RTFS_DISABLE_INTERRUPT OSDisableInterrupts()
#define RTFS_ENABLE_INTERRUPT OSEnableInterrupts()
#define RTFS_SHUTDOWN_INTERRUPT_HANDLING

/* RWPUBLICEND */

#endif /* RTFSGCN_H */
