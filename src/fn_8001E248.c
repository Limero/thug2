// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001E248-0x8001E2FC (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80300288;
void fn_8001E248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 mode) {
    register s32 arg0_pin __asm__("r30");
    s32 arg1_bit = arg1 * 2;
    s32 arg4_lo = (arg4 * 4) & 0x3C;
    s32 flags = arg3 | arg1_bit;
    s32 arg2_hi = arg2 << 6;
    flags |= arg4_lo;
    flags |= arg2_hi;
    arg0_pin = arg0;
    if (mode != 0) {
        flags |= arg5 << 7;
    }
    {
        s32 lo_flags = flags;
        register s32 hi_flags __asm__("r0");
        if (mode != 2) {
            lo_flags |= 0x200;
        }
        hi_flags = (arg4 << 7) & 0x7800;
        if (mode != 0) {
            hi_flags |= 0x400;
        }
        {
            s32 all_flags = lo_flags | hi_flags;
            /* Generic arithmetic only: materialise the hook's page anchor at this
             * exact point in the block, then read through it with want's literal
             * 0x288 displacement (0x8030<<16 + 0x288 == lbl_80300288). */
            register char *pg __asm__("r29");
            s32 id0;
            u16 idf;
            s32 (*hook)(u16, s32);
            s32 (*hook2)(u16, s32);
            pg = (char *)&lbl_80300288;
            __asm__ volatile("clrlwi %0,%1,0x1e" : "=r"(id0) : "r"(arg0_pin));
            hook = (s32 (*)(u16, s32))(*(s32 *)((char *)pg));
            __asm__ volatile("addi %0,%1,0x100e" : "=r"(idf) : "r"(id0));
            hook(idf, all_flags);
            if ((u32)(arg0_pin - 4) <= 1U) {
                hook2 = (s32 (*)(u16, s32))(*(s32 *)((char *)pg));
                hook2((u16)(arg0_pin + 0x100C), all_flags);
            }
        }
    }
}
