// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A1D4-0x8015A2D0 (252B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_801A2D90(Unk_31DE137E *, s32, Unk_C7387A53 *);
extern void* lbl_80305EAC;
bool ScriptSetSkaterCamAnimShouldPause(CStruct *pParams, CScript *pScript) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    Unk_FFAD6788 *var_r3;

    spC = 0;
    if (GetChecksum_2(pParams, QB_SKATERID, &sp8, 0) != 0) {
        var_r3 = fn_8009F498(sp8);
    } else {
        GetInteger(pParams, QB_SKATER, &spC, 0);
        var_r3 = fn_801746A4(lbl_80305EAC, spC);
    }
    if ((var_r3 != NULL) && (var_r3->unk0xC8 != 0)) {
        sp10 = 0;
        GetChecksum_2(pParams, QB_NAME, &sp10, 0);
        sp14 = 0;
        GetInteger(pParams, QB_SHOULD_PAUSE, &sp14, 0);
        fn_801A2D90(((Unk_40426380 *)lbl_80305EAC)->unk0x378, sp10, sp14 != 0);
    }
    return true;
}
