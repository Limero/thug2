// WIP DRAFT (non-matching) — semantic reconstruction of 0x80254E80.
// family=m2c range=0x80254E80-0x80254FA8 size=296B
// PARKED 14.9% (11/74 words masked; want 296B got 292B) — re-scored 2026-09-25
// via diff_near.py after removing the inline-asm SDA loads (prior asm-carrying
// body scored 29.7% / 22/74). Most of that delta is POSITIONAL, not coloring:
// honest `extern` heap refs emit lis+lwz (2 words) vs want's single r13-relative
// lwz at each of the 2 sites (+2 words total), shifting every downstream masked
// index; the SDA words themselves need the -msdata link route (sda_verify.py),
// which standalone -G0 scoring can never credit.
// Semantics (confident): f32 table alloc/fill-or-free pair. fn_8024EECC is
// the (heap, count, size) array allocator (prologue mullw r31,r4,r5);
// fn_8024EBD8 is the (heap, ptr) free (reads r3+r4, frameless); arg0==0
// fills arr[i] = (f32)fn_8027052C((f32)(((f32)fn_8027052C(
// (f32)(((i+0.5)/n)*PI_2)))**2 * PI_2)) with den=(f32)(f64)(s32)n hoisted,
// else frees arr and returns NULL. lbl_802B1B90 = int->double magic
// 0x4330000080000000, lbl_802B1B98 = 0.5f, lbl_802B1BA0 = PI/2 (double);
// lbl_803CA340 (.sdata) is the heap global, read twice (alloc + free).
// fn_8027052C returns f64 in f1 (fsub/fneg f1 tails) — the caller's
// frsp f0,f1 pair is the (f32) narrowing, so the f64 proto is correct.
// Blocker (allocator wall, doc-33 class): saved-GPR span (want stmw r27,
// got stmw r26 — one extra saved reg) + rodata2 page-anchor merge (want 3
// lis for the 0x802B page, got 2) + f13/f1 scratch coloring. The two heap
// loads are r13-relative SDA21 words standalone ngccc (-G0) can never emit
// (lis+lwz absolute instead) — those 2 words need the -msdata link route
// (sda_verify.py), counted as expected diffs here, not a source error.
// Tried 2026-09-25: removed inline-asm SDA loads (banned construct) in favor
// of honest `extern void *lbl_803CA340` used directly at both call sites
// (also kills the function-long heap web that may own the extra saved reg);
// kept f64 callee proto (verified correct), union int->double dance, 5
// volatile-double frame dummies (stfd f28-f31 frame), guarded-do loop shape.
// Frame layout otherwise exact; the 2 SDA words are verifiable only via the
// -msdata link route (sda_verify.py), never via the standalone sweep.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
void fn_8024EBD8(void *heap, void *ptr);
void *fn_8024EECC(void *heap, s32 count, s32 size);
f64 fn_8027052C(f32 x);

extern f64 lbl_802B1B90;
extern f32 lbl_802B1B98;
extern f64 lbl_802B1BA0;
extern void *lbl_803CA340;

f32 *fn_80254E80(s32 arg0, s32 arg1) {
    volatile double _dummy0;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    volatile double _dummy4;
    s32 i;
    u32 magic;
    f32 *arr;
    f32 *walker;
    f32 den;
    f32 num;
    f32 s1;
    f32 cadd;
    f64 csub;
    f64 cmul;
    f64 r1;
    union {
        u32 w[2];
        f64 d;
    } cvt;

    magic = QB_INT_TO_DOUBLE_BIAS;
    arr = (f32 *)fn_8024EECC(lbl_803CA340, arg1, 4);
    if (arg0 == 0) {
        i = 0;
        if (i < arg1) {
            cvt.w[1] = (u32)arg1 ^ 0x80000000;
            cvt.w[0] = magic;
            csub = lbl_802B1B90;
            walker = arr;
            cadd = lbl_802B1B98;
            cmul = lbl_802B1BA0;
            den = (f32)(cvt.d - csub);
            do {
                cvt.w[1] = (u32)i ^ 0x80000000;
                i += 1;
                cvt.w[0] = magic;
                num = (f32)(cvt.d - csub) + cadd;
                r1 = fn_8027052C((f32)((num / den) * cmul));
                s1 = (f32)r1;
                *walker = (f32)fn_8027052C((f32)(((f64)(s1 * s1)) * cmul));
                walker += 1;
            } while (i < arg1);
        }
        return arr;
    }
    fn_8024EBD8(lbl_803CA340, arr);
    return NULL;
}
