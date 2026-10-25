// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010C4C8-0x8010C5DC (276B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 Mth_Rnd(s32);

s32 fn_8010C4C8(CStruct *arg0) {
    s32 sp14;
    s32 sp10;
    void *spC;
    s32 sp8;
    s32 var_r30;
    s32 var_r31;

    if (GetStructure_2(arg0, QB_SOUNDACTION, &sp8, 0) != 0) {
        return sp8;
    }
    GetArray(arg0, QB_SOUNDACTION, &spC, 1);
    var_r30 = 0;
    var_r31 = ((CStruct *)spC)->unk0x4;
    for (var_r31 = var_r31 - 1; var_r31 != -1; var_r31--) {
        sp8 = fn_80129528(spC, var_r31);
        GetInteger(sp8, QB_CHANCE, &sp10, 1);
        var_r30 += sp10;
    }
    var_r30 = Mth_Rnd(var_r30);
    var_r31 = ((CStruct *)spC)->unk0x4;
    for (var_r31 = var_r31 - 1; var_r31 != -1; var_r31--) {
        sp8 = fn_80129528(spC, var_r31);
        GetInteger(sp8, QB_CHANCE, &sp14, 1);
        var_r30 -= sp14;
        if (var_r30 < 0) {
            return sp8;
        }
    }
    return 0;
}
