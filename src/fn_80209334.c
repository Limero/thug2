// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209334-0x802093E8 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
// Removes value arg1 from the s32 list at arg0+0x124C (count at +0x1248):
// shifts the tail left over the removed slot and decrements the count.
// Suggested rename: fn_80209334_list_remove_value.
#include "types.h"
#include "structs.h"
void fn_80209334(Unk_90685748 *arg0, s32 arg1) {
    s32 temp_r9;
    s32 var_r7;
    s32 *var_r8;
    s32 var_r6;
    s32 *var_r5;
    s32 temp_r0;
    s32 var_r10;
    char *var_r11;
    s32 var_ctr;
    char *var_r3_2;
    s32 var_r10_2;
    char *var_r11_2;
    s32 var_r9_2;

    temp_r9 = arg0->unk0x1248;
    var_r7 = 0;
    if (var_r7 < temp_r9) {
        var_r8 = (s32 *)((char *)arg0 + 0x124C);
        var_r6 = 0;
        var_r5 = var_r8;
        do {
            temp_r0 = *var_r8;
            var_r8 += 1;
            if (temp_r0 == arg1) {
                var_r10 = var_r7;
                if (var_r10 < temp_r9 - 1) {
                    var_r11 = (char *)(var_r6 + (s32)var_r5);
                    do {
                        *(s32 *)var_r11 = ((Unk_4C649A8C *)var_r11)->unk0x4;
                        var_r10 += 1;
                        var_r11 += 4;
                    } while (var_r10 < (arg0->unk0x1248) - 1);
                }
                (arg0->unk0x1248) -= 1;
            }
            temp_r9 = arg0->unk0x1248;
            var_r7 += 1;
            var_r6 += 4;
        } while (var_r7 < temp_r9);
    }
    var_ctr = 100;
    var_r3_2 = (char *)arg0 + 0xA78;
    var_r10_2 = 0;
    __asm__("" : "+r"(var_r10_2));
    var_r11_2 = var_r3_2;
    __asm__("" : "+r"(var_r11_2));
    var_r9_2 = 0;
    do {
        if (*(s32 *)(var_r9_2 + (s32)var_r11_2) == arg1) {
            *(s32 *)(var_r9_2 + (s32)var_r3_2) = var_r10_2;
        }
        var_r9_2 += 0x14;
    } while (--var_ctr != 0);
}
