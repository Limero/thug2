// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241D58-0x80241E38 (224B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern void* lbl_802FFE98;
void *fn_8000F10C(Unk_4897C6F8 * arg0, s32 arg1, s32 arg2, Unk_E15B2970 * arg3);
void fn_80241D58(Unk_C7387A53 *arg0, s32 arg1) {
    CStruct *temp_r11;
    void *temp_r9;
    u32 temp_r0;
    s32 temp_r10;
    s32 temp_r8;
    s32 temp_r0_2;
    void *var_r29;
    s32 var_r5;
    CStruct *var_r7;
    u32 var_r6;

    var_r29 = NULL;
    if (arg1 > 2) {
        var_r29 = fn_8000F10C(lbl_802FFE98, (arg1 - 2) * 0xC, 1, 0);
    }
    if (var_r29 != NULL) {
        if (*((u32 *)&arg0->unk0x28) != 0) {
            temp_r0 = *((u32 *)&arg0->unk0x2C);
            if (temp_r0 > (u32)arg1) {
                goto after;
            }
            var_r6 = 2;
            if (var_r6 >= temp_r0) {
                goto after;
            }
            var_r7 = var_r29;
            var_r5 = 0x18;
            do {
                var_r6 += 1;
                temp_r9 = (char *)(var_r5 + *((u32 *)&arg0->unk0x28));
                temp_r11 = temp_r9 - 0x18;
                temp_r10 = *(s32 *)((char *)temp_r9 - 0x18);
                temp_r0_2 = temp_r11->unk0x4;
                var_r5 += 0xC;
                temp_r8 = temp_r11->unk0x8;
                var_r7->unk0x0 = temp_r10;
                var_r7->unk0x4 = temp_r0_2;
                var_r7->unk0x8 = temp_r8;
                var_r7 = (char *)var_r7 + 0xC;
            } while (var_r6 < *((u32 *)&arg0->unk0x2C));
after:;
        }
    }
    if (*((u32 *)&arg0->unk0x28) != 0) {
        Mem_Free((void *)*((u32 *)&arg0->unk0x28));
    }
    *((u32 *)&arg0->unk0x28) = (u32)var_r29;
    *((u32 *)&arg0->unk0x2C) = (u32)arg1;
}
