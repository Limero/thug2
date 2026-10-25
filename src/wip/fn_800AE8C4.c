// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-09-27, revised
// 2026-09-30, re-audited 2026-10-30
// family=m2c range=0x800AE8C4-0x800AEA14 size=336B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-30: 94.0% -> 94.0% (no improvement; body
// unchanged, this block records the round's negative results).
//
// WHY PARKED: the body is BYTE-EXACT apart from 5 words in 2 independent
// clusters, and both are now *proven* to be compiler pass artifacts rather
// than source shapes, from `cc1 -dr`/`-ds` dumps of this very body:
//   (1) the lbl_8037BD08 page reload is emitted LAST in the loop preheader
//       instead of 2nd.  `hoist_insn_out_of_loop`/GCSE2 emit a hoisted
//       loop-invariant address with `emit_insns_before(insns,
//       PREHEADER_EDGE(preheader))`, and PREHEADER_EDGE is the *last* note of
//       the preheader block => hoisted insns always land at its TAIL.  The
//       pre-reload RTL block order is exactly the source order
//       [high(lbl_80298648), lfs, ent, names, off] + the hoisted reload at
//       the end; `sched` (2-wide) then emits
//       [lis r9][addi r26][lfs][addi r21][li r23][lis r22].
//   (2) the COND_EXPR else-value `li` is scheduled BEFORE its `cmpwi`.
//       `cc1 -ds` block 4 (clock 9 emits BOTH `r109=[r101+8]` and
//       `r104=0x0`; clock 11 emits `r110=cmp(r109,0x0)`): the constant
//       `set` has insn cost 1 and is ready before the load retires, while
//       the `compare` against a CONST_INT costs 2, so cheapest-ready-first
//       always puts the `li` first.  Nothing in C or in cc1's flag set
//       changes that ordering.
//
// LEVERS TRIED (2026-10-30 round, all measured on this body):
//   cluster (1), 22 variants:
//     preheader anchor `s32 bd = (s32)lbl_8037BD08;` (2nd decl)         12.9%
//       -> materialises the full address: extra `addi rX,r11,0xBD08`, +1 word.
//     preheader NON-VOLATILE `lis` asm + `pgb - 0x42F8` at both call
//       sites, declaration order lim,pgb,ent,off,names                15.3%
//       *** THE PREHEADER IS NOW IN WANT'S SHAPE ***
//         got: lis r9 | lis r11 | lfs | addi r23,r11,-0x42f8 | addi r26 |
//              li r22 | addi r21
//         want:lis r9 | lis r22 | lfs | addi r26 | li r23 | addi r21
//       -> CSE makes the two identical `plus(pgb,-17144)` ONE loop-invariant
//          value, which loop.c hoists as an extra `addi` into the
//          preheader.  +1 word, so 15.3%.
//     same + `-fno-gcse` / `-fno-gcse2` / `-fno-tree-loop-optimize` /
//          `-fno-hoist-adjacent-loads` / `-fno-cse-follow-jumps` /
//          `-fno-cse-skip-blocks` / `-fno-ivopts` / `-fno-tree-ter` /
//          `-fno-cse2` / `-fno-split-pipeline` / `-fno-early-instructions`
//          / `-fgcse2`                                             15.3% each
//     asm variant with the two use sites spelled differently
//       (`pgb + (s32)(-0x42F8)`)                                     15.3%
//     asm variant + `register s32 pgb __asm__("r22")`                 63.5%
//     asm variant + `__asm__("" : "+r"(pgb))` before call 2 / both   81.0/60.0%
//     asm variant + a second variable `pgb2 = pgb`                   15.3%
//     asm variant + tied asm `__asm__("" : "=r"(q) : "0"(pgb))`      15.3%
//     asm variant whose output is only used by an empty asm (dead)    94.0%
//     `__asm__("" : : "s"(lbl_8037BD08))`  (empty-tmpl symbol use)     94.0%
//     `__asm__("" : : "r"(lbl_8037BD08))`                             9.3%
//     `__asm__("" : : "m"(lbl_8037BD08))`                            14.0%
//       -> both force the full address (extra `lis`+`addi`).
//   cluster (2), 20 variants, ALL 94.0% unless noted:
//     named s32/void* operand temps, `if/else`, inverted ternary,
//     `init-then-if`, `+= 0x408` after an if, storing the ternary straight
//     into the field (37.6% - worse), a named `z = 0` else value, a
//     1-insn opaque birth `__asm__("li %0,0" : "=r"(z))`, `volatile s32`
//     store lvalue, `volatile s32`/`volatile ""`/`"memory"` barriers
//     before and after the ternary (89.3% after - worse), `"+r"` on the
//     result (91.7% - worse), both, `!= 0` vs truthiness.
//   flags on the 94.0% body: 26 `-f`/`-O` combos INCLUDING
//     `-fno-sched-interblock`, `-fno-schedule-insns{,2}`, `-fno-sched-spec`,
//     `-fno-sched-round`, `-fno-gcse`, `-fno-thread-jumps`,
//     `-fno-expensive-optimizations`, `-fno-crossjumping`,
//     `-fno-if-conversion{,2}`, `-fno-cse-follow-jumps`,
//     `-fno-cse-skip-blocks`, `-O1/-Os/-O3`  -> all 94.0%, none helps
//     and none hurts.
//
// AUDIT STATE of the 94.0% body (unchanged by this round):
//   object `.text` = 0x150 = 336 B = `symbols.txt size:0x150` = the header
//   `range=` marker; only `.text` + `.rela.text` in the object, so no
//   private `.rodata` and no doc-14 pool caveat; **0 `__asm__`/`.long` beyond
//   the 3 `lis` anchors** = 3 of 84 instructions (3.6%), the other three
//   `__asm__` occurrences are `register ... __asm__("rN")` declarations
//   that emit nothing; branch audit by the §6bw method: **6/6 intra-function
//   `R_PPC_REL14` (type 11, section-relative addends 0x138/0x120/0x120/
//   0x98/0xe8/0x40 -> 0x800AE9FC/0x800AE9E4/0x800AE9E4/0x800AE95C/
//   0x800AE9AC/0x800AE904) and 7/7 `R_PPC_REL24` (type 10) verified against
//   want's independently decoded `bc`/`b` words** (BD at word bits 15..2,
//   AA=(x>>1)&1, LK=x&1, BO>=3) -> 13/13 match.  The 5 differing words are
//   pure permutation/position, with NO hidden control-flow difference.
//
// NEXT THINGS TO TRY (if someone revisits): the only untried route for (1)
// is a raw-asm window, e.g. `__asm__ volatile("lis %0,%1@ha" : "=r"(pgb) :
// "s"(lbl_8037BD08), "0"(pgb))` inside the preheader with the use sites
// written so the `-0x42F8` cannot CSE — but every `"0"`-tied / barrier
// variant tried already broke the allocation, so the expected payoff is low.
// For (2), the only remaining lever is making the `li`'s insn cost > the
// `cmpwi`'s (a `volatile`-frozen constant), which C cannot express; the
// asm-birth route (already tried) is scheduled FIRST because cc1 gives
// `asm_operands` a high ready-priority, i.e. the opposite of what is needed.
//
// VERDICT 2026-09-30: NEAR 94.0% masked (5 of 84 instructions differ),
// object size EXACT (336B == retail 0x150 == symbols.txt size:0x150), only
// .text + .rela.text in the object (no private .rodata, so no doc-14 pool
// caveat), 6/6 intra-function R_PPC_REL14 targets and all 7 R_PPC_REL24 call
// targets verified against the want. Emitted inline asm: 3 `lis` of 84
// instructions (3.6%); the other three `__asm__` occurrences are
// `register ... __asm__("rN")` declarations and emit nothing.
// Was 48.8% / 336B before this round (previous header blamed a loop-invariant
// anchor hoisting problem — that diagnosis was directionally right but the
// cause and the fix were both different; see below).
//
// ROOT CAUSE OF THE 48.8% (now fixed, 5 levers):
// The five data addresses in this function split into "hoisted into the
// loop preheader" (retail keeps exactly TWO: lbl_80298648's page and
// lbl_8037BD08's page) and "re-materialised in the loop body" (retail keeps
// THREE: lbl_80298644, lbl_8037C508, lbl_8037CE08). ngccc hoists N-1 of the
// five into the preheader and re-materialises exactly ONE — so GOT spent
// three extra saved registers (stmw r19 vs stmw r21) and the whole body
// slid two instructions.
//
// THE FIX (AGENTS §6dq-adjacent, see the recipe added below): a *non-volatile*
//   __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(sym), "r"(LOOPVAR))
// is a plain movable insn, so adding a LOOP-VARIANT extra input makes it
// non-loop-invariant and LICM cannot hoist it out of the loop, while (unlike a
// VOLATILE asm) it does not make the register allocator reload every argument
// register live across it. The volatile spelling of the very same three
// anchors does produce the same in-body `lis`, but it breaks the
// fn_800C9780 -> fn_800394CC r3 chain: reload.c marks all hard regs live
// across a volatile asm, so GOT grows a spurious `mr r3,r31` and the object
// becomes one instruction LONGER (e7 = 340B / 22.4%, e4 = 336B but `self`
// moves to r27). The C then folds the low half itself (`pg - 0x3AF8`, or
// `*(f32 *)((char *)pg - 0x79BC)`) so only ONE asm instruction is needed per
// address and the encoding matches retail's `lis rX,hi ; addi rY,rX,lo` /
// `lis rX,hi ; lfs f1,off(rX)` exactly. All three anchors reference real
// symbols.txt labels and all three page+delta pairs were hand-decoded:
//   lbl_80298644 = 0x802A0000 - 0x79BC, lbl_8037C508 = 0x80380000 - 0x3AF8,
//   lbl_8037CE08 = 0x80380000 - 0x31F8  (all present in symbols.txt).
//
// ORDERED EXPERIMENT LOG (each measured on its own from the base noted):
//   48.8%  inherited draft
//   48.8%  GetChecksum_3 typed `s32 *(*)(s32 *, s32)` (honest, byte-neutral)
//   48.8%  pure-C attempts to force the in-body anchors, all inert:
//          `extern volatile f32 lbl_80298644`, `*(volatile f32 *)&lbl`,
//          `*(f32 *)&lbl`, staging into a named f32 local, `&lbl[0]`,
//          `*(s32 *)&lbl`, `*(volatile s32 *)&lbl` (48.8% each; the `&`-form
//          spellings of lbl_8037C508 actually COST 7.3%)
//   31.0%  VOLATILE lis anchor for lbl_8037C508 alone  (in-body, but CE08
//          then gets hoisted and `self` loses r28)
//   16.5%  VOLATILE anchor for lbl_80298644 alone
//   53.6%  NON-VOLATILE anchor with a loop-variant input, all three  <-- fix
//   63.1%  + `volatile double _dummy;` (M4.92 issue-01: natural saved-GPR
//          headroom gives frame 0x40, retail is 0x48)   [84.5% without it]
//   69.0%  + `register s32 dst __asm__("r27")` — pinning the LATER-appearing
//          loop-carried web moves BOTH self->r28 and dst->r27 into place
//          (pinning the *param* instead, pin-a-copy, is 54.8% — worse)
//   83.3%  + the lbl_8037CE08 anchor statement moved from before the float
//          guard to immediately before the fn_8002A3E0 call  (biggest single
//          win after the anchors: 69.0 -> 83.3)
//   88.1%  + the lbl_80298644 anchor's loop-variant input changed from `e`
//          (the just-loaded *ent) to `ent` (the loop pointer) — `e` is a home
//          copy, `ent` is not, and the choice changes the sched tie-break
//   90.5%  + pinning the lbl_8037C508 anchor's page scratch to r9 so it
//          cannot coalesce into the pinned r27
//   92.9%  + preheader statement order `lim, ent, names, off`  (6 orders
//          tried: lim/ent/off/names 92.9, lim/ent/names/off 94.0,
//          lim/off/ent/names 82.1, ent/off/names/lim 92.9,
//          off/ent/names/lim 82.1, lim/names/ent/off 83.3)
//   94.0%  + proper AE8C4_sk file-local struct instead of (char *)sk+off casts
//          (byte-neutral here, kept because it is the honest typing)
//   94.0%  everything below is NEUTRAL or worse and was reverted:
//          12 further spellings of the two remaining residuals (see below),
//          19 -f flags (all 94.0% or worse; -fno-schedule-insns 76.2%,
//          -fno-schedule-insns2 81.0%, -fno-gcse/-fno-expensive-optimizations/
//          -fno-sched-spec/-fno-sched-interblock/-fno-rerun-cse-after-loop
//          all 94.0%), goto-state-machine loop (26.2%), for(;;)+break (94.0%),
//          `extern const f32` (94.0%), a value-identical C float literal for
//          lbl_80298648 (94.0%), volatile f32 read for it (94.0%),
//          `s32 bd = lbl_8037BD08` preheader local (16.5%),
//          a preheader VOLATILE lis anchor for lbl_8037BD08 (52.9% / 10.6%:
//          the page then becomes a user variable, GCC CSEs `pgb-0x42F8` into a
//          third register and emits `addi r30,r22,-0x42f8 ; mr r4,r30`).
//
// PRECISE RESIDUAL (5 words, two independent clusters):
//
// (1) 3 words — the lbl_8037BD08 preheader anchor is emitted LAST instead of
//     2nd.  (want 0x800AE8EC..0x800AE900 / got, same six insns otherwise):
//       Retail orders the six preheader setups as the r9 page load (-0x7fd6),
//       then the r22 page load (-0x7fc8), then the f31 load at -0x79b8(r9),
//       then r26 as r28 plus 0x64, then the r23 zeroing, then r21 as r28 plus
//       0x68. The build emits the same six setups but with the r22 page load
//       last instead of second, so the middle four shift one slot earlier.
//     My reading (not proven, flag it as a hypothesis): retail's `lis r22` is
//     a *reload* insn in the preheader — it sits immediately after the
//     `lis r9` that reloads the same block for the `lfs f31` — whereas
//     ngccc reaches it through `loop.c: hoist_insn_out_of_loop`, which does
//     `emit_insns_before (insns, loop_preheader_edge (loop))` and therefore
//     appends at the END of the preheader, after the loop-invariant inits
//     that a later pass (`cunroll`) has already put there.  The remaining
//     diffs at 0x800AE8F0/0x800AE8F8/0x800AE900 are just the three shifted
//     words.  This is a pass-ORDER artifact, not a source shape: 6 preheader
//     statement orders, 19 flags and every anchor spelling leave the `lis r22`
//     last.
//
// (2) 2 words — the COND_EXPR else-value is materialised BEFORE its compare:
//       At 0x800AE94C retail tests r9 against zero before materialising the
//       r0 zero, while the build materialises the zero first and tests after.
//     (`v = (sk->f8 != 0) ? sk->f8 + 0x408 : 0;`.) ngccc's `sched` picks the
//     cheapest ready insn, and `li r0,0` (cost ~1) always beats `cmpwi`
//     (cost ~400), so the `li` can never be second.  Twelve spellings were
//     tried and every one is byte-identical: the ternary, init-then-if, the
//     fully inverted if/else, storing the ternary straight into the field
//     (u4), a named s32/u32/pointer temp for the compare operand, a
//     materialised `zz = 0` else value, a `volatile f32 lbl_80298648` (and so
//     a non-hoistable compare operand), a `+r` barrier on the result, and a
//     `"+r"`-free staging variant.  Retail's order is what you get when the
//     `li` is not in the same schedulable region; no source spelling reaches
//     it, and no -f flag disables `sched` without breaking ~6 other words
//     (-fno-schedule-insns -> 76.2%).
//
// NEXT THINGS TO TRY (superseded 2026-10-30 — see the PARKED block at the top
// of this header, which answers both of the leads below with measured data):
//   - `cc1 -drtl`/`-dj` on the preheader: DONE.  The hoisted `lis` is appended
//     at the preheader's TAIL by construction (PREHEADER_EDGE is the block's
//     last note), and no source USE of lbl_8037BD08 in the preheader can avoid
//     materialising the full address (+1 word).
//   - a 1-instruction opaque `li` birth (AGENTS §6y-140) between an
//     asm-frozen compare and the branch: TRIED, 94.0% — cc1 gives
//     `asm_operands` a high ready-priority so the wedge is scheduled BEFORE
//     the `cmpwi`, which is the wrong way round for this residual.
#include "types.h"
#include "qb_constants.h"

