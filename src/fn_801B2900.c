// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2900-0x801B2958 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802ABF3C;
void *GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 fn_800CC314(Unk_C7387A53 * arg0);

s32 fn_801B2900(Unk_31DE137E *arg0) {
    s32 var_r3;
    s32 ret;

    if (arg0->unk0xB8 >= lbl_802ABF3C) {
        ret = fn_800CC314((void *)GetChecksum_3((void *)arg0->unk0xC, QB_ANIMBLENDER));
        var_r3 = 1;
        if (ret == 0) {
var_zero:
            var_r3 = 0;
        }
        return var_r3;
    }
    goto var_zero;
}
