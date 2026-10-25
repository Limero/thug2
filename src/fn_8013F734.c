// fn_8013F734 / fn_8013F74C / fn_8013F764 — bit-flag getters on a 32-bit
// flags field at offset 0x6C of an object (5th, 6th, 7th matched functions).
//
// Each compiles to the identical 6-instruction leaf pattern:
//   lwz r0, 0x6c(r3); li r3, 1; andi. r9, r0, <bit>; bnelr; li r3, 0; blr
// i.e. `if (flags & BIT) return 1; return 0;` — the ternary form
// `return (flags & BIT) ? 1 : 0` instead compiles to a 3-instruction
// rlwinm bit-extract and does NOT match.
//
// Note: the nearby setters (fn_8013F6E4/8003F708/8003F77C) are parked — they
// contain a `li rX,4; stw rX,8(r1)` dead-store we can't reproduce with any
// available ngccc build or flag (same family as the FPR frame quirk, §4c).
#include "types.h"

typedef struct {
    char pad[0x6C];
    u32 flags; /* offset 0x6C */
} Obj8013F734;

bool fn_8013F734(Obj8013F734 *o) { /* bit 2 (0x4) */
    if (o->flags & 4)
        return true;
    return false;
}

bool fn_8013F74C(Obj8013F734 *o) { /* bit 0 (0x1) */
    if (o->flags & 1)
        return true;
    return false;
}

bool fn_8013F764(Obj8013F734 *o) { /* bit 1 (0x2) */
    if (o->flags & 2)
        return true;
    return false;
}
