// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010B48-0x80010C1C (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_80010A38(void *arg0);
void fn_800107C0(s32 arg0, void *arg1);
extern char lbl_80290648[];
extern char lbl_802906A0[];
void *fn_80010B48(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    CStruct *temp_r10;
    CStruct *temp_r11;
    CStruct *temp_r11_2;
    CStruct *temp_r11_3;
    CStruct *temp_r28;
    Unk_C8FEE62D *temp_r29;
    CStruct *temp_r9;
    s32 zero;

    zero = 0;
    arg0->unk0x80 = (s32)lbl_80290648;
    temp_r11 = (CStruct *)((char *)arg0 + 4);
    temp_r11->unk0x4 = zero;
    temp_r9 = (CStruct *)((char *)arg0 + 0x10);
    temp_r11->unk0x8 = zero;
    temp_r10 = (CStruct *)((char *)arg0 + 0x1C);
    temp_r9->unk0x4 = zero;
    temp_r11_2 = (CStruct *)((char *)arg0 + 0x28);
    temp_r9->unk0x8 = zero;
    temp_r29 = (Unk_C8FEE62D *)((char *)arg0 + 0x48);
    temp_r10->unk0x4 = zero;
    temp_r10->unk0x8 = zero;
    temp_r11_2->unk0x4 = zero;
    temp_r11_2->unk0x8 = zero;
    temp_r28 = (CStruct *)((char *)arg0 + 0x60);
    arg0->unk0x34 = arg1;
    arg0->unk0x38 = arg2;
    arg0->unk0x44 = arg3;
    temp_r29->unk0xC = (s32)temp_r29;
    temp_r29->unk0x10 = (s32)temp_r29;
    temp_r29->unk0x8 = zero;
    temp_r29->unk0x14 = (s32)lbl_802906A0;
    temp_r29->unk0x4 = -1;
    fn_80010A38(temp_r28);
    fn_800107C0(arg0->unk0x34, arg0);
    temp_r11_3 = (CStruct *)((char *)arg0 + 0x64);
    temp_r11_3->unk0x10 = (s32)temp_r29;
    temp_r11_3->unk0xC = temp_r29->unk0xC;
    ((CStruct *)temp_r29->unk0xC)->unk0x10 = (s32)temp_r11_3;
    temp_r29->unk0xC = (s32)temp_r11_3;
    arg0->unk0x40 = (s32)temp_r28;
    return arg0;
}
