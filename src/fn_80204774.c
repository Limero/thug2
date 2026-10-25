// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80204774-0x802047E0 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_80204774(Unk_DB0E2BAB *arg0) {
    extern s32 GetChecksum_3(Unk_6A70655D *, s32);
    extern void fn_80205084(Unk_C8FEE62D *);
    arg0->unk0x1C = GetChecksum_3(arg0->unk0xC, QB_SKATERCOREPHYSICS);
    arg0->unk0x20 = GetChecksum_3(arg0->unk0xC, 0x7713C7B);
    arg0->unk0x24 = GetChecksum_3(arg0->unk0xC, QB_INPUT);
    fn_80205084(arg0);
}