// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D55A8-0x800D5624 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct * arg0, s32 arg1);
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
bool fn_800D55A8(Unk_C7387A53 *arg0, CStruct *arg1) {
    if (ContainsFlag(arg1, -QB_UNKNOWN_0x2BBC5D44) != 0) {
        *((u32 *)&arg0->unk0x20) &= QB_UNKNOWN_0xFFFFFEFF;
    } else {
        *((u32 *)&arg0->unk0x20) |= 0x100;
        GetFloat(arg1, 0, (void *)(arg0->unk0xC + 0x5C), 0);
    }
    return true;
}
