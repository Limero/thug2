// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80164488-0x801644F4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801745B4(s32);
bool ScriptGetSkaterModelIsSwapped(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_B9C514A7 *var_r3;

    if (GetInteger(pParams, QB_SKATER, &sp8, 0) != 0) {
        var_r3 = fn_801746A4(lbl_80305EAC, sp8);
    } else {
        var_r3 = fn_801745B4(lbl_80305EAC);
    }
    return (var_r3->unk0x350 != 0) ? 1 : 0;
}
