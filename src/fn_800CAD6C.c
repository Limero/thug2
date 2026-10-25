// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CAD6C-0x800CADFC (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80299460[];
extern char lbl_802994D8[];
void *fn_800CAD6C(Unk_C8FEE62D *arg0) {
    CStruct *temp_r3;
    Unk_C8FEE62D *temp_r9;
    CStruct *p44;

    fn_8009F53C();
    temp_r9 = (char *)arg0 + 0x2C;
    arg0->unk0x18 = (s32)lbl_80299460;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x14 = (s32)lbl_802994D8;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x8 = 0;
    p44 = (char *)arg0 + 0x44;
    p44->unk0x4 = 0;
    temp_r3 = Mem_Alloc2(0xC);
    arg0->unk0x44 = temp_r3;
    arg0->unk0x4 = QB_ANIMBLENDER;
    temp_r3->unk0x8 = temp_r3;
    temp_r3->unk0x4 = temp_r3;
    return arg0;
}
