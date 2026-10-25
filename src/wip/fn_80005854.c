// WIP DRAFT (non-matching) — src/wip/, INERT: not in splits.txt/configure.py,
// so it is never compiled into the DOL and never counts toward objdiff progress.
//
// family=m2c range=0x80005854-0x800058CC size=120B
// extra_cflags: -mps-float
//
// Gram-Schmidt: dest -= dot(dest, vec2) * vec2, on 4-wide PS vector pairs.
//   dot      = d[0].x*v[0].x + d[1].x*v[1].x          (one lane per pair)
//   dest[i] -= broadcast(v[i].x * dot)               (both lanes of pair i)
//
// ---------------------------------------------------------------------------
// STATUS 2026-10-30: PARKED at 16/30 words (53.3%), object SIZE-EXACT
//   120 B == want 120 B.  The previous state was also 53.3% but with a **112 B**
//   object — i.e. 8 bytes (2 instructions) SHORT.  Same percentage, much better
//   starting point: with the object size-correct every remaining difference is a
//   pure permutation / displacement difference, not a missing-instruction cascade
//   (AGENTS.md §6cs-1: a 1-word length error shifts every downstream index and
//   makes the masked % meaningless; §6es: never judge a draft whose
//   len(object) != symbols.txt size).
//
//   The 2 missing words are the two `ps_mr` Gekko pair copies at want offsets
//   0x48 and 0x5C.  They are emitted here by two 1-instruction inline-asm
//   wedges (§4g budget: **2 of 30 instructions = 6.7%**, well under the 20% cap;
//   the C carries all the semantics, the asm only materialises two register
//   copies that GCC 2.95.2's copy-propagation deletes — the "undeletable
//   result-home copy" class of §73-183 / §6al-183).
//
// VERIFY WITH:  tools/venv/bin/python tools/ps_diff.py 0x80005854 120
//   ps_diff.py is the ONLY authoritative scorer for this draft.  It adds
//   -mps-float by default and decodes/masks the PS words.  test_wip_drafts.py /
//   score_body.py / flagdiff.py / diff_near.py are all PS-unaware (§6au-204), so
//   their verdicts here are meaningless — do not "fix" this body based on them.
//
// ---------------------------------------------------------------------------
// WHAT IS NOW EXACT (16 of 30 words, want offsets 0x00-0x30, 0x3C, 0x54, 0x70,
// 0x74):
//   * frame `stwu r1,-0x28(r1)` + the `mr r11,r3` dest-base copy (real pointer
//     return: 0x801eb538 and 0x80211080 both `mr r31,r3`/`mr r28,r3` right after
//     the call, and the callee never restores r3 — return-type SPELLING makes no
//     difference, all six combinations score identically)
//   * the whole 13-word dot block with want's exact FPR colouring:
//     f9=d1 f10=v1 f11=v0 f12=d0 f13=zero — psq_l x4, lis/addi/psq_l of the
//     lbl_8028FCC8 {0.0f,0.0f} pair, ps_mul, ps_merge00, ps_madd, ps_sum0
//   * `fmr f13,f0`, `psq_st f10,16(r1)` and both ps_mr destinations
//
// THE TAIL IS NOW A PURE PERMUTATION.  want 0x4C-0x6C and got 0x4C-0x6C contain
// the SAME NINE WORDS (muls0 f10, muls0 f11, psq_st f10/16, ps_sub f12,f12,f11,
// ps_mr f13,f10, psq_st f12/0(r11), ps_sub f9,f9,f13, psq_st f11/8(r1),
// psq_st f9/8(r11)) in a different order:
//   want 0x4C-0x6C and got 0x4C-0x6C contain the same nine words in a
// different order: the want runs the p1 muls0, the p0 muls0, the first sink
// store, the lane-0 subtract, the f13 pair copy, the d[0] store, the lane-1
// subtract, the second sink store, and the d[1] store, while this build runs
// the p0 muls0 first, then the p1 muls0, the f13 copy, the first sink store,
// the lane-0 subtract, the lane-1 subtract, the d[0] store, the d[1] store,
// and the second sink store last.
//
// ---------------------------------------------------------------------------
// RESIDUAL (14 words) — four independent causes, all MEASURED this round:
//
// (1) STACK-SLOT ORDER, 3 words (0x34/0x38/0x40, plus 0x44's displacement).
//     want: dot pair @ sp+0x18, round-trip scalar @ sp+0x20.  This build puts the
//     4-byte `volatile f32 scalar` @ sp+0x18 and the 8-byte `SN_PS_type dot` @
//     sp+0x20.  **The 4-byte slot ALWAYS sorts before the 8-byte PS object in
//     cc1 2.95.2** — measured across 8 structurally different spellings:
//       volatile f32 + SN_PS_type            -> scalar 0x18, dot 0x20   (3 words off)
//       SN_PS_type u (8B) + bc = *(volatile __ps_t*)&u -> SAME, still swapped
//       volatile SN_PS_type u + bc = u.ps    -> u collapses onto sp+0x8
//       both slots as 8-byte SN_PS_type (v13: `u.flt.hi = dot.flt.hi;`
//         then muls0(v1,u.ps) / muls0(v0,u.ps))  -> **SLOTS CORRECT** (0x18/0x20)
//         BUT the head FPR colouring becomes a 5-cycle: got
//         v1=f11 d1=f10 d0=f13 zero=f9 v0=f12 vs want f10/f9/f12/f13/f11
//       struct frame template holding all four slots   -> frame grows to 0x30
//       struct frame template holding only s0/s1 + pad -> frame grows to 0x30
//     DECLARATION ORDER IS **NOT** THE LEVER (swapping `scalar`/`dot`
//     declarations alone: byte-identical 53.3% object).
//     So: the slot order and the head FPR colouring are coupled — getting both
//     needs a shape where the round-trip slot is 8 bytes AND the head allocation
//     is unchanged, and no spelling tried here does that.
//
// (2) RELOAD REGISTER, 1 word (0x44) + ps_mr operand (0x48).
//     want reloads the pair into **f13** (`psq_l f13,32(r1)`) — f13 being the
//     register the zero-pair just died in — then copies f13->f0.  This build
//     reloads straight into f0 and the asm copy coalesces (`ps_mr f0,f0`).
//     MEASURED: `register __ps_t bc __asm__("fr13")` is **INERT** (byte-identical
//     53.3%).  Adding `&` to the ps_mr asm constraint makes the OUTPUT f13 and
//     the INPUT f0 — the inverse of what is wanted.  `=f` lets cc1 coalesce both
//     operands onto f0.  There is no spelling found that gives (load=f13,
//     copy=f0); the ps_mr needs a GPR `mr`-style wedge's `"=&r"` early-clobber
//     semantics, but PS-mode asm outputs take `"f"` and cc1 honours `=&f` by
//     moving the OUTPUT instead of the input.
//
// (3) TAIL PERMUTATION, 8 words (0x4C-0x6C excluding the ps_mr/0x54 items).
//     All nine tail words are PS TARGET_INSNs of equal cost, so `sched2`'s
//     cheapest-ready-first tie-break picks the order (AGENTS.md §6bz: PS ops are
//     schedulable, integer ops are frozen — here there are no integer ops, so
//     nothing is frozen and source order does not survive).  MEASURED, every
//     variant is either byte-identical or costs the HEAD's f11/f12 assignment.
//     This draft's order (p1, p0, first sink store, lane-0 subtract, f13 copy,
//     lane-1 subtract, d[0] store, second sink store, d[1] store) scores 53.3%.
//     Four reorderings that move the second sink store earlier or swap the two
//     muls0 (p1, first sink, p0, sub0, copy, d[0] store, sub1, second sink,
//     d[1]; p1, p0, first sink, sub0, second sink, copy, d[0], sub1, d[1];
//     p1, p0, first sink, sub0, copy, second sink, d[0], sub1, d[1]; p0, p1,
//     first sink, sub0, copy, d[0], sub1, second sink, d[1]) all score 46.7%
//     with the head f11 becoming f12. Appending a trailing memory-clobber
//     barrier collapses to 6.7% (116 B).
//     Every reordering that moves the tail also rotates `v0` out of f11, i.e.
//     the head's 5-value scratch-pool assignment {f9..f13} is a single unit.
//     Untested next lever: `volatile` on ONE of the two `psq_st` sinks to move it
//     out of the schedulable set (§6fs's frozen-TARGET_INSN fix), which is the
//     only mechanism known to break an all-PS tie-break.
//
// (4) The two `ps_mr` wedges themselves are stable but interact:
//       asm #1 `"=f"`  -> ps_mr f0,f0    (coalesced, wrong)
//       asm #1 `"=&f"` -> ps_mr f13,f0   (registers swapped)
//       asm #2 `"=f"`  -> ps_mr f13,f10  (CORRECT destination register)
//       asm #2 `"=&f"` -> ps_mr f13,f10  (same)
//     so `"=&f"` is required on #2 and insufficient on #1.
//
// ---------------------------------------------------------------------------
// PROVEN FACTS (do not re-derive):
//   * `ps_mr` IS emittable from cc1 2.95.2/3.9.3 under `-mps-float` via
//     `__asm__("ps_mr %0,%1" : "=&f"(o) : "f"(i))`.  This CORRECTS the pessimism
//     of AGENTS.md §6cw (fn_800BA704), where an asm `ps_mr` scored a net loss —
//     but that instance REPLACED a `psq_l` reload, so the extra insn re-rolled the
//     whole loop's FPR allocation.  Here the asm only ADDS a copy of a value that
//     is already live, which costs nothing else.
//   * `register __ps_t x __asm__("frN")` does **NOT** bind for mode(PS) locals in
//     this build: 5 registers (fr9..fr13) x 1 pin, all byte-identical 23.3%.
//     §6cw is right here; §6cx's retraction does not apply to a PS value that
//     feeds a `ps_mr` asm.
//   * `lbl_8028FCC8` is the {0.0f, 0.0f} zero pair (size:0x2C object, first 8
//     bytes zero) and MUST be declared `extern __ps_t lbl_8028FCC8;` — the form
//     the byte-verified src/fn_800A11D8.c and src/fn_800A07F0.c use, so it emits
//     lis/addi/psq_l.  `extern char []` + pun gives lis+ori and never matches.
//   * The dot -> scalar -> broadcast round trip is the `SN_PS_type` union +
//     `volatile f32` + pun-read idiom, byte-for-byte the same shape as the
//     promoted src/fn_800A11D8.c (`psq_st f0,8(r1); lfs f0,8(r1)`).
//   * `ps_muls0` is a broadcast of one lane, so the subtracted vector is built
//     from a single lane of each pair — the semantic reading above.
//   * The two `psq_st` at sp+0x8 / sp+0x10 are DEAD stores of the muls0 results.
//     They are reproduced by declaring `s0`/`s1` as *volatile* __ps_t SINKS and
//     doing the subtractions from the register temps p0/p1.  Reading s0/s1 in
//     the subtractions (the obvious spelling) makes GCC emit the stores PLUS two
//     reloads and collapses the function.  The sink ORDER matters:
//     `s1 = p1; s0 = p0;` after `p1 = muls0(v1,..); p0 = muls0(v0,..);` is the
//     only one of four orderings that scores (53.3% vs 36.7% / 16.7%).
//   * That sink choice ALSO steers the FPR colouring of the whole dot block.
//     With the wrong sink order every declaration/statement ordering produced
//     f11=d0 f12=zero f13=v0; with this order want's f11=v0 f12=d0 f13=zero
//     falls out with no pins at all.
//   * Making `dot` `volatile` is catastrophic (forces FPR spills: 132 B object
//     with stfd f31).  Making the frame a struct is worse (frame 0x30).
//
// Raw opcode-4 words were hand-decoded (A-form, VD/VA/VB/VC, xo5): the stream is
// ps_mul(25), ps_merge00(16,C=16), ps_madd(29), ps_sum0(10), ps_mr(XO10=72) at
// 0x48 and 0x5C, ps_muls0(12) x2, ps_sub(20) x2 — every word is a standard,
// emittable Gekko PS op.  No VMX and no xo5=6/7 words, so this is NOT a doc-29
// wall and NOT the doc-06 emission wall (docs/parkings/06-paired-single-ops.md).
#include "types.h"

