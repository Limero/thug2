// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800346D8-0x80034728 (80B). Byte-identical.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"
bool fn_800346D8(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 var_r9;
    void *var_r3;
    void *var_r4;

    var_r4 = arg1;
    var_r3 = arg0 + 0x18;
    var_r9 = 0x900;
    do {
        var_r9 -= 0x18;
        ((Unk_DB0E2BAB *)var_r4)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r3)->unk0x0;
        ((Unk_DB0E2BAB *)var_r4)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r3)->unk0x4;
        ((Unk_DB0E2BAB *)var_r4)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r3)->unk0x8;
        ((Unk_DB0E2BAB *)var_r4)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r3)->unk0xC;
        ((Unk_DB0E2BAB *)var_r4)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r3)->unk0x10;
        temp_r0 = ((Unk_DB0E2BAB *)var_r3)->unk0x14;
        var_r3 += 0x18;
        ((Unk_DB0E2BAB *)var_r4)->unk0x14 = temp_r0;
        var_r4 += 0x18;
    } while (var_r9 != 0);
    return true;
}
