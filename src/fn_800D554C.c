// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D554C-0x800D55A8 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct * arg0, s32 arg1);
bool fn_800D554C(Unk_C7387A53 *arg0, CStruct *arg1) {
    u32 v;

    if (ContainsFlag(arg1, -QB_UNKNOWN_0x2BBC5D44) != 0) {
        v = *((u32 *)&arg0->unk0x20);
        v |= 0x10;
        *((u32 *)&arg0->unk0x20) = v;
    } else {
        v = *((u32 *)&arg0->unk0x20);
        v &= QB_UNKNOWN_0xFFFFFFEF;
        *((u32 *)&arg0->unk0x20) = v;
    }
    return true;
}
