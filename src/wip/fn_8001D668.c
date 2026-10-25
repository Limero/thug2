// WIP DRAFT (non-matching) — hand-rebuilt from the disasm by the agent.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 67.1875% -> 70.3125% per-object flags: -fno-schedule-insns -> -
// family=m2c range=0x8001D668-0x8001D768 size=256B
// PARKED 2026-10-30: 51.6% -> 67.2% (NEAR, size-exact, not 100%)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// 0x8001D668 = ARQ chunked DMA upload helper.  3 args: (dst, src, size).
//   r24 = src & ~0x1F,  r29 = src & 0x1F,  r31 = size,  r22 = dst (loop carried)
//   One big stack array serves BOTH as the ARQRequest out-param (at r1+8) and
//   as the 32-byte-aligned staging area: ((s32)&sp8[0x3F]) & ~0x1F  =>  r1+0x47
//   -> rlwinm -> r1+0x40.  locals = 0x40A0 - 16 - 4*13 = 0x4064 (so the array is
//   declared 0x405C: the volatile flag read below makes ngccc reserve 8 more).
//   Loop: chunk = min(rest, 0x4000 - off); flush staging range; ARQPostRequest
//   with the 32-aligned sub-length; spin on the completion flag written by the
//   ARQ callback fn_8001D4EC; flush again; memcpy out; advance dst and src.
//   The ARQ callback address and the flag are real symbols
//   (fn_8001D4EC = .text:0x8001D4EC, lbl_803627E0 = .bss:0x803627E0); m2c had
//   used a raw 0x8001D4EC literal (ori form) which never matches.
//   memcpy is left UNPROTOTYPED on purpose: retail keeps one `crclr cr1eq`
//   before that call and none before the other two.
//

