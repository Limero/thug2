// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80007308-0x800073AC (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80007308(f32 *arg0, f32 *arg1, s32 *arg2) {
    s32 var_r9;

    var_r9 = 0;
    *arg2 = 0;
    if (!(arg1[0] >= arg0[0])) goto skip0;
    if (!(arg1[0] <= arg0[4])) goto skip0;
    var_r9 = 1;
    *arg2 = 1;
skip0:
    if (!(arg1[1] >= arg0[1])) goto skip1;
    if (!(arg1[1] <= arg0[5])) goto skip1;
    var_r9 += 1;
    *arg2 |= 2;
skip1:
    if (!(arg1[2] >= arg0[2])) goto skip2;
    if (!(arg1[2] <= arg0[6])) goto skip2;
    var_r9 += 1;
    *arg2 |= 4;
skip2:
    return var_r9;
}
