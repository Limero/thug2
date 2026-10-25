// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0958-0x801F0A04 (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ADE94;
f32 fn_801F0958(Unk_31DE137E *arg0) {
    s32 temp_r9;
    s32 var_r0;
    Unk_C7387A53 *var_r3;

    temp_r9 = arg0->unk0x1C;
    if (temp_r9 != QB_SKITCH) {
        if ((u32)temp_r9 <= (u32)QB_SKITCH) {
            if (temp_r9 != QB_NOSEMANUAL) {
                var_r0 = QB_GRIND;
                goto block_7;
            }
            goto block_28;
        }
        if (temp_r9 != QB_LIP) {
            if ((u32)temp_r9 <= (u32)QB_LIP) {
                var_r0 = QB_SLIDE;
block_7:
                if (temp_r9 == var_r0) {
                    goto block_98;
                }
                goto block_def;
            }
            if (temp_r9 == QB_MANUAL) {
                goto block_28;
            }
            goto block_def;
        }
        goto block_108;
    }
    goto block_178;
block_98:
    var_r3 = (char *)arg0 + 0x98;
    goto block_ret;
block_108:
    var_r3 = (char *)arg0 + 0x108;
    goto block_ret;
block_178:
    var_r3 = (char *)arg0 + 0x178;
    goto block_ret;
block_28:
    var_r3 = (char *)arg0 + 0x28;
    goto block_ret;
block_def:
    return lbl_802ADE94;
block_ret:
    return *((f32 *)&var_r3->unk0x34);
}
