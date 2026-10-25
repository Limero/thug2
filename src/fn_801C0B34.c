// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0B34-0x801C0BA0 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801C0B34(Unk_FFAD6788 *arg0, Unk_6A70655D *arg1) {
    if (arg1 != 0) {
        arg0->unk0xA8 = arg1;
        arg0->unk0xAC = GetChecksum_3(arg1, QB_WALK);
        arg0->unk0xB0 = GetChecksum_3(arg0->unk0xA8, QB_SKATERPHYSICSCONTROL);
        return;
    }
    arg0->unk0xA8 = arg1;
    arg0->unk0xAC = arg1;
    arg0->unk0xB0 = arg1;
}
