// WIP DRAFT (non-matching) — semantic paired-single reconstruction
// family=m2c range=0x801CBBD0-0x801CBC78 size=168B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled by the
// project build, and not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 73.8% -> 78.6% (33/42 words), 168B size-exact,
// ProDG/3.9.3 -mps-float. Baseline re-measured first and confirmed at 73.8%, so
// the +2 words are real and reproducible (tools/test_wip_drafts.py --addr).
//
// Object has only `.text` (0xA8 = 168B = symbols.txt size:0xA8) + `.rela.text`
// — no private `.rodata`, so a future EXACT would be promote-clean. The frame
// is exact and unchanged: stwu -0x40, stmw r29,0x34, LR at 0x44, pair slots
// at sp+0x08 (d2) / 0x10 (d1) / 0x18+0x20 (fn_801CCF64's 16B out-param) / 0x28
// (inv). All arithmetic is genuine C using __ps_t and __builtin_ps_*; there is
// NO inline asm — four `register __ps_t __asm__("frN")` hard-reg pins, which
// emit zero instructions (asm density 0).
//
// The eight opcode-4 words in the want are all standard, emittable Gekko PS
// (hand-decoded, doc 06 M5.0q discipline): 0x11ad0028 ps_sub (A=f13,B=f0),
// 0x11ad0372 ps_mul (f13), 0x10006028 ps_sub (A=f0,B=f12), 0x11ad5c20
// ps_merge00 (C=16), 0x1000683a ps_madd (D=f0,A=f0,C=f0,B=f13), 0x10000014
// ps_sum0, 0x10000034 ps_rsqrte, 0x10000030 ps_res. No VMX/PS wall is involved
// (the earlier "ps_add prints as vsel" suspicion is §6ag-9 capstone mislabelling;
// tools/ps_diff.py decodes them all).
//
// *** TWO CORRECTIONS TO THE PREVIOUS SESSION'S NOTE (both were blockers) ***
// 1. "pinning `total` to fr0 is ignored" is FALSE. With `d1` ALSO pinned fr13,
//    `register __ps_t total __asm__("fr0")` is worth +9.5 points and is what puts
//    the ps_madd's D on the accumulator instead of the addend (§6da's warning
//    that the pin is "advisory" holds only when the accumulator pin is the ONLY
//    one — with a second fr0 pin in the function cc1 drops it).
// 2. The `ozw` fr0 pin is not load-bearing and in fact STEALS f0 from the
//    accumulator. ozw naturally lands in f0 (it is the first PS value in the
//    entry block) whether pinned or not, so the pin is pure loss: dropping it
//    is worth +4.8. Live ranges are disjoint (ozw dies at 0x4C, total is born at
//    0x6C) so both values legitimately share f0 — pinning is what broke that.
// 3. `register __ps_t d1 __asm__("fr13")` DOES bind and fixes the 0x4C ps_sub's
//    D: want has `ps_sub f13,f13,f0` (result in the LHS pzw's register) and the
//    ps_sub is a 3-way coalesce tie-break between pzw and ozw, both of which die
//    at it. Pinning d1 picks the LHS. This is the pin the old note recorded as
//    "+d1 fr13, 73.8%" — it was measured against the wrong `ozw` pin set.
//
// RESIDUAL — 9 of 42 words. At word offset 0x54 the want reloads the pair at
// r1+24 into f0 while this draft emits the square multiply into f0 instead
// (the square result took f0 where the want has f13). At 0x58 the want holds
// the square multiply in f13 while this draft loads a float into f10 from
// r11-0x4524. At 0x5C the want performs that float load while this draft
// reloads the pair at r1+24 into f13 (the pxy reload took f13 where the want
// has f0). At 0x60 the want subtracts into f0 while this draft merges into f0.
// At 0x64 the want merges into f13 while this draft subtracts into f13. At
// 0x68 the want stores the f0 pair at r1+8 while this draft emits the
// multiply-add into f0 with f13 as the addend. At 0x6C the want holds the
// multiply-add with f0 as destination and first operands and f13 as the
// addend, while this draft stores the f13 pair at r1+8. At 0x80 the want
// reloads a single float from r1+0x28 while this draft reloads the pair at
// r1+40 (a tail reload width difference). At 0x84 the want copies f0 to f13
// with a plain register move while this draft uses a pair move.
// One cause drives 0x54..0x6C: the `total` fr0 pin makes f0 attractive to the
// EARLIER ps_mul result, so `square`/`merged` go to f0 and the later `fr.pxy`
// reload is pushed to f13. want has square/merged in f13 and pxy/d2/total in f0.
// The madd itself IS correct in this body (`ps_madd f0,f13,f13,f0` — D=f0 is
// the accumulator); only its operands are swapped relative to want, because d2
// and merged landed in the wrong pair of registers.
//
// BEST ALTERNATIVE SHAPE (71.4%, 30/42 — WORSE overall but the FPR ASSIGNMENT
// of the whole middle block is exactly right: mul f13, psq_l f0, ps_sub f0,
// merge f13, madd A=C=f0 B=f13). It is x3 (this body) plus a nested-scope pin on
// the volatile reload so it keeps f0:
//     { register __ps_t pxyv __asm__("fr0"); pxyv = fr.pxy; d2 = pxyv - oy; }
// (file kept only as the idea; scoring 71.43%, 12 diffs). Its two failures are
// (a) the psq_l is still emitted at 0x5C instead of 0x54 and (b) the madd's D
// goes to f13. `cc1 -dr` on that shape shows the POST-RELOAD RTL already has
// want's register assignment AND want's block order, so both residual words are
// made by `local_alloc` + `sched`, i.e. below source level (§6bz / §6ek
// discipline: dump `-dr` before grinding). THAT IS THE LEAD FOR NEXT TIME:
// start from the nested-pxyv-pin shape, not from this body.
//
// LEVERS MEASURED THIS ROUND (all vs the 73.8% baseline body unless noted;
// `d1` pin = register __ps_t d1 __asm__("fr13"), `total` pin = ... fr0):
//  * d1 pin + total pin + ozw UNPINNED  ....... 78.57%  <-- KEPT (33/42)
//    (same, with ozw left fr0-pinned) ........... 73.81%
//  * d1 pin only ............................. 69.05%
//  * total pin only (ozw pinned) ............. 69.05%
//  * d1 pin + ozw pinned + oy fr12 + pzw fr13 (old best) . 73.81%
//  * no pins at all ........................... 61.90%
//  * square fr13 / merged fr13 pins, alone or combined ... 78.57% (no-op)
//  * d2 fr0 pin (with the above) .............. 71.43% (d2 and total fight for fr0)
//  * total fr1 ............................... 69.05%   (only fr0 works)
//  * pzw unpinned / pxy fr0 pin ............... 78.57% (both redundant)
//  * in-place forms that all failed to move the madd D or regressed the block:
//    `d1 = pzw; d1 = d1 - ozw` 73.81% | `d1 = pzw; ...` copy-then-sub 73.81% |
//    extra name for pzw 73.81% | `__builtin_ps_sub` 73.81% |
//    inline `fr.pzw` read (drop the pzw var) 47.62% |
//    `pzw = pzw - ozw` 69.05% | `d1 = ozw; d1 = pzw - d1` 73.81% |
//    madd with nested merge00 arg 71.43% | fully nested mul+merge+madd 71.43% |
//    in-place accumulator `d2 = madd(d2,d2,merged)` 69.05-71.43% |
//    `total = d2; total = madd(total,total,merged)` 71.43% |
//    add a redundant ps_add/ps_res after the madd 47.73-48.84% (length breaks)
//  * ORDER of the volatile `fr.pxy` read inside the statement block: all four
//    positions (before the mul / after the mul / before threshold / after the
//    merge) score 78.57% — byte-identical objects. The load is emitted at 0x5C
//    regardless, so statement order is NOT the lever here (this RE-CONFIRMS the
//    old note's "statement order is a no-op" finding, now on the corrected body).
//  * TAIL (`lfs f0,0x28(r1)` + `fmr f13,f0`): every spelling regresses or
//    changes the length — `*(volatile f32 *)&fr.inv` 64.29% | `fr.inv` as a
//    non-volatile PSU member + `result = fr.inv` 61.90% | `.flt.hi` direct
//    64.29% | PSU + a separate `f32 x` 61.90% | `result.ps = total; fr.inv =
//    result;` 35.56%. The non-volatile-PSU route is the sibling's exact trick
//    (src/fn_800A07F0.c emits `psq_st`+`lfs`+`fmr`) but it drops the psq_st.
//  * Flags: the old note's sweep is still valid (all inert except
//    -fno-schedule-insns2 66.7% / -fno-schedule-insns 42.9% / -O1 9.3%).
//
// TWIN ORACLE (src/fn_800A07F0.c, promoted, byte-identical, 104B): identical
// normalized-distance idiom and it confirms want's FPR colour order
// (f13, f0, f12 ... ps_mul f13 / ps_merge00 f13 / ps_madd f0,f0,f0,f13 /
// ps_sum0 f0 / psq_st f0,8(r1) / lfs f0,8(r1) / fmr f1,f0). It also shows the
// madd's D CAN land on the first operand — so the D choice is not a cc1 wall in
// general, only in this pinned configuration.
//
#include "types.h"
#include "dolphin/SN_PS.h"

