// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80107228-0x801072A4 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-spec
#include "types.h"
s32 Mem_Free_3(s32);
typedef struct {
    char _p[0x24];
    s32 unk0x24;
    char _m[4];
    s32 unk0x2C;
} E728;
void fn_80107228(void *arg0) {
    s32 var_r11;
    s32 zero;
    E728 *var_r31;
    s32 var_r30;

    var_r11 = 0;
    zero = 0;
    do {
        var_r31 = (E728 *)((char *)arg0 + ((((var_r11 * 0x10) - var_r11) << 6) + 0x30));
        var_r30 = 0x14;
        do {
            if (var_r31->unk0x2C != 0) {
                Mem_Free_3(var_r31->unk0x2C);
                var_r31->unk0x2C = zero;
            }
            var_r31->unk0x24 = zero;
            var_r31 = (E728 *)((char *)var_r31 + 0x30);
        } while (--var_r30 != 0);
        var_r11 += 1;
    } while (var_r11 <= 0x13);
}
