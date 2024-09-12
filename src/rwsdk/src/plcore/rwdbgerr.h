#define RWECODE(a,b) a,

enum RwErrorCodePlugin_errcore 
{
#include "errcore.def"
    rwLASTERROR_errcore = RWFORCEENUMSIZEINT
};
typedef enum RwErrorCodePlugin_errcore RwErrorCodePlugin_errcore;

#undef RWECODE
