// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A14A8-0x800A14E0 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 AddChecksum(CStruct *, s32, s32);
bool fn_800A14A8(Unk_31DE137E *arg0, s32 arg1, CScript *arg2) {
    AddChecksum(arg2->unk0x18, QB_OBJTYPE, arg0->unk0x1C);
    return true;
}
