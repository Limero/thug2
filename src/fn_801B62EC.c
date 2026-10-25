// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B62EC-0x801B6310 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802AC188;
void fn_801B62EC(s32 arg0) {
    char *var_r3;
    f32 temp_f0;
    s32 var_ctr;
    var_ctr = 4;
    var_r3 = (char *)arg0 + 0x44;
    temp_f0 = lbl_802AC188;
    do {
        __asm__("" :: "r"(var_r3));
        *(f32 *)var_r3 = temp_f0;
        var_r3 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
}
