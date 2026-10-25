// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F5AA4-0x801F5B38 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
extern f32 lbl_802AE360;
extern f32 lbl_802AE364;
void fn_801F4628(s32, f32 *, f32 *, f32 *);

void fn_801F5AA4(void *arg0) {
    f32 a[4];
    f32 *ap;
    f32 v3, v4, z;
    void *t;
    s32 base;
    ap = a;
    z = lbl_802AE360;
    ap[0] = z;
    ap[1] = z;
    ap[2] = z;
    ap[3] = lbl_802AE364;
    v4 = z;
    base = *(s32 *)((char *)arg0 + 0xAC00);
    v3 = z;
    fn_801F4628(base, ap, &v3, &v4);
    *(f32 *)(*(s32 *)((char *)arg0 + 0xAC08) + 0x8C) = v3;
    *(f32 *)(*(s32 *)((char *)arg0 + 0xAC08) + 0x7C) = v4;
    t = (void *)*(s32 *)((char *)arg0 + 0xAC08);
    *(__ps_t *)((char *)t + 0x40) = *(__ps_t *)ap;
    *(__ps_t *)((char *)t + 0x48) = *(__ps_t *)(ap + 2);
}
