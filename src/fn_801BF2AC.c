// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF2AC-0x801BF320 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801BF2AC(Unk_5B483C70 *arg0, Unk_6A70655D *arg1) {
    *((s32 *)&arg0->unk0x17C) = arg1;
    if (arg1 == 0) {
        *((s32 *)&arg0->unk0x180) = arg1;
        arg0->unk0x184 = arg1;
        return;
    }
    *((s32 *)&arg0->unk0x180) = GetChecksum_3(arg1, QB_SKATERSTATE);
    arg0->unk0x184 = GetChecksum_3(*((s32 *)&arg0->unk0x17C), QB_SKATERPHYSICSCONTROL);
    arg0->unk0x30 = 3;
}
