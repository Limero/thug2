// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A150-0x8011A238 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
extern char lbl_80383644[];
extern s32 lbl_80302C44;
void fn_8011EF04(s32 key);
void fn_8011A150(s32 arg1, s32 arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r5;
    register s32 var_r6 __asm__("r6");
    register s32 var_r7 __asm__("r7");
    s32 var_r8;
    void *var_r10;
    void *var_r11;
    void *var_r9;
    s32 key;

    var_r6 = 0;
    temp_r0 = lbl_80302C44;
    key = arg0;
    __asm__("" : "+r"(key));
    if (var_r6 < temp_r0) {
        var_r8 = temp_r0;
        var_r9 = (void *)lbl_80383644;
        var_r5 = (s32)var_r9 - 0x24;
        do {
            if ((*(u8 *)((char *)var_r9 + 6) == 2) && (*(u8 *)((char *)var_r9 + 7) == key)) {
                temp_r0 = var_r8 * 0x24;
                var_r10 = var_r9;
                var_r7 = 0x18;
                var_r11 = (void *)(temp_r0 + var_r5);
                do {
                    var_r7 -= 0x18;
                    ((Unk_DB0E2BAB *)var_r10)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x0;
                    ((Unk_DB0E2BAB *)var_r10)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x4;
                    ((Unk_DB0E2BAB *)var_r10)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x8;
                    ((Unk_DB0E2BAB *)var_r10)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0xC;
                    ((Unk_DB0E2BAB *)var_r10)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x10;
                    temp_r0_2 = ((Unk_DB0E2BAB *)var_r11)->unk0x14;
                    var_r11 += 0x18;
                    ((Unk_DB0E2BAB *)var_r10)->unk0x14 = temp_r0_2;
                    var_r10 += 0x18;
                } while (var_r7 != 0);
                temp_r0_2 = ((Unk_DB0E2BAB *)var_r11)->unk0x0;
                __asm__ __volatile__("addi %0,%0,-1" : "+r"(var_r8));
                ((Unk_DB0E2BAB *)var_r10)->unk0x0 = temp_r0_2;
                ((Unk_DB0E2BAB *)var_r10)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x4;
                ((Unk_DB0E2BAB *)var_r10)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r11)->unk0x8;
            } else {
                var_r9 += 0x24;
                var_r6 += 1;
            }
        } while (var_r6 < var_r8);
        lbl_80302C44 = var_r8;
    }
    fn_8011EF04(key);
}
