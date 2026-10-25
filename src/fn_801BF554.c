// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF554-0x801BF5B8 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801BF554(Unk_6A70655D *arg0) {
    arg0->unk0x9C = GetChecksum_3(arg0->unk0xC, QB_CAMERALOOKAROUND);
    arg0->unk0xA0 = GetChecksum_3(arg0->unk0xC, QB_CAMERA);
    arg0->unk0xA4 = GetChecksum_3(arg0->unk0xC, QB_SKATERCAMERA);
}
