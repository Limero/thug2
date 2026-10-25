// WIP DRAFT (non-matching) — family=m2c range=0x8027291C-0x802731A0 size=2180B
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 3.3510% -> 3.4420% per-object flags: -Os -> -fno-strength-reduce
// FLAG: -fno-strength-reduce
// PARKED @32.6% (177/543 masked insns; baseline m2c husk was DIFF ~5%) — hand
// rebuilt as the float twin of fn_80272094 (see that header for the shared
// blocker analysis). VERIFY with:
// tools/venv/bin/python <scratch> 0x8027291C -msdata=eabi -G128
// IDENTIFIED: FLOAT twin of fn_80272094 — Sun fdlibm __kernel_rem_pio2 ported to
// single precision with BASE-2^8 limbs (SN libm float kernel; ProDG-compiled,
// dead-linked zone docs/neversoft-math-lib.md). Proof: init_jk={4,7,9} ints
// @lbl_803CBBE0 (size 0xC); PIo2f[] float pool @lbl_803CBBEC (size 0x50 =
// 20 floats: 5 pi/2 components + zeros + one/two8/twon8/1e30 packed after);
// constants two8=256.0f/twon8=0.00390625f; callees fn_80273268(f32,s32)=scalbnf,
// fn_802731A0(f32)=floorf. Same structure as fdlibm k_rem_pio2.c:
//   jv=(e0-3)/8, q0=e0-8*(jv+1), digit masks 0x100/0xFF/0x7F/0x3F, shifts >>8.
// STRUCTURE (want 545 insns, frame stwu -0x1A0, mfcr r12, stfd f31,0x198,
// stmw r18,0x160 [r18-r31 = 14 GPRs], CR save 0x15C):
//   sp+0x008 iq[20] | +0x058 f[20] f32 | +0x0A8 fq[20] f32 | +0x0F8 q[20] f32
//   +0x150 SHARED cvt slot: fctiwz->stfd->lwz->xoris->stw->lfd->fsub(magicA
//   dbl)->frsp  == (float)(double)(int)v via REAL .sdata double lbl_803CA920.
//   Constants (r13-rel): -0x7960 magicA dbl, -0x7958 0.0f, -0x7954 twon8,
//   -0x7950 two8, -0x794C 0.125f, -0x7948 8.0f, -0x7944 0.5f, -0x7940 1.0f.
//   Long-range CR webs like the double twin: cr3=(prec vs 2) from entry;
//   mfcr r25 = (ih>0) reused at every y[] sign branch (doc-28 class).
// REMAINING BLOCKERS (mirror fn_80272094 header): (1) mfcr/mtcrf compare-cache
// across scalbnf/floorf calls missing -> whole saved-reg map shifted one slot
// (want stmw starts at r18, mine r19); (2) same minor scheduler flips; plus
// (3) want locals region is 0x154B vs my four-arrays+cvt model 0x148B (~12B
// unexplained holes) -> frame 0x1A0 vs 0x190.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 1.9% ([1]rev->1.8% [13]rev->1.9% [12]rev->1.9%).
#include "types.h"
#include "qb_constants.h"

extern f64 lbl_803CA920; /* 0x4330000080000000 */
extern f32 lbl_803CA928; /* 0.0f */
extern f32 lbl_803CA92C; /* twon8 */
extern f32 lbl_803CA930; /* two8 */
extern f32 lbl_803CA934; /* 0.125f */
extern f32 lbl_803CA938; /* 8.0f */
extern f32 lbl_803CA93C; /* 0.5f */
extern f32 lbl_803CA940; /* 1.0f */
extern s32 lbl_803CBBE0[3];
extern f32 lbl_803CBBEC[20];

extern f32 fn_80273268(f32 x, s32 n); /* scalbnf */
extern f32 fn_802731A0(f32 x);        /* floorf */

typedef union { u32 w[2]; f64 d; } cvt_u;

s32 fn_8027291C(f32 *x, f32 *y, s32 e0, s32 nx, s32 prec, s32 *ipio2) {
    s32 iq[20];
    f32 f[20], fq[20], q[20];
    volatile cvt_u cvt;
    s32 jz, jx, jv, jp, jk, carry, n, i, j, k, m, q0, ih;
    f32 z, fw;

/* int -> (double -> float) via the game's own .sdata magic pair (shared slot) */
#define I2D(iv) (cvt.w[1] = (u32)(iv) ^ 0x80000000, cvt.w[0] = QB_INT_TO_DOUBLE_BIAS, \
                 (f32)(cvt.d - lbl_803CA920))
