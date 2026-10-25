// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007F7F8-0x8007F980 (392B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8007F7F8(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, u32 *arg3) {
    s32 temp_r0;
    s32 temp_r0_3;
    s32 var_r12;
    s32 var_r31;
    s32 var_r7;
    s32 var_r8;
    s32 var_r9;
    u32 temp_r0_2;
    u32 temp_r6;
    u32 temp_r11;
    Unk_A8B25094 *temp_r11_2;
    Unk_BA2D8CF9 *temp_r7;
    Unk_C7387A53 *temp_r9;
    Unk_1C4D340C *temp_r9_2;

    temp_r9 = arg0->unk0x30;
    var_r31 = 0;
    temp_r6 = *arg3;
    if (temp_r9 != NULL) {
        temp_r9_2 = temp_r9->unk0x54;
        if (temp_r9_2 != NULL) {
            var_r7 = 0;
            /* variable-operand guard: want `cmpw r31,r0` (r31 = the result
               variable, still 0) rather than the folded `cmpwi r0,0` */
            if (var_r31 < (s32) temp_r9_2->unk0x5E) {
                do {
                    temp_r7 = (Unk_BA2D8CF9 *)*(s32 *)((char *)*(s32 *)((char *)*(s32 *)((char *)*(s32 *)((char *)*(s32 *)((char *)*(s32 *)((char *)arg0 + 0x30) + 0x54) + 0x58) + (var_r7 * 4)) + 0x14) + 0x4);
                    if (temp_r7 != NULL) {
                        var_r12 = 0;
                        var_r8 = arg2;
                        temp_r0 = temp_r7->unk0x18;
                        if (temp_r0 == arg1) {
                            var_r12 = 1;
                        } else if ((u32) temp_r0 > (u32) arg1) {
                            temp_r0_2 = temp_r0 - arg1;
                            if (temp_r0_2 <= 0x7FU) {
                                temp_r11 = temp_r0_2 >> 3U;
                                temp_r0_3 = temp_r0_2 & 7;
                                if (temp_r0_3 != 0) {
                                    if (temp_r0_3 == (s32) (arg2 + 1)) {
                                        var_r12 = 1;
                                        var_r8 = 0;
                                    }
                                } else if (((s32) temp_r11 != 0) && (temp_r11 & (1 << arg2))) {
                                    var_r12 = 1;
                                    var_r9 = 0;
                                    /* variable-operand guard: want `cmpw r9,r8` */
                                    if (var_r9 < var_r8) {
                                        do {
                                            if (!(temp_r11 & (1 << var_r9))) {
                                                var_r8 -= 1;
                                            }
                                            var_r9 += 1;
                                        } while (var_r9 < arg2);
                                    }
                                }
                            }
                        }
                        if ((var_r12 != 0) && (var_r8 < (s32) *((u8 *)&temp_r7->unk0x4))) {
                            temp_r11_2 = (Unk_A8B25094 *)(*(s32 *)((char *)*(s32 *)((char *)*(s32 *)((char *)arg0 + 0x30) + 0x54) + 0x38) + ((temp_r7->unk0xC + var_r8) << 5));
                            if (!(*((u16 *)&temp_r11_2->unk0x4) & 0x10)) {
                                /* store run rotated left by one to survive
                                   ngccc's last-first emission (§6k-64) */
                                var_r31 = 1;
                                temp_r11_2->unk0xC = (u8) (temp_r6 >> 0x18);
                                temp_r11_2->unk0xD = (u8) ((temp_r6 & 0xFF0000) >> 0x10);
                                temp_r11_2->unk0xE = (u8) ((temp_r6 & 0xFF00) >> 8);
                                ((Unk_10929AA9 *)temp_r7)->unk0x6 = (u8) (((Unk_10929AA9 *)temp_r7)->unk0x6 | 0x10);
                            }
                        }
                    }
                    var_r7 += 1;
                } while (var_r7 < (s32) ((Unk_1C4D340C *)(*(s32 *)((char *)*(s32 *)((char *)arg0 + 0x30) + 0x54)))->unk0x5E);
            }
        }
    }
    return var_r31;
}
