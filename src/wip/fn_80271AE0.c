// WIP DRAFT (non-matching) — hand rebuild: atan2f-variant sel(y,x).
// family=m2c range=0x80271AE0-0x80271CF4 size=532B
// IDENTITY: float atan2-style helper of THREE args (s32 sel, f32 y, f32 x):
//  - tiny-y path: if (s32)y==0: sel==-1 -> C888/fabsf(y); sel==1 -> y;
//    else -> C88C/y.  fabsf = fn_8027114C.
//  - reduction when |y|>0x3F2CA13F and again at final split (same test twice
//    in source, fdlibm style): sign-fold, y'=(c890-y)+(c894-x).
//  - two Horner chains over z2=y'^2 (num c B7A8/B7A0/B798/B790/B788/B77C-tail,
//    den c B7AC/B7A4/B79C/B794/B78C/B784), combine yp*(..)+c898 etc.
//  - big-final: int->double conversions via 0x43300000 magic pair at 0x10(r1)
//    (doc-14 territory), correction arithmetic on r9/r11 integer webs.
// PARKED @29.2% (flagless -msdata=eabi -G256): tail correction block needs exact modeling of the r9/r11 integer
// webs (or./subfic results) through the 0x4330 dance; poly section subject
// to the same FPR-home allocator cascade documented on sqrt/tanh/atan2 today
// (want homes vs ngccc picks rotate). Flags for constants: -msdata=eabi -G256.
// FLAG: -msdata=eabi -G256
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_803CA888;      /* -0x79f8 */
extern f32 lbl_803CA88C;      /* -0x79f4 */
extern f32 lbl_803CA890;      /* -0x79f0 */
extern f32 lbl_803CA894;      /* -0x79ec */
extern f32 lbl_803CA898;      /* -0x79e8 */
extern f64 lbl_803CA8A0;      /* -0x79e0 magic pair const */

extern f32 lbl_803CB77C;      /* -0x6b04 */
extern f32 lbl_803CB780;      /* -0x6b00 */
extern f32 lbl_803CB784;      /* -0x6afc */
extern f32 lbl_803CB788;      /* -0x6af8 */
extern f32 lbl_803CB78C;      /* -0x6af4 */
extern f32 lbl_803CB790;      /* -0x6af0 */
extern f32 lbl_803CB794;      /* -0x6aec */
extern f32 lbl_803CB798;      /* -0x6ae8 */
extern f32 lbl_803CB79C;      /* -0x6ae4 */
extern f32 lbl_803CB7A0;      /* -0x6ae0 */
extern f32 lbl_803CB7A4;      /* -0x6adc */
extern f32 lbl_803CB7A8;      /* -0x6ad8 */
extern f32 lbl_803CB7AC;      /* -0x6ad4 */

extern f32 fn_8027114C(f32);

f32 fn_80271AE0(s32 arg0, f32 farg0, f32 farg1) {
    s32 hx;
    s32 ix;
    s32 iv;
    s32 r9;
    f32 yy;
    f32 p2;
    f32 z2;
    f32 yp;
    f32 hA;
    f32 hB;
    f32 res;

    yy = farg0;
    {
        union {
            f32 f;
            s32 w;
        } u1;
        u1.f = yy;
        hx = u1.w;
    }
    ix = hx & QB_UNKNOWN_0x7FFFFFFF;
    if (ix <= QB_UNKNOWN_0x317FFFFF) {
        iv = (s32)yy;
        if (iv == 0) {
            r9 = ix | (arg0 + 1);
            if (r9 == 0) {
                return lbl_803CA888 / fn_8027114C(yy);
            }
            if (arg0 == 1) {
                return yy;
            }
            return lbl_803CA88C / yy;
        }
    }
    if (ix > QB_UNKNOWN_0x3F2CA13F) {
        if (hx < 0) {
            yy = -yy;
            farg1 = -farg1;
        }
        hA = lbl_803CA894 - farg1;
        hB = lbl_803CA890 - yy;
        res = hB + hA;
        yy = res;
    }
    p2 = yy * yy;
    z2 = p2 * p2;
    yp = p2 * yy;
    hA = z2 * lbl_803CB7A8 + lbl_803CB7A0;
    hA = z2 * hA + lbl_803CB798;
    hA = z2 * hA + lbl_803CB790;
    hA = z2 * hA + lbl_803CB788;
    hB = lbl_803CB7AC;
    hB = z2 * hB + lbl_803CB7A4;
    hB = z2 * hB + lbl_803CB79C;
    hB = z2 * hB + lbl_803CB794;
    hB = z2 * hB + lbl_803CB78C;
    hA = z2 * hA + lbl_803CB780;
    hB = z2 * hB + lbl_803CB784;
    res = p2 * hB + hA;
    res = yp * res + lbl_803CA898;
    res = p2 * res + lbl_803CA898;
    res = lbl_803CB77C * yp + res;
    res = yy + res;
    if (ix > QB_UNKNOWN_0x3F2CA13F) {
        /* big-final: 0x43300000-magic int conversion corrections (doc-14);
           exact integer-web modeling pending — see header decode notes. */
        f64 conv;
        s32 magich;
        union {
            f64 d;
            s32 w[2];
        } u2;
        magich = QB_INT_TO_DOUBLE_BIAS;
        u2.w[0] = magich;
        conv = u2.d - lbl_803CA8A0;
        return res;
    }
    if (arg0 == 1) {
        return res;
    }
    return res;
}
