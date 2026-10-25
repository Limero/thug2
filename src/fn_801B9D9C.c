// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9D9C-0x801B9DE0 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
bool fn_801B9D9C(Unk_6A70655D *arg0) {
    *((f32 *)&arg0->unk0xE4) = *(f32 *)((char *)GetChecksum_3(arg0->unk0xC, QB_MOTION) + (s32)0x30);
    return true;
}
