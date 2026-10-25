// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80215AF0-0x80215B28 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_80215AF0(Unk_10F6FD8D *arg0, s32 dummy, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_HANGINITANIMTYPE, arg0->unk0x19C4);
    return true;
}
