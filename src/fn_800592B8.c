// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800592B8-0x800592F8 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

extern void *lbl_80364C3C;
void fn_8007C2E8(s32);

void fn_800592B8(s32 arg0, __ps_t *arg1) {
    struct {
        __ps_t p0;
        __ps_t p1;
    } *arr = lbl_80364C3C;
    arr[arg0].p0 = *(__ps_t *)((char *)arg1 + 0);
    arr[arg0].p1 = *(__ps_t *)((char *)arg1 + 8);
    fn_8007C2E8(arg0);
}
