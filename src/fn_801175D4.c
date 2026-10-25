// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801175D4-0x80117620 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8012543C(s32);
void fn_8012DE30(s32);

bool ScriptCleanUpAndRemoveSymbol(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 r;

    GetChecksum_2(pParams, 0, &sp8, 1);
    r = fn_8012543C(sp8);
    if (r == 0) {
        return false;
    }
    fn_8012DE30(r);
    return true;
}
