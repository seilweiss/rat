#ifndef XDEBUGTWEAK_H
#define XDEBUGTWEAK_H

#include "xString.h"

struct tweak_info;

struct tweak_callback
{
    void(*on_change)(tweak_info&);
    void(*on_select)(tweak_info&);
    void(*on_unselect)(tweak_info&);
    void(*on_start_edit)(tweak_info&);
    void(*on_stop_edit)(tweak_info&);
    void(*on_expand)(tweak_info&);
    void(*on_collapse)(tweak_info&);
    void(*on_update)(const tweak_info&);
    void(*convert_mem_to_tweak)(tweak_info&, void*);
    void(*convert_tweak_to_mem)(tweak_info&, void*);

    static tweak_callback create_update(void(*on_update)(const tweak_info&))
    {
        tweak_callback cb = {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            on_update,
            NULL,
            NULL
        };
        return cb;
    }
};

struct tweak_info
{
    substr name;
    void* value;
    const tweak_callback* cb;
    void* context;
    U8 type;
    U8 value_size;
    U16 flags;
    union
    {
        struct
        {
            S32 value_def;
            S32 value_min;
            S32 value_max;
        } int_context;
        struct
        {
            U32 value_def;
            U32 value_min;
            U32 value_max;
        } uint_context;
        struct
        {
            F32 value_def;
            F32 value_min;
            F32 value_max;
        } float_context;
        struct
        {
            bool value_def;
        } bool_context;
        struct
        {
            U32 value_def;
            U32 labels_size;
            const char** labels;
            void* values;
        } select_context;
        struct
        {
            U32 value_def;
            U32 mask;
        } flag_context;
        struct
        {
            U8 pad[16];
        } all_context;
    };
};

#ifdef DEBUGRELEASE
void* xDebugTweak_StaticAlloc(U32 size);
#endif

#ifndef DEBUGRELEASE
inline void xDebugAddTweak(const char* name, const F32* v, F32 vmin, F32 vmax, const tweak_callback* cb, void* context, U32 flags)
{
}

void xDebugRemoveTweak(const char* name);

#define xTWEAKFLOAT(name, v, vmin, vmax, cb, context, flags) xDebugAddTweak(name, v, vmin, vmax, cb, context, flags)
#define xTWEAKBOOL(name, v, cb, context, flags)
#define xTWEAKMESSAGE(name, message, cb, context, flags)
#define xTWEAKREMOVE(name) xDebugRemoveTweak(name)

#define xAUTOTWEAKRANGE(prefix, name, v, vmin, vmax, cb, context, flags, process)
#define xAUTOTWEAKBOOL(prefix, name, v, cb, context, flags, process)
#else
void xDebugAddTweak(const char* name, F32* v, F32 vmin, F32 vmax, const tweak_callback* cb, void* context, U32 flags);
void xDebugAddTweak(const char* name, bool* v, const tweak_callback* cb, void* context, U32 flags);
void xDebugAddTweak(const char* name, const char* message, const tweak_callback* cb, void* context, U32 flags);

void _auto_tweak(const char* prefix, const char* name, S32* v, S32 vmin, S32 vmax, const tweak_callback* cb, void* context, U32 flags, bool process);
void _auto_tweak(const char* prefix, const char* name, F32* v, F32 vmin, F32 vmax, const tweak_callback* cb, void* context, U32 flags, bool process);
void _auto_tweak(const char* prefix, const char* name, bool* v, const tweak_callback* cb, void* context, U32 flags, bool process);

void xDebugRemoveTweak(const char* name);

template <class T, class T2>
inline void _t_auto_tweak(const char* prefix, const char* name, T* v, T2 vmin, T2 vmax, const tweak_callback* cb, void* context, U32 flags, bool process)
{
    _auto_tweak(prefix, name, v, vmin, vmax, cb, context, flags, process);
}

template <>
inline void _t_auto_tweak(const char* prefix, const char* name, bool* v, S32 vmin, S32 vmax, const tweak_callback* cb, void* context, U32 flags, bool process)
{
    _auto_tweak(prefix, name, v, cb, context, flags, process);
}

#define xTWEAKFLOAT(name, v, vmin, vmax, cb, context, flags) xDebugAddTweak(name, v, vmin, vmax, cb, context, flags)
#define xTWEAKBOOL(name, v, cb, context, flags) xDebugAddTweak(name, v, cb, context, flags)
#define xTWEAKMESSAGE(name, message, cb, context, flags) xDebugAddTweak(name, message, cb, context, flags)
#define xTWEAKREMOVE(name) xDebugRemoveTweak(name)

#define xAUTOTWEAKRANGE(prefix, name, v, vmin, vmax, cb, context, flags, process) _t_auto_tweak(prefix, name, v, vmin, vmax, cb, context, flags, process)
#define xAUTOTWEAKBOOL(prefix, name, v, cb, context, flags, process) _t_auto_tweak(prefix, name, v, 0, 0, cb, context, flags, process)
#endif

#endif
