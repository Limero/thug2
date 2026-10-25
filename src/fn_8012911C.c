// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012911C-0x801291FC (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802FFE98[];
#include "structs.h"
void fn_8000F2F8(Unk_9F352E7C *arg0, s32 arg1);
void *Mem_Alloc_3(u32 size);
void fn_8000F320(Unk_F12C5E01 *self);
s32 *fn_801291FC(CStruct *arg0);
void Mem_Free_3(s32 arg0);
void fn_8012911C(CStruct *arg0, s32 arg1) {
    s32 *temp_r28;
    s32 *var_r3;
    s32 *var_r9;
    s32 temp_r0;
    u32 temp_r0_2;
    u32 var_r11;
    u32 var_r11_2;
    Unk_C7387A53 *temp_r3;

    if (arg1 != (s32) arg0->unk0x4) {
        temp_r3 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
        temp_r28 = Mem_Alloc_3(arg1 * 4);
        fn_8000F320(*(void **)(s32)lbl_802FFE98);
        var_r3 = fn_801291FC(arg0);
        var_r11 = 0U;
        var_r9 = temp_r28;
        while (var_r11 < (u32) arg0->unk0x4) {
            temp_r0 = *var_r3;
            var_r11 += 1;
            var_r3 += 1;
            *var_r9 = temp_r0;
            var_r9 += 1;
        }
        var_r11_2 = 0U;
        temp_r0_2 = arg1 - arg0->unk0x4;
        while (var_r11_2 < temp_r0_2) {
            *var_r9 = 0;
            var_r11_2 += 1;
            var_r9 += 1;
        }
        if ((u32) arg0->unk0x4 > 1U) {
            Mem_Free_3(arg0->unk0x8);
        }
        arg0->unk0x8 = (s32) temp_r28;
        arg0->unk0x4 = arg1;
    }
}
