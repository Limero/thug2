// WIP DRAFT (non-matching) — hand-rebuilt from want; INERT (not in splits.txt)
// family=m2c range=0x8005E08C-0x8005E198 size=268B
// STATUS: NEAR 97.0% — size-exact 268B == symbols.txt size:0x10C.
// 65 of 67 words byte-identical. The only residual is ONE 2-word transposition
// in the loop preheader (see === PARKED === below).
#include "types.h"

extern const s32 lbl_80293A5C[6];
extern const char lbl_80293A74[];
extern char lbl_80293ADC[];
extern f32 lbl_80293AF4;
extern s32 lbl_80300DFC;
extern s32 lbl_80300E00;
extern s32 lbl_803CAF5C;

void *fn_8005DD6C(s32);
f32 fn_80125784(s32, s32);
void fn_800244BC(s32, f32);

void fn_8005E08C(s32 arg0) {
    s32 temp_r8;
    s32 var_r30;
    s32 temp_r31;
    f32 temp_f31;
    s32 bound;
    volatile double _dummy;

    lbl_80300DFC = (s32)((char *)lbl_80293A74 + arg0 * 0x10);
    temp_r8 = lbl_80293A5C[arg0];
    lbl_803CAF5C = arg0;
    lbl_80300E00 = temp_r8;
    var_r30 = 0;
    if (var_r30 < temp_r8) {
        /* The scale load is born before the bound copy, and the one
           zero-code asm keeps both values live at the same point: the
           copy has to wait for the scale, while the switch compares stay
           free to move around it. */
        temp_f31 = lbl_80293AF4;
        bound = temp_r8;
        __asm__("" : "+f"(temp_f31), "+r"(bound));
        do {
            temp_r31 = *(s32 *)((char *)fn_8005DD6C(var_r30) + 0x18);
            if (temp_r31 != 0) {
                switch (arg0) {
                case 1:
                    fn_800244BC(temp_r31, fn_80125784((s32)lbl_80293ADC, 0) * temp_f31);
                    break;
                case 2:
                    fn_800244BC(temp_r31, fn_80125784((s32)lbl_80293ADC, 0));
                    break;
                default:
                    fn_800244BC(temp_r31, fn_80125784((s32)lbl_80293ADC, 0));
                    break;
                }
            }
            var_r30 += 1;
        } while (var_r30 < bound);
    }
}

