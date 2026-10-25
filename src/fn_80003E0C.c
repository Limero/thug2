// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003E0C-0x80003EB0 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
// FIXED 2026-09-24: the previous body read `lbl_8028FC64 - 0x39c` (0x8028F8C8)
// because it treated WANT's `lis r9,0x8029; lfs f13,-0x39c(r9)` displacement as
// an offset from the SYMBOL instead of from the 0x80290000 page. WANT's actual
// float targets are 0x8028FC64 (f13) and 0x8028FC60 (f12) — masked compares
// cannot see the lis/addi halfwords, so the bug survived the sweep (M8.277).
extern f32 lbl_8028FC64;
extern f32 lbl_8028FC60;
float sinf(float);
float cosf(float);
void *fn_80003E0C(Unk_DB0E2BAB *arg0, f32 farg0) {
    volatile double dum1;
    volatile double dum2;
    register s32 page0 __asm__("r9");
    register s32 page1 __asm__("r11");
    f32 temp_f12;
    register f32 temp_f13 __asm__("fr13");
    f32 temp_f1;
    f32 temp_f30;

    temp_f30 = sinf(farg0);
    temp_f1 = cosf(farg0);
    page1 = (s32)&lbl_8028FC60;
    page0 = (s32)&lbl_8028FC64;
    temp_f13 = *(f32 *)page0;
    temp_f12 = *(f32 *)page1;
    *((volatile f32 *)&arg0->unk0x24) = (f32) -temp_f30;
    *((volatile f32 *)&arg0->unk0x28) = temp_f1;
    *((volatile f32 *)&arg0->unk0x38) = temp_f13;
    *((volatile f32 *)&arg0->unk0x3C) = temp_f12;
    *((volatile f32 *)&arg0->unk0x0) = temp_f12;
    *((volatile f32 *)&arg0->unk0x4) = temp_f13;
    *((volatile f32 *)&arg0->unk0x8) = temp_f13;
    *((volatile f32 *)&arg0->unk0xC) = temp_f13;
    *((volatile f32 *)&arg0->unk0x10) = temp_f13;
    *((volatile f32 *)&arg0->unk0x14) = temp_f1;
    *((volatile f32 *)&arg0->unk0x18) = temp_f30;
    *((volatile f32 *)&arg0->unk0x1C) = temp_f13;
    *((volatile f32 *)&arg0->unk0x20) = temp_f13;
    *((volatile f32 *)&arg0->unk0x2C) = temp_f13;
    *((volatile f32 *)&arg0->unk0x30) = temp_f13;
    *((volatile f32 *)&arg0->unk0x34) = temp_f13;
    return arg0;
}
