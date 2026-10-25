// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801877F8-0x80187838 (64B). Byte-identical.
// Looks up QB_NAME on arg1 via fn_80128E34 and returns the stored value.
// First param (r3) is unused by the callee.
// Suggested rename: fn_GetQbNameValue(inst, entry, arg).
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_801877F8(s32 arg0, CStruct *arg1, s32 arg2) {
    s32 sp8;

    sp8 = 0;
    fn_80128E34(arg1, QB_NAME, &sp8, arg2);
    return sp8;
}