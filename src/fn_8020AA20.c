// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020AA20-0x8020ABF8 (472B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_800AA9DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_80207430(void *arg0, s32 arg1, s32 arg2);

register s32 r31_guard __asm__("r31");

void fn_8020AA20(Unk_C7387A53 *arg0) {
    Unk_C7387A53 *temp_r9;
    u32 temp_r28;
    s32 var_r29;

    temp_r9 = *((void * *)&arg0->unk0x24);
    temp_r28 = *((u32 *)&temp_r9->unk0x20);
    var_r29 = fn_800AA9DC((temp_r28 >> 6) & 1, (temp_r28 >> 7) & 1, (temp_r28 >> 5) & 1, (temp_r28 >> 4) & 1);
    fn_80207430(arg0, 1, var_r29 == 1);
    fn_80207430(arg0, 2, var_r29 == 2);
    fn_80207430(arg0, 3, var_r29 == 3);
    fn_80207430(arg0, 4, var_r29 == 4);
    fn_80207430(arg0, 5, var_r29 == 5);
    fn_80207430(arg0, 6, var_r29 == 6);
    fn_80207430(arg0, 7, var_r29 == 7);
    fn_80207430(arg0, 8, var_r29 == 8);
    fn_80207430(arg0, 9, (temp_r28 >> 9) & 1);
    fn_80207430(arg0, 0xA, (temp_r28 >> 0xB) & 1);
    fn_80207430(arg0, 0xC, (temp_r28 >> 8) & 1);
    fn_80207430(arg0, 0xB, (temp_r28 >> 0xA) & 1);
    fn_80207430(arg0, 0xD, (temp_r28 >> 0xC) & 1);
    fn_80207430(arg0, 0xE, (temp_r28 >> 0xE) & 1);
    fn_80207430(arg0, 0xF, (temp_r28 >> 0x10) & 1);
    fn_80207430(arg0, 0x10, (temp_r28 >> 0xD) & 1);
    fn_80207430(arg0, 0x11, (temp_r28 >> 0xF) & 1);
    fn_80207430(arg0, 0x12, (temp_r28 >> 0x11) & 1);
    fn_80207430(arg0, 0x13, (temp_r28 >> 0x16) & 1);
    fn_80207430(arg0, 0x14, (temp_r28 >> 0x17) & 1);
    fn_80207430(arg0, 0x15, (temp_r28 >> 0x18) & 1);
}
