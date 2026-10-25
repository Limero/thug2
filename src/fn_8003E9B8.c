// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E9B8-0x8003EA2C (116B). Byte-identical.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void *fn_8003E9B8(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 var_r10;
    void *var_r11;
    void *var_r9;

    var_r11 = arg0 + 0x40;
    var_r9 = arg1;
    var_r10 = 0x4410;
    do {
        var_r10 -= 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x0;
        ((Unk_DB0E2BAB *)var_r11)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x4;
        ((Unk_DB0E2BAB *)var_r11)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x8;
        ((Unk_DB0E2BAB *)var_r11)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0xC;
        ((Unk_DB0E2BAB *)var_r11)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x10;
        temp_r0 = ((Unk_DB0E2BAB *)var_r9)->unk0x14;
        var_r9 += 0x18;
        ((Unk_DB0E2BAB *)var_r11)->unk0x14 = temp_r0;
        var_r11 += 0x18;
    } while (var_r10 != 0);
    ((Unk_DB0E2BAB *)var_r11)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x0;
    ((Unk_DB0E2BAB *)var_r11)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x4;
    ((Unk_DB0E2BAB *)var_r11)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0x8;
    ((Unk_DB0E2BAB *)var_r11)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r9)->unk0xC;
    return arg1 + 0x4420;
}
