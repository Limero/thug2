// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FB80-0x8003FBF0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_80292308;
extern f32 lbl_8029230C;
extern f32 lbl_80292310;

void fn_8003FB80(u8 *arg0, s32 arg1, f32 f) {
    f32 v = f * lbl_80292308 / lbl_8029230C + lbl_80292310;
    f32 *p = (f32 *)((char *)arg0 + 0xD0);

    if (p[0xF] != v) {
        p[0xF] = v;
        *(s32 *)(arg0 + 0xC) |= 0x400;
    }
    if (arg1 != 0) {
        f32 *q = (f32 *)((char *)arg0 + 0x88);

        if (q[0xF] != v) {
            q[0xF] = v;
            *(s32 *)(arg0 + 0xC) |= 0x400;
        }
    }
}
