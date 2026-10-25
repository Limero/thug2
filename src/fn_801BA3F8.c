// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BA3F8-0x801BA464 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void AddChecksum(CStruct *, s32, s32);

bool fn_801BA3F8(CStruct *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_NODE_TO, arg0->unk0x5C);
    AddChecksum(arg2->unk0x18, QB_NODE_FROM, arg0->unk0x58);
    AddChecksum(arg2->unk0x18, QB_NODE_NEXT, arg0->unk0x60);
    return true;
}
