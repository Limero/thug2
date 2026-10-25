// WIP DRAFT (non-matching) — family=m2c range=0x80272094-0x8027291C size=2184B
// FLAG: -Os -fno-rerun-cse-after-loop
// PARKED @23.8% (129/542 masked insns; baseline m2c husk was DIFF ~5%) — hand
// rebuilt from fdlibm source below; honest form (no synthesized-pool casts).
// VERIFY with: tools/venv/bin/python <scratch> 0x80272094 \
//   -msdata=eabi -G128     (want loads pool via r13-relative SDA21 relocs;
// <scratch> = tools/flagdiff.py + R_PPC_EMB_SDA21 masking)
// IDENTIFIED: Sun fdlibm __kernel_rem_pio2(x,y,e0,nx,prec,ipio2) — SN libm port,
// ProDG-compiled (lis+ori constants; zone docs/neversoft-math-lib.md "strtod-shaped"
// dead-linked helpers). Proof: init_jk[]={2,3,4,6} @lbl_803CBB70 and ipio2[]
// (0x3FF921FB,0x40000000,0x3E74442D,...) @lbl_803CBB80 match netlib fdlibm
// k_rem_pio2.c verbatim; all 8 PIo2[] doubles match to the last bit; callees
// fn_802712F0(f64,s32)=scalbn, fn_80270290(f64)=floor.
// STRUCTURE (want 546 insns, frame stwu -0x280, mfcr r12, stfd f31,0x278,
// stmw r19,0x244 [r19-r31], CR save 0x240): sp+8 iq[20] s32 | +0x58 f[20] f64 |
// +0xF8 fq[20] | +0x198 q[20] | +0x238 SHARED int<->double cvt slot (~10 dance
// sites, §6j-1 via REAL .sdata double lbl_803CA8E0 = 0x4330000080000000).
// Constants (r13-rel .sdata): -0x79A0 magicA, -0x7998 0.0, -0x7990 twon24,
// -0x7988 two24, -0x7980 0.125, -0x7978 8.0, -0x7970 0.5, -0x7968 1.0.
// Want saved-reg map (allocation desc from r31): j/jz=r31, &iq=r30, jx=r29,
// q0=r28, jk=r27, y=r26, &q=r25, CR-hold=r24(mfcr), jv=r23, n=r22, x=r21,
// prec=r20, ipio2=r19; z lives in f31.
// REMAINING BLOCKERS (all avenues exhausted):
//  1. GCC compare-cache across calls (doc-28 class): want does cmpwi ih,0 ->
//     cr0; mfcr r24; ... mtcrf 0x80,r24; beq/bne at EACH of the 4 y[] sign
//     branches ((ih==0)?fw:-fw), i.e. ONE compare cached through scalbn/floor
//     calls. My compiles re-test with fresh cmpwis -> one missing live GPR
//     shifts the whole callee-saved map by one slot and renames every cr
//     field (cr3->cr2, cr4->cr3). Tried: n/ih hard-reg pins (no effect),
//     -fno-schedule-insns[-2]/-fno-strength-reduce (all worse), staging.
//  2. Minor scheduler flips: scalbn call arg moves emit mr r3 BEFORE fmr f1
//     (want reversed); I2D lis-hoist floats above the dance (want materializes
//     inside); fill/distill loop countdowns live in CTR in want (mfctr/addic./
//     mtctr juggling) vs plain regs here — GPR-pressure artifacts that should
//     fall out if blocker 1 is solved.
// NOTE: an earlier variant scored 31.9% by writing the two ROUND sites as
// `(f64)` casts of TOINT() results — ngccc then synthesizes its own
// int->double pool into module .rodata (doc-14 promote blocker) — rejected;
// this file keeps the manual dance and is promotable-in-principle.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 2.6% ([4]rev->2.6% [11]rev->2.6% [12]rev->2.6%).
#include "types.h"
#include "qb_constants.h"
extern f64 lbl_803CA8E0; /* 0x4330000080000000 */
extern f64 lbl_803CA8E8; /* 0.0 */
extern f64 lbl_803CA8F0; /* twon24 */
extern f64 lbl_803CA8F8; /* two24 */
extern f64 lbl_803CA900; /* 0.125 */
extern f64 lbl_803CA908; /* 8.0 */
extern f64 lbl_803CA910; /* 0.5 */
extern f64 lbl_803CA918; /* 1.0 */
extern s32 lbl_803CBB70[4];
extern f64 lbl_803CBB80[8];
extern f64 fn_802712F0(f64 x, s32 n); /* scalbn */
extern f64 fn_80270290(f64 x);        /* floor */
typedef union { u32 w[2]; f64 d; } cvt_u;
s32 fn_80272094(f64 *x, f64 *y, s32 e0, s32 nx, s32 prec, s32 *ipio2) {
    s32 iq[20];
    f64 f[20], fq[20], q[20];
    volatile cvt_u cvt;
    s32 jz, jx, jv, jp, jk, carry, n, i, j, k, m, q0, ih;
    f64 z, fw;
/* int -> double via the game's own .sdata magic pair (shared slot) */
#define I2D(iv) (cvt.w[1] = (u32)(iv) ^ 0x80000000, cvt.w[0] = QB_INT_TO_DOUBLE_BIAS, \
                 cvt.d - lbl_803CA8E0)
