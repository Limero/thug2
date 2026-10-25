// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DDE8-0x8002DE3C (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802918B8;
void fn_8002DE3C(void *);
void fn_8002DDE8(char *arg0, f32 farg0) {
    volatile double _dummy;
    f32 f31;
    f31 = *(f32 *)(arg0 + 0x24);
    *(f32 *)(arg0 + 0x24) = lbl_802918B8;
    *(f32 *)(arg0 + 0x1c) += farg0;
    fn_8002DE3C(arg0);
    *(f32 *)(arg0 + 0x24) = f31;
}
