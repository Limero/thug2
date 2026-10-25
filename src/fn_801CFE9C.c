// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CFE9C-0x801CFED4 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_801CFE9C(Unk_9D99273B *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_AMMO_TYPE, arg0->unk0x350);
    return true;
}
