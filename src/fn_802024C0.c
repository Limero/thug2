// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802024C0-0x80202504 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_RunScript(s32, s32, s32, s32, s32);
bool fn_802024C0(Unk_09AB3653 *arg0) {
    arg0->unk0x9F8 = 1;
    Script_RunScript(QB_CONSOLE_UNHIDE, 0, 0, 0, 0);
    return true;
}
