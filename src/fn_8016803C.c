// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016803C-0x801680AC (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
register s32 r31_guard __asm__("r31");
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_80168890(s32);
s32 s_calculate_total_space_used_on_card(s32, s32);
void AddInteger(CStruct *, s32, s32);
bool ScriptGetMemCardSpaceRequired(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    s32 val;

    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    val = s_calculate_total_space_used_on_card(sp8, fn_80168890(sp8));
    AddInteger(pScript->unk0x18, QB_SPACEREQUIRED, val);
    return true;
}
