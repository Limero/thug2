// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015EA20-0x8015EB38 (280B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EC0;
extern s32 lbl_80305EFC;
extern f32 lbl_802A8230;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 IsTrue(s32, void *);
s32 fn_801A7120(Unk_93C2DF4D *, s32);
s32 fn_801A5DAC(s32, s32);
s32 fn_801A5D88(Unk_C7387A53 *);
s32 fn_801A5210(s32, void *);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptGetStatValue(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    f32 temp_f13;
    Unk_4915AEDE *var_r31;

    var_r31 = lbl_80305EAC;
    temp_f13 = var_r31->unk0x420;
    if (temp_f13 != lbl_802A8230) {
        var_r31 = (s32)temp_f13;
        AddChecksum(pScript->unk0x18, QB_OVERRIDDEN, QB_OVERRIDDEN);
    } else {
        GetChecksum_2(pParams, 0, &sp8, 1);
        if (IsTrue(lbl_80305EC0, QB_IS_CLASSIC) != 0) {
            var_r31 = fn_801A7120(var_r31->unk0x24, sp8);
        } else {
            var_r31 = lbl_80305EFC;
            var_r31 = fn_801A5210(
                (GetChecksum_2(pParams, QB_SKATER, &spC, 0) != 0)
                    ? fn_801A5DAC(var_r31, spC)
                    : fn_801A5D88(var_r31),
                sp8);
        }
    }
    AddInteger(pScript->unk0x18, QB_STAT_VALUE, var_r31);
    return true;
}
