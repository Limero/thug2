// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DCF0-0x8005DD6C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_802939BC[];
extern s32 lbl_803C9E18[];
extern s32 fn_8005E198(void *, s32);

void fn_8005DCF0(void) {
    f32 tmp[5];
    f32 *tp = tmp;
    f32 *in = lbl_802939BC;
    s32 *out = lbl_803C9E18;
    s32 *end = out + 9;

    do {
        tp[1] = in[0];
        tp[2] = in[1];
        tp[3] = in[2];
        tp[4] = in[3];
        in += 4;
        *out = fn_8005E198(tp, 0);
        out++;
    } while (out <= end);
}
