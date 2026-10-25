// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80151A64-0x80151B4C (232B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_8009F010(s32, s32, s32);

void fn_80151A64(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 var_r30;
    s32 temp_r0;
    s32 temp_mask;

    var_r30 = 1;
    temp_r0 = arg1->unk0x4;
    arg1->unk0xC = var_r30;
    switch (temp_r0) {
    case 0:
        arg0->unk0x28 =
            arg0->unk0x28 | (var_r30 << arg1->unk0x0);
        goto block_16;
    case 1:
        arg0->unk0x28 =
            arg0->unk0x28 & ~(var_r30 << arg1->unk0x0);
        goto block_16;
    case 2:
        temp_mask = var_r30 << arg1->unk0x0;
        if ((arg0->unk0x28 & temp_mask) == 0) {
            return;
        }
        goto block_16;
    case 3:
        arg0->unk0xC =
            arg0->unk0xC | arg1->unk0x0;
        return;
    case 4:
        arg0->unk0xC =
            arg0->unk0xC & ~arg1->unk0x0;
        return;
    case 5:
        fn_8009F010(arg0, arg1->unk0x0, 0);
        goto block_16;
    case 6:
    default:
        return;
    }
block_16:
    arg1->unk0x8 = var_r30;
}