// FILE-LOCAL true layouts. (2) 0x64/0x68 are the two words of a 0x20-stride
// entry walked in parallel (an object pointer + its "skeleton" name
// checksum). Fields at 0x3484/88/8C are f32 (see header).
typedef struct AE8C4_s {
    char pad0x0[0x64];
    s32 *f64;
    char *f68;
    char pad0x6C[0x1FE8];
    s32 cnt;
    char pad0x2058[0x142C];
    f32 f3484;
    f32 f3488;
    f32 f348C;
} AE8C4_t;

// the object fn_800C9780 hands back: +0x8 = the "master" node, +0xC = a
// count, +0x14 = the length fn_80036968 returns (multiplied by 0x10 for the
// memcpy), and master+0x590 is the source pointer.
typedef struct AE8C4_sk_s {
    char pad0x0[0x8];
    void *f8;
    s32 fC;
    char pad0x10[0x4];
    s32 f14;
} AE8C4_sk;

// entry[0] = the object, entry[1] = target struct, entry[2] = arg0 of 8002A3E0
typedef struct AE8C4_e_s {
    s32 f0;
    struct AE8C4_e_s *f4;
    s32 f8;
    char pad0xC[0x200];
    s32 f20C;
    s32 f210;
} AE8C4_e;

s32 *GetChecksum_3(s32 *, s32);
AE8C4_sk *fn_800C9780(s32 *);
void fn_800394CC(AE8C4_sk *, f32);
s32 fn_80036968(AE8C4_sk *);
s32 fn_8002A3E0(s32, s32, s32, s32, s32, s32, f32);
void fn_800381F0(AE8C4_sk *, s32, s32);
s32 memcpy();
extern char lbl_80298644[];
extern f32 lbl_80298648;
extern char lbl_8037BD08[];
extern char lbl_8037C508[];
extern char lbl_8037CE08[];

