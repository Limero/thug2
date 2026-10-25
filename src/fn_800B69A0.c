// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B69A0-0x800B6A88 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} Vec4;

extern __ps_t lbl_80298828; /* rodata2 pair { 0.0f, 0.0f } */
extern f32 lbl_80298980;    /* 0.5f  */
extern f32 lbl_80298984;    /* 0.0f  */
extern f32 lbl_80298988;    /* 1.0f  */

f32 sinf(f32);
f32 cosf(f32);
s32 fn_8002C8FC(void *, f32);                          /* stfs f1, 0xC(r3) */
void fn_8002C904(void *, f32, f32, f32);               /* stfs f3/f1/f2 at +8/+0/+4 */

void *fn_800B69A0(void *arg0, Vec4 *arg1, f32 farg0) {
    volatile __ps_t sp8;
    __ps_t *v = (__ps_t *)arg1;
    __ps_t z2, t, m;
    f32 f30, f31, q;
    register f32 r __asm__("fr0"); /* see key insight 5 above */

    f30 = farg0 * lbl_80298980;
    z2 = lbl_80298828;
    t = __builtin_ps_merge00(__builtin_ps_mul(v[1], v[1]), z2);
    m = __builtin_ps_madd(v[0], v[0], t);
    m = __builtin_ps_sum0(m, m, m);
    sp8 = __builtin_ps_res(__builtin_ps_rsqrte(m));

    r = *(f32 *)&sp8;
    f31 = r;
    if (r > lbl_80298984) {
        q = lbl_80298988 / f31;
    } else {
        q = lbl_80298984;
    }
    f31 = q;
    f31 = f31 * sinf(f30);

    fn_8002C904(arg0, f31 * arg1->x, f31 * arg1->y, f31 * arg1->z);
    fn_8002C8FC(arg0, cosf(f30));
    return arg0;
}
