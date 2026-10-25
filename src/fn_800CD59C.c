// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD59C-0x800CD5F0 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800B11D4(s32);
void fn_800CD59C(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;

    if (GetChecksum_2(arg1, QB_PROXIMNODE, &sp8, 0) != 0) {
        arg0->unk0x2C = fn_800B11D4(sp8);
    }
}
