// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CB038-0x801CB074 (60B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801CB038(Unk_31DE137E *arg0) {
    arg0->unk0x64 = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
}
