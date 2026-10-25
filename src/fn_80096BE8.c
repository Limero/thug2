// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80096BE8-0x80096D38 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mcpu=630
#include "types.h"
#include "structs.h"
extern f32 lbl_802974B8[1];
extern f32 lbl_802974BC[3];
void PSMTXMultVecArray(void *, void *, void *, s32);

typedef struct {
    f32 x;
    f32 w;
    f32 y;
} Vec96BE8;

s32 fn_80096BE8(void *arg0, f32 *arg1) {
    Vec96BE8 buf[8];
    Vec96BE8 out[8];
    f32 z = arg1[3];
    f32 x = arg1[0];
    f32 w = arg1[1];
    f32 y = arg1[2];
    f32 dx = x - z;
    f32 dw = w - z;
    f32 dy = y - z;
    f32 sy = y + z;
    f32 sx = x + z;
    f32 sw = w + z;
    f32 *p;
    f32 *q;
    f32 v;
    s32 mask = 0xFF;
    s32 sel;
    s32 i;

    for (i = 0; i < 8; i++) {
        buf[i].x = (i & 4) ? sx : dx;
        buf[i].w = (i & 2) ? sw : dw;
        buf[i].y = (i & 1) ? sy : dy;
    }
    PSMTXMultVecArray(arg0, buf, out, 8);
    p = &out[0].x;
    q = &out[0].w;
    for (i = 0; i < 8; i++) {
        sel = 0;
        v = *p;
        p += 3;
        if (v > lbl_802974B8[0]) {
            sel = 1;
        } else if (v < lbl_802974BC[0]) {
            sel = 2;
        }
        v = *q;
        if (v > lbl_802974B8[0]) {
            sel |= 4;
        } else if (v < lbl_802974BC[0]) {
            sel |= 8;
        }
        mask &= sel;
        if (mask == 0) {
            return 1;
        }
        q += 3;
    }
    return 0;
}
