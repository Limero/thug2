// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5DBC-0x800A5E8C (208B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_802980E0[];
s32 Mem_NewZero(s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_800A5DBC(CStruct *arg0, s32 arg1) {
    CStruct *temp_r11;
    Unk_C7387A53 *temp_r3;
    Unk_C8FEE62D *temp_r3_2;
    void *temp_r3_3;
    void *temp_r0;
    CStruct *var_r9;
    CStruct *var_r9_2;

    var_r9 = arg0->unk0x10;
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    var_r9_2 = var_r9;
    if (var_r9_2 != NULL) {
loop_3:
        if ((s32) var_r9_2->unk0x4 != arg1) {
            var_r9_2 = var_r9_2->unk0xC;
            if ((s32) var_r9_2->unk0x4 == -1) {
                var_r9_2 = NULL;
            }
            if (var_r9_2 == NULL) {
                goto block_7;
            }
            goto loop_3;
        }
    } else {
block_7:
        temp_r3 = *(void * *)&lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
        temp_r3_2 = Mem_NewZero(0x18);
        temp_r3_3 = *(void * *)&lbl_802FFE98;
        temp_r3_2->unk0x4 = arg1;
        temp_r3_2->unk0xC = temp_r3_2;
        temp_r3_2->unk0x10 = temp_r3_2;
        temp_r3_2->unk0x14 = (s32)lbl_802980E0;
        temp_r3_2->unk0x8 = 0;
        fn_8000F320(temp_r3_3);
        temp_r11 = (char *)arg0 + 4;
        temp_r0 = temp_r11->unk0x10;
        temp_r3_2->unk0xC = temp_r11;
        temp_r3_2->unk0x10 = temp_r0;
        *(s32 *)(*(s32 *)((char *)((char *)temp_r11) + 0x10) + 0xC) = temp_r3_2;
        temp_r11->unk0x10 = temp_r3_2;
    }
}
