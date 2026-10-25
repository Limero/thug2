// M4: first subsystem — RNG (complete, 3/3 functions matched). Two streams of
// 3x s32 state (lbl_80311250..58 and lbl_8031125C..64), both seeded by
// Mth_InitialRand and stepped by the PRNG Mth_Rnd (stream 1) / Mth_Rnd2
// (stream 2, byte-identical shape with 125C/1260/1264 globals).
//
// THUG2 GC was built with SN Systems ProDG (ngccc / GCC 2.95.2) using
// -O2 -G0, NOT Metrowerks mwcc. Matching gotchas verified here:
//  * Mth_InitialRand: stores must be in ascending address order (50..64).
//  * Mth_Rnd/8000353C: `s2n` must be its own local — GCC then schedules
//    s2 - 0x10101010 as an independent value interleaved with `t`,
//    reproducing the original's addis/addi placement exactly.
#include "types.h"
#include "qb_constants.h"

extern s32 lbl_80311250;
extern s32 lbl_80311254;
extern s32 lbl_80311258;
extern s32 lbl_8031125C;
extern s32 lbl_80311260;
extern s32 lbl_80311264;

void Mth_InitialRand(s32 arg0) {
    lbl_80311250 = arg0;
    lbl_80311254 = QB_UNKNOWN_0x12B9B0A1;
    lbl_80311258 = QB_UNKNOWN_0x0AA2FB3F;
    lbl_8031125C = arg0;
    lbl_80311260 = QB_UNKNOWN_0x12B9B0A1;
    lbl_80311264 = QB_UNKNOWN_0x0AA2FB3F;
}

s32 Mth_Rnd(s32 scale) {
    // NOTE: t = s0*s1 + s2 relies on wrapping signed overflow (UB in C) —
    // the original emits mullw/add. Do NOT add -fwrapv or reorder these.
    s32 t = lbl_80311250 * lbl_80311254 + lbl_80311258;
    // s2n must stay a local: GCC 2.95.2 then emits addis/addi -0x10101010
    // early, interleaved with `t` — matches the original exactly.
    s32 s2n = lbl_80311258 - QB_RNG_STEP;
    lbl_80311250 = t;
    lbl_80311254 = (lbl_80311254 ^ t) + (t >> 4);
    lbl_80311258 = s2n + (t >> 3);
    // Signed arithmetic shift (srawi): keep s32 and 0xFFFF as-is.
    return ((t & 0xFFFF) * scale) >> 16;
}

// Identical PRNG step over the second stream (5C/60/64). Same shape as
// Mth_Rnd; keep s2n a local here too.
s32 Mth_Rnd2(s32 scale) {
    s32 t = lbl_8031125C * lbl_80311260 + lbl_80311264;
    s32 s2n = lbl_80311264 - QB_RNG_STEP;
    lbl_8031125C = t;
    lbl_80311260 = (lbl_80311260 ^ t) + (t >> 4);
    lbl_80311264 = s2n + (t >> 3);
    return ((t & 0xFFFF) * scale) >> 16;
}
