// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC540-0x800CC5BC (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299548[];
extern char lbl_802995C0[];
void *fn_800CC540(Unk_C8FEE62D *arg0) {
    Unk_C8FEE62D *temp_r9;

    fn_8009F53C();
    temp_r9 = (char *)arg0 + 0x1C;
    arg0->unk0x18 = (s32)lbl_80299548;
    temp_r9->unk0x14 = (s32)lbl_802995C0;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x8 = 0;
    arg0->unk0x4 = QB_TEXTUREPROJECTION;
    arg0->unk0x34 = 0;
    arg0->unk0x38 = 0;
    arg0->unk0x3C = 0;
    return arg0;
}
