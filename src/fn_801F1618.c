// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1618-0x801F1650 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_801F1618(Unk_31DE137E *arg0, s32 dummy, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_SPARKSPOS, arg0->unk0x194);
    return true;
}
