// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80077630-0x80077678 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80096D38(void *);
void fn_80077630(f32 *arg0, f32 farg0) {
    f32 sp8[4];
    f32 *p = sp8;
    sp8[0] = arg0[0];
    sp8[1] = arg0[1];
    p[2] = arg0[2];
    sp8[3] = farg0;
    fn_80096D38(p);
}
