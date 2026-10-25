// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802590B4-0x802590F8 (68B). Byte-identical.
#include "types.h"
extern s32 lbl_803CA340;

void fn_80257CC4(void *dst, s32 n);   /* zero-fill(dst,n), 2-arg */
void fn_8024EBD8(void *heap, s32 * ptr);

void Vtable0x8030804C_m20(void *arg0) {
    if (arg0 != 0) {
        s32 lblv;
        fn_80257CC4((void *)arg0, 0x58);
        lblv = lbl_803CA340;
        fn_8024EBD8(lblv, (void *)arg0);
    }
}
