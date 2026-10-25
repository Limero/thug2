// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80007A4C-0x80007B94 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

extern f32 lbl_8028FE40;
extern f32 lbl_8028FE44;
extern f32 lbl_8028FE48;

s32 fn_80007308(f32 *a, f32 *b, s32 *out);

void fn_80007A4C(f32 *arg0, f32 *arg1, f32 *arg2) {
    s32 sp8;
    s32 best;
    s32 idx;
    s32 off;
    s32 ctr;
    s32 one;
    f32 lim;
    f32 pick;
    f32 a;
    f32 b;
    f32 c;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 lo;
    f32 pickv;
    f32 g1;
    f32 *arg0b;
    __ps_t *dst;
    __ps_t *src;

    if (fn_80007308(arg0, arg1, &sp8) == 3) {
        ctr = 3;
        lim = lbl_8028FE40;
        best = -1;
        pick = lbl_8028FE44;
        arg0b = arg0 + 4;
        idx = 0;
        off = 0;
        do {
            ctr -= 1;
            a = *(f32 *)(off + (s32)arg1);
            b = *(f32 *)(off + (s32)arg0);
            c = *(f32 *)(off + (s32)arg0b);
            g1 = a - b;
            lo = c - a;
            if (g1 < lo) {
                lo = g1;
                pickv = b;
            } else {
                pickv = c;
            }
            if ((idx == 0) || (lo < lim)) {
                lim = lo;
                best = idx;
                pick = pickv;
            }
            off += 4;
            idx += 1;
        } while (ctr != 0);
        dst = (__ps_t *)arg2;
        src = (__ps_t *)arg1;
        dst[0] = src[0];
        dst[1] = src[1];
        *(f32 *)((char *)arg2 + best * 4) = pick;
        return;
    }
    ctr = 3;
    idx = 0;
    arg2[3] = lbl_8028FE48;
    one = 1;
    arg0b = arg0 + 4;
    off = 0;
    do {
        ctr -= 1;
        if (sp8 & (one << idx)) {
            *(f32 *)(off + (s32)arg2) = *(f32 *)(off + (s32)arg1);
        } else {
            a2 = *(f32 *)(off + (s32)arg1);
            b2 = *(f32 *)(off + (s32)arg0);
            if (a2 <= b2) {
                *(f32 *)(off + (s32)arg2) = b2;
            } else {
                c2 = *(f32 *)((char *)arg0b + off);
                *(f32 *)((char *)arg2 + off) = c2;
            }
        }
        off += 4;
        idx += 1;
    } while (ctr != 0);
}
