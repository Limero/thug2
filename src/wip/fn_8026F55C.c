// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-08-26 (group 8)
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 1.0000% -> 1.6000% per-object flags: -fno-rerun-cse-after-loop -> -O3
// FLAG: -O3
// family=pow range=0x8026F55C-0x8026FD2C size=2000B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ============================================================================
// IDENTIFICATION: libm pow(double x, double y) — prebuilt runtime-library object.
//
// Modern BSD/Kargl-style __ieee754_pow (FreeBSD/OpenBSD post-2011 e_pow.c):
//   - cp_h/cp_l split-log method, L1..L6 log poly + P1..P5 exp poly,
//   - ivln2/ivln2_hi/ivln2_lo, lg2_hi, ln2, huge=1e300, tiny=1e-300,
//   - T = 0x43300000_80000000 exponent-reconstruction trick,
//   - sqrt-table boundaries 0x3988E / 0xBB679 (want F8DC/F900),
//   - bp[] = {1.0, 1.5}, dp_h[] = {0, 0.5849624872207642},
//     dp_l[] = {0, 1.350039202129749e-08} (verified from DOL sec11).
//
// Callers (REL24 scan): 0x802552FC / 0x80255EA0 / 0x8025637C (game math).
// Callees: fn_8026FD2C = sqrt(f64)f64, fn_802712F0 = scalbn(f64,s32),
//          fn_80270254 = fabs (bit-clear leaf).
//
// WHY PARKED (structural — do not polish blind):
//  1. SDA addressing. Want materializes EVERY constant/table access as
//     `lfd/lwz disp(r13)` small-data refs (_SDA_BASE_=0x803D2280; tables via
//     `lfdx` off r13-0x7070/-0x7060/-0x7050 = .sdata2 0x803CB210/220/230).
//     Game-code objects compile with -G0 -> every lbl_ ref emits lis+addi
//     absolute form, NEVER r13-relative. This whole zone (printf engines
//     BD70/D288 + their writer helpers, string/memory libc, ctype users
//     0x8026E5xx, libm from 0x8026FD2C on) shipped prebuilt with small-data
//     ON and an sdata/sdata2 split — different flags than game code.
//     Route worth one probe (cf. AGENTS.md 5q): extra_cflags
//     ["-msdata=eabi","-G8"] makes extern refs emit R_PPC_EMB_SDA21 resolved
//     vs _SDA_BASE_ — try `--extra-cflags "-msdata=eabi -G8"` on this draft.
//  2. Even flagged: byte-exactness needs schedule equality over 500 insns
//     (~40 FMADD chain, one FDIV, mfcr/mtcrf CR save of field 0x8, frame
//     0x78 saving f30/f31 + r26-r31). Multi-session grind.
//
// STRUCTURE MAP (anchors in <scratch>):
//   F55C prologue: stwu -0x78, mfcr->r12(sp4c), stfd f30/f31, stmw r26.
//     regs: r27=x_hi r28=x_lo r29=y_hi r8=y_lo r31=|x_hi| r30=|y_hi|
//           r26=yisint r5=xsignbit f30=y f31=x; cr4 = (x<0) live to F76C!
//   F5C4  y==0 -> 1.0 (lbl_803CA508)
//   F5CC  NaN(x)||NaN(y) -> x+y
//   F604  hx<0: y-integrality -> r26 = 2-(odd): bounds 0x433FFFFF /
//         0x3FEFFFFF, shift-mask tests on ly (k>20) and |y_hi| (k<=20)
//   F678  ly==0 specials: |y|=inf: x==+-1 -> y-y NaN; |x|>1: hy<0?0:y;
//         else hy<0?-y:0. |y|=1: hy<0?1/x:x. y==2: x*x.
//         y==0.5 && hx>=0 (cr4): sqrt [bl fn_8026FD2C]
//   F72C  ax = fabs(x) [bl fn_80270254]; lx==0 && |ix| in {inf,0,0x3FF00000}:
//         z=ax, hy<0 -> 1/z, hx<0(cr4!): (|ix|-0x3FF00000)|yisint==0 -> NaN,
//         yisint==1 -> -z. Then sx(srwi 31)!=0 && !yisint -> (x-x)/(x-x).
//   F7B8  |y|>0x41E00000: >0x43F00000 pure sign paths (|x|>1 vs <1);
//         else near-one window |ix| in (0x3FEFFFFE,0x3FF00000]: v=x-1,
//         s=v(thrd-v*qrtr), r=v*v*s*(half-s),
//         t1=v*ivln2_hi, t2=v*ivln2_lo-r*ivln2 (fmsub F864),
//         round {hi(t1+t2),lo=0} -> yy, del=t2-(yy-t1)   [sp8/spC slots]
//   F890  normal: subnormal -> ax*=2^53(lbl_803CA550), i=-53; m=hx&0xFFFFF;
//         n=i-0x3FF+(hx>>20); k=0/1/0+n++ by 0x3988E/0xBB679;
//         t={m|0x3FF00000(+ -0x100000), lo(ax)};
//         inv=1/(t+bp[k]); s=(t-bp)*inv; z=roundsd(s){lo=0};
//         dph={(j'|0x20000000... wait: (j'>>1|0x20000000)+0x80000+(k<<18)},
//         lo=dword@0x803CA514(=0); w=t-(dph-bp[k]); ss=s*s;
//         A=ss*(L6+ss*(L5+ss*(L4+ss*(L3+ss*(L2+ss*L1)))))(F9B8-F9F0);
//         r1=((t-bp)-z*dph-z*w)*inv; corr=r1*(z+s); poly=ss*A+corr(F9F8-FA00);
//         base=roundsd((z*z)+three+poly)(sp10); err=poly-((base-three)-z*z);
//         s_lo=err*s+(...); log2-hi=z+s? -> (yy,del)=(roundsd(sum),low)
//   FAC4  sign factor f31/f6: (sx&&yisint==1) ? -1 : 1
//   FADC  y split {y_hi,0}->yt; p1=yt*log_hi; p2=(y-yt)*log_hi+y*log_lo;
//         ss=p2+p1
//   FB1C  gates: hi(ss)>0x408FFFFF: !=0x40900000||lo -> sign*huge*huge;
//         tie: p2+tiny2 > ss-p1 -> huge. |hi|>0x4090CBFF:
//         (hi+0x3F6F3400)|lo != 0 -> sign*tiny*tiny; tie via cror/bns.
//   FBB0  n extraction: kk=(|hi|>>20)-0x3FE; r3=hi+(0x100000>>kk);
//         n=((r3>>20)&0x7FF)-0x3FF; t={andc(r3,~(0xffff...>>n)) ,0};
//         frac=((r3&0xFFFFF)|0x100000)>>(20-n) (neg if ss<0); p1-=t
//   FC28  exp: tt=roundsd(p2+p1); e=tt*ln2_hi + ((p2-(tt-p1))*ln2 +
//         tt*lg2_lo); u=e*e; q=u*(P1+u*(P2+u*(P3+u*(P4+u*P5)))) shape per
//         FCA8-FCA0 (one FDIV); val=n-(q-...); 
//   FCC0  bits+=frac<<20; if exp<=0 -> scalbn(f1,frac)[bl fn_802712F0];
//         else rebuild {hi+frac<<20, lo}; return sign*res
// ============================================================================
#include "types.h"
#include "qb_constants.h"

