// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007C340-0x8007C39C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
} Vec16;

extern Vec16 *lbl_80364C3C;
extern Vec16 lbl_80377660;
extern f32 lbl_80295D50;
extern bool lbl_80377670;

Vec16 *fn_8007C340(s32 arg0) {
    Vec16 *dst;
    s32 off;
    f32 *row;
    f32 v0, v1, v2, cw;

    if (lbl_80377670 == 0) {
        lbl_80377670 = 1;
    }
    dst = &lbl_80377660;
    off = arg0 * 16;
    v0 = *(f32 *)((char *)off + (s32)lbl_80364C3C);
    row = (f32 *)((char *)off + (s32)lbl_80364C3C);
    v1 = row[1];
    v2 = row[2];
    cw = lbl_80295D50;
    dst->f0 = v0;
    dst->f1 = v1;
    dst->f2 = v2;
    dst->f3 = cw;
    return dst;
}
