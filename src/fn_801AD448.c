// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AD448-0x801AD5DC (404B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern s32 fn_800E9D30(Unk_C7387A53 * arg0, s32 arg1);
s32 fn_801AD3DC(void *arg0, Unk_C7387A53 * arg1, Unk_C7387A53 * arg2);
void fn_801AE5A4(void *arg0, Unk_C8FEE62D * arg1, Unk_C7387A53 * arg2);
s32 fn_801ADCE4(void *arg0, void *arg1);

// MATCHED
bool fn_801AD448(Unk_C7387A53 *arg0, void *arg1, s32 arg2, void **arg3) {
    f32 sp8[4];
    f32 sp18[4];
    register void **a3 __asm__("r25");
    register void *pos __asm__("r26");
    register s32 msk __asm__("r27");
    register s32 var_r28 __asm__("r28");
    register s32 off_r __asm__("r24");
    __ps_t *bufB;
    Unk_C7387A53 *temp_r31;
    s32 var_r9;
    s32 off;

    __asm__ volatile("li %0,0" : "=r"(var_r28));
    pos = arg1;
    msk = arg2;
    a3 = arg3;
    if (var_r28 < arg0->unk0x50) {
        bufB = (__ps_t *)sp18;
        __asm__ volatile("" : "+r"(off_r));
        off_r = 0;
        do {
            temp_r31 = (void *)(arg0->unk0x48 + off_r);
            if (fn_801AD3DC(arg0, temp_r31, pos) != 0) {
                if ((temp_r31->unk0x48 != 0) ||
                    (temp_r31->unk0x4C != NULL)) {
                    if (temp_r31 != pos) {
                        if (temp_r31->unk0x48 != 0) {
                            if (fn_800E9D30(temp_r31, 2) != 0) {
                                var_r9 = (temp_r31->unk0x50 & msk) != 0;
                                if (var_r9 == 0) {
                                    fn_801AE5A4(sp8, arg0, temp_r31);
                                    fn_801AE5A4(sp18, arg0, (void *)temp_r31->unk0x48);
                                    if (fn_801ADCE4(sp8, sp18) != 0) {
                                        *a3 = temp_r31;
                                        return true;
                                    }
                                }
                            }
                        }
                        if (temp_r31->unk0x4C != NULL) {
                            if (fn_800E9D30((void *)temp_r31->unk0x4C, 2) != 0) {
                                var_r9 = (*(s32 *)((char *)(temp_r31->unk0x4C) + 0x50) & msk) != 0;
                                if (var_r9 == 0) {
                                    fn_801AE5A4(sp8, arg0, (void *)temp_r31->unk0x4C);
                                    fn_801AE5A4(sp18, arg0, temp_r31);
                                    if (fn_801ADCE4(sp8, sp18) != 0) {
                                        *a3 = (void *)temp_r31->unk0x4C;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            var_r28 += 1;
            off_r += 0x60;
        } while (var_r28 < arg0->unk0x50);
    }
    return false;
}
