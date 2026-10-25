// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80079CC4-0x80079DA8 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80079CC4(Unk_9994C3F5 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u32 arg5) {
    s32 temp_r30;
    u32 var_r28;
    s32 var_r31;
    Unk_DE797DC2 *temp_r9;
    Unk_DE797DC2 *temp_r9_2;

    temp_r9 = (Unk_DE797DC2 *)arg0->unk0x8;
    if (temp_r9->unk0x15C((char *)arg0 + *(s16 *)&temp_r9->unk0x158) != 0) {
        temp_r9_2 = (Unk_DE797DC2 *)arg0->unk0x8;
        var_r28 = 0U;
        var_r31 = temp_r9_2->unk0x15C((char *)arg0 + *(s16 *)&temp_r9_2->unk0x158) + (((arg3 * (u16) (1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 0x6))) + arg2) * 4);
        if (var_r28 < arg5) {
            temp_r30 = arg4 * 4;
            do {
                var_r28 += 1;
                memcpy(arg1, var_r31, temp_r30);
                arg1 += temp_r30;
                var_r31 += (((1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 0x6)) << 2) & 0x3FFFC);
            } while (var_r28 < arg5);
        }
    }
}
