// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E96C-0x8009E9A4 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_8009E96C(CScript *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_OBJID, arg0->unk0x18);
    return true;
}
