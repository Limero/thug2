// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7E60-0x800B7EAC (76B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern bool lbl_80301B14;
extern bool lbl_80301B18;
bool ScriptToggleRigidBodyDebug(CStruct *pParams, CScript *pScript) {
    if (lbl_80301B14 != 0) {
        if (lbl_80301B18 != 0) {
            lbl_80301B14 = 0;
            lbl_80301B18 = 0;
        } else {
            lbl_80301B18 = 1;
        }
    } else {
        lbl_80301B14 = 1;
    }
    return true;
}
