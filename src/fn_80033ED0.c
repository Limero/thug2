// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033ED0-0x80033F10 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800C9780(s32);
s32 fn_80033ED0(Unk_9994C3F5 *arg0) {
    s32 temp_r3 = GetChecksum_3(arg0->unk0x8, QB_SKELETON);
    return temp_r3 != 0 ? fn_800C9780(temp_r3) : 0;
}
