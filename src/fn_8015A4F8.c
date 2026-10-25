// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A4F8-0x8015A5C8 (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801A2E88(Unk_31DE137E *, s32);
extern void* lbl_80305EAC;
s32 ScriptSkaterCamAnimHeld(CStruct *pParams, CScript *pScript) {
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
        return fn_801A2E88(((Unk_40426380 *)lbl_80305EAC)->unk0x378, sp10);
    }
    return 1;
}