/* double -> int via fctiwz through the shared slot */
#define TOINT(dv) ({ f64 _h; __asm__ volatile("fctiwz %0,%1" : "=f"(_h) : "f"(dv)); \
                     cvt.d = _h; (s32)cvt.w[1]; })
/* (double)(int)(dv): truncate then rebuild through the same slot */
#define ROUND(dv) ({ f64 _h; __asm__ volatile("fctiwz %0,%1" : "=f"(_h) : "f"(dv)); \
                     cvt.d = _h; \
                     cvt.w[1] ^= 0x80000000; \
                     cvt.w[0] = QB_INT_TO_DOUBLE_BIAS; \
                     cvt.d - lbl_803CA8E0; })
    jk = lbl_803CBB70[prec];
    jp = jk;
    jx = nx - 1;
    jv = (e0 - 3) / 24;
    if (jv < 0) {
        jv = 0;
    }
    q0 = e0 - 24 * (jv + 1);
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? lbl_803CA8E8 : I2D(ipio2[j]);
    }
    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = lbl_803CA8E8; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }
        q[i] = fw;
    }
    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = ROUND(z * lbl_803CA8F0);
        iq[i] = TOINT(z - lbl_803CA8F8 * fw);
        z = q[j - 1] + fw;
    }
    ih = 0;
    z -= I2D(n);
    n = TOINT(z);
    z -= lbl_803CA908 * fn_80270290(z * lbl_803CA900);
    z = fn_802712F0(z, q0);
    if (q0 > 0) {
        i = iq[jz - 1] >> (24 - q0);
        n += i;
        iq[jz - 1] -= i << (24 - q0);
        ih = iq[jz - 1] >> (23 - q0);
    } else if (q0 == 0) {
        ih = iq[jz - 1] >> 23;
    } else {
        if (z >= lbl_803CA910) {
            ih = 2;
        }
    }
    if (ih > 0) {
        n += 1;
        carry = 0;
        for (i = 0; i < jz; i++) {
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x1000000 - j;
                }
            } else {
                iq[i] = 0xffffff - j;
            }
        }
        if (q0 > 0) {
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7fffff;
                break;
            case 2:
                iq[jz - 1] &= 0x3fffff;
                break;
            }
        }
        if (ih == 2) {
            z = lbl_803CA918 - z;
            if (carry != 0) {
                z -= fn_802712F0(lbl_803CA918, q0);
            }
        }
    }
    if (z == lbl_803CA8E8) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) {
            j |= iq[i];
        }
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++) {
            }
            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = I2D(ipio2[jv + i]);
                for (j = 0, fw = lbl_803CA8E8; j <= jx; j++) {
                    fw += x[j] * f[jx + i - j];
                }
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }
    if (z == lbl_803CA8E8) {
        jz -= 1;
        q0 -= 24;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 24;
        }
    } else {
        z = fn_802712F0(z, -q0);
        if (z >= lbl_803CA8F8) {
            fw = ROUND(z * lbl_803CA8F0);
            iq[jz] = TOINT(z - lbl_803CA8F8 * fw);
            jz += 1;
            q0 += 24;
            iq[jz] = TOINT(fw);
        } else {
            iq[jz] = TOINT(z);
        }
    }
    fw = fn_802712F0(lbl_803CA918, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * I2D(iq[i]);
        fw *= lbl_803CA8F0;
    }
    for (i = jz; i >= 0; i--) {
        for (fw = lbl_803CA8E8, k = 0; k <= jp && k <= jz - i; k++) {
            fw += lbl_803CBB80[k] * q[i + k];
        }
        fq[jz - i] = fw;
    }
    switch (prec) {
    case 0:
        fw = lbl_803CA8E8;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = lbl_803CA8E8;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        fw = fq[0] - fw;
        for (i = 1; i <= jz; i++) {
            fw += fq[i];
        }
        y[1] = (ih == 0) ? fw : -fw;
        break;
    case 3:
        for (i = jz; i > 0; i--) {
            fq[i - 1] = fw;
            fq[i] += fq[i - 1] - fw;
            fw = fq[i - 1] + fq[i];
        }
        for (i = jz; i > 1; i--) {
            fq[i - 1] = fw;
            fq[i] += fq[i - 1] - fw;
            fw = fq[i - 1] + fq[i];
        }
        for (fw = lbl_803CA8E8, i = jz; i >= 2; i--) {
            fw += fq[i];
        }
        if (ih == 0) {
            y[0] = fq[0];
            y[1] = fq[1];
            y[2] = fw;
        } else {
            y[0] = -fq[0];
            y[1] = -fq[1];
            y[2] = -fw;
        }
        break;
    }
    return n & 7;
}
