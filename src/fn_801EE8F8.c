// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EE8F8-0x801EE948 (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_801EE8F8(Unk_C8FEE62D *arg0) {
    arg0->unk0x1C = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    arg0->unk0x20 = GetChecksum_3(arg0->unk0xC, QB_SKATERSTATE);
}
