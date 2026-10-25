// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EC5A4-0x800EC63C (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 Mem_Alloc2(s32);
f32 fn_800144C8(void);
extern f32 lbl_8029ADB4;
extern char lbl_8029ADF0[];
void *fn_800EC5A4(Unk_9AA07378 *arg0) {
    CStruct *temp_r3;

    fn_8009F53C();
    arg0->unk0x20 = 0;
    arg0->unk0x18 = (s32)lbl_8029ADF0;
    temp_r3 = Mem_Alloc2(0xC);
    arg0->unk0x1C = temp_r3;
    arg0->unk0x24 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x38 = 0;
    arg0->unk0x4 = QB_PARTICLECHAIN;
    *((f32 *)&arg0->unk0x34) = lbl_8029ADB4;
    temp_r3->unk0x4 = temp_r3;
    temp_r3->unk0x8 = temp_r3;
    *((f32 *)&arg0->unk0x30) = fn_800144C8();
    arg0->unk0x48 = 0;
    arg0->unk0x3C = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    return arg0;
}
