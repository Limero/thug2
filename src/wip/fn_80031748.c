// PARKED 2026-10-06 (fn_80031748 / heavy-PS spline blend): hand-written
// reconstruction, best measured 6.41% masked (234-word symbol, frame exactly
// 0xe0, all six stfd f26..f31 + mflr/mfcr/stw r0/stw r12 slots matching, plus
// the five `mr r18..r16` argument moves).  Official verdict DIFF.  The m2c
// stub this replaced scored 9.84% but was only 244B of the 936B symbol, so
// that percentage was scored over 61 words and is meaningless per the
// want_got SIZE MISMATCH rule / AGENTS §6cs-1; this body is 1248B and is
// scored over the whole symbol.
// RESIDUAL: (1) frame layout — want `stmw r15,0x6c(r1)` / `stw r12,0x68(r1)`,
// got `stmw r14,0x68(r1)` / `stw r12,0x64(r1)`: GCC allocates r14-r28 so the
// stmw area is 8 bytes shorter and the CR slot lands 4 low.  (2) entry order —
// want `mr r21,r9` last of the six arg moves, GCC schedules it first; GCC
// then also makes loop-invariant copies (mr r14/r18, mr r22/r23, mr r15/r20,
// mr r17/r21) and spills a3/a4 to the stack.  (3) the whole k-loop body:
// scalar-vs-PS form (lfs/stfs instead of psq_l/psq_st for the negation copy),
// and the psq_set pattern `va.p1 = t.p0` (want) is not expressible in C.
// RULED OUT: whole-body / store-order permutation sweeps; `-mps-float`
// alternatives — `1/sqrtf` and `1/x` do NOT give frsqrte in ngccc (verified:
// it calls sqrtf / uses fdivs) and there is no scalar frsqrte intrinsic, so
// want's `frsqrte + 3.0f/0.5f Newton refine` is unreachable from plain C;
// SN_PS.h's `PS_BUILD` compound-literal splat makes ngccc emit an EMPTY
// object (use __builtin_ps_merge00 instead — see below); fn_800313BC is a
// structural near-twin (same 0x900 record walk, same fn_8002B8E4/E8 pair,
// lbl_80291A0C..1C) but it is itself only an m2c stub, so no twin transfer.
// Semantics recovered and encoded below: 7 args (r18=recs, r23=f32 weights,
// r20=s32 ids, r19=count, r16=dst recs, r8=n, r21=id); the record is 0x900 =
// 64x Vec4A @+0, 64x Vec4B @+0x400, 64x s32 used-flags @+0x800; alpha =
// 1.0f - w[j]/(w[j]+w[i]+acc); per element both-used => dot<0 flips pi->A,
// lerp+normalise into pi->A, lerp pi->B->pj->B by alpha.x only; only-pi-used
// => copy 32B pi->A/pi->B into pj and set the flag.
// WIP DRAFT (non-matching)
// family=m2c range=0x80031748-0x80031AF0 size=936B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

/* 8-byte paired single.  NB: `sn_ps` is already typedef'd by SN_PS.h, so do
 * NOT include that header here (ngccc silently emits an empty object on a
 * duplicate typedef), and do NOT use its PS_BUILD compound literal (also an
 * empty object); SPLAT below is the working replacement. */
typedef float sn_ps __attribute__((mode(PS)));

typedef union {
    sn_ps p;
    f32 f[2];
} PSU;

#define SPLAT(x) __builtin_ps_merge00((x), (x))

extern f32 lbl_80291A20;   /* 0.0f  */
extern f32 lbl_80291A24;   /* 1.0f  */
extern f32 lbl_80291A28;   /* 1e-5f */
extern f32 lbl_80291A2C;   /* 0.5f  */
extern f32 lbl_80291A30;   /* 3.0f  */

void fn_8002B8E4(void *);         /* 4-byte stub: just `blr` */
void fn_8002B8E8(void *, void *); /* 16-byte PS copy (two psq_l/psq_st pairs) */
void memcpy(void *, const void *, u32);

