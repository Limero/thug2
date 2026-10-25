// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD3A0-0x800CD430 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
} CD3A0Entry;

void fn_800CD3A0(Unk_FFAD6788 *arg0, void *arg1, s32 arg2) {
    CD3A0Entry *var_r4;
    char *var_r11;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r10;
    CD3A0Entry *var_r9;
    s32 var_r8;

    var_r4 = (CD3A0Entry *)arg1;
    var_r9 = (CD3A0Entry *)arg0;
    var_r10 = 0;
    var_r11 = (char *)var_r9 + 0x3C;
    var_r8 = 0;
loop_1:
    temp_r0 = *(s32 *)var_r11;
    var_r11 += 0x30;
    if (temp_r0 == 0) {
        var_r9 = (CD3A0Entry *)((char *)var_r9 + 0x3C);
        arg0 = (Unk_FFAD6788 *)&arg0->unk0x68;
        arg2 += 0x7D0;
        var_r11 = (char *)0x30;
        do {
            var_r11 -= 0x18;
            var_r9->unk0x0 = var_r4->unk0x0;
            var_r9->unk0x4 = var_r4->unk0x4;
            var_r9->unk0x8 = var_r4->unk0x8;
            var_r9->unk0xC = var_r4->unk0xC;
            var_r9->unk0x10 = var_r4->unk0x10;
            temp_r0_2 = var_r4->unk0x14;
            var_r4 += 1;
            var_r9->unk0x14 = temp_r0_2;
            var_r9 += 1;
        } while (var_r11 != 0);
        *(s32 *)((char *)arg0 + var_r8) = arg2;
        return;
    }
    var_r10 += 1;
    var_r9 = (CD3A0Entry *)((char *)var_r9 + 0x30);
    var_r8 += 0x30;
    if (var_r10 > 1) {
        return;
    }
    goto loop_1;
}