// ---------------------------------------------------------------------------
// ROUND r4 (2026-10-30) RESULT: 51.6% -> 67.2%, 31 -> 21 masked diffs, object
// stays 256 B (size-exact).  The prior round's diagnosis ("a pure local_alloc
// permutation plus one extra slot") was only HALF right: the missing word was
// NOT just a permutation -- the loop was genuinely 2 instructions short of want
// before the first `bl`, and that structural gap was what made every
// downstream word compare as a diff.
//
// WHAT ACTUALLY FIXED IT (all plain C, no new flags, 0 emitted inline insns):
//   The raw chunk length `chunk + off` is used TWICE in retail: once rounded
//   in place (the DCFlushRange length) and once unrounded (to advance
//   var_r24 and as the second flush's length).  Retail materialises it ONCE
//   (add r30,r28,r29), COPIES it (mr r26,r30), then rounds r30 IN PLACE
//   (addi r30,r30,0x1f ; rlwinm r30,r30).  Our draft expressed the second
//   use as a RECOMPUTATION (`temp_r26 = temp_r28 + var_r29;`) which forced
//   GCC to keep a second `add` alive, so the round could not be in-place and
//   it borrowed r0 as a scratch (`addi r0, r31, 0x1f`) -- an extra word and
//   a 2-slot shift for the rest of the loop.
//   The fix is a COPY whose def is not re-derivable, plus a SPLIT round:
//       temp_r30 = temp_r28 + var_r29;
//       temp_r26 = temp_r30 + var_r29 - var_r29;   /* raw copy, non-remat */
//       lbl_803627E0 = 0;
//       temp_r30 = temp_r30 + 0x1F;                /* IN PLACE, no r0 scratch */
//       temp_r30 = temp_r30 & 0xFFFFFFE0;          /* IN PLACE */
//   The `+ var_r29 - var_r29` is load-bearing: it is the ONLY thing that stops
//   GCC from coalescing temp_r26 into temp_r30 and deleting the copy (plain
//   `temp_r26 = temp_r30;` -> 252 B, 1 word short, 17.5%).  The SPLIT round
//   (`+= 0x1F` then `&= ~0x1F` as two statements) is what makes the addi
//   in-place; the fused `(x + 0x1F) & 0xFFFFFFE0` lets combine pick a
//   scratch register.  Measured: fused form with the copy = 64.06%/23 diffs,
//   split form = 67.19%/21 diffs.
//
// RESIDUAL (21 of 64 words), all now PURE REGISTER NUMBERS, no missing or
// extra instruction, length exact:
//   * a 3-cycle over {r28, r29, r31} = {chunk, off, count}. Retail homes off
//     in r29, chunk in r28 and count in r31; this build homes off in r31,
//     chunk in r29 and count in r28. (The chained 2-cycles of r23/r24, i.e.
//     the src-plus-off vs src-aligned pair, are also swapped.)
//   * the r9 copy of r30 (ARQPostRequest arg 7) is emitted AFTER the r3..r8
//     setup; retail emits it FIRST, before `addi r3, r1, 8`.  That is a
//     1-insn arg-setup-order transposition (doc-15 family), and it shifts
//     the 8-word ARQ window, so those 8 rows are counted as diffs even
//     though the values are right.
//
// INERT / EXHAUSTED THIS ROUND (all measured, do not re-grind):
//   * hard-reg pins: 10 variables x 8 registers = 80 combos on the fixed
//     body; best was 23 diffs (temp_r27->r27 + var_r24->r24 together, 6bf-A
//     conjunction) and adding a THIRD pin was neutral or worse (23).  On the
//     older body, single pins on chunk/off/count bind but cascade nothing
//     (2-3 defs each).  A single-def ALIAS for the count (var_r31 = cnt_a)
//     drops the body to 17.2% -- the alias adds a live range and the whole
//     map rotates.  Same for a chunk alias (29.7%).
//   * local DECLARATION order: 49 adjacent pairs + 24 random shuffles of the
//     10 locals, all >= 29 diffs.  Decl order is genuinely not a lever here.
//   * flags (16 combos): `-fno-schedule-insns` alone is the ONLY load-bearing
//     one (21 vs 28 flagless).  `-fno-sched-spec`/`-fno-sched-interblock`/
//     `-fno-gcse`/`-fno-thread-jumps` added to it are all identical 21.
//     `-fno-schedule-insns2` REGRESSES to 29, and adding it to
//     `-fno-schedule-insns` regresses to 32.  `-fno-expensive-optimizations`
//     and `-fno-rerun-cse-after-loop` are no-ops/worse.  `-fno-crossjumping`
//     and `-fno-tree-pre` are not options in ProDG cc1 (compile error).
//   * M8.31 return-type flip on ARQPostRequest (void<->s32): byte-identical.
//     Its arity of 8 IS correct (its prologue does `cmplwi r10,0`, i.e. it
//     reads the 8th arg register r10).
//   * scratch-birth-then-copy for the staging base (6s-1 / w1) = 60.9%, and
//     with the r24 pin = 64.06% -- i.e. no better than pinning directly.
//   * a 1-insn `asm("mr %0,%1" : "=r"...)` or `"=&r"` for the copy = 50.0%
//     (50 diffs) -- worse than the `+x-x` trick, and not needed.
//   * `volatile` read for the copy (c) forces a spill+reload through sp8 and
//     destroys the frame: 10.9%.
//   * a `__asm__("" : "+r"(temp_r30))` barrier before the copy (v1) collapses
//     the copy AND the in-place round: 15.9%.
//
// VERIFIED on this body: .text = 0x100 = 256 B = symbols.txt size:0x100 =
// the range= marker; object has ONLY .text + .rela.text (no private .rodata,
// so masked-EXACT would also be promote-clean).  All 5 intra-function
// R_PPC_REL14 addends (.text+ec, +48, +b4, +a8, +38) and all 4 R_PPC_REL24
// targets (DCFlushRange x2, ARQPostRequest, memcpy) match retail (6bw
// method).  Emitted inline instructions: 0 (the only __asm__ is the
// `register ... __asm__("rN")` attribute form in the levers above, and the
// shipped body has none).
//
// NEXT LEVER: the residual is a positional local-hard-reg pool rotation that
// no single pin can reach (6ds-2: pin ONE member of a permuted group; a
// 3-cycle needs the pool OFFSET itself moved).  Two untried routes:
//   (a) the `mr r9, r30` arg-order transposition -- try 6dl/7d-4 (permute the
//       C ARGUMENT LIST of the ARQPostRequest cast so the 7th value's type
//       position changes while its register stays r9), and 4p-27/4q
//       (per-call-site return-type/param-type) on the DCFlushRange pair;
//   (b) give one of {chunk, off, count} a SECOND def that is NOT rematerial-
//       isable, so the pin binds (both have 2 defs today; the `+x-x` trick
//       worked on the copy var and the same shape on a def that is already
//       load-bearing may break the cycle without adding an instruction).
// ---------------------------------------------------------------------------
// VERDICT (SUPERSEDED, kept for history): NEAR 51.6% (31 of 64 words differ), object length EXACT (256 B =
// symbols.txt size:0x100).  Started from 34.4% (an m2c HUSK - see below).
// The control flow is now PROVEN IDENTICAL to retail: all 5 intra-function
// R_PPC_REL14 targets (.text+0xec, +0x48, +0xb4, +0xa8, +0x38) and all 4
// R_PPC_REL24 call targets (DCFlushRange x2, ARQPostRequest, memcpy) match
// the want exactly (section-relative addends, per the 6bw method).
//
// WHAT THE INHERITED 34.4% BODY ACTUALLY WAS: a statics-DCE-style husk.  m2c
// declared `s32 sp8;` so the frame came out `stwu -0x48` against retail's
// `-0x40a0`; every stack displacement and both LR slots were wrong by
// ~16 KB, so that body can never match however the masked % scores.  The
// masked % is LOWER on the correct body because the husk's short prologue
// accidentally aligned the arg-setup block.  Do not "restore" the husk.
//
// EXPERIMENT LOG (masked diff count out of 64, lower = better):
//   inherited m2c husk (frame -0x48) ................ 40 diffs / 35.5%
//   frame from the closed form + real buffer .......... 50 / 20.6%  (masked %
//        drops, but the prologue becomes byte-exact: this is the 6cs-1
//        "the score is only meaningful once the structure is right" case)
//   + declare locals=0x4064, 14 saved GPRs ........... 50 / 20.6%
//   + release one callee-saved reg: read the completion flag in the SPIN
//     loop through a `volatile s32 *` cast -> the second `lis` stops being
//     hoisted into the outer loop head and stays in the spin preheader in a
//     CALLER-SAVED reg => 13 saved GPRs, `stmw r19, 0x406c` matches ... 50 /
//        19.1%  (prologue now 4/4 exact)
//   + array 0x405C (the volatile read reserves 8 extra bytes) => frame
//     `stwu -0x40a0` exact ........................... 52 / 17.5%  (all 5
//        prologue words + both epilogue words + the spin loop exact)
//   + entry-block order dst/dma/src/count/off ......... 51 / 19.1%
//   + the latch must COPY rest into the loop's count register
//     (`var_r31 = temp_r25; } while (var_r31 != 0);` -> want's
//     `or. r31, r25, r25`, not a `cmpwi`) ............ included above
//   + express the un-rounded chunk size as a RECOMPUTATION
//     (`temp_r26 = temp_r28 + var_r29;`) instead of a copy of the sum:
//     GCC coalesces `a = b; b = f(b);` and DROPS retail's `mr r26, r30`, so
//     the object came out 4 B short; the recompute restores the 64th
//     instruction and the length becomes exact .................. 43 / 32.8%
//     *** WRONG PARTIAL FIX, SUPERSEDED BY ROUND r4: the recompute does restore
//     the length, but it is NOT what retail wrote -- it forces a second `add`
//     to stay live, which blocks the in-place round and costs an r0 scratch
//     word.  Round r4 replaces it with a non-rematerialisable COPY + a SPLIT
//     round (51.6% -> 67.2%).  See the round-r4 block above. ***
//   + `// FLAG: -fno-schedule-insns` (measured load-bearing ON THIS BODY:
//     43 -> 31; -fno-gcse, -fno-sched-interblock, -fno-schedule-insns2,
//     -fno-expensive-optimizations, -fno-rerun-cse-after-loop are all
//     no-ops or worse) ........................................ 31 / 51.6%
//
// INERT (measured, do not re-grind): local DECLARATION order (6 orders, all
// identical - decl order is not a lever here, unlike 6ec); hard-reg pins on
// chunk/off/count (SILENTLY DROPPED - all three have 2-3 defs, and a pin
// needs a single def pseudo, cf. 6cw/7a-137) and on rest/dmaoff/src/raw/dma
// (bind but cascade nothing, 32-46 diffs); the raw/rounding statement
// position (7 positions, 31-52); the chunk `if`/`?:`/`>`-ternary spellings
// (the `>` forms flip retail's `bgt` to `ble` and cost ~6 diffs, so the
// `if (count <= 0x3FFF)` form is required); a 1-insn `asm("mr %0,%1")` wedge
// for the copy (will not compile - cc1 rejects a declaration after a
// statement inside the loop body, 6cq).
//
// EXACT RESIDUAL (want vs got), all 31 words - one 1-insn slot plus a pure
// register-number permutation, no missing or extra instruction anywhere:
// at 0x6b8 the want keeps its raw copy as a register-to-register move of r30
// into r26, while this build materialises the rounding addend as an
// immediate add of 0x1f into the scratch r0, which then feeds the rounding.
// The entry block homes the destination in r22 in the want vs r23 here, the
// offset in r29 vs r30, the count in r31 vs r28, with the source born fourth
// in r24 in both; the rest value matches in r25 in both, the aligned value
// reads r30 in the want vs r31 here, and the dma value matches in r27
// in both. The chunk/off/count 3-cycle homes chunk in r28, offset in r29
// and count in r31 in the want, vs chunk in r29, offset in r30 and count in
// r28 here, and this build
// borrows r0 for the rounding. Everything else (prologue, spin loop, both
//   window, crclr, memcpy window, epilogue) is byte-identical.
//
// WHAT I BELIEVE BLOCKS IT: pure GCC 2.95 `local_alloc` colouring.  Thirteen
// values live across the calls; the local hard-reg pool is positional, so the
// ONE extra callee-saved register that a hoisted `lis` consumed earlier
// rotated the whole map, and after the count reached 13 the map lands one
// slot off in three independent groups.  No source order, declaration order,
// single hard-reg pin, or scheduling flag moves it (all measured above); the
// only untried routes are (a) a 3-4 pin set on the single-def values
// (rest/dmaoff/src/raw) chosen to shift the pool, which the 6ds-2 single-pin
// result suggests will cascade only if the right member is pinned, and (b) an
// opaque 1-insn `asm("addi"/"mr")` window around the rounding so the `mr` and
// the in-place `addi` both survive.  Emitted-asm count of the current body:
// 0 (the only `volatile` is a cast, not a statement).
// ---------------------------------------------------------------------------
#include "types.h"

