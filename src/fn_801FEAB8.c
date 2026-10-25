// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FEAB8-0x801FEAF8 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "types.h"
#include "structs.h"
void AddChecksum(CStruct *, s32, s32);
bool fn_801FEAB8(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    Unk_C7387A53 *temp_r9;

    temp_r9 = arg0->unk0xC;
    AddChecksum(arg2->unk0x18, QB_RUNTIMERID, temp_r9->unk0x2E8 + QB_THE_RUN_TIMER);
    return true;
}
