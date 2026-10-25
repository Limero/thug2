// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA2B4-0x801FA318 (100B). Byte-identical.
// extra_cflags: -fno-strength-reduce -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void fn_801FA2B4(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 var_r9;
    void *var_r3;
    void *var_r4;

    var_r4 = arg1;
    var_r3 = arg0 + 0x38;
    var_r9 = 0x1128;
    do {
        var_r9 -= 0x18;
        ((Unk_DB0E2BAB *)var_r3)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x0;
        ((Unk_DB0E2BAB *)var_r3)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x4;
        ((Unk_DB0E2BAB *)var_r3)->unk0x8 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x8;
        ((Unk_DB0E2BAB *)var_r3)->unk0xC = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0xC;
        ((Unk_DB0E2BAB *)var_r3)->unk0x10 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x10;
        temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x14;
        var_r4 += 0x18;
        ((Unk_DB0E2BAB *)var_r3)->unk0x14 = temp_r0;
        var_r3 += 0x18;
    } while (var_r9 != 0);
    ((Unk_DB0E2BAB *)var_r3)->unk0x0 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x0;
    ((Unk_DB0E2BAB *)var_r3)->unk0x4 = (s32) ((Unk_DB0E2BAB *)var_r4)->unk0x4;
    *((u16 *)&((Unk_DB0E2BAB *)var_r3)->unk0x8) = *((u16 *)&((Unk_DB0E2BAB *)var_r4)->unk0x8);
}
