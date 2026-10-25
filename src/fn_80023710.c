// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023710-0x8002381C (268B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_803CAF18[];
void fn_80023710(u8 arg0, u32 arg1) {
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    u8 *temp_r9_4;
    u8 *temp_r9_5;
    u8 *temp_r9_6;
    u8 *temp_r9_7;
    Unk_9994C3F5 *temp_r10;
    Unk_9994C3F5 *temp_r10_2;
    Unk_9994C3F5 *temp_r10_3;
    Unk_9994C3F5 *temp_r10_4;
    CStruct *temp_r11;
    CStruct *temp_r11_2;
    Unk_9994C3F5 *temp_r11_3;
    Unk_9994C3F5 *temp_r11_4;
    CStruct *temp_r9;

    temp_r9 = *(void * *)&lbl_803CAF18;
    if ((u32) (*((u32 *)&temp_r9->unk0x8) + 1) > (u32) *((u32 *)&temp_r9->unk0xC)) {
        fn_8028D464();
    }
    temp_r10 = *(void * *)&lbl_803CAF18;
    temp_r9_2 = temp_r10->unk0x8;
    *temp_r9_2 = 8;
    temp_r10->unk0x8 = (u8 *) (temp_r9_2 + 1);
    temp_r11 = *(void * *)&lbl_803CAF18;
    if ((void *) (*((u32 *)&temp_r11->unk0x8) + 1) > (u32) *((u32 *)&temp_r11->unk0xC)) {
        fn_8028D464();
    }
    temp_r10_2 = *(void * *)&lbl_803CAF18;
    temp_r9_3 = temp_r10_2->unk0x8;
    *temp_r9_3 = arg0;
    temp_r10_2->unk0x8 = (u8 *) (temp_r9_3 + 1);
    temp_r11_2 = *(void * *)&lbl_803CAF18;
    if ((void *) (*((u32 *)&temp_r11_2->unk0x8) + 4) > (u32) *((u32 *)&temp_r11_2->unk0xC)) {
        fn_8028D464();
    }
    temp_r10_3 = *(void * *)&lbl_803CAF18;
    temp_r9_4 = temp_r10_3->unk0x8;
    *temp_r9_4 = (arg1 & QB_UNKNOWN_0xFF000000) >> 0x18;
    temp_r10_3->unk0x8 = (u8 *) (temp_r9_4 + 1);
    temp_r11_3 = *(void * *)&lbl_803CAF18;
    temp_r9_5 = temp_r11_3->unk0x8;
    *temp_r9_5 = (arg1 & QB_MASK_BYTE2) >> 0x10;
    temp_r11_3->unk0x8 = (u8 *) (temp_r9_5 + 1);
    temp_r10_4 = *(void * *)&lbl_803CAF18;
    temp_r9_6 = temp_r10_4->unk0x8;
    *temp_r9_6 = (arg1 & QB_MASK_BYTE1) >> 8;
    temp_r10_4->unk0x8 = (u8 *) (temp_r9_6 + 1);
    temp_r11_4 = *(void * *)&lbl_803CAF18;
    temp_r9_7 = temp_r11_4->unk0x8;
    *temp_r9_7 = arg1;
    temp_r11_4->unk0x8 = (u8 *) (temp_r9_7 + 1);
}
