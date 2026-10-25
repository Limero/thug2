// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182B88-0x80182C08 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_802A93EC;
extern s32 lbl_80305EAC;
void *fn_8017471C(s32, s16);
void fn_8009F054(void *, s32, s32, f32);
void fn_80182B88(void *arg0, s32 arg1) {
    void *var_r3;
    s32 var_r4;
    if (arg1 != *(s32 *)((char *)arg0 + 0x80)) {
        s16 v = *(s16 *)((char *)arg0 + 0xC);
        s32 h = lbl_80305EAC;
        *(s32 *)((char *)arg0 + 0x80) = arg1;
        var_r3 = fn_8017471C(h, v);
        if (var_r3 != 0) {
            var_r4 = QB_SKATEREXITSPECIAL;
            if (*(s32 *)((char *)arg0 + 0x80) != 0) {
                var_r4 = QB_SKATERENTERSPECIAL;
            }
            fn_8009F054(var_r3, var_r4, 0, lbl_802A93EC);
        }
    }
}
