// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E3520-0x800E359C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029A784;
extern char lbl_8029A7B0[];
void *fn_800E3520(Unk_C8FEE62D *arg0) {
    Unk_C8FEE62D *temp_r11;

    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_8029A7B0;
    temp_r11 = (Unk_C8FEE62D *)((char *)arg0 + 0x1C);
    temp_r11->unk0x4 = 0;
    temp_r11->unk0x8 = 0;
    arg0->unk0x4 = QB_FLEXIBLEPARTICLE;
    arg0->unk0x1C = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x34 = 0;
    arg0->unk0x38 = 0;
    arg0->unk0x3C = 0;
    *((f32 *)&arg0->unk0x30) = lbl_8029A784;
    return arg0;
}
