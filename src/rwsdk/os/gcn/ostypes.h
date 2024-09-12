#ifndef GCN_OSTYPES_H
#define GCN_OSTYPES_H

#define rwBIGENDIAN

typedef long RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;
typedef char RwChar;
typedef float RwReal;
typedef RwInt32 RwBool;
typedef long long RwInt64;
typedef unsigned long long RwUInt64;

typedef struct _RwUInt128 RwUInt128;
typedef struct _RwInt128 RwInt128;
struct _RwUInt128
{
    RwUInt64 top;
    RwUInt64 bottom;
};

struct _RwInt128
{
    RwInt64 top;
    RwUInt64 bottom;
};

#define RwInt32MAXVAL 0x7FFFFFFF
#define RwInt32MINVAL 0x80000000
#define RwUInt32MAXVAL 0xFFFFFFFF
#define RwUInt32MINVAL 0x00000000
#define RwRealMAXVAL (RwReal)(3.40282347e+38)
#define RwRealMINVAL (RwReal)(1.17549435e-38)
#define RwInt16MAXVAL 0x7FFF
#define RwInt16MINVAL 0x8000
#define RwUInt16MAXVAL 0xFFFF
#define RwUInt16MINVAL 0x0000

#define RWALIGN(type, x) type
#define rwMATRIXALIGNMENT sizeof(RwUInt32)
#define rwFRAMEALIGNMENT sizeof(RwUInt32)
#define rwV4DALIGNMENT sizeof(RwUInt32)

#define rwMALLOCALIGNMENT 32

#endif
