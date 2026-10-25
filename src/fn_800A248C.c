// PROMOTED 2026-08-31 — fn_800A248C (byte-identical, verified 15/15 masked)
// range=0x800A248C-0x800A24C8 size=60B (leaf). Registered + DOL byte-identical.
// Anonymous predicate (compare-switch sibling of fn_800A24C8).
//
// MATCHED 2026-08-31 (was parked at 66.7%): the two prior blockers are both
// beaten by the mixed-form recipe below:
//   1. `t0 & 1` proves t0 in {0,1}, so ngccc folds the A-block's
//      `(t0 == 0) ? 1 : 0` into `xori r3,r0,1` (AGENTS.md §4p-7: `(x == 0)`
//      value-returns fold unless blocked). The NON-COMBINABLE XOR operand
//      `(t0 ^ 1) != 0` keeps the branchy form and still canonicalizes to
//      `cmpwi r0,0; li r3,1; beqlr` (recipe-100 / §4p-7 xor-blocker).
//   2. The `if (f & 1) goto B;` block order flips to `[B][A]` + `beq` when
//      BOTH leaf blocks use constant returns — the B-block must keep the
//      r-variable form (`r=1; if (t0!=0) return r; r=0; return r;`), which
//      pins the wanted `[A][B]` + `bne B` layout. A-block constant + B-block
//      r-var is the exact combination.
// Semantics: returns 1 iff bit 0 of arg0[4] equals bit 0 of arg1[0xC]
// (`return (t0 == f) ? 1 : 0` on the two masked bits). No game symbol is
// available for this 0x800A2xxx zone (all fn_ placeholders), so no rename
// suggestion beyond the structural one (e.g. `SameLowBit` / parity-equal
// predicate).
#include "types.h"
#include "structs.h"
s32 fn_800A248C(CStruct *arg0, Unk_C7387A53 *arg1) {
    s32 t0 = arg0->unk0x4 & 1;
    s32 r;
    if ((arg1->unk0xC & 1) != 0) goto B;
    if ((t0 ^ 1) != 0) return 1;
    return 0;
B:
    r = 1;
    if (t0 != 0) return r;
    r = 0;
    return r;
}
