// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023597C-0x802359A4 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_8023597C(Unk_673C6403 *arg0) {
    s32 temp_r0;

    temp_r0 = arg0->unk0x1772C;
    if (!(temp_r0 & 5) || (temp_r0 & 8)) {
        return false;
    }
    return true;
}
