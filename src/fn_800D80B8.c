// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D80B8-0x800D80F8 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_800D67D0(Unk_6A70655D *, s32);
void fn_800D80B8(CScript *arg0) {
    fn_800D67D0(arg0, arg0->unk0x1D8);
    arg0->unk0x1C = (s32) ((arg0->unk0x1C | 0x10) & QB_UNKNOWN_0xFFFFFFF7);
}
