// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182C50-0x80182C8C (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_802A93F0;
void fn_80182C50(Unk_6A3B48DF *arg0) {
    s32 var_ctr;
    s8 *var_r9;
    register s32 z11 __asm__("r11");

    __asm__("li %0,0" : "=r"(z11));
    arg0->unk0x1548 = 0;
    arg0->unk0x1554 = 0;
    arg0->unk0x1550 = 0;
    var_r9 = (s8 *)arg0 + 0x1543;
    var_ctr = 0x9C4;
    do {
        *((s8 *)var_r9) = (s8)z11;
        var_r9 -= 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x1558 = lbl_802A93F0;
}
