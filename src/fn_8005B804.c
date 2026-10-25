// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B804-0x8005B848 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802935B8;
extern f32 lbl_80366438[];
extern bool lbl_80366448;
f32 *fn_8005B804(void) {
    if (lbl_80366448 == 0) {
        f32 v = lbl_802935B8;
        lbl_80366448 = 1;
        lbl_80366438[0] = v;
        lbl_80366438[1] = v;
        lbl_80366438[2] = v;
        lbl_80366438[3] = v;
    }
    return lbl_80366438;
}
