// libgcc L_moddi3 TU (promoted from src/wip/fn_80273BA8.c; port modeled on
// libs/libgcc/src/__divdi3.c).
// range 0x80273BA8-0x802740DC (1332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G256
// Identity: SN ProDG runtime __moddi3 (L_moddi3 object of gcc-2.95.2
// libgcc2.c): upstream L_moddi3 body verbatim (negate-dividend-only sign head,
// rp=&w remainder store), shared static-inline __udivmoddi4 + __clz_tab idiom
// copied from the LINK-SIM EXACT divdi3 port. Table = lbl_803CBD3C (proven by
// raw DOL scan: addi r9,r13,-0x6544 at 3 sites, same idiom as divdi3).
// VERIFIED: tools/sda_verify.py -> LINK-SIM EXACT (1332 bytes match DOL) on
// first attempt — no source iteration needed.
#include "types.h"

extern u8 lbl_803CBD3C[256]; /* static const UQItype __clz_tab[] of this TU */

typedef union { struct { s32 high, low; } s; u64 ll; } DIunion_;

#define SI_TYPE_SIZE_ 32
#define __BITS4_ (SI_TYPE_SIZE_ / 4)
#define __ll_B_ (1L << (SI_TYPE_SIZE_ / 2))
#define __ll_lowpart(t) ((u32) (t) % __ll_B_)
#define __ll_highpart(t) ((u32) (t) >> (SI_TYPE_SIZE_ / 2))

#define count_leading_zeros(count, x)                                        \
    do {                                                                     \
        u32 __xr = (x);                                                      \
        u32 __a;                                                             \
        __a = __xr < ((u32) 1 << 2 * __BITS4_)                               \
                  ? (__xr < ((u32) 1 << __BITS4_) ? 0 : __BITS4_)            \
                  : (__xr < ((u32) 1 << 3 * __BITS4_) ? 2 * __BITS4_         \
                                                      : 3 * __BITS4_);       \
        (count) = SI_TYPE_SIZE_ - (lbl_803CBD3C[__xr >> __a] + __a);         \
    } while (0)

#define sub_ddmmss(sh, sl, ah, al, bh, bl)                                   \
    do {                                                                     \
        u32 __x;                                                             \
        __x = (al) - (bl);                                                   \
        (sh) = (ah) - (bh) - (__x > (al));                                   \
        (sl) = __x;                                                          \
    } while (0)

#define umul_ppmm(w1, w0, u, v)                                              \
    do {                                                                     \
        u32 __x0, __x1, __x2, __x3;                                          \
        u32 __ul, __vl, __uh, __vh;                                          \
        __ul = __ll_lowpart(u);                                              \
        __uh = __ll_highpart(u);                                             \
        __vl = __ll_lowpart(v);                                              \
        __vh = __ll_highpart(v);                                             \
        __x0 = (u32) __ul * __vl;                                            \
        __x1 = (u32) __ul * __vh;                                            \
        __x2 = (u32) __uh * __vl;                                            \
        __x3 = (u32) __uh * __vh;                                            \
        __x1 += __ll_highpart(__x0);                                         \
        __x1 += __x2;                                                        \
        if (__x1 < __x2)                                                     \
            __x3 += __ll_B_;                                                 \
        (w1) = __x3 + __ll_highpart(__x1);                                   \
        (w0) = __ll_lowpart(__x1) * __ll_B_ + __ll_lowpart(__x0);            \
    } while (0)

