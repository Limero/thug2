// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E440-0x8009E474 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 ContainsFlag(s32);
s32 fn_8009E440(Unk_C7387A53 *arg0) {
    s32 temp_r0 = arg0->unk0x24;
    if (temp_r0 == 0) {
        return 0;
    }
    return ContainsFlag(temp_r0);
}