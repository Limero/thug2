// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801601F0-0x80160264 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern Unk_C7387A53 * lbl_80305F24;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801A6CCC(Unk_93C2DF4D *);
s32 fn_801B0F94(Unk_C7387A53 *, s32);
void fn_801B0C78(Unk_C8FEE62D *, s32);

bool ScriptGetLevelRecords(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_C7387A53 *temp_r31;

    temp_r31 = (void *)lbl_80305EAC;
    if (GetInteger(pParams, QB_LEVEL, &sp8, 0) == 0) {
        sp8 = fn_801A6CCC(temp_r31->unk0x24);
    }
    fn_801B0C78(fn_801B0F94(lbl_80305F24, sp8), pScript->unk0x18);
    return true;
}