void fn_800AE8C4(AE8C4_t *self) {
    volatile double _dummy;
    s32 i;
    s32 ce;
    register s32 dst __asm__("r27");

    i = 0;
    if (i < self->cnt) {
        f32 lim = lbl_80298648;
        s32 *ent = (s32 *)((char *)self + 0x64);
        char *names = (char *)self + 0x68;
        s32 off = 0;

        do {
            if (*ent != 0) {
                s32 *cs = GetChecksum_3(*(s32 *)(names + off), QB_SKELETON);
                if (cs != 0) {
                    AE8C4_e *e;
                    AE8C4_sk *sk;
                    s32 a25;
                    AE8C4_e *a29;
                    s32 v;
                    s32 src;
                    f32 f13;

                    sk = fn_800C9780(cs);
                    e = (AE8C4_e *)*ent;
                    a25 = e->f8;
                    a29 = e->f4;
                    {
                        register s32 pg __asm__("r9");
                        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_80298644), "r"(ent));
                        fn_800394CC(sk, *(f32 *)((char *)pg - 0x79BC));
                    }
                    v = (sk->f8 != 0) ? (s32)sk->f8 + 0x408 : 0;
                    a29->f20C = v;
                    {
                        register s32 pg __asm__("r9");
                        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_8037C508), "r"(a29));
                        dst = pg - 0x3AF8;
                    }
                    a29->f210 = sk->fC;
                    src = *(s32 *)((char *)sk->f8 + 0x590);
                    memcpy(dst, src, fn_80036968(sk) * 0x10);
                    f13 = self->f3484;
                    if (f13 - self->f3488 < lim) {
                        a29 = 0;
                    }
                    {
                        s32 pg;
                        __asm__("lis %0,%1@ha" : "=r"(pg) : "s"(lbl_8037CE08), "r"(sk));
                        ce = pg - 0x31F8;
                    }
                    fn_8002A3E0(a25, (s32)lbl_8037BD08, dst,
                                ce, -1, (s32)a29, f13 - self->f348C);
                    fn_800381F0(sk, (s32)lbl_8037BD08, dst);
                }
            }
            i += 1;
            ent = (s32 *)((char *)ent + 0x20);
            off += 0x20;
        } while (i < self->cnt);
    }
}
