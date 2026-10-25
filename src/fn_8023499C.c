// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023499C-0x802349F0 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
extern char lbl_80305FF8[];
s32 fn_80232F24(s32, s32, s32, s32);
// arg0 = the QB data block, forwarded r3->r3 into GetInteger (matches the
// GetInteger call pattern across the whole Script* family).
bool ScriptSaveParkToDisk(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    sp8 = 0;
    GetInteger(pParams, QB_SLOT, &sp8, 1);
    fn_80232F24(*(s32 *)&lbl_80305FF8, 1, sp8, 0);
    return true;
}