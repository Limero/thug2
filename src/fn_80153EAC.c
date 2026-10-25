// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80153EAC-0x80153EF4 (72B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_80305F9C[];
extern char lbl_802A7F00[];

s32 fn_80128A90(CStruct *, void *);
void fn_80219640(CStruct *, s32);

bool ScriptSetServerMode(CStruct *pParams, CScript *pScript) {
    s32 temp_r30;

    temp_r30 = *(s32 *)&lbl_80305F9C;
    fn_80219640(temp_r30, fn_80128A90(pParams, (s32)lbl_802A7F00) ^ 1);
    return true;
}
