// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002AE34-0x8002AE6C (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80029A30(s32);
// Gate wrapper: calls fn_80029A30 (large skater-setup helper, itself
// unmatched) only when flag 0x800000 is set on [arg0+4], else returns 0.
// Caller fn_80033C1C passes 6 args; callee ignores args 2-6.
// EXACT via ternary form: result coalesced into r3, arg0 spilled to r9.
// Suggested rename: check_flag_and_setup.
s32 fn_8002AE34(CStruct *arg0) {
    return (arg0->unk0x4 & 0x800000)
               ? fn_80029A30((s32)arg0) : 0;
}