/* runtime libm callees (prototypes audited from prologues) */
extern f64 fn_8026FD2C(f64);        /* sqrt   @0x8026FD2C (f1 in/out)        */
extern f64 fn_802712F0(f64, s32);   /* scalbn @0x802712F0 (x f1, n r3)       */
extern f64 fn_80270254(f64);        /* fabs   @0x80270254 (clrlwi leaf)      */

/* .sdata constants — want loads each as `lfd disp(r13)`.
 * Values verified from DOL sec10 (@_SDA_BASE_=0x803D2280 - disp). */
extern f64 lbl_803CA508;  /* -0x7d78 one   = 1.0                              */
extern f64 lbl_803CA518;  /* -0x7d68 inf                                      */
extern f64 lbl_803CA520;  /* -0x7d60 qrtr  = 0.25                             */
extern f64 lbl_803CA528;  /* -0x7d58 thrd  = 0.33333333333333331              */
extern f64 lbl_803CA530;  /* -0x7d50 half  = 0.5                              */
extern f64 lbl_803CA538;  /* -0x7d48 ivln2_hi = 1.4426950216293335            */
extern f64 lbl_803CA540;  /* -0x7d40 ivln2_lo = 1.9259629911266175e-08        */
extern f64 lbl_803CA548;  /* -0x7d38 ivln2    = 1.4426950408889634            */
extern f64 lbl_803CA550;  /* -0x7d30 two53 = 9007199254740992 (2^53)          */
extern f64 lbl_803CA558;  /* -0x7d28 L6 = 0.20697501780033842                 */
extern f64 lbl_803CA560;  /* -0x7d20 L5 = 0.23066074577556175                 */
extern f64 lbl_803CA568;  /* -0x7d18 L4 = 0.27272812380853401                 */
extern f64 lbl_803CA570;  /* -0x7d10 L3 = 0.33333332981837743                 */
extern f64 lbl_803CA578;  /* -0x7d08 L2 = 0.42857142857855018                 */
extern f64 lbl_803CA580;  /* -0x7d00 L1 = 0.59999999999999465                 */
extern f64 lbl_803CA588;  /* -0x7cf8 three = 3.0                              */
extern f64 lbl_803CA598;  /* -0x7ce8 cp_l  = -7.0284616509527583e-09          */
extern f64 lbl_803CA5A0;  /* -0x7ce0 cp_h  = 0.96179669392597555              */
extern f64 lbl_803CA5A8;  /* -0x7cd8 T = 4503601774854144 (0x4330000080000000)*/
extern f64 lbl_803CA5B0;  /* -0x7cd0 neg1 = -1.0                              */
extern f64 lbl_803CA5B8;  /* -0x7cc8 huge = 1.0000000000000001e+300           */
extern f64 lbl_803CA5C0;  /* -0x7cc0 tiny2 = 8.0085662595372941e-17           */
extern f64 lbl_803CA5C8;  /* -0x7cb8 tiny = 1e-300                            */
extern f64 lbl_803CA5D0;  /* -0x7cb0 lg2_hi = 0.69314718246459961             */
extern f64 lbl_803CA5D8;  /* -0x7ca8 ln2 = 0.69314718055994529                */
extern f64 lbl_803CA5E0;  /* -0x7ca0 lg2_lo = -1.904654299957768e-09          */
extern f64 lbl_803CA5E8;  /* -0x7c98 P5 = 4.1381367970572385e-08              */
extern f64 lbl_803CA5F0;  /* -0x7c90 P4 = -1.6533902205465252e-06             */
extern f64 lbl_803CA5F8;  /* -0x7c88 P3 = 6.6137563214379344e-05              */
extern f64 lbl_803CA600;  /* -0x7c80 P2 = -0.0027777777777015593              */
extern f64 lbl_803CA608;  /* -0x7c78 P1 = 0.16666666666666602                 */
extern f64 lbl_803CA610;  /* -0x7c70 two  = 2.0                               */

