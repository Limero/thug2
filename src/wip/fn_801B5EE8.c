// WIP DRAFT — PARKED at NEAR 66.2% (compiles; non-matching body rebuilt from disasm)
// family=m2c range=0x801B5EE8-0x801B6004 size=284B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Original state: compile FAIL — m2c garbage (`cosf()` no-arg call, bogus
// `if ((0 == 0) || ...)` float-compare conditions, s32*-indexed derefs,
// wrong 3-arg signature recovered from prologue: (arg0, farg0=offset f1,
// farg1=amplitude f2)).
// Twin of fn_801B5DC4 (same template, no fsubs/fdivs: amp = farg1 directly;
// array at arg0+0x38; labels AC124/AC128/AC130/AC138/AC13C/AC140).
//   for i in 0..3: v = prod*(f32)((f64)i - magic) - farg0   (magic dance via
//   union + real .rodata2 double lbl_802AC130, §6j-1 — NOT plain casts,
//   which would synthesize private .rodata pool constants, doc-14);
//   if (!(|v| >= lo && |v| <= hi)) arr[i] = clamp(amp*cosf(v)+arr[i]).
// Negated range-check form required (cror+bns/bso = NaN->body, §6r-95).
// NOTE the twins swap amp/off FPR roles: here off=f29/amp=f30 (want
// fmr f29,f1 then fmr f30,f2); DC4 is the opposite.
//
// RE-TRIAGED 2026-10-19: sweep stable at NEAR 66.2% — the 0x43300000
// hoist wall stands. Parked as-is.
// PARKED: same 0x43300000 hoist wall as fn_801B5DC4 (~54% word-match local,
// 66.2% harness NEAR). Want hoists lis r26,0x4330 pre-loop + direct stw r26
// in-loop; GCC 2.95 rematerializes per iteration. Pins/barriers/wedges/fences
// all cost more than they gain (details in fn_801B5DC4.c header); all GPR
// assignments cascade one slot down vs want. Same root cause as parked
// Pcm_Init. Frame matches via five volatile doubles (6-FPR x 8B quirk,
// recipe 63); FPR homes exact via frN pins.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802AC124;
extern f32 lbl_802AC128;
extern f64 lbl_802AC130;
extern f32 lbl_802AC138;
extern f32 lbl_802AC13C;
extern f32 lbl_802AC140;

extern f32 cosf(f32);

typedef union {
    u32 w[2];
    f64 d;
} cvt_t;

typedef struct {
    char _pad[0x38];
    f32 arr[4];
} arr_t;

void fn_801B5EE8(s32 arg0, f32 farg0, f32 farg1) {
    cvt_t cvt;
    volatile double _dm0;
    volatile double _dm1;
    volatile double _dm2;
    volatile double _dm3;
    volatile double _dm4;
    arr_t *ap;
    register f32 hi __asm__("fr26");
    register f32 lo __asm__("fr27");
    register f64 magicd __asm__("fr28");
    register f32 off __asm__("fr29");
    register f32 amp __asm__("fr30");
    f32 pa;
    f32 pb;
    f32 prod;
    f32 v;
    f32 a;
    f32 y;
    u32 k;
    s32 i;

    pa = lbl_802AC124;
    pb = lbl_802AC128;
    magicd = lbl_802AC130;
    prod = pa * pb;
    hi = lbl_802AC138;
    lo = prod;
    off = farg0;
    k = QB_INT_TO_DOUBLE_BIAS;
    amp = farg1;
    ap = (arr_t *)arg0;
    for (i = 0; i <= 3; i++) {
        cvt.w[1] = (u32)i ^ 0x80000000U;
        cvt.w[0] = k;
        v = prod * (f32)(cvt.d - magicd) - off;
        a = fabsf(v);
        if (!(a >= lo && a <= hi)) {
            y = amp * cosf(v) + ap->arr[i];
            ap->arr[i] = y;
            if (y > lbl_802AC13C) {
                ap->arr[i] = lbl_802AC13C;
            }
            if (ap->arr[i] < lbl_802AC140) {
                ap->arr[i] = lbl_802AC140;
            }
        }
    }
}
