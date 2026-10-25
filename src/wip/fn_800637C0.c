// WIP DRAFT (non-matching) — hand-reconstructed from the retail bytes.
// family=m2c range=0x800637C0-0x800639E8 size=552B
// FLAG: -mps-float -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARK: 23/138 masked words (16.7%), .text length is exact (552B) and the
// semantics/frame layout/store order are all pinned down, but ngccc's FPR
// allocation for this routine is not reproducible from reconstructed C.
// Retail keeps 1.0f live in f8 and 0.0f live in f10 for the whole body and
// rotates the 8-wide cached-matrix copy through f0/f7/f12/f13; this build
// picks f11/f6 for the literals and rotates f0/f13. Every later word then
// differs even though the op sequence is right. See docs/parkings/ for the
// full residual analysis.
// RE-TRIAGED 2026-10-19: sweep verdict DIFF (the 16.7% above is a masked
// score — want_got.py masks the entire PS body as `?`, so the unmasked
// codegen is almost fully diverged). FPR-allocation wall stands; needs a
// new lever for pinning literals to f8/f10. Parked as-is.
#include "types.h"
#include "structs.h"

typedef union { __ps_t p; f32 w[2]; } Pair;
typedef union { __ps_t p[2]; f32 w[4]; } Quad;
typedef struct { f32 f[16]; } Mat;

typedef struct {
    char pad0x00[0xD8];
    f32 x;      /* 0xD8 */
    f32 y;      /* 0xDC */
    f32 z;      /* 0xE0 */
    Mat *cached;/* 0xE4 */
} Obj;

extern const f32 lbl_80294060;   /* 1.0f  */
extern const f32 lbl_80294064;   /* 0.0f  */
extern const f32 lbl_80294068;   /* 0.99f */
extern __ps_t lbl_80293FE8;      /* {0.0f, 0.0f} */

#define PIN(x) __asm__("" : "+f"(x))

void fn_800637C0(Obj *arg0, Mat *arg1, f32 farg6) {
    Mat *cached = arg0->cached;
    const __ps_t *s8;
    __ps_t *d8;

    if (cached != 0) {
        s8 = (const __ps_t *)cached->f;
        d8 = (__ps_t *)arg1->f;
        d8[0] = s8[0];
        d8[1] = s8[1];
        d8[2] = s8[2];
        d8[3] = s8[3];
        d8[4] = s8[4];
        d8[5] = s8[5];
        d8[6] = s8[6];
        d8[7] = s8[7];
        return;
    }

    {
    f32 *m = arg1->f;
    f32 *r3 = arg1->f + 12;
    f32 *r2 = arg1->f + 8;
    f32 one = lbl_80294060;
    f32 zero = lbl_80294064;
    volatile __ps_t *zp = &lbl_80293FE8;
    Quad *q = (Quad *)arg1;
    volatile Quad uA;              /* sp+0x08 */
    volatile Quad uB;              /* sp+0x18 */
    volatile Pair t1;              /* sp+0x28 */
    volatile Pair t2;              /* sp+0x30 */
    volatile Pair t3;              /* sp+0x38 */
    Pair s;
    __ps_t nz;
    __ps_t ny;
    __ps_t r;
    __ps_t a0;
    __ps_t a1;
    __ps_t d0;
    __ps_t d1;
    __ps_t v0;
    __ps_t v1;
    __ps_t v2;
    __ps_t v3;

    m[0] = one;
    m[10] = one;
    m[8] = zero;
    m[9] = zero;
    m[11] = zero;
    m[1] = zero;
    m[2] = zero;
    m[3] = zero;
    m[4] = zero;
    m[5] = one;
    m[6] = zero;
    m[7] = zero;
    m[13] = zero;
    m[14] = zero;
    m[15] = one;
    m[12] = zero;
    r3[3] = one;
    r3[1] = zero;
    r3[2] = zero;

    m[8] = arg0->x;
    r2[1] = arg0->y;
    r2[2] = arg0->z;
    r2[3] = one;

    /* normalize the direction already stored in m[8..11] */
    nz = q->p[5];
    r = nz * nz;
    r = __builtin_ps_merge00(r, *zp);
    ny = q->p[4];
    r = __builtin_ps_madd(ny, ny, r);
    r = __builtin_ps_sum0(r, r, r);
    s.p = r;
    if (s.w[0] > zero) {
        r = __builtin_ps_rsqrte(r);
        t1.p = r;
        t1.w[1] = one;
        q->p[4] = __builtin_ps_muls0(ny, r);
        q->p[5] = __builtin_ps_mul(nz, t1.p);
    }

    /* up-vector fallback: X-up when the direction is mostly vertical */
    uA.w[0] = zero;
    uA.w[1] = one;
    uA.w[2] = zero;
    uA.w[3] = one;
    if (__builtin_fabsf(m[9]) > lbl_80294068) {
        uB.w[0] = one;
        uB.w[2] = zero;
        uB.w[1] = zero;
        uB.w[3] = one;
        uA = uB;
    }

    /* Gram-Schmidt against the up vector, packed two rows per ps register */
    a1 = uA.p[1];
    a0 = uA.p[0];
    d0 = q->p[4];
    d1 = q->p[5];

    v0 = __builtin_ps_merge10(a0, a1);
    v1 = __builtin_ps_merge00(a1, a0);
    v2 = __builtin_ps_merge10(d0, d1);
    v3 = a0 * v2;
    v0 = v0 * d0;
    PIN(v3); PIN(v0);
    v3 = v3 - v0;
    t2.p = __builtin_ps_merge00(v3, v3);
    v1 = v1 * __builtin_ps_merge00(d0, d1);
    t2.w[1] = one;
    v0 = __builtin_ps_merge10(v1, v1);
    PIN(v1); PIN(v0);
    v1 = v1 - v0;
    v3 = __builtin_ps_merge10(v3, v1);
    v1 = t2.p;
    v2 = v3 * v2;
    q->p[0] = v3;
    v0 = v1;
    v1 = __builtin_ps_merge10(v3, v0);
    q->p[1] = v0;
    v1 = v1 * d0;
    v0 = __builtin_ps_merge00(v0, v3);
    PIN(v2); PIN(v1);
    v2 = v2 - v1;
    t3.p = __builtin_ps_merge00(v2, v2);
    v0 = v0 * __builtin_ps_merge00(d0, d1);
    t3.w[1] = one;
    v3 = __builtin_ps_merge10(v0, v0);
    PIN(v0); PIN(v3);
    v0 = v0 - v3;
    v2 = __builtin_ps_merge10(v2, v0);
    v0 = t3.p;
    q->p[2] = v2;
    v3 = v0;
    q->p[3] = v3;
    uB.p[0] = v2;
    uB.p[1] = v3;
    }
}
