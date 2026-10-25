// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801506D8-0x80150714 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800EFBB4(s32);
void fn_80128E34(CStruct *, void *, void *, s32);
// ScriptNodeExists @ 0x801506D8
void ScriptNodeExists(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    fn_80128E34(pParams, 0, &sp8, 1);
    fn_800EFBB4(sp8);
}