#define __udiv_qrnnd_c(q, r, n1, n0, d)                                      \
    do {                                                                     \
        u32 __d1, __d0, __q1, __q0;                                          \
        u32 __r1, __r0, __m;                                                 \
        __d1 = __ll_highpart(d);                                             \
        __d0 = __ll_lowpart(d);                                              \
        __r1 = (n1) % __d1;                                                  \
        __q1 = (n1) / __d1;                                                  \
        __m = (u32) __q1 * __d0;                                             \
        __r1 = __r1 * __ll_B_ | __ll_highpart(n0);                           \
        if (__r1 < __m) {                                                    \
            __q1--, __r1 += (d);                                             \
            if (__r1 >= (d))                                                 \
                if (__r1 < __m)                                              \
                    __q1--, __r1 += (d);                                     \
        }                                                                    \
        __r1 -= __m;                                                         \
        __r0 = __r1 % __d1;                                                  \
        __q0 = __r1 / __d1;                                                  \
        __m = (u32) __q0 * __d0;                                             \
        __r0 = __r0 * __ll_B_ | __ll_lowpart(n0);                            \
        if (__r0 < __m) {                                                    \
            __q0--, __r0 += (d);                                             \
            if (__r0 >= (d))                                                 \
                if (__r0 < __m)                                              \
                    __q0--, __r0 += (d);                                     \
        }                                                                    \
        __r0 -= __m;                                                         \
        (q) = (u32) __q1 * __ll_B_ | __q0;                                   \
        (r) = __r0;                                                          \
    } while (0)

#define udiv_qrnnd(q, r, nh_, nl_, d_) __udiv_qrnnd_c(q, r, nh_, nl_, d_)
#define UDIV_NEEDS_NORMALIZATION_ 1

static __inline__ s64 negdi2_(s64 u_)
{
    DIunion_ w;
    DIunion_ uu;

    uu.ll = u_;

    w.s.low = -uu.s.low;
    w.s.high = -uu.s.high - ((u32) w.s.low > 0);

    return w.ll;
}

static __inline__ u64 udivmoddi4_(u64 n, u64 d, u64 *rp)
{
    DIunion_ ww;
    DIunion_ nn, dd;
    DIunion_ rr;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 b, bm;

    nn.ll = n;
    dd.ll = d;

    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            /* 0q = nn / 0D */
            count_leading_zeros(bm, d0);
            if (bm != 0) {
                /* Normalize, i.e. make the most significant bit of the
                   denominator set. */
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (SI_TYPE_SIZE_ - bm));
                n0 = n0 << bm;
            }
            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
            /* Remainder in n0 >> bm. */
        } else {
            /* qq = NN / 0d */
            if (d0 == 0)
                d0 = 1 / d0; /* Divide intentionally by zero. */
            count_leading_zeros(bm, d0);
            if (bm == 0) {
                /* From (n1 >= d0) /\ (the most significant bit of d0 is set),
                   conclude (the most significant bit of n1 is set) /\ (the
                   leading quotient digit q1 = 1).  This special case is
                   necessary, not an optimization.  (Shifts counts of
                   SI_TYPE_SIZE are undefined.) */
                n1 -= d0;
                q1 = 1;
            } else {
                /* Normalize. */
                b = SI_TYPE_SIZE_ - bm;
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q1, n1, n2, n1, d0);
            }
            /* n1 != d0...  */
            udiv_qrnnd(q0, n0, n1, n0, d0);
            /* Remainder in n0 >> bm. */
        }
        if (rp != 0)
        {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            /* 00 = nn / DD */
            q0 = 0;
            q1 = 0;
            /* Remainder in n1n0. */
            if (rp != 0)
            {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            /* 0q = NN / dd */
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                /* From (n1 >= d1) /\ (the most significant bit of d1 is set),
                   conclude (the most significant bit of n1 is set) /\ (the
                   quotient digit q0 = 0 or 1). */
                /* The condition on the next line takes advantage of that
                   n1 >= d1 (true due to program flow). */
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;
                q1 = 0;
                if (rp != 0)
                {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                u32 m1, m0;
                /* Normalize. */
                b = SI_TYPE_SIZE_ - bm;
                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);
                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }
                q1 = 0;
                /* Remainder in (n1n0 - m1m0) >> bm. */
                if (rp != 0)
                {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

s64 fn_80273BA8(s64 u_, s64 v_)
{
    int c = 0;
    DIunion_ uu, vv;
    s64 w;

    uu.ll = u_;
    vv.ll = v_;

    if (uu.s.high < 0)
        c = ~c,
        uu.ll = negdi2_(uu.ll);
    if (vv.s.high < 0)
        vv.ll = negdi2_(vv.ll);

    (void) udivmoddi4_(uu.ll, vv.ll, &w);

    if (c)
        w = negdi2_(w);

    return w;
}
