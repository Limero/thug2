// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80008F20-0x80008FE4 (196B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80008F20(Unk_DB0E2BAB *arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r11;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r8;
    s32 var_r4;
    s32 var_r5;

    var_r4 = arg1;
    var_r5 = arg2;
    temp_r8 = arg0->unk0xC;
    arg0->unk0x14 = (s32) (arg0->unk0x14 + var_r5);
    if (temp_r8 < var_r5) {
        temp_r11 = 0x20 - temp_r8;
        temp_r0 = (arg0->unk0x8 & ((1 << temp_r11) - 1)) | (var_r4 << temp_r11);
        arg0->unk0x8 = temp_r0;
        **((s32 * *)&arg0->unk0x0) = temp_r0;
        var_r5 -= temp_r8;
        arg0->unk0x8 = 0;
        var_r4 = var_r4 >> temp_r8;
        arg0->unk0xC = 0x20;
        arg0->unk0x0 = (s32 *) (arg0->unk0x0 + 4);
    }
    temp_r0_2 = arg0->unk0xC;
    temp_r5 = temp_r0_2 - var_r5;
    temp_r0_3 = 0x20 - temp_r0_2;
    arg0->unk0xC = temp_r5;
    temp_r4 = (arg0->unk0x8 & ((1 << temp_r0_3) - 1)) | (var_r4 << temp_r0_3);
    arg0->unk0x8 = temp_r4;
    if (temp_r5 == 0) {
        **((s32 * *)&arg0->unk0x0) = temp_r4;
        arg0->unk0xC = 0x20;
        arg0->unk0x8 = temp_r5;
        arg0->unk0x0 = (s32 *) (arg0->unk0x0 + 4);
    }
}
