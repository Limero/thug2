// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801453E4-0x80145480 (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_801293FC(CStruct *, s32);
void fn_80202448(Unk_09AB3653 *, s32, s32);
void fn_801453E4(Unk_7258DEBD *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r4;
    s32 temp_r5;
    s32 var_r31;
    CScript *temp_r11;
    s32 temp_r30;
    Unk_64253088 *temp_r9;

    register s32 var_z __asm__("r30");

    temp_r11 = arg0->unk0x2B8;
    var_z = 0;
    var_r31 = 0;
    temp_r9 = temp_r11->unk0x18;
    ((s32 (*)(void *, s32))(temp_r9->unk0x34))(
        (void *)((char *)temp_r11 + temp_r9->unk0x30), 0);
    sp8 = var_z;
    GetArray(arg1, QB_STATGOALS, &sp8, 0);
    do {
        temp_r30 = arg0->unk0x2B8;
        temp_r5 = fn_801293FC(sp8, var_r31);
        temp_r4 = var_r31;
        var_r31 += 1;
        fn_80202448(temp_r30, temp_r4, temp_r5);
    } while (var_r31 <= 0x45);
}
