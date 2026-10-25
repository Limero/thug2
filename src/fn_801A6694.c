// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6694-0x801A6734 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801A6694(CStruct *arg0, s32 *arg1) {
    Unk_9994C3F5 *var_r11;
    CStruct *var_r3;

    var_r3 = arg0->unk0x8;
    arg0->unk0x10 = 0;
    var_r11 = 0;
    while (var_r3 != 0) {
        if (var_r3->unk0x0 == *arg1) {
            if (var_r11 != 0) {
                var_r11->unk0x8 = var_r3->unk0x8;
            } else {
                arg0->unk0x8 = var_r3->unk0x8;
            }
            if (arg0->unk0xC == var_r3) {
                arg0->unk0xC = var_r11;
            }
            Mem_Free((void *)var_r3);
            arg0->unk0x4 = (s32) (arg0->unk0x4 - 1);
            return;
        }
        var_r11 = var_r3;
        var_r3 = var_r3->unk0x8;
    }
}
