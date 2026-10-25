// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B6004-0x801B608C (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802AC144;

f32 fn_8012570C(s32, s32);

register s32 unused_r31 __asm__("r31");

void fn_801B6004(s32 arg0) {
    volatile double _dummy;
    f32 *var_r30;
    f32 temp_f0;
    f32 scale;
    f32 limit;
    f32 zero;
    s32 var_ctr;

    scale = fn_8012570C(QB_PED_WHISKER_DECAY_FACTOR, 1);
    limit = fn_8012570C(QB_PED_MIN_BIAS, 1);
    zero = lbl_802AC144;
    var_ctr = 4;
    var_r30 = (f32 *)((char *)arg0 + 0x48);
    do {
        temp_f0 = *var_r30 * scale;
        *var_r30 = temp_f0;
        if (temp_f0 < limit) {
            *var_r30 = zero;
        }
        var_r30 += 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
