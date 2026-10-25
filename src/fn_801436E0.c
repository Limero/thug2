// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801436E0-0x8014385C (380B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern s32 lbl_80303150;
s32 fn_80141FA4(Unk_5FCDF30E *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_801A5610(s32, s32);
s32 fn_801A572C(s32);
s32 fn_801A5848(s32);
s32 fn_801A56F4(s32);
void fn_80009314(CStruct *, void *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, void *, void *, s32);
s32 Tmr_GetTime(void);
void strcpy(void *, s32);
void fn_801F0FC4(Unk_C7387A53 *);
void fn_801436E0(Unk_F8E9878F *arg0, s32 arg1) {
    s32 *temp_r9;
    s32 temp_r30;
    s32 sp8;
    s32 temp_r3;
    char *temp_r27;
    char *temp_r28;
    CStruct *temp_r30_2;
    s32 temp_t120;

    temp_r30 = lbl_802FFE98;
    temp_r27 = (char *)arg0 + (s32)0x170;
    temp_r28 = (char *)arg1 + (s32)0x6C;
    temp_r9 = (s32 *)((char *)temp_r30 + (s32)0x1A4);
    fn_8000F2F8(temp_r30, *(s32 *)((char *)temp_r9 + (fn_80141FA4(arg0) << 2)));
    arg0->unk0x118 = fn_801A5610(arg1, QB_PUSHSTYLE);
    arg0->unk0x120 = (fn_801A5610(arg1, QB_STANCE) ^ QB_GOOFY) == 0;
    arg0->unk0x124 = fn_801A572C(arg1);
    fn_80009314((void *)temp_r27, fn_801A5848(arg1));
    arg0->unk0x11C = 0;
    GetInteger((s32)temp_r28, QB_IS_MALE, (char *)arg0 + (s32)0x128, 1);
    GetChecksum_2((s32)temp_r28, QB_SKATESTYLE, (char *)arg0 + (s32)0x11C, 0);
    GetText((s32)temp_r28, QB_FIRST_NAME, &sp8, 1);
    strcpy((char *)arg0 + (s32)0x12C, sp8);
    arg0->unk0x16C = fn_801A56F4(arg1);
    if ((s32)arg0->unk0xC8 != 0) {
        temp_t120 = arg0->unk0x120;
        temp_r3 = temp_t120 ^ 1;
        temp_r30_2 = (s32)(*(s32 *)((char *)(arg0->unk0x2AC) + (s32)0x15BC)) + (s32)0x30;
        if (temp_r30_2->unk0x4 != temp_r3) {
            temp_r30_2->unk0x4 = temp_r3;
            temp_r30_2->unk0x8 = lbl_80303150 + Tmr_GetTime();
        }
        fn_801F0FC4(GetChecksum_3((s32)arg0, QB_SKATERFLIPANDROTATE));
    }
    fn_8000F320(lbl_802FFE98);
}
