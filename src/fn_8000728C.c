// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000728C-0x80007308 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8000728C(f32 *arg0, f32 *arg1) {
    if (arg1[0] < arg0[0]) {
        arg0[0] = arg1[0];
    }
    if (arg1[1] < arg0[1]) {
        arg0[1] = arg1[1];
    }
    if (arg1[2] < arg0[2]) {
        arg0[2] = arg1[2];
    }
    if (arg1[0] > arg0[4]) {
        arg0[4] = arg1[0];
    }
    if (arg1[1] > arg0[5]) {
        arg0[5] = arg1[1];
    }
    if (arg1[2] > arg0[6]) {
        arg0[6] = arg1[2];
    }
}
