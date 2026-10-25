// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2BA8-0x800F2CB0 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Script_GetInteger(s32, s32);
s32 Script_GenerateCRC(s32);
void *fn_800F34F0(s32, s32 *, s32);
void fn_800137C4(s32);
s32 fn_800F2628(Unk_C7387A53 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct {
    char pad0[0x10];
    s16 off0x10;
    char pad0x12[2];
    s32 (*fn0x14)(void *);
    char pad0x18[0x30];
    s16 off0x48;
    char pad0x4A[2];
    s32 (*fn0x4C)(void *);
} VT_f2ba8;

typedef struct {
    char pad0[0x50];
    VT_f2ba8 *vtable;
} Obj_f2ba8;

s32 fn_800F2BA8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp8, s32 arg_spC) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r30;
    void *temp_r3;
    VT_f2ba8 *vt;
    Obj_f2ba8 *obj;

    sp10 = arg3;
    if (arg3 == 0) {
        sp10 = Script_GenerateCRC(arg1);
    }
    temp_r3 = fn_800F34F0(arg0->unk0x24, &sp10, 1);
    if (temp_r3 != NULL) {
        obj = (Obj_f2ba8 *)temp_r3;
        vt = obj->vtable;
        var_r30 = vt->fn0x14((char *)obj + vt->off0x10);
        goto poll_test;
    poll_retry:
        fn_800137C4(0);
    poll_test:
        vt = obj->vtable;
        if (vt->fn0x4C((char *)obj + vt->off0x48) == 0) {
            goto poll_retry;
        }
    } else {
        sp8 = arg_sp8;
        spC = arg_spC;
        var_r30 = fn_800F2628(arg0, arg1, arg2, sp10, arg4, arg5, arg6, arg7, sp8, spC);
    }
    Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0);
    return var_r30;
}
