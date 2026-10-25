// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EA78-0x8009EAC4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_8009EA78(Unk_C7387A53 *arg0) {
    s32 temp_r3;

    temp_r3 = fn_8009EEAC();
    if (temp_r3 == 0) {
        return false;
    }
    arg0->unk0x28 = (s32) (arg0->unk0x28 | temp_r3);
    return true;
}
