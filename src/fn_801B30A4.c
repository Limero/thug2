// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B30A4-0x801B30E8 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8012EE64(Unk_069CE08E *, s32);
void fn_801B30A4(Unk_C7387A53 *arg0) {
    s32 temp;

    temp = arg0->unk0x34;
    if (temp != 0) {
        fn_8012EE64(temp, 3);
        arg0->unk0x34 = 0;
    }
}
