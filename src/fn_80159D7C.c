// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159D7C-0x80159E20 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];

s32 GetInteger(CStruct *, u32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801745B4(s32);
void AddChecksum(CStruct *, u32, s32);

bool ScriptGetSkaterID(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_C8FEE62D *var_r3;

    sp8 = 0;
    if (GetInteger(pParams, QB_SKATER, &sp8, 0) != 0) {
        var_r3 = fn_801746A4(*(s32 *)&lbl_80305EAC, sp8);
    } else {
        var_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
    }
    if ((var_r3 != NULL) && (var_r3->unk0xC8 != 0)) {
        AddChecksum(pScript->unk0x18, QB_OBJID, var_r3->unk0x18);
        return true;
    }
    return false;
}
