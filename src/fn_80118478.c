// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118478-0x801184E0 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029D2F4[];
void GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128A90(CStruct *, void *);

bool ScriptDumpFragments(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0x3C00;
    GetInteger(pParams, 0, &sp8, 0);
    if (fn_80128A90(pParams, (s32)lbl_8029D2F4) != 0) {
        sp8 <<= 10;
    }
    return true;
}