// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB050-0x801BB0B0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void AddChecksum(CStruct *, s32, s32);

bool fn_801BB050(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    if ((s32) arg0->unk0x20 == 1) {
        AddChecksum(arg2->unk0x18, QB_GENDER, QB_FEMALE);
    } else {
        AddChecksum(arg2->unk0x18, QB_GENDER, QB_MALE);
    }
    return true;
}