/* float -> int via fctiwz through the shared slot */
#define TOINT(dv) ({ f64 _h; __asm__ volatile("fctiwz %0,%1" : "=f"(_h) : "f"(dv)); \
                     cvt.d = _h; (s32)cvt.w[1]; })
/* (float)(double)(int)(dv): truncate then rebuild through the same slot */
#define ROUND(dv) ({ f64 _h; __asm__ volatile("fctiwz %0,%1" : "=f"(_h) : "f"(dv)); \
                     cvt.d = _h; \
                     cvt.w[1] ^= 0x80000000; \
                     cvt.w[0] = QB_INT_TO_DOUBLE_BIAS; \
                     (f32)(cvt.d - lbl_803CA920); })

    jk = lbl_803CBBE0[prec];
    jp = jk;

    jv = (e0 - 3) / 8;
    jx = nx - 1;
    if (jv < 0) {
        jv = 0;
    }
    q0 = e0 - 8 * (jv + 1);

    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++) {
        f[i] = (j < 0) ? lbl_803CA928 : I2D(ipio2[j]);
    }

    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = lbl_803CA928; j <= jx; j++) {
            fw += x[j] * f[jx + i - j];
        }
        q[i] = fw;
    }

    jz = jk;
recompute:
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = ROUND(z * lbl_803CA92C);
        iq[i] = TOINT(z - lbl_803CA930 * fw);
        z = q[j - 1] + fw;
    }

    z = fn_80273268(z, q0);
    z -= lbl_803CA938 * fn_802731A0(z * lbl_803CA934);
    n = TOINT(z);
    z -= I2D(n);
    ih = 0;
    if (q0 > 0) {
        i = iq[jz - 1] >> (8 - q0);
        n += i;
        iq[jz - 1] -= i << (8 - q0);
        ih = iq[jz - 1] >> (7 - q0);
    } else if (q0 == 0) {
        ih = iq[jz - 1] >> 7;
    } else {
        if (z >= lbl_803CA93C) {
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
                    iq[i] = 0x100 - j;
                }
            } else {
                iq[i] = 0xff - j;
            }
        }
        if (q0 > 0) {
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7f;
                break;
            case 2:
                iq[jz - 1] &= 0x3f;
                break;
            }
        }
        if (ih == 2) {
            z = lbl_803CA940 - z;
            if (carry != 0) {
                z -= fn_80273268(lbl_803CA940, q0);
            }
        }
    }

    if (z == lbl_803CA928) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) {
            j |= iq[i];
        }
        if (j == 0) {
            for (k = 1; iq[jk - k] == 0; k++) {
            }
            for (i = jz + 1; i <= jz + k; i++) {
                f[jx + i] = I2D(ipio2[jv + i]);
                for (j = 0, fw = lbl_803CA928; j <= jx; j++) {
                    fw += x[j] * f[jx + i - j];
                }
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    if (z == lbl_803CA928) {
        jz -= 1;
        q0 -= 8;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 8;
        }
    } else {
        z = fn_80273268(z, -q0);
        if (z >= lbl_803CA930) {
            fw = ROUND(z * lbl_803CA92C);
            iq[jz] = TOINT(z - lbl_803CA930 * fw);
            jz += 1;
            q0 += 8;
            iq[jz] = TOINT(fw);
        } else {
            iq[jz] = TOINT(z);
        }
    }

    fw = fn_80273268(lbl_803CA940, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * I2D(iq[i]);
        fw *= lbl_803CA92C;
    }

    for (i = jz; i >= 0; i--) {
        for (fw = lbl_803CA928, k = 0; k <= jp && k <= jz - i; k++) {
            fw += lbl_803CBBEC[k] * q[i + k];
        }
        fq[jz - i] = fw;
    }

    switch (prec) {
    case 0:
        fw = lbl_803CA928;
        for (i = jz; i >= 0; i--) {
            fw += fq[i];
        }
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = lbl_803CA928;
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
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (i = jz; i > 1; i--) {
            fq[i - 1] = fw;
            fq[i] += fq[i - 1] - fw;
            fw = fq[i - 1] + fq[i];
        }
        for (fw = lbl_803CA928, i = jz; i >= 2; i--) {
            fw += fq[i];
        }
        if (ih == 0) {
            y[2] = fw;
            y[1] = fq[1];
            y[0] = fq[0];
        } else {
            y[0] = -fq[0];
            y[1] = -fq[1];
            y[2] = -fw;
        }
        break;
    }
    return n & 7;
}