extern s32 lbl_803627E0;

void DCFlushRange(s32, s32);
void ARQPostRequest(s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_8001D4EC(s32);

void fn_8001D668(s32 arg0, s32 arg1, s32 arg2) {
    char sp8[0x405C];
    s32 var_r22;
    s32 var_r24;
    s32 var_r29;
    s32 var_r31;
    s32 temp_r23;
    s32 temp_r25;
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r30;

    var_r22 = arg0;
    temp_r27 = ((s32)&sp8[0x3F]) & 0xFFFFFFE0;
    var_r29 = arg1 & 0x1F;
    var_r31 = arg2;
    var_r24 = arg1 & 0xFFFFFFE0;
    if (var_r31 != 0) {
        do {
            temp_r28 = 0x4000 - var_r29;
            if (var_r31 <= 0x3FFF) {
                temp_r28 = var_r31;
            }
            temp_r30 = temp_r28 + var_r29;
            temp_r26 = temp_r30 + var_r29 - var_r29;
            lbl_803627E0 = 0;
            temp_r30 = temp_r30 + 0x1F;
            temp_r30 = temp_r30 & 0xFFFFFFE0;
            temp_r23 = temp_r27 + var_r29;
            temp_r25 = var_r31 - temp_r28;
            var_r31 = var_r22 + temp_r28;
            DCFlushRange(temp_r27, temp_r30);
            ARQPostRequest((s32)&sp8, 0, 1, 1, var_r24, temp_r27, temp_r30, (s32)fn_8001D4EC);
            if (lbl_803627E0 == 0) {
                do {

                } while (*(volatile s32 *)&lbl_803627E0 == 0);
            }
            var_r24 += temp_r26;
            DCFlushRange(temp_r27, (temp_r26 + 0x1F) & 0xFFFFFFE0);
            var_r29 = 0;
            memcpy(var_r22, temp_r23, temp_r28);
            var_r22 = var_r31;
            var_r31 = temp_r25;
        } while (var_r31 != 0);
    }
}
