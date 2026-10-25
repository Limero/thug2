// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011850C-0x801185F4 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301B48;
s32 GetText(CStruct *, void *, void *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F2F90(Unk_C7387A53 *);
s32 Script_GenerateCRC(s32);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(Unk_C7387A53 *, s32);
bool ScriptUnloadAnim(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r31;
    s32 var_r4;

    temp_r31 = lbl_80301B48;
    sp8 = 0;
    GetText(pParams, QB_NAME, &sp8, 1);
    spC = 0;
    sp10 = 0;
    GetChecksum_2(pParams, QB_DESCCHECKSUM, &spC, 1);
    if (GetChecksum_2(pParams, QB_REFCHECKSUM, &sp10, 0) == 0) {
        sp10 = fn_800F2F90(temp_r31);
    }
    if (spC != 0) {
        var_r4 = fn_800F2A48(temp_r31, spC + sp10, 0);
    } else {
        var_r4 = fn_800F2A48(temp_r31, Script_GenerateCRC(sp8), 0);
    }
    if (var_r4 != 0) {
        fn_800F28E4(temp_r31, var_r4);
    }
    return true;
}