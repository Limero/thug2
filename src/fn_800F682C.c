// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F682C-0x800F68D4 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_800F3A1C(s32);
void fn_800F682C(Unk_31DE137E *arg0, void *arg1, s32 arg2) {
    s32 temp_r0;
    s32 var_r9;
    void *var_r3;
    void *var_r4;

    var_r3 = fn_800F3A1C(0x40);
    arg0->unk0x64 = var_r3;
    if (arg1 != NULL) {
        var_r4 = arg1;
        var_r9 = 0x30;
        do {
            var_r9 -= 0x18;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x0;
            ((Unk_DB0E2BAB *)var_r3)->unk0x0 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x4;
            ((Unk_DB0E2BAB *)var_r3)->unk0x4 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x8;
            ((Unk_DB0E2BAB *)var_r3)->unk0x8 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0xC;
            ((Unk_DB0E2BAB *)var_r3)->unk0xC = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x10;
            ((Unk_DB0E2BAB *)var_r3)->unk0x10 = temp_r0;
            temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x14;
            var_r4 += 0x18;
            ((Unk_DB0E2BAB *)var_r3)->unk0x14 = temp_r0;
            var_r3 += 0x18;
        } while (var_r9 != 0);
        temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x0;
        ((Unk_DB0E2BAB *)var_r3)->unk0x0 = temp_r0;
        temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x4;
        ((Unk_DB0E2BAB *)var_r3)->unk0x4 = temp_r0;
        temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0x8;
        ((Unk_DB0E2BAB *)var_r3)->unk0x8 = temp_r0;
        temp_r0 = ((Unk_DB0E2BAB *)var_r4)->unk0xC;
        ((Unk_DB0E2BAB *)var_r3)->unk0xC = temp_r0;
    }
}
