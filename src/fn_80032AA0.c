// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032AA0-0x80032ACC (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: reads a 32-bit field at 0x3C off a game object (via the
// pass-through helper fn_80032A60 = `o->0x3C`), returns whether that field
// is NOT equal to 1 (the `xori;subfic;adde` fold is `(!(f ^ 1)) == 0` == `f != 1`).
// Sibling: fn_80032A70 returns `!(0x3C == 0)` for the same object.
#include "types.h"
#include "structs.h"
s32 fn_80032A60(Unk_C7387A53 * o);
s32 fn_80032AA0(Unk_C7387A53 *o) {
    s32 temp_r3;

    temp_r3 = fn_80032A60(o) ^ 1;
    return (temp_r3 == 0);
}