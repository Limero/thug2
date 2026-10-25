// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A94C8-0x800A952C (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800F0F84(s32, s32);
s32 fn_800F078C(s32, void *);
s32 fn_800F0598(s32);
void fn_800A94C8(Unk_A9157FE7 *arg0) {
    s32 var_r0;
    s32 h;

    h = fn_800F0F84(arg0->unk0x64, 1);
    fn_800F078C(h, (char *)arg0 + 0x80);
    if (fn_800F0598(arg0->unk0x64) == 0) {
        var_r0 = arg0->unk0xB4 | 2;
    } else {
        var_r0 = arg0->unk0xB4 & ~2;
    }
    arg0->unk0xB4 = var_r0;
}
