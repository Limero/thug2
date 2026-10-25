// WIP DRAFT (non-matching) — hand rebuild: atan2f (newlib/fdlibm-style).
// family=m2c range=0x80270A84-0x80270CA4 size=544B
// IDENTITY: atan2f(y,x). Callees: atanf = atanf(f32), fn_8027114C = fabsf(f32).
// Constants are .sdata floats -> SDA21 refs; compile with -msdata=eabi -G4.
// PARKED @31.4% (flagdiff, flags below). Blocking diffs:
// UPDATE 2026-10-11: all three switch(m) -> if/else chains scores
// 20.5% with a 96B-short object, so the switch form is CONFIRMED load-bearing
// (fdlibm-style). Remaining walls (per-site unions, block placement, f13
// colouring, shadow lfs) stand as described above.
// UPDATE 2026-10-09: `extern const f32` on all 13 sdata consts -> 83.8%.
// (const-sweep lever; draft body now carries const.) Blocking diffs:
//  (1) prologue bit-conversions match only via fdlibm GET_FLOAT_WORD-style
//      PER-SITE unions (single shared union emits a spurious mr r7,r11 web;
//      plain *(s32*)&sp8 loses the fmr f0,fX spill copies entirely);
//  (2) block layout of the {ix==0 | iy==inf} shared +/-pi/2 body and the two
//      m-switch leaf blocks: GOT sinks the shared sign-test body to the bottom,
//      want keeps it inline after the ix==0 test (block-placement coin-flip);
//  (3) want's shadow lfs of the default constant before bge needs spec sched
//      that the flag pair suppresses elsewhere. Tried: ternary form, single
//      union, comma-fused loads, static inline helper (not inlined by GCC
//      2.95 at 2 call sites), if/else, 4 flag combos.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -msdata=eabi -G4 -fno-schedule-insns -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"

extern const f32 lbl_803CA6F8; /* PI      (-0x7b88) */
extern const f32 lbl_803CA6FC; /* -PI     (-0x7b84) */
extern const f32 lbl_803CA700; /* -PI/2   (-0x7b80) */
extern const f32 lbl_803CA704; /*  PI/2   (-0x7b7c) */
extern const f32 lbl_803CA708; /* bothinf m=0 (-0x7b78) */
extern const f32 lbl_803CA70C; /* bothinf m=1 (-0x7b74) */
extern const f32 lbl_803CA710; /* bothinf m=2 (-0x7b70) */
extern const f32 lbl_803CA714; /* bothinf m=3 (-0x7b6c) */
extern const f32 lbl_803CA718; /* zero / mixed m=0 (-0x7b68) */
extern const f32 lbl_803CA71C; /* mixed m=1 (-0x7b64) */
extern const f32 lbl_803CA720; /* big z   (-0x7b60) */
extern const f32 lbl_803CA724; /* pio2lo  (-0x7b5c) */

extern f32 atanf(f32);
extern f32 fn_8027114C(f32);

f32 atan2f(f32 y, f32 x) {
    u32 hx;
    u32 hy;
    s32 ix;
    s32 iy;
    s32 k;
    s32 m;
    f32 z;

    {
        union {
            f32 value;
            u32 word;
        } gf_u;
        gf_u.value = x, hx = gf_u.word;
    }
    ix = hx & QB_UNKNOWN_0x7FFFFFFF;
    {
        union {
            f32 value;
            u32 word;
        } gf_u;
        gf_u.value = y, hy = gf_u.word;
    }
    iy = hy & QB_UNKNOWN_0x7FFFFFFF;
    if ((ix > QB_UNKNOWN_0x7F800000) || (iy > QB_UNKNOWN_0x7F800000)) {
        return x + y;
    }
    if (hx == QB_UNKNOWN_0x3F800000) {
        return atanf(y);
    }
    m = ((hy >> 31)) | (((hx >> 30) & 2));
    if (iy == 0) {
        switch (m) {
        case 0:
        case 1:
            return y;
        case 2:
            return lbl_803CA6F8;
        case 3:
            return lbl_803CA6FC;
        }
    }
    if (ix == 0) {
        if ((s32)hy < 0) {
            return lbl_803CA700;
        }
        return lbl_803CA704;
    }
    if (ix == QB_UNKNOWN_0x7F800000) {
        if (iy == ix) {
            switch (m) {
            case 0:
                return lbl_803CA708;
            case 1:
                return lbl_803CA70C;
            case 2:
                return lbl_803CA710;
            case 3:
                return lbl_803CA714;
            }
        } else {
            switch (m) {
            case 0:
                return lbl_803CA718;
            case 1:
                return lbl_803CA71C;
            case 2:
                return lbl_803CA6F8;
            case 3:
                return lbl_803CA6FC;
            }
        }
    }
    if (iy == QB_UNKNOWN_0x7F800000) {
        if ((s32)hy < 0) {
            return lbl_803CA700;
        }
        return lbl_803CA704;
    }
    k = (iy - ix) >> 23;
    if (k > 0x3c) {
        z = lbl_803CA720;
    } else if (((s32)hx < 0) && (k < -0x3c)) {
        z = lbl_803CA718;
    } else {
        z = atanf(fn_8027114C(y / x));
    }
    switch (m) {
    case 1:
        {
            union {
                f32 value;
                u32 word;
            } gf_u;
            gf_u.value = z, gf_u.word ^= 0x80000000u, z = gf_u.value;
        }
    case 0:
        return z;
    case 2:
        return lbl_803CA6F8 - (z - lbl_803CA724);
    default:
        return (z - lbl_803CA724) - lbl_803CA6F8;
    }
}