// === PARKED ===
// Score 97.0% (NEAR), object .text 268B == want 268B == symbols.txt size:0x10C.
//
// WHAT IS ALREADY RIGHT (do not re-derive):
//  * loop shape = guarded do-while `if (i < n) { ...; do {} while (i < bound); }`
//    (sibling fn_8005E1E8, promoted byte-identical, uses the same shape)
//  * `switch (arg0) {case 1/case 2/default}` with THREE separate bodies — an
//    if/else-if chain loses a word (264B) and drops to 32%.  Template:
//    src/fn_801BE820.c (promoted) has the byte-identical switch.
//  * callee prototypes, all audited from retail prologues:
//      void *fn_8005DD6C(s32)   reads r3, returns a pointer
//      f32     fn_80125784(s32,s32)  -> f1 (f32 return; m2c had no proto at all,
//                     so it got 2 crclr cr1eq and passed the float in r4)
//      void    fn_800244BC(s32,f32)  f1 -> *(f32*)(r3+0xB8), no r3 result
//  * `const` on the two .rodata2 objects so reload hoists their HI16 anchors
//    above the three .data/.sbss stores (that IS want's order).
//  * `volatile double _dummy;` — load-bearing: frame 0x30 / stmw r28,0x18 /
//    CR save 0x14 / f31 0x28.  Removing it = 82.1%.  A plain `double` + `"m"`
//    pin instead = 94.0% (it stops stealing slot 8, S6dt).
//  * zero-code `"+r"(bound)` — the game's latch bound is a SECOND NAME for the
//    count (want: guard `cmpw r30,r8` uses r8, latch `cmpw r30,r28` uses r28,
//    bridged by `mr r28,r8`).  Without the barrier local_alloc keeps one web
//    and the `mr` disappears -> object 264B.
//  * zero-code `"+f"(temp_f31)` — pins the hoisted `lfs f31` in the preheader;
//    worth +4 words (94.0% -> 97.0%).  Placement relative to `bound =` is inert.
//
// THE RESIDUAL (2 words, one transposition):
//   in the loop preheader want orders the six setup operations as the r9 page
//   anchor, the cr3 compare of r3 against 2, the f31 load, the r28-from-r8 copy,
//   the cr4 compare and the r29 page anchor, while this body swaps the middle
//   two so the copy lands right after the anchor and the cr3 compare third.
// Both halves (cmp3 / mr) are present and correct; they are just swapped.
// WHY it is stuck: `mr r28,r8` is a reg_alloc/local_alloc COPY inserted at the
// loop boundary (r8's last use is the `lbl_80300E00` store, r28's first use is
// the latch compare), so it has no source position — only sched2 chooses its
// slot.  `cc1 -dj` shows INSN_COST: elf_high 506, movsi 512, movsf 523,
// sleu+1 (cmpwi->CC) 646, and the post-reload RTL order of the six insns is
// EXACTLY got's printed order, i.e. got == "cheapest ready first" (512 < 646)
// and want is the opposite.  So closing it needs the copy to be unschedulable
// or to cost >646 — not reachable from C.
//
// 16 further variants measured, none better.  Two are informative:
//   * Moving `bound = temp_r8` above the `lbl_80300E00` store (W6) DOES put
//     `cmpwi cr3` first — the copy loses its reason to exist there and sched2
//     emits the want's order — but it costs 8 words (43/67) because r8 is then
//     live into the guard and the whole preheader reorders.
//   * `__asm__ __volatile__("" : "+r"(bound))` (W8) moves the copy to the very
//     top, ahead of the `lis`, and drops to 61/67 — so the barrier CAN order
//     the copy relative to the hoisted anchors, just never into want's slot.
// Everything else is inert at 65/67: barrier with an extra `"r"(temp_r8)`
// input, swapping the bound/f31 barrier order, a second `b2 = bound` copy,
// `volatile s32 bound` (77.6%, frame changes to stmw r29), re-reading the
// rodata slot for bound, `switch (a0)` on a local copy, `switch (arg0 + 0)`,
// `<= bound-1` for the latch (94.0%, adds an `addi`), f31 hoisted to the top of
// the function (71.6%), and a doubled barrier (89.6%).
// CONCLUSION: the copy can be pushed earlier (W8) or made to vanish (W6) but
// never nudged exactly one slot later.  The cc1 cost argument above still
// stands; no C spelling reaches it.
//
// MEASURED AND REJECTED (do NOT re-run):
//  flags: -fno-schedule-insns (20 diffs), -fno-schedule-insns2 (9),
//    -fno-sched-spec / -fno-gcse / -fno-thread-jumps /
//    -fno-expensive-optimizations / -O3 (4 = no-op), -Os (57).
//  statement order: bound<->temp_f31 swapped (no-op), `var_r30 = 0` before vs
//    after the three global stores (the latter is worth +11: 83.6% -> 94.0%),
//    CAF5C/E00 store order swapped (worse), bound assigned above the guard
//    (64%), latch bound read from the global lbl_80300E00 (74.6%).
//  other: `switch ((u32)arg0)` (no-op), `f32 v =` temp in case 1 (no-op),
//    hard pin `register s32 bound __asm__("r28")` (36%), inline lbl_80293AF4 in
//    the case-1 arm (3%, object 260B), extra `"+r"` barriers on bound/temp_r8
//    (83-90%), `__asm__ volatile("")` block barrier (no-op), memory-clobber
//    fence after the lfs (95.5%), 1-insn volatile `asm("mr %0,%1")` for the
//    copy (92.5% — freezing it drags cmp4/lis r29 out of place too).
//  emitted asm instructions: 0 (both barriers are zero-code).
//
// CURRENT BODY: the scale load is born before the bound copy and a single
// zero-code asm (`"+f"(temp_f31), "+r"(bound)`) makes the two values live at
// the same point, so the copy is tied behind the scale load while the two
// switch compares stay free to schedule around the pair.  The preheader order
// this targets is compare(2), scale load, bound copy, compare(1), channel
// anchor; the separate-barrier form left the copy ahead of the scale load.
// UNTRIED alternatives: make the latch bound a genuine second computation
// (re-reading lbl_80293A5C[arg0] adds a second indexed load want does not
// have); a struct/bitfield trick to change the copy's insn class; hoisting
// both the scale load and the copy out of the loop body by loop-invariant
// motion instead of spelling them in the preheader.
