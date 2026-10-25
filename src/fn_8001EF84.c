// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EF84-0x8001EFBC (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: dispatch-setter through the fn-ptr table at lbl_80300288 (sdata):
// 2-arg: sets (arg0&1)|0x100A + *arg1; call is prototyped ((**)(s32,s32) — no crclr in want).
// EXACT via the unprototyped-vs-prototyped fn-ptr-cast spelling (doc-51 zone).
#include "types.h"
extern char lbl_80300288[];
s32 fn_8001EF84(s32 arg0, s32 *arg1) {
    return (*(s32 (**)(s32, s32))lbl_80300288)((arg0 & 1) | 0x100A, *arg1);
}
