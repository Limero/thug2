// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5714-0x800D5770 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(CStruct *, s32);
bool fn_800D5714(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 var_r0;
    if (ContainsFlag(arg1, QB_OFF) != 0) {
        var_r0 = arg0->unk0x20 & ~0x200;
    } else {
        var_r0 = arg0->unk0x20 | 0x200;
    }
    arg0->unk0x20 = var_r0;
    return true;
}
