// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80238784-0x802388E4 (352B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os -mps-float
#include "types.h"

s32 fn_80238784(void *out, s32 unused1, u8 *in, f32 *opt, void *unused8) {
    __ps_t t[2];
    volatile f32 *vp;
    register char *p9 __asm__("r5");
    register char *p8 __asm__("r4");
    register char *p7 __asm__("r10");
    f32 k9;
    f32 k8;
    f32 k7;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    register char *page __asm__("r30");
    void *dst;

    p9 = (char *)0x802B0000;
    p8 = (char *)0x802B0000;
    p7 = (char *)0x802B0000;
    k9 = *(f32 *)(p9 + 0x544);
    k8 = *(f32 *)(p8 + 0x548);
    k7 = *(f32 *)(p7 + 0x54C);
    x = (f32)(f64)(s16)(in[0] - 29) * k9;
    y = (f32)(f64)(s8)in[1] * k8;
    z = (f32)(f64)(s16)(in[2] - 29) * k7;
    page = (char *)0x802B0000;
    w = *(f32 *)(page + 0xD40);
    __asm__("" : "+f"(w), "+f"(z));
    vp = (volatile f32 *)&t[0];
    vp[0] = x;
    vp[1] = y;
    vp[3] = w;
    vp[2] = z;
    if (opt != NULL) {
        opt[0] = (f32)(f64)(in[3] & 0xFF) * k9;
        opt[1] = (f32)(f64)(in[4] & 0xFF) * k8;
        opt[2] = (f32)(f64)(in[5] & 0xFF) * k7;
    }
    dst = out;
    *(volatile __ps_t *)((char *)dst + 8) = *(volatile __ps_t *)((char *)vp + 8);
    *(volatile __ps_t *)dst = *(volatile __ps_t *)vp;
    return (s32)dst;
}
