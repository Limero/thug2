// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003EED8-0x8003EF48 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
bool fn_8003EED8(f32 *arg0, f32 *arg1, f32 *arg2) {
    if (arg0[0] > arg1[0]) return false;
    if (arg0[1] > arg1[1]) return false;
    if (arg0[2] > arg1[2]) return false;
    if (arg0[0] < arg2[0]) return false;
    if (arg0[1] < arg2[1]) return false;
    if (arg0[2] < arg2[2]) return false;
    return true;
}
