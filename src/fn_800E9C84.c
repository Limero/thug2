// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E9C84-0x800E9D30 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 GetStructure(s32 arg0, s32 arg1);
s32 GetFloat(s32 arg0, s32 arg1, f32 *arg2, s32 arg3);

f32 fn_800E9C84(s32 arg0) {
    struct { f32 sp8; f32 spC; f32 sp10; char _pad[16]; } fr;
    f32 v8;
    f32 vC;
    s32 t;

    t = GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(t, QB_HANG_CRITICAL_POINT_VERT_OFFSET, &fr.sp8, 1);
    v8 = fr.sp8;
    t = GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(t, QB_MAX_CAS_SCALING, &fr.spC, 1);
    vC = fr.spC;
    t = GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(t, QB_HANG_VERT_ORIGIN_OFFSET, &fr.sp10, 1);
    return v8 - (vC * fr.sp10);
}
