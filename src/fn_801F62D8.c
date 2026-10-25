// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F62D8-0x801F63F0 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
extern s32 fn_801F626C(void * arg0);
extern s32 fn_801F16E8(s32 arg0);
extern s32 fn_801F443C(Unk_AF33B3CC * arg0);
void fn_801F203C(Unk_5FCDF30E * arg0);
extern void fn_801F559C(Unk_F0C166E4 * arg0);
void fn_801F62D8(Unk_F0C166E4 *arg0) {
    s32 temp_r26;
    s32 var_r10;
    s32 var_r11;
    register s32 var_r27 __asm__("r27");
    register s32 var_r28 __asm__("r28");
    register s32 var_r30 __asm__("r30");
    s32 var_r9;
    void *var_r31;
    char *var_r9_2;
    char *page;
    s32 one;

    var_r28 = 0;
    temp_r26 = fn_801F16E8(fn_801F626C(arg0));
    __asm__ volatile("");
    do {
        var_r27 = 1;
        var_r30 = 0;
        var_r31 = (char *)arg0 + 0x20;
loop_2:
        var_r9 = 1;
        if ((s32) ((Unk_EB543EE2 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if (((var_r9 != 0) && (fn_801F443C(var_r31) != 0)) && (((s32) ((Unk_EB543EE2 *)var_r31)->unk0x0 == temp_r26) && ((s32) ((Unk_EB543EE2 *)var_r31)->unk0x2C0 == var_r28))) {
            var_r28 += 1;
            var_r27 = 0;
        } else {
            var_r30 += 1;
            var_r31 += 0x370;
            if (var_r30 <= 0x31) {
                goto loop_2;
            }
        }
    } while (var_r27 == 0);
    var_r10 = 0;
    page = (char *)arg0 + 0x10000;
    one = 1;
    __asm__ volatile("" ::: "memory");
    var_r9_2 = (char *)arg0 + 0x20;
    for (; var_r10 <= 0x31; var_r10++) {
        var_r11 = 1;
        if ((s32) ((Unk_B140335C *)var_r9_2)->unk0x2BE == 0) {
            var_r11 = 0;
        }
        if (var_r11 == 0) {
            arg0->unk0xAC00 = (s32)var_r9_2;
            fn_801F203C((void *)var_r9_2);
            *(u8 *)(arg0->unk0xAC00 + 0x2BE) = 1;
            *(s32 *)(arg0->unk0xAC00 + 0x0) = temp_r26;
            *(s32 *)(arg0->unk0xAC00 + 0x2C0) = var_r28;
            fn_801F559C(arg0);
            return;
        }
        var_r9_2 += 0x370;
    }
}
