// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118EEC-0x80118F14 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
// ScriptRandomize @ 0x80118EEC
bool ScriptRandomize(CStruct *pParams, CScript *pScript) {
    fn_800145AC();
    Mth_InitialRand();
    return true;
}
