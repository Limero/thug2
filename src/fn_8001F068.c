// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001F068-0x8001F0A0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: dispatch-setter through the fn-ptr table at lbl_80300288 (sdata):
// 1-arg: sets (*arg0>>8)|0xF2000000; call is prototyped ((**)(s32,s32) — no crclr in want).
// EXACT via the unprototyped-vs-prototyped fn-ptr-cast spelling (doc-51 zone).
#include "types.h"
#include "qb_constants.h"
extern char lbl_80300280[];
s32 fn_8001F068(u32 *arg0) {
    return (*(s32 (**)(u32))lbl_80300280)(((u32) *arg0 >> 8U) | QB_UNKNOWN_0xF2000000);
}
