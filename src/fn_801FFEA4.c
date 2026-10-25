// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FFEA4-0x801FFEE8 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_80200264(Unk_F7B42654 *);
void fn_801FFEA4(Unk_F7B42654 * arg0) {
    arg0->unk0xA8 = GetChecksum_3(arg0->unk0xC, QB_CAMERALOOKAROUND);
    fn_80200264(arg0);
}
