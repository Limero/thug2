// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004EA60-0x8004EAC0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009E31C(Unk_C7387A53 *, s32, s32);
void SetChecksumTag(Unk_C7387A53 *, s32, s32);
void fn_8004EA60(Unk_CACD1EF6 *arg0) {
    SetChecksumTag(arg0, QB_TAG_SELECTED_ID, arg0->unk0x194);
    fn_8009E31C(arg0, QB_TAG_SELECTED_INDEX, arg0->unk0x190);
    fn_8009E31C(arg0, QB_TAG_SELECTED_CHILDS_GRID_INDEX, arg0->unk0x1C0);
}
