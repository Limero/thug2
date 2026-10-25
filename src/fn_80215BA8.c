// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215BA8-0x80215BEC (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddChecksum(CStruct *, s32, s32);
extern u32 lbl_802AF48C[];
bool fn_80215BA8(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_PREVIOUSSTATE,
                lbl_802AF48C[arg0->unk0x24]);
    return true;
}
