// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E3C3C-0x800E3C84 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
void fn_800E3C3C(Unk_C7387A53 *arg0) {
    s32 temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SUSPEND);
    arg0->unk0x34 = temp_r3;
    if (temp_r3 != 0) {
        fn_800DB364();
    }
}
