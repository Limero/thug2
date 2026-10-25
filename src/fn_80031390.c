// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80031390-0x800313BC (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"

extern f32 lbl_80291A08;

typedef struct {
    char pad0[0x38];
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    f32 unk0x44;
    f32 unk0x48;
} T80031390;

void fn_80031390(T80031390 *arg0, f32 farg0, f32 farg1)
{
    register f32 value __asm__("fr2");
    register f32 threshold __asm__("fr0");

    value = farg1;
    arg0->unk0x44 = value;
    threshold = lbl_80291A08;
    arg0->unk0x3C = farg0;
    __asm__ volatile("fcmpu 0,%0,%1" : : "f"(value), "f"(threshold));
    arg0->unk0x48 = value;
    __asm__ volatile("bne 8f");
    arg0->unk0x38 = farg0;
    __asm__ volatile("8:");
    __asm__ volatile("" ::: "memory"); /* blocks store->load forwarding */
    arg0->unk0x40 = arg0->unk0x38;
}
