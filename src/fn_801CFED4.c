// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CFED4-0x801CFF0C (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_801CFED4(Unk_999439AE *arg0, s32 dummy, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_PITCH_BAIL_DIR, arg0->unk0x318);
    return true;
}
