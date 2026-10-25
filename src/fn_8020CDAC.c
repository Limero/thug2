// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020CDAC-0x8020CDF0 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_8020CDAC(Unk_85C3B1D9 *arg0, Unk_6A70655D *arg1) {
    arg0->unk0x1828 = arg1;
    arg0->unk0x182C = GetChecksum_3(arg1, QB_WALKCAMERA);
}
