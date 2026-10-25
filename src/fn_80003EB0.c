// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003EB0-0x80003F54 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern f32 lbl_8028FC68;
extern f32 lbl_8028FC6C;
float sinf(float);
float cosf(float);
void *fn_80003EB0(Unk_DB0E2BAB *arg0, f32 farg0) {
    volatile double dum1;
    volatile double dum2;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f30;

    temp_f30 = sinf(farg0);
    temp_f1 = cosf(farg0);
    temp_f13 = lbl_8028FC68;
    temp_f12 = lbl_8028FC6C;
    *((volatile f32 *)&arg0->unk0x8) = (f32) -temp_f30;
    *((volatile f32 *)&arg0->unk0x20) = temp_f30;
    *((volatile f32 *)&arg0->unk0x28) = temp_f1;
    *((volatile f32 *)&arg0->unk0x38) = temp_f13;
    *((volatile f32 *)&arg0->unk0x3C) = temp_f12;
    *((volatile f32 *)&arg0->unk0x0) = temp_f1;
    *((volatile f32 *)&arg0->unk0x4) = temp_f13;
    *((volatile f32 *)&arg0->unk0xC) = temp_f13;
    *((volatile f32 *)&arg0->unk0x10) = temp_f13;
    *((volatile f32 *)&arg0->unk0x14) = temp_f12;
    *((volatile f32 *)&arg0->unk0x18) = temp_f13;
    *((volatile f32 *)&arg0->unk0x1C) = temp_f13;
    *((volatile f32 *)&arg0->unk0x24) = temp_f13;
    *((volatile f32 *)&arg0->unk0x2C) = temp_f13;
    *((volatile f32 *)&arg0->unk0x30) = temp_f13;
    *((volatile f32 *)&arg0->unk0x34) = temp_f13;
    return arg0;
}
