// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015491C-0x80154950 (52B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80128E34(CStruct *, void *, void *, s32);
// ScriptOmnigonAllowed @ 0x8015491C
bool ScriptOmnigonAllowed(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    fn_80128E34(pParams, QB_CHEAT_FLAG, &sp8, 1);
    return true;
}
