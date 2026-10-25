// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018ECF4-0x8018ED70 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8009CF2C(CStruct *);
extern char lbl_80305F9C[];
s32 fn_8018ECF4(Unk_C7387A53 *arg0) {
    s32 temp_r0;
    s32 temp_r9;
    s32 var_r0;
    s32 var_r3;

    if (fn_8009CF2C(*(s32 *)&lbl_80305F9C) != 0) {
        temp_r9 = arg0->unk0x70;
        arg0->unk0x40 = 0;
        arg0->unk0x44 = 0;
        if (temp_r9 & QB_UNKNOWN_0x10000000) {
            var_r0 = temp_r9 & QB_UNKNOWN_0xEFFFFFFF;
            goto block_5;
        }
        goto block_6;
    }
    temp_r0 = arg0->unk0x70;
    if (temp_r0 & QB_UNKNOWN_0x20000000) {
        var_r0 = temp_r0 & QB_UNKNOWN_0xDFFFFFFF;
block_5:
        var_r3 = 1;
        __asm__("" : "+r"(var_r3));
        arg0->unk0x70 = var_r0;
        return var_r3;
    }
block_6:
    return 0;
}
