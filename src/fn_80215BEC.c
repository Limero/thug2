// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215BEC-0x80215C30 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddChecksum(CStruct *, s32, s32);
extern u32 lbl_802AF48C[];
bool fn_80215BEC(Unk_31DE137E *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_STATE,
                lbl_802AF48C[arg0->unk0x1C]);
    return true;
}
