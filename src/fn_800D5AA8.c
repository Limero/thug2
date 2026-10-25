// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5AA8-0x800D5AEC (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
void fn_800D81F0(s32, s32, s32, void *, s32);
bool fn_800D5AA8(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        __ps_t a;
        __ps_t b;
    } var_temp;
    register s32 base __asm__("r11");
    base = (s32)&var_temp;
    *(__ps_t *)((char *)base + 0) = *(__ps_t *)((char *)arg0 + 0x1C8);
    *(__ps_t *)((char *)base + 8) = *(__ps_t *)((char *)arg0 + 0x1D0);
    fn_800D81F0(arg0, arg1, arg2, (void *)base, 0);
    return true;
}
