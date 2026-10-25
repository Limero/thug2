// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80091B00-0x80091C1C (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
extern f32 lbl_80297168;
extern f32 lbl_8029716C;
typedef union { f32 f[4]; __ps_t p[2]; } Blk;
s32 *fn_80091B00(s32 *arg0) {
    s32 d1;
    s32 d2;
    s32 d3;
    Blk blk;
    __ps_t *q;
    __ps_t *bp;
    f32 z;
    f32 o;
    f32 w;
    d1 = 1;
    do { } while (--d1 != -1);
    d2 = 1;
    q = (__ps_t *)((char *)arg0 + 8);
    do { } while (--d2 != -1);
    d3 = 1;
    do { } while (--d3 != -1);
    bp = (__ps_t *)&blk;
    z = lbl_80297168;
    o = lbl_8029716C;
    ((f32 *)bp)[0] = z;
    ((f32 *)bp)[1] = z;
    ((f32 *)bp)[2] = z;
    ((f32 *)bp)[3] = o;
    arg0[0] = 0;
    *(__ps_t *)((char *)arg0 + 0x08) = bp[0];
    w = 255.0f;                       /* == lbl_80297170; see L2 note above */
    q[1] = bp[1];
    ((f32 *)bp)[0] = z;
    ((f32 *)bp)[1] = z;
    ((f32 *)bp)[2] = z;
    ((f32 *)bp)[3] = o;
    *(__ps_t *)((char *)arg0 + 0x18) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x20) = bp[1];
    ((f32 *)bp)[0] = w;
    ((f32 *)bp)[1] = w;
    ((f32 *)bp)[2] = w;
    ((f32 *)bp)[3] = w;
    *(__ps_t *)((char *)arg0 + 0x28) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x30) = bp[1];
    *(__ps_t *)((char *)arg0 + 0x38) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x40) = bp[1];
    *(__ps_t *)((char *)arg0 + 0x58) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x60) = bp[1];
    *(__ps_t *)((char *)arg0 + 0x68) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x70) = bp[1];
    *(__ps_t *)((char *)arg0 + 0x48) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x50) = bp[1];
    *(__ps_t *)((char *)arg0 + 0x78) = bp[0];
    *(__ps_t *)((char *)arg0 + 0x80) = bp[1];
    return arg0;
}
