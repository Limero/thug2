// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9970-0x801B99A8 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_801B9970(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_LOGICSTATE, arg0->unk0x28);
    return true;
}
