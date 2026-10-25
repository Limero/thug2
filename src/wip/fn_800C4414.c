// WIP DRAFT (non-matching) — target: byte-identical to retail fn_800C4414
// family=m2c range=0x800C4414-0x800C4560 size=332B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 84.34% -> 89.16% (74/83 -> 75/83 words;
// object stays SIZE-EXACT 332 B).
//
// WHY PARKED: the last 9 words are one contiguous `sched` window right after the
// `bl fn_800C319C` call — the `lwz r0,0x1b0(r30)` lands in the bl's DELAY SLOT in
// retail and last in got, and the cvt `stw 0x18/0x1c(r1)` pair plus the LUT
// `lfsx f11,r27,r3` come out in a different order inside the same 11-insn block.
// `cc1 -dr` shows the POST-RELOAD RTL is still in exact source order, so the
// divergence is created by `sched`/`sched2`/`final`, not by the front end.
//
// WHAT WAS FIXED THIS ROUND (+4 words, both load-bearing, no new flag):
//  1. The first loop guard's loaded value must live in r9 — the register the
//     preheader's HI16 page anchor used and released.  Name it and hard-pin it:
//       register s32 g1 __asm__("r9");
//       g1 = *(s32 *)(o + 0xBC); if (g1 != 0 && *(s32 *)(o + 4) != 1) {
//     11 diffs -> 9.  Pinning the SECOND guard's value to r0 as well is WORSE
//     (12), and dropping the pin entirely is worse (11).
//  2. `d = __builtin_fabsf(-pos / (dt * vel))` — dt FIRST, not vel.  This is the
//     exact spelling of the three byte-identical promoted siblings
//     src/fn_800C4734.c / fn_800C47EC.c / fn_800C48A0.c (all promoted, all
//     byte-exact, same object and same node walk).  GCC's MULT operand
//     canonicalisation follows the SOURCE order for rA, so `vel*dt` emits
//     `fmuls f0,f9,f8` and leaves dt in f9; `dt*vel` emits retail's
//     `fmuls f0,f8,f9` with dt=f8 / vel=f9, which also fixes the two-word
//     `fmuls f13,f9,f13` + `fmadds f12,f13,f8,f10` at 0x800C4520/4524.
//     11 diffs -> 9 (2 words).
//
// STILL LOAD-BEARING SCAFFOLDING (re-measured this round, do not remove):
//  * `-Os`  (28.6% at -O2).  30 flags swept ON THE FIXED BODY: every one is a
//    no-op or worse; `-fno-schedule-insns` 60.2%, `-fno-gcse` 2.4% (object grows
//    to 340 B), `-fno-schedule-insns2` 79.5%, `-O2`/`-O3` 28.9%.
//  * `register s32 c4330 __asm__("r26")` — forces `li r26,0x4330` into the
//    preheader instead of rematerialising `lis` in the loop.  20.2% without.
//  * the two `volatile double` dummies + the `"m"` pins (frame 0x48, cvt at
//    sp+0x18, 6 saved GPRs at stmw r26,0x20).
//
// PROVEN DEAD (re-measured this round — do NOT re-run):
//  * Statement order of the whole post-call block.  A full sweep of all 5! = 120
//    orders of {vel, dt, pos, cvt.hi, cvt.lo} x 6 insertion slots of the `d = ...`
//    statement (720 bodies) bottoms out at 9/83 diffs.  Only the call statement's
//    position matters (it must be first: putting it last costs 80 words), and the
//    residual is a pure permutation of 9 instructions.  `-Os`+`-fno-schedule-
//    insns2`, `-fexpensive-optimizations`, `-fno-sched-interblock` under every
//    one of those orders: same 9.
//  * Frozen-ness / opaque levers on the window: `volatile` store on cvt.hi (no-op),
//    `volatile` store OR load on cvt.lo (41 diffs, object 336 B), a `volatile` or
//    plain `__asm__("lwz %0,0x1b0(%1)")` birth of the cvt-low value (74 diffs,
//    object 336 B), a `"memory"` fence after the cvt pair (19 diffs).
//  * `lo = u[0x1B0/4];` split out as its own statement (no-op), staging `dt*vel`
//    into a `prod` local (no-op), splitting the `fneg` (no-op), naming the LUT
//    index (no-op), `t*t` staged in a temp (20), the cvt denominator staged
//    (14), all four at once (20).
//  * cvt as a plain `struct { s32 hi; s32 lo; }` read via `*(f64 *)&` (no-op),
//    cvt with a `u64` member (no-op), cvt reached through a `s32 *cp` pointer
//    (81 diffs, object 340 B).
//  * `f32 *o` + `o[K/4]` (the siblings' walk spelling, with the two integer
//    guards still read through a `char *oc` alias): byte-identical 89.16%.
//    With `&o[0xBC/4]` address-of guards it explodes the frame (500 B).
//  * Every `register f32 __asm__("frN")` pin (f8/f9/f10/f11/f12/f13) is inert at
//    function scope or REGRESSES the fmadds: pinning dt to fr8 fixes 0x800C4520
//    but then makes the pin the fmadds destination (`fmadds f8,f13,f8,f10`),
//    and pinning both dt and vel to fr8/fr9 cascades (`fmuls f13,f9,f9`).
//    Looping `register` pins inside the do-block do not bind at all.
//  * Callee prototype variants for fn_800C319C (named params, `s32 *` first arg,
//    passing `u` instead of `arg0`) and LUT spellings (`tbl[i]`, `((f32*)tbl)[i]`,
//    old-style `s32 fn_800C319C();`) — all no-ops or worse.  Per the sibling's
//    note, the promoted `fn_800C319C` prologue (`mr r10,r3 / lfs f0,0x31c(r10)`)
//    proves `s32 (void*, f32)` is right, and M8.31 has no flip available.
//
// UNTRIED LEVER: the one thing that could still move the window is a 2-instruction
// opaque `asm` pair pinning `lwz r0,0x1b0(%1)` + `stw r0,0x1c(1)` at retail's
// two slots (and a second pair for `stw r26,0x18(1)`), i.e. transcribing 4 of the
// 83 instructions.  That is inside the 30% asm budget but well past the point
// where it is honest decompilation.
//
// INERT: not registered in splits.txt/configure.py — never compiled, not
// counted in objdiff progress. activate via tools/wip.py.
//
// FLAG: -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802990E0;   /* 2^52 — the game's own conversion-bias double */
extern f32 lbl_802990E8;   /* zero test on node->0x8 */
s32 fn_800C319C(void *, f32);

