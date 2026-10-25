// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159E20-0x80159EA0 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddChecksum(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
s32 fn_801746A4(Unk_C7387A53 *, void *);
extern char lbl_80305EAC[];
bool ScriptSkaterExists(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CScript *var_r31;

    var_r31 = NULL;
    if (GetInteger(pParams, QB_SKATER, &sp8, 1) != 0) {
        var_r31 = fn_801746A4(*(s32 *)&lbl_80305EAC, sp8);
    }
    if (var_r31 != NULL) {
        AddChecksum(pScript->unk0x18, QB_OBJID,
                    var_r31->unk0x18);
        return true;
    }
    return false;
}
