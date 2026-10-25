// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801834C4-0x801835B4 (240B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801842C0(Unk_C7387A53 *);
void CStruct_delete(CStruct *, s32);
void fn_8018B394(CStruct *, s32);
extern char lbl_802A95C0[];
void fn_801834C4(Unk_31DE137E *arg0, s32 arg1) {
    s32 temp_r0;
    Unk_C8FEE62D *base;
    s32 temp_r0_2;
    CStruct *temp_r11;
    CStruct *temp_r11_2;
    CStruct *var_r10;
    register void *birth __asm__("r9");
    register void *var_r8 __asm__("r8");

    fn_801842C0(arg0);
    if ((s32) arg0->unk0x1C != 0) {
        CStruct_delete(arg0->unk0x1C, 3);
    }
    birth = (char *)arg0 + 0x20;
    temp_r11 = ((Unk_C7387A53 *)birth)->unk0xC;
    base = birth;
    temp_r0 = temp_r11->unk0x4;
    var_r10 = temp_r11;
    if (temp_r0 == -1) {
        var_r10 = NULL;
    }
    if (var_r10 != NULL) {
        do {
            temp_r11_2 = var_r10->unk0xC;
            temp_r0_2 = temp_r11_2->unk0x4;
            var_r8 = temp_r11_2;
            if (temp_r0_2 == -1) {
                var_r8 = NULL;
            }
            *(s32 *)(*(s32 *)((char *)((char *)var_r10) + 0x10) + 0xC) = temp_r11_2;
            *(s32 *)(*(s32 *)((char *)((char *)var_r10) + 0xC) + 0x10) =  var_r10->unk0x10;
            var_r10->unk0xC = var_r10;
            var_r10->unk0x10 = var_r10;
            var_r10 = var_r8;
        } while (var_r10 != NULL);
    }
    base->unk0x14 = (s32)lbl_802A95C0;
    *(s32 *)(*(s32 *)((char *)((char *)base) + 0x10) + 0xC) =  base->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)base) + 0xC) + 0x10) =  base->unk0x10;
    base->unk0xC = base;
    base->unk0x10 = base;
    fn_8018B394((char *)arg0 + 4, 2);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
