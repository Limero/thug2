// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2EDC-0x800F2F88 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 Script_GenerateCRC(s32);
s32 fn_800F2CB0(CScript *, s32);
s32 fn_800F2BA8(CScript *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

s32 fn_800F2EDC(CScript *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 spC;
    s32 sp8;
    s32 var_r31;
    s32 res;

    var_r31 = Script_GenerateCRC(arg1);
    if (arg2 != 0) {
        var_r31 = arg2 + arg3;
    }
    spC = fn_800F2CB0(arg0, var_r31);
    if (!spC) {
        sp8 = spC;
        if (fn_800F2BA8(arg0, arg1, 5, var_r31, 0, arg4, arg5, arg0->unk0x18, sp8, spC) != 0) {
            res = 1;
        } else {
            res = 0;
        }
        return res;
    }
    return 0;
}
