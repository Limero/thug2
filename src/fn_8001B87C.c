// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B87C-0x8001B8B0 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: arg-forwarding thunk through the callback fn-ptr at lbl_80300178
// (.data): passes r3 through unwritten, dispatch constant 12 (0xC) in r4, call
// unprototyped (crclr cr1eq). Part of the 6-member Thunk_CallTable family
// (0x8001B6A8..0x8001B87C). Suggested rename: Thunk_CallTable_12.
#include "types.h"
extern char lbl_80300178[];
s32 fn_8001B87C(s32 arg0) {
    return (*(s32 (**)())lbl_80300178)(arg0, 0xC);
}
