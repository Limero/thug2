// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B5DC4-0x801B5EE8 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802AC108;
extern f32 lbl_802AC10C;
extern f64 lbl_802AC110;
extern f32 lbl_802AC118;
extern f32 lbl_802AC11C;
extern f32 lbl_802AC120;

extern f32 cosf(f32);

typedef union {
    u32 w[2];
    f64 d;
} cvt_t;

typedef struct {
    char pad[0x30];
    cvt_t cvt;
} frame_t;

typedef struct {
    char _pad[0x48];
    f32 arr[4];
} arr_t;

void fn_801B5DC4(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    frame_t fr;
    arr_t *ap;
    register f32 hi __asm__("fr26");
    register f32 lo __asm__("fr27");
    register f64 magicd __asm__("fr28");
    register f32 off __asm__("fr30");
    f32 t;
    f32 pa;
    f32 pb;
    f32 prod;
    f32 amp;
    f32 v;
    f32 a;
    f32 y;
    u32 k;
    s32 i = 0;

    t = (farg3 - farg2) / farg3;
    pa = lbl_802AC108;
    pb = lbl_802AC10C;
    magicd = lbl_802AC110;
    hi = lbl_802AC118;
    k = QB_INT_TO_DOUBLE_BIAS;
    prod = pa * pb;
    amp = farg1 * t;
    lo = prod;
    off = farg0;
    ap = (arr_t *)arg0;
    for (; i <= 3; i++) {
        fr.cvt.w[1] = (u32)i ^ 0x80000000U;
        __asm__ volatile("" ::: "memory");
        fr.cvt.w[0] = k;
        v = prod * (f32)(fr.cvt.d - magicd) - off;
        a = fabsf(v);
        if (!(a >= lo && a <= hi)) {
            y = amp * cosf(v) + ap->arr[i];
            ap->arr[i] = y;
            if (y > lbl_802AC11C) {
                ap->arr[i] = lbl_802AC11C;
            }
            if (ap->arr[i] < lbl_802AC120) {
                ap->arr[i] = lbl_802AC120;
            }
        }
    }
}
