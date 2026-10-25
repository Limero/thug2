// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019BC6C-0x8019BD0C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80305EAC;
extern char lbl_802AAB9C[];
#include "qb_constants.h"
#include "structs.h"
s32 fn_80125814(void *, s32);
s32 fn_8017471C(s32, s32);
s32 fn_8019BC6C(Unk_9994C3F5 *arg0) {
    s32 temp_r29;
    s32 temp_r4;
    s32 temp_r9;
    s32 var_r0;
    s32 var_r30;
    s32 var_r31;

    temp_r29 = lbl_80305EAC;
    var_r30 = 0;
    for (var_r31 = 0; var_r31 <= 7; var_r31++) {
        temp_r9 = arg0->unk0x8 + var_r31;
        temp_r4 = temp_r9 + 1;
        var_r0 = temp_r4;
        if (temp_r4 < 0) {
            var_r0 = temp_r9 + 8;
        }
        var_r30 = temp_r4 - (var_r0 & QB_UNKNOWN_0xFFFFFFF8);
        if (fn_8017471C(temp_r29, var_r30) != 0) {
            break;
        }
    }
    if (fn_80125814(lbl_802AAB9C, 0) != 0) {
        var_r30 = 0;
    }
    return var_r30;
}
