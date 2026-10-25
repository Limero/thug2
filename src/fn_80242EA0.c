// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80242EA0-0x80242F80 (224B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80241E38(void *arg0, s32 arg1);
void fn_80242EA0(Unk_ECD1B899 *arg0, Unk_C7387A53 *arg1, Unk_F96D0DC8 *arg2, u8 arg3, u8 arg4) {
    u8 *slot;
    s32 temp_r0;
    s32 temp_r5;
    s32 temp_r7;
    u8 var_c3;
    u8 var_c4;
    u8 var_c5;

    slot = (u8 *)fn_80241E38(arg0, (*((s32 *)&arg0->unk0x30))++);
    if (arg1 != NULL) {
        slot[0] = arg2->unk0x0;
        slot[1] = arg2->unk0x1;
        temp_r0 = arg2->unk0x2;
        slot[3] = arg3;
        slot[2] = (u8)temp_r0;
        slot[4] = arg4;
        *((u32 *)&((Unk_9994C3F5 *)slot)->unk0x8) = *((u32 *)&arg1->unk0x34);
        temp_r7 = arg2->unk0x0 + arg2->unk0x3;
        temp_r0 = (s8) * (u8 *)((char *)arg2 + 1) + arg2->unk0x4;
        temp_r5 = arg2->unk0x2 + arg2->unk0x5;
        var_c3 = arg0->unk0x3;
        var_c5 = arg0->unk0x5;
        var_c4 = arg0->unk0x4;
        if (temp_r7 > var_c3) {
            var_c3 = (u8)temp_r7;
        }
        if (temp_r0 > var_c4) {
            var_c4 = (u8)temp_r0;
        }
        if (temp_r5 > var_c5) {
            var_c5 = (u8)temp_r5;
        }
        arg0->unk0x3 = var_c3;
        arg0->unk0x4 = var_c4;
        arg0->unk0x5 = var_c5;
    }
}
