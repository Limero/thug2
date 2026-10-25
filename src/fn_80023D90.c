// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80023D90-0x80023E94 (260B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8028D464(void);
extern void *lbl_803CAF18;
void fn_80023D90(s32 arg0, s32 arg1, u16 arg2) {
    u8 *temp_r9_2;
    u8 *temp_r9_3;
    u8 *temp_r9_4;
    u8 *temp_r9_5;
    u8 *temp_r9_6;
    u32 temp_r30;
    Unk_9994C3F5 *temp_r10;
    Unk_9994C3F5 *temp_r10_2;
    Unk_9994C3F5 *temp_r10_3;
    CStruct *temp_r11;
    CStruct *temp_r11_2;
    Unk_9994C3F5 *temp_r11_3;
    Unk_9994C3F5 *temp_r8;
    CStruct *temp_r9;

    temp_r9 = (CStruct *)lbl_803CAF18;
    if ((u32) (temp_r9->unk0x8 + 1) > (u32) temp_r9->unk0xC) {
        fn_8028D464();
    }
    temp_r10 = (Unk_9994C3F5 *)lbl_803CAF18;
    temp_r9_2 = (u8 *)temp_r10->unk0x8;
    *temp_r9_2 = 0x38;
    temp_r10->unk0x8 = (s32) (temp_r9_2 + 1);
    temp_r11 = (CStruct *)lbl_803CAF18;
    if ((u32) (temp_r11->unk0x8 + 2) > (u32) temp_r11->unk0xC) {
        fn_8028D464();
    }
    temp_r8 = (Unk_9994C3F5 *)lbl_803CAF18;
    temp_r9_3 = (u8 *)temp_r8->unk0x8;
    temp_r30 = (((arg1 - 1) << 0xC) & 0xF000) | arg0;
    *temp_r9_3 = (u8) (arg2 >> 8U);
    temp_r8->unk0x8 = (s32) (temp_r9_3 + 1);
    temp_r10_2 = (Unk_9994C3F5 *)lbl_803CAF18;
    temp_r9_4 = (u8 *)temp_r10_2->unk0x8;
    *temp_r9_4 = (u8) arg2;
    temp_r10_2->unk0x8 = (s32) (temp_r9_4 + 1);
    temp_r11_2 = (CStruct *)lbl_803CAF18;
    if ((u32) (temp_r11_2->unk0x8 + 2) > (u32) temp_r11_2->unk0xC) {
        fn_8028D464();
    }
    temp_r10_3 = (Unk_9994C3F5 *)lbl_803CAF18;
    temp_r9_5 = (u8 *)temp_r10_3->unk0x8;
    *temp_r9_5 = (u8) (temp_r30 >> 8U);
    temp_r10_3->unk0x8 = (s32) (temp_r9_5 + 1);
    temp_r11_3 = (Unk_9994C3F5 *)lbl_803CAF18;
    temp_r9_6 = (u8 *)temp_r11_3->unk0x8;
    *temp_r9_6 = (u8) temp_r30;
    temp_r11_3->unk0x8 = (s32) (temp_r9_6 + 1);
}
