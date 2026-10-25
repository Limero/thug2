// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802395B8-0x80239604 (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_802395B8(s32 unk, Unk_E9E106BA *base, s32 *arg2, s32 *arg3, u16 *arg4, s32 *arg5, s32 *arg6, s32 *arg7) {
    s32 temp_r0;

    *arg6 = base->unk0xE;
    *arg7 = base->unk0xF;
    *arg2 = base->unk0x12;
    *arg3 = base->unk0x10;
    *arg4 = base->unk0x8;
    temp_r0 = base->unk0x18;
    if (temp_r0 != 0) {
        *arg5 = temp_r0;
        return;
    }
    *arg5 = QB_DEFAULT;
}