/* shared low-word slot: want rebuilds doubles as {computed_hi, *(u32*)here}
 * (value 0) at F990/FBF8. Kept as extern to document the traffic. */
extern u32 lbl_803CA514;

/* .sdata2 lookup tables (lfdx off r13-0x7070/-0x7060/-0x7050 + k*8) */
extern f64 lbl_803CB210[]; /* bp[2]   = {1.0, 1.5}                   */
extern f64 lbl_803CB220[]; /* dp_h[2] = {0.0, 0.5849624872207642}    */
extern f64 lbl_803CB230[]; /* dp_l[2] = {0.0, 1.350039202129749e-08} */

typedef union dblbits {
    f64 d;
    struct { u32 hi; u32 lo; } w;   /* big-endian: hi = word at lower addr */
} dblbits;

/* zero materializer: want loads its 0.0 from .sdata lbl_803CA510 via
 * `lfd disp(r13)`; a literal 0.0 emits the same value with different
 * addressing. Static so the call sites stay call-free. */
static f64 lbl_803CA510_zero(void) { return 0.0; }

f64 fn_8026F55C(f64 x, f64 y)
{
    dblbits X, Y, S;
    f64 ax, yy, del, ss, p1, p2, cor, t, tt, val, res;
    f64 tv, inv, sv, z, w, r1, corr, poly, base, err;
    s32 i, k, n, frac;
    u32 hx, lx, hy, ly, ix, iy, j, m;

    X.d = x;
    Y.d = y;
    hx = X.w.hi; lx = X.w.lo;
    hy = Y.w.hi; ly = Y.w.lo;
    ix = hx & QB_UNKNOWN_0x7FFFFFFF;
    iy = hy & QB_UNKNOWN_0x7FFFFFFF;

    /* y == +-0 */
    if ((iy | ly) == 0) {
        return lbl_803CA508;
    }

    /* x or y is NaN */
    if (ix > QB_UNKNOWN_0x7FF00000 || (ix == QB_UNKNOWN_0x7FF00000 && lx != 0) ||
        iy > QB_UNKNOWN_0x7FF00000 || (iy == QB_UNKNOWN_0x7FF00000 && ly != 0)) {
        return x + y;
    }

    /* yisint: 0 non-integer, 1 odd, 2 even (only needed when x < 0) */
    k = 0;
    if (hx < 0) {
        if (iy > QB_UNKNOWN_0x433FFFFF) {
            k = 2;
        } else if (iy >= QB_UNKNOWN_0x3FF00000) {
            j = iy >> 20;
            n = j - 0x3FF;
            if (n > 20) {
                m = ly >> (52 - n);
                if ((m << (52 - n)) == ly) {
                    k = 2 - (m & 1);
                }
            } else if (ly == 0) {
                m = j >> (20 - n);
                if ((m << (20 - n)) == j) {
                    k = 2 - (m & 1);
                }
            }
        }
    }
    /* want keeps yisint live in r26 from here on */
    i = k;
    k = 0;                                  /* k reused as table selector below */

    if (ly == 0) {
        if (iy == QB_UNKNOWN_0x7FF00000) {                          /* y = +-inf */
            if ((ix - QB_UNKNOWN_0x3FF00000) == 0 && lx == 0) {
                return y - y;                            /* x == +-1: NaN */
            }
            if (ix > QB_UNKNOWN_0x3FEFFFFF) {                       /* |x| > 1 */
                return hy < 0 ? lbl_803CA510_zero() : y;
            }
            return hy < 0 ? -y : lbl_803CA510_zero();    /* |x| < 1 */
        }
        if (iy == QB_UNKNOWN_0x3FF00000) {                          /* y = +-1 */
            if (hy < 0) {
                return lbl_803CA508 / x;
            }
            return x;
        }
        if (hy == QB_UNKNOWN_0x40000000) {                          /* y = 2 */
            return x * x;
        }
        if (hy == QB_UNKNOWN_0x3FE00000 && hx >= 0) {               /* y = 0.5, x>0 */
            return fn_8026FD2C(x);
        }
    }

    ax = fn_80270254(x);

    /* special values of x (low word zero) */
    X.d = ax;
    if (lx == 0) {
        if (ix == QB_UNKNOWN_0x7FF00000 || ix == 0 || ix == QB_UNKNOWN_0x3FF00000) {
            res = ax;
            if (hy < 0) {
                res = lbl_803CA508 / res;
            }
            if (hx < 0) {
                if (((ix - QB_UNKNOWN_0x3FF00000) | i) == 0) {
                    return (res - res) / (res - res);
                }
                if (i == 1) {
                    res = -res;
                }
            }
            return res;
        }
    }

    /* x < 0 and y not an odd integer -> NaN */
    if ((hx >> 31) != 0 && i == 0) {
        return (x - x) / (x - x);
    }

    yy = lbl_803CA510_zero();
    del = lbl_803CA510_zero();
    n = 0;

    if (iy > QB_UNKNOWN_0x41E00000) {
        /* ---- huge |y| shortcuts ---- */
        if (iy > QB_UNKNOWN_0x43F00000) {
            if (ix > QB_UNKNOWN_0x3FEFFFFF) {
                return hy > 0 ? lbl_803CA518 : lbl_803CA510_zero();
            }
            return hy > 0 ? lbl_803CA510_zero() : lbl_803CA518;
        }
        if (ix > QB_UNKNOWN_0x3FEFFFFE && ix <= QB_UNKNOWN_0x3FF00000) {
            /* |x| very near 1: one refined log step decides the limit */
            f64 v = x - lbl_803CA508;
            f64 s = v * (lbl_803CA528 - v * lbl_803CA520);
            f64 r = (v * v) * s * (lbl_803CA530 - s);
            f64 t1 = v * lbl_803CA538;
            f64 t2 = v * lbl_803CA540 - r * lbl_803CA548;
            S.d = t1 + t2;
            S.w.lo = 0;
            yy = S.d;
            del = t2 - (yy - t1);
        } else if (ix > QB_UNKNOWN_0x3FEFFFFF) {
            return hy > 0 ? lbl_803CA518 : lbl_803CA510_zero();
        } else {
            return hy > 0 ? lbl_803CA510_zero() : lbl_803CA518;
        }
    } else {
        /* ---- normal path: log2(|x|) via table + L-poly ---- */
        dblbits TT;
        f64 dph, bpv, A;
        i = 0;
        if (ix < QB_UNKNOWN_0x00100000) {                   /* subnormal */
            ax *= lbl_803CA550;
            X.d = ax;
            ix = X.w.hi;
            i = -53;
        }
        n = i + (ix >> 20) - 0x3FF;
        m = ix & QB_UNKNOWN_0x000FFFFF;
        j = m | QB_UNKNOWN_0x3FF00000;
        if (m <= 0x03988E) {
            k = 0;
        } else if (m <= 0x0BB679) {
            k = 1;
        } else {
            k = 0;
            n += 1;
            j -= QB_UNKNOWN_0x00100000;
        }
        TT.d = ax;
        TT.w.hi = j;
        tv = TT.d;
        bpv = lbl_803CB210[k];
        dph = lbl_803CB220[k];
        /* (dp_l[k] lives at lbl_803CB230[k]; want folds it into the
         * dph-built double's correction path) */
        inv = lbl_803CA508 / (tv + bpv);
        sv = (tv - bpv) * inv;
        /* z = sv with low mantissa word cleared */
        S.d = sv;
        S.w.lo = 0;
        z = S.d;
        w = tv - (dph - bpv);
        ss = sv * sv;
        A = lbl_803CA558;                                     /* L6 */
        A = ss * A + lbl_803CA560;                            /* + L5 */
        A = ss * A + lbl_803CA568;                            /* + L4 */
        A = ss * A + lbl_803CA570;                            /* + L3 */
        A = ss * A + lbl_803CA578;                            /* + L2 */
        A = ss * A + lbl_803CA580;                            /* + L1 */
        r1 = ((tv - bpv) - z * dph - z * w) * inv;
        corr = r1 * (z + sv);
        poly = ss * ss * A + corr;
        base = (z * z) + lbl_803CA588 + poly;
        S.d = base;
        S.w.lo = 0;
        base = S.d;
        err = poly - ((base - lbl_803CA588) - (z * z));
        yy = base + (err * sv) + (r1 * inv) * lbl_803CA530;
        /* (exact double-double fold differs in scheduling from want;
         * see STRUCTURE MAP F9D0-FAC0 for the precise web) */
        del = (err * sv) - (yy - base);
    }

    /* ---- multiply log2(x) by y (y split for exactness) ---- */
    {
        f64 sg = ((hx < 0) && (i == 1)) ? lbl_803CA5B0 : lbl_803CA508;
        S.d = y;
        S.w.lo = 0;
        {
            f64 yt = S.d;
            p1 = yt * yy;
            p2 = (y - yt) * yy + y * del;
            ss = p2 + p1;
        }

        /* overflow / underflow gates */
        S.d = ss;
        m = S.w.hi;
        if (m > QB_UNKNOWN_0x408FFFFF) {
            if ((m + QB_UNKNOWN_0xBF700000) != 0 || S.w.lo != 0) {
                return sg * lbl_803CA5B8 * lbl_803CA5B8;
            }
            cor = p2 + lbl_803CA5C0;
            if (cor > ss - p1) {
                return sg * lbl_803CA5B8 * lbl_803CA5B8;
            }
        } else {
            j = m & QB_UNKNOWN_0x7FFFFFFF;
            if (j > QB_UNKNOWN_0x4090CBFF) {
                if (((m + QB_UNKNOWN_0x3F6F3400) | S.w.lo) != 0) {
                    return sg * lbl_803CA5C8 * lbl_803CA5C8;
                }
                /* tie: fall through unless p2 < ss-p1 */
            }
        }

        /* reduce to 1+frac/2^n and extract n */
        j = m & QB_UNKNOWN_0x7FFFFFFF;
        frac = 0;
        if ((s32)j > (s32)QB_UNKNOWN_0x3FE00000) {
            s32 kk = (j >> 20) - 0x3FE;
            u32 rh = m + (QB_UNKNOWN_0x00100000 >> kk);
            n = ((rh >> 20) & 0x7FF) - 0x3FF;
            rh &= ~(QB_UNKNOWN_0x000FFFFF >> n);
            S.w.hi = rh;
            S.w.lo = lbl_803CA514;
            t = S.d;
            frac = (s32)(((rh & QB_UNKNOWN_0x000FFFFF) | QB_UNKNOWN_0x00100000) >> (20 - n));
            if ((s32)m < 0) {
                frac = -frac;
            }
            p1 -= t;
        }

        /* exponential of the remainder, times 2^frac (want FC40-FCC8) */
        S.d = p2 + p1;
        S.w.lo = 0;
        tt = S.d;
        {
            f64 lg_hi = tt * lbl_803CA5D0;               /* *lg2_hi   */
            f64 rest = (p2 - (tt - p1)) * lbl_803CA5D8   /* *ln2      */
                     + tt * lbl_803CA5E0;                /* *lg2_lo   */
            f64 e = lg_hi + rest;
            f64 uu = e * e;
            f64 qq = uu * lbl_803CA5E8;                  /* P5        */
            f64 d, rat, g;
            qq = uu * (qq + lbl_803CA5F0);               /* u*(q+P4)? per FCA8 chain */
            qq = uu * (qq + lbl_803CA5F8);
            qq = uu * (qq + lbl_803CA600);
            qq = uu * (qq + lbl_803CA608);
            d = e - qq;                                  /* FC94 */
            rat = (e * d) / (d - lbl_803CA610);          /* FC98-FCA0 */
            g = rest - (e - lg_hi);                      /* FCA4-FCA8 */
            g = e * g + g;                               /* FCAC */
            val = lbl_803CA508 - ((rat - g) - e);        /* FCB0-FCB8 */
        }
        {
            dblbits R;
            R.d = val;
            j = R.w.hi + ((u32)frac << 20);
            if ((s32)j <= 0) {
                res = fn_802712F0(val, frac);
            } else {
                R.w.hi = j;
                res = R.d;
            }
        }
        return sg * res;
    }
}
