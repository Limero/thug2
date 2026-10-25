// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023590C-0x8023597C (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2 -fno-strength-reduce
#include "types.h"
#include "structs.h"
typedef struct Cpy18_590C { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; } Cpy18_590C;

void fn_8023590C(Unk_673C6403 *arg0, void *arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r9;
    s32 var_r11;
    Cpy18_590C *var_r4;
    Cpy18_590C *var_r9;

    var_r4 = (Cpy18_590C *)arg1;
    var_r9 = (Cpy18_590C *)((char *)arg0 + 0x10000);
    var_r11 = 0x3A98;
    var_r9 = (Cpy18_590C *)((char *)var_r9 + 0x3C94);
    do {
        var_r11 -= 0x18;
        var_r9->f0 = var_r4->f0;
        var_r9->f4 = var_r4->f4;
        var_r9->f8 = var_r4->f8;
        var_r9->fC = var_r4->fC;
        var_r9->f10 = var_r4->f10;
        temp_r0 = var_r4->f14;
        var_r4 += 1;
        var_r9->f14 = temp_r0;
        var_r9 += 1;
    } while (var_r11 != 0);
    temp_r9 = arg0->unk0x1772C;
    arg0->unk0x1772C = (s32) (temp_r9 | 6);
    if (arg2 != 0) {
        arg0->unk0x1772C = (s32) (temp_r9 | 0xE);
    }
}
