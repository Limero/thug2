// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80107A28-0x80107A80 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CB90;
extern f32 lbl_8029CB94;
void fn_80107A28(Unk_C5652918 *arg0) {
    register f32 temp_f13 asm("fr13");
    f32 temp_f0;
    Unk_5EF41E38 *temp_r9;
    Unk_5EF41E38 *temp_r11;

    temp_f0 = lbl_8029CB90;
    temp_f13 = lbl_8029CB94;
    arg0->unk0x54 = 0x10;
    arg0->unk0x56 = 0;
    temp_r9 = (char *)arg0 + 0x28;
    arg0->unk0x20 = 0;
    temp_r11 = (char *)arg0 + 0x38;
    arg0->unk0xBC = 0;
    arg0->unk0x28 = temp_f0;
    temp_r9->unk0x4 = temp_f0;
    temp_r9->unk0x8 = temp_f0;
    ((Unk_4C649A8C *)temp_r9)->unk0xC = temp_f13;
    arg0->unk0x38 = temp_f0;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    ((Unk_4C649A8C *)temp_r11)->unk0xC = temp_f13;
}
