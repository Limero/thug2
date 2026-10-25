// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801555B8-0x801556DC (292B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE54;
extern s32 lbl_802FFE98;
extern s32 lbl_80301B48;
extern char lbl_802A7F94[];

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 Script_GenerateCRC(s32);
s32 fn_800F2A48(s32, s32, s32);
void fn_800F28E4(Unk_C7387A53 *, CStruct *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_800F2EDC(CScript *, s32, s32, s32, s32, s32);
void fn_8000F320(Unk_F12C5E01 *);

bool ScriptReloadAnim(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r30;
    s32 temp_r3;
    s32 temp_r4;
    Unk_C7387A53 *temp_r3_2;

    sp8 = 0;
    GetChecksum_2(pParams, QB_REFERENCECHECKSUM, &sp8, 0);
    spC = 0;
    GetChecksum_2(pParams, QB_ANIM, &spC, 0);
    sp10 = (s32)lbl_802A7F94;
    GetString(pParams, QB_FILENAME, &sp10, 0);
    var_r30 = lbl_80301B48;
    temp_r3 = Script_GenerateCRC(sp10);
    if (spC != 0) {
        temp_r3 = spC + sp8;
    }
    temp_r4 = fn_800F2A48(var_r30, temp_r3, 0);
    if (temp_r4 == 0) {
        return false;
    }
    fn_800F28E4(var_r30, temp_r4);
    if (lbl_802FFE54 != 0) {
        temp_r3_2 = (void *)lbl_802FFE98;
        fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x178);
    }
    fn_800F2EDC(var_r30, sp10, spC, sp8, 0, 0);
    if (lbl_802FFE54 != 0) {
        fn_8000F320((void *)lbl_802FFE98);
    }
    return true;
}
