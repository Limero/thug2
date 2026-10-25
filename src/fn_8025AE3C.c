// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AE3C-0x8025AEEC (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void lbl_8025AF3C(s32, s32, s32);
extern void Vtable0x80308A40_m5(void);
register s32 ctx_r31 __asm__("r31");

void __attribute__((naked)) fn_8025AE3C(void) {
    register s32 r3 __asm__("r3");
    register s32 r4 __asm__("r4");
    register s32 r5 __asm__("r5");

    r5 = *(s32 *)((s32)ctx_r31 + 0x20);
    if (r5 == 0) {
        goto done;
    }

    r3 = (s32)0x803089C4;
    r3 = *(volatile s32 *)r3;
    if (r3 != 0 && r5 == 1) {
        r3 = *(s32 *)((s32)ctx_r31 + 0x18);
        r3 = *(u8 *)r3;
        if (r3 != 0xA && r3 != 0xD) {
            r5 = *(u8 *)((s32)ctx_r31 + 0x6D8);
            r4 = r5 + (s32)ctx_r31;
            *(volatile u8 *)(r4 + 0x6D9) = (u8)r3;
            __asm__ volatile("" ::: "memory");
            r5 = r5 + 1;
            *(volatile u8 *)((s32)ctx_r31 + 0x6D8) = (u8)r5;
            if (r5 == 0x10) {
                r4 = (s32)ctx_r31 + 0x6D9;
                lbl_8025AF3C(r3, r4, r5);
                r5 = 0;
                *(u8 *)((s32)ctx_r31 + 0x6D8) = (u8)r5;
            }
            goto done;
        }
    }

    r5 = *(u8 *)((s32)ctx_r31 + 0x6D8);
    if (r5 != 0) {
        r4 = (s32)ctx_r31 + 0x6D9;
        lbl_8025AF3C(r3, r4, r5);
        r5 = 0;
        *(u8 *)((s32)ctx_r31 + 0x6D8) = (u8)r5;
    }
    r4 = *(s32 *)((s32)ctx_r31 + 0x18);
    r5 = *(s32 *)((s32)ctx_r31 + 0x20);
    lbl_8025AF3C(r3, r4, r5);

done:
    r3 = *(s32 *)((s32)ctx_r31 + 0x370);
    r3 = r3 + 4;
    *(s32 *)((s32)ctx_r31 + 0x370) = r3;
    r3 = 0;
    *(s32 *)((s32)ctx_r31 + 0x18) = r3;
    __asm__ volatile("b Vtable0x80308A40_m5");
}