typedef struct {
    char pad0x00[0x58];
    __ps_t xy;
    __ps_t zw;
} DistObject;

typedef struct {
    volatile __ps_t d2;
    volatile __ps_t d1;
    volatile __ps_t pxy;
    volatile __ps_t pzw;
    volatile __ps_t inv;
} DistFrame;

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSU;

extern DistObject *lbl_80305F9C;
extern DistObject *fn_802203E4(DistObject *);
extern void fn_801CCF64(volatile __ps_t *, DistObject *);
extern __ps_t lbl_802AD128;
extern f32 lbl_802ABADC;

s32 fn_801CBBD0(DistObject *arg0) {
    DistFrame fr;
    DistObject *other;
    __ps_t ozw;
    register __ps_t pzw __asm__("fr13");
    register __ps_t oy __asm__("fr12");
    register __ps_t d1 __asm__("fr13");
    __ps_t d2;
    __ps_t square;
    __ps_t merged;
    register __ps_t total __asm__("fr0");
    f32 threshold;
    PSU result;

    other = fn_802203E4(lbl_80305F9C);
    fn_801CCF64(&fr.pxy, arg0);
    ozw = *(volatile __ps_t *)&other->zw;
    pzw = fr.pzw;
    oy = other->xy;

    d1 = pzw - ozw;
    fr.d1 = d1;
    square = __builtin_ps_mul(d1, d1);
    threshold = lbl_802ABADC;
    d2 = fr.pxy - oy;
    merged = __builtin_ps_merge00(square, lbl_802AD128);
    fr.d2 = d2;
    total = __builtin_ps_madd(d2, d2, merged);
    total = __builtin_ps_sum0(total, total, total);
    total = __builtin_ps_rsqrte(total);
    total = __builtin_ps_res(total);
    fr.inv = total;
    result.ps = fr.inv;
    return result.flt.hi < threshold;
}
