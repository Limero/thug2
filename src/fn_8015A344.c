// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A344-0x8015A428 (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801A33BC(Unk_31DE137E *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern void* lbl_80305EAC;
bool ScriptGetSkaterCamAnimParams(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    Unk_FFAD6788 *var_r3;

    sp8 = 0;
    GetChecksum_2(pParams, QB_NAME, &sp8, 0);
    sp10 = 0;
    if (GetChecksum_2(pParams, QB_SKATERID, &spC, 0) != 0) {
        var_r3 = fn_8009F498(spC);
    } else {
        GetInteger(pParams, QB_SKATER, &sp10, 0);
        var_r3 = fn_801746A4(lbl_80305EAC, sp10);
    }
    if ((var_r3 != NULL) && (var_r3->unk0xC8 != 0)) {
        temp_r3 = fn_801A33BC(((Unk_40426380 *)lbl_80305EAC)->unk0x378, sp8);
        if (temp_r3 != 0) {
            fn_80126FF4(pScript->unk0x18, temp_r3);
            return true;
        }
    }
    return false;
}
