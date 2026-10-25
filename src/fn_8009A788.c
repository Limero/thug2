// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009A788-0x8009A898 (272B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f64 lbl_802975A8;
extern f32 lbl_802975B0;
extern f32 lbl_802975B4;
extern f64 lbl_802975B8;
void fn_8009A788(s16 *arg0, u32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    f32 s = lbl_802975B0;
    f32 t = lbl_802975B4;
    arg0[0] = (s16)((f32) arg1 * s);
    arg0[1] = (s16)((f32) arg2 * t);
    arg0[2] = (s16)((f32) (arg3 - (s32) arg1) * s);
    arg0[3] = (s16)((f32) (arg4 - (s32) arg2) * t);
}
