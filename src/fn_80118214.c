// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80118214-0x8011825C (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
s32 ContainsFlag(s32, s32);
void fn_80010758(s32);
bool ScriptSetMemThreadSafe(s32 arg0) {
    if (ContainsFlag(arg0, QB_OFF) != 0) {
        fn_80010758(0);
    } else {
        fn_80010758(1);
    }
    return true;
}
