// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F15E0-0x801F1618 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddInteger(CStruct *, s32, s32);
bool fn_801F15E0(Unk_2DD055BA *arg0, void *dummy, CScript *arg2) {
    AddInteger(arg2->unk0x18, QB_TERRAIN, (s32)arg0->unk0x148);
    return true;
}
