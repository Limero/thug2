// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A5FF8-0x801A6070 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A65EC(Unk_C8FEE62D *, s32 *, s32 *);
s32 fn_801A572C(s32);
void fn_801A4FF0(CStruct *, s32);
void fn_801A5FF8(Unk_9994C3F5 *arg0, s32 arg1) {
    s32 spC;
    u32 sp8;
    u32 var_r30;
    u32 temp_r29;
    temp_r29 = arg0->unk0x8;
    for (var_r30 = 0U; var_r30 < temp_r29; var_r30++) {
        s32 temp_r31;
        sp8 = var_r30;
        temp_r31 = fn_801A65EC((Unk_C8FEE62D *)((char *)arg0 + 4), &sp8, &spC);
        if (fn_801A572C(temp_r31) == 0) {
            fn_801A4FF0((CStruct *)temp_r31, arg1);
        }
    }
}