extern __ps_t lbl_8028FCC8;

__ps_t *fn_80005854(__ps_t *dest, __ps_t *vec2) {
    __ps_t *d;
    __ps_t d0, d1, v0, v1, t;
    __ps_t p0, p1;
    __ps_t bc, bc2, q1;
    SN_PS_type dot;
    volatile __ps_t s0, s1;
// 2026-10-18: single-volatile-sink lever tried (s0 plain) — sink optimized
// away (116B, 44.8%). Reverted; both sinks must stay volatile.
    volatile f32 scalar;

    d = dest;
    d1 = d[1];
    v1 = vec2[1];
    d0 = d[0];
    v0 = vec2[0];

    /* dot = d1*v1 (one lane kept) + d0*v0 */
    t = __builtin_ps_mul(d1, v1);
    t = __builtin_ps_merge00(t, lbl_8028FCC8);
    dot.ps = __builtin_ps_madd(d0, v0, t);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);

    /* round-trip the high word through scalar memory, then rebroadcast */
    scalar = dot.flt.hi;
    bc = *(volatile __ps_t *)&scalar;
    /* retail keeps a real pair copy here; cc1 2.95.2 copy-propagates it away */
    __asm__("ps_mr %0,%1" : "=f"(bc2) : "f"(bc));

    p1 = __builtin_ps_muls0(v1, bc2);
    p0 = __builtin_ps_muls0(v0, bc2);
    s1 = p1;
    s0 = p0;

    d0 = __builtin_ps_sub(d0, p0);
    /* and again here, before the second ps_sub */
    __asm__("ps_mr %0,%1" : "=&f"(q1) : "f"(p1));
    d1 = __builtin_ps_sub(d1, q1);

    d[0] = d0;
    d[1] = d1;
    return dest;
}