void fn_800C4414(void *arg0) {
    /* Two dummies: 2 saved FPRs -> 16 bytes of headroom, which puts the cvt
       union at sp+0x18 and the GPR save area at 0x20 (want). */
    volatile double _dummy;
    volatile double _dummy2;
    union {
        f64 d;
        struct { s32 hi; s32 lo; } w;   /* hi at +0 (0x18), lo at +4 (0x1c) */
    } cvt;
    register s32 c4330 __asm__("r26");  /* see header: hoists li r26,0x4330 */
    s32 *u = (s32 *)arg0;
    f32 *f = (f32 *)arg0;
    int cnt;
    register s32 g1 __asm__("r9");
    __asm__("" : : "m"(_dummy));
    __asm__("" : : "m"(_dummy2));
    if (u[0x328 / 4] == 0) {
    if (u[0x334 / 4] == 0) {
    if (u[0x32C / 4] == 0) {
        cnt = u[0x1AC / 4];
        if (cnt-- == 0)
            return;
        {
        f64 magic = lbl_802990E0;
        f32 zero = lbl_802990E8;
        char *tbl;
        char *base;
        char *o;
        tbl = (char *)arg0 + 0x300;
        c4330 = QB_INT_TO_DOUBLE_BIAS;
        do {
            f32 dt;
            f32 pos;
            f32 vel;
            f32 t;
            f32 d;
            f32 n;
            f32 acc;
            base = *(char **)&u[0x2F0 / 4];
            o = base + cnt * 480;    /* ivopts -> the -0x1E0 byte IV in r28 */
            {
                g1 = *(s32 *)(o + 0xBC);
                if (g1 != 0 && *(s32 *)(o + 4) != 1) {
                t = *(f32 *)(tbl + (fn_800C319C(arg0,
                         __builtin_fabsf(*(f32 *)(o + 8))) << 2));
                cvt.w.hi = c4330;
                dt = f[0x158 / 4];
                pos = *(f32 *)(o + 8);
                vel = *(f32 *)(o + 0xCC);
                ((s32 *)&cvt)[1] = u[0x1B0 / 4];
                d = __builtin_fabsf(-pos / (dt * vel));
                n = (f[0x2F8 / 4] * t * t) / (f32)(cvt.d - magic);
                if (n > d) {
                    n = d;
                }
                if (!(pos < zero)) {
                    n = -n;
                }
                acc = vel * n;
                *(f32 *)(o + 8) = (acc * dt) + pos;
                *(f32 *)(o + 0xA4) = *(f32 *)(o + 0xA4) + acc;
                }
            }
        } while (--cnt != -1);
        }
    }}}
}
