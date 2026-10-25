// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D418-0x8002D4D8 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8002D008(Unk_998B8376 *);
u32 fn_8002CC78(Unk_998B8376 *, s32, s32, s32, s32, s32);
void *fn_8002D418(Unk_FFAD6788 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u32 temp_r3;
    s32 var_r29;
    Unk_998B8376 **var_r31;
    Unk_998B8376 *temp_r9;

    var_r29 = 0;
    var_r31 = (Unk_998B8376 **)((char *)arg0 + 4);
loop_1:
    temp_r9 = *var_r31;
    if (temp_r9->unk0x4 == arg1) {
        return NULL;
    }
    if (fn_8002D008(temp_r9) == 0) {
        temp_r3 = fn_8002CC78(*var_r31, arg1, arg2, arg3, arg4, arg5);
        arg0->unk0xD0 = (s32)(arg0->unk0xD0 + temp_r3);
        if (temp_r3 != 0) {
            arg0->unk0xCC = (s32)(arg0->unk0xCC + 1);
            return *var_r31;
        }
        goto block_6;
    }
    var_r29 += 1;
    var_r31 += 1;
    if (var_r29 > 0x31) {
block_6:
        return NULL;
    }
    goto loop_1;
}
