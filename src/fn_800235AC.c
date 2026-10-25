// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800235AC-0x80023638 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_803CAF18[];
void fn_800235AC(u32 arg0) {
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    u8 *temp_r9_4;
    Unk_9994C3F5 *temp_r10;
    Unk_9994C3F5 *temp_r10_2;
    Unk_9994C3F5 *temp_r11;
    CStruct *temp_r9;

    temp_r9 = *(void * *)&lbl_803CAF18;
    if ((u32) (*((u32 *)&temp_r9->unk0x8) + 3) > (u32) *((u32 *)&temp_r9->unk0xC)) {
        fn_8028D464();
    }
    temp_r10 = *(void * *)&lbl_803CAF18;
    temp_r9_2 = temp_r10->unk0x8;
    *temp_r9_2 = (arg0 & QB_MASK_BYTE2) >> 0x10;
    temp_r10->unk0x8 = (u8 *) (temp_r9_2 + 1);
    temp_r11 = *(void * *)&lbl_803CAF18;
    temp_r9_3 = temp_r11->unk0x8;
    *temp_r9_3 = (arg0 & QB_MASK_BYTE1) >> 8;
    temp_r11->unk0x8 = (u8 *) (temp_r9_3 + 1);
    temp_r10_2 = *(void * *)&lbl_803CAF18;
    temp_r9_4 = temp_r10_2->unk0x8;
    *temp_r9_4 = arg0;
    temp_r10_2->unk0x8 = (u8 *) (temp_r9_4 + 1);
}
