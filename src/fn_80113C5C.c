// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80113C5C-0x80113CC4 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_8029D118[];

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128A90(CStruct *, s32);
void SetTrackForbiddenStatus(s32, s32, s32);

bool ScriptChangeTrackState(CStruct *pParams, CScript *pScript) {
    s32 sp8 = 0;

    GetInteger(pParams, 0, &sp8, 0);
    SetTrackForbiddenStatus(sp8, fn_80128A90(pParams, (s32)lbl_8029D118), 0);
    return true;
}