typedef struct {
    f32 v[4];
} Vec4;

typedef struct {
    sn_ps p[2];
} Vec4P;

/* 0x900-byte spline record: 64 vec4 keys, 64 vec4 values, 64 s32 used-flags. */
typedef struct {
    Vec4 a[64];
    Vec4 b[64];
    s32 f[64];
} Rec;

register Rec *p_a0 __asm__("r18");
register f32 *p_a1 __asm__("r23");
register s32 *p_a2 __asm__("r20");
register s32 p_a3 __asm__("r19");
register Rec *p_a4 __asm__("r16");
register s32 p_a6 __asm__("r21");

void fn_80031748(Rec *arg0, f32 *arg1, s32 *arg2, s32 arg3, Rec *arg4, s32 arg5, s32 arg6) {
    Rec *a0 = p_a0 = arg0;
    f32 *a1 = p_a1 = arg1;
    s32 *a2 = p_a2 = arg2;
    s32 a3 = p_a3 = arg3;
    Rec *a4 = p_a4 = arg4;
    s32 a6 = p_a6 = arg6;
#define arg0 a0
#define arg1 a1
#define arg2 a2
#define arg3 a3
#define arg4 a4
#define arg6 a6
    /* retail keeps the two epsilons, the running weight sum and the Newton
     * constants in f26..f31 -- pin them so the frame comes out at 0xe0 with
     * the same six stfd/lfd pairs. */
    register f32 eps1 __asm__("fr26");
    register f32 acc __asm__("fr27");
    register f32 eps2 __asm__("fr28");
    register f32 half __asm__("fr29");
    register f32 three __asm__("fr30");
    register f32 alpha __asm__("fr31");
    volatile double d0;  /* frame filler: want's locals end at 0x38, CR at 0x68 */
    volatile double d1;
    Vec4 t;               /* sp+0x08 */
    Vec4P n;              /* sp+0x18, the &fn_8002B8E4/E8 argument */
    f32 sp28;             /* sp+0x28 */
    PSU sp30;             /* sp+0x2c, read back with psq_l 48(r1) */
    f32 sum;
    s32 i;
    s32 j;
    s32 k;
    Rec *pj;
    Rec *pi;

    sum = lbl_80291A20;
    if (arg5 > 1) {
        s32 cnt = arg5 - 1;
        f32 zero = sum;
        s32 off = 4;
        do {
            f32 w = *(f32 *)((char *)arg1 + off);
            if (w != zero && *(s32 *)((char *)arg2 + off) == arg6) {
                sum += w;
            }
            off += 4;
            cnt -= 1;
        } while (cnt != 0);
    }
    arg1[0] = lbl_80291A24 - sum;
    acc = lbl_80291A20;
    i = arg5 - 1;
    if (arg0 > arg4) {
        eps1 = lbl_80291A28;
        while (i > 0) {
            s32 i2 = i - 1;
            f32 wi = arg1[i];
            if (wi >= eps1 && arg2[i] == arg6) {
                alpha = wi + acc;
                j = i2;
                do {
                    j--;
                    wi = arg1[j];
                    if (wi > eps1) {
                        break;
                    }
                } while (j > 0 && arg2[j] != arg6);
                if (arg2[j] == arg6) {
                    alpha = lbl_80291A24 - (wi / (wi + alpha));
                    pj = arg0 + j;
                    pi = arg0 + i;
                    acc += arg1[i];
                    eps2 = lbl_80291A28;
                    half = lbl_80291A2C;
                    three = lbl_80291A30;
                    for (k = 0; k < arg3; k++) {
                        Vec4 *va = &pj->a[k];
                        Vec4 *vb = &pi->a[k];
                        Vec4 *cb = &pj->b[k];
                        Vec4 *db = &pi->b[k];
                        if (pj->f[k] != 0) {
                            if (pi->f[k] != 0) {
                                f32 d = va->v[0] * vb->v[0] + va->v[1] * vb->v[1]
                                      + va->v[2] * vb->v[2] + va->v[3] * vb->v[3];
                                sp28 = alpha;
                                if (d < lbl_80291A20) {
                                    ((f32 *)&n)[0] = -vb->v[0];
                                    ((f32 *)&n)[1] = -vb->v[1];
                                    ((f32 *)&n)[2] = -vb->v[2];
                                    ((f32 *)&n)[3] = -vb->v[3];
                                    vb->v[0] = ((f32 *)&n)[0];
                                    vb->v[1] = ((f32 *)&n)[1];
                                    vb->v[2] = ((f32 *)&n)[2];
                                    vb->v[3] = ((f32 *)&n)[3];
                                }
                                t = *vb;
                                sp30.f[0] = alpha;
                                va->v[0] = vb->v[0];
                                va->v[1] = vb->v[1];
                                va->v[2] = t.v[0];
                                va->v[3] = t.v[1];
                                {
                                    sn_ps A0 = *(sn_ps *)&va->v[0];
                                    sn_ps A1 = *(sn_ps *)&va->v[2];
                                    sn_ps B0 = *(sn_ps *)&vb->v[0];
                                    sn_ps B1 = *(sn_ps *)&vb->v[2];
                                    sn_ps al = SPLAT(alpha);
                                    sn_ps r0 = __builtin_ps_add(__builtin_ps_mul(__builtin_ps_sub(B0, A0), al), A0);
                                    sn_ps r1 = __builtin_ps_add(__builtin_ps_mul(__builtin_ps_sub(B1, A1), al), A1);
                                    sn_ps s = __builtin_ps_add(__builtin_ps_mul(r0, r0), __builtin_ps_mul(r1, r1));
                                    PSU u;
                                    sn_ps l2 = __builtin_ps_sum0(s, s, s);
                                    f32 y;
                                    u.p = __builtin_ps_rsqrte(l2);
                                    y = u.f[0];
                                    y = (three - (y * y) * u.f[0]) * (y * half);
                                    al = __builtin_ps_sel(__builtin_ps_sub(l2, SPLAT(eps2)), SPLAT(half - half), SPLAT(y));
                                    n.p[0] = __builtin_ps_muls0(r0, al);
                                    n.p[1] = __builtin_ps_muls0(r1, al);
                                    vb->v[0] = ((f32 *)&n)[0];
                                    vb->v[1] = ((f32 *)&n)[1];
                                    vb->v[2] = ((f32 *)&n)[2];
                                    vb->v[3] = ((f32 *)&n)[3];
                                }
                                t = *vb;
                                va->v[0] = vb->v[0];
                                va->v[1] = vb->v[1];
                                va->v[2] = t.v[0];
                                va->v[3] = t.v[1];
                                fn_8002B8E4(&n);
                                {
                                    sn_ps u = sp30.p;
                                    sn_ps e0 = __builtin_ps_sub(*(sn_ps *)&db->v[0], *(sn_ps *)&cb->v[0]);
                                    sn_ps e1 = __builtin_ps_sub(*(sn_ps *)&db->v[2], *(sn_ps *)&cb->v[2]);
                                    sn_ps m0 = __builtin_ps_madd(e0, u, *(sn_ps *)&cb->v[0]);
                                    sn_ps m1 = __builtin_ps_madd(e1, u, *(sn_ps *)&cb->v[2]);
                                    n.p[0] = m0;
                                    n.p[1] = m1;
                                }
                                fn_8002B8E8(&t, &n);
                                cb->v[0] = t.v[0];
                                cb->v[1] = t.v[1];
                                cb->v[2] = t.v[0];
                                cb->v[3] = t.v[1];
                            }
                        } else if (pi->f[k] != 0) {
                            pj->f[k] = 1;
                            *va = *vb;
                            *cb = *db;
                        }
                    }
                }
            }
            i = i2;
        }
    }
    d0 = 0.0;
    d1 = 0.0;
    if (arg0 != arg4) {
        memcpy(arg4, arg0, arg3 * 0x900);
    }
}