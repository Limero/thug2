// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F49A0-0x800F4A78 (216B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
s32 GetChecksum_2(void *, void *, void *, void *);
s32 ContainsFlag(void *, s32);
#include "qb_constants.h"
#include "structs.h"
s32 fn_800F3A1C(s32);
void fn_800F49A0(Unk_C7387A53 *arg0, void *arg1, CStruct *arg2) {
    s32 *temp_r3;
    char *var_r9;
    s32 temp_r0;
    s32 var_r11;
    char *var_r4;

    temp_r3 = (s32 *)fn_800F3A1C(0x48);
    arg0->unk0x54 = (s32)temp_r3;
    __asm__ volatile("li %0,0" : "=r"(temp_r0) : "r"(temp_r3));
    *((s32 *)temp_r3) = temp_r0;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x54) + 0x4) = temp_r0;
    if (arg1 != NULL) {
        var_r9 = (char *)arg0->unk0x54;
        var_r4 = (char *)arg1;
        var_r11 = 0x48;
        do {
            var_r11 -= 0x18;
            *(s32 *)(var_r9 + 0x0) = *(s32 *)(var_r4 + 0x0);
            *(s32 *)(var_r9 + 0x4) = *(s32 *)(var_r4 + 0x4);
            *(s32 *)(var_r9 + 0x8) = *(s32 *)(var_r4 + 0x8);
            *(s32 *)(var_r9 + 0xC) = *(s32 *)(var_r4 + 0xC);
            *(s32 *)(var_r9 + 0x10) = *(s32 *)(var_r4 + 0x10);
            temp_r0 = *(s32 *)(var_r4 + 0x14);
            var_r4 += 0x18;
            *(s32 *)(var_r9 + 0x14) = temp_r0;
            var_r9 += 0x18;
        } while (var_r11 != 0);
    }
    if (arg2 != 0) {
        GetChecksum_2(arg2, QB_SCENE, arg0->unk0x54, 0);
        *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x54) + 0x4) = ContainsFlag(arg2, QB_IS_NET);
    }
}
