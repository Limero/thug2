// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80245128-0x802451A4 (124B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802444D0(Unk_7044F700 *, s32, s32, CStruct *, Unk_C7387A53 *);
void fn_80245128(Unk_09BB4394 *arg0, CStruct *arg1, Unk_C7387A53 *arg2) {
    u32 temp_r29;
    u32 temp_r30;
    CScript *var_r31;

    temp_r29 = (u32) (arg0->unk0x7 + arg0->unk0x9) >> 1U;
    temp_r30 = (u32) (arg0->unk0x8 + arg0->unk0xA) >> 1U;
    var_r31 = *((s32 *)&arg0->unk0xC);
    if (var_r31 != NULL) {
        do {
            fn_802444D0(var_r31, temp_r29, temp_r30, arg1, arg2);
            var_r31 = var_r31->unk0x18;
        } while (var_r31 != NULL);
    }
}
