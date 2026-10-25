// PARKED 2026-10-03 (a16): DIFF 36.8% — unchanged; the body below is the best
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 35.6322% -> 39.0805% per-object flags: - -> -fno-schedule-insns
// honest one (every variant tried this round scored ≤ 36.8%). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800BD518
// (the draft's own `// FLAG: -O1` earns 36.8%; plain -O2 gives 35.6%.)
// FLAG: -fno-schedule-insns
//
// REMAINING DIFF IS ONE EXTRA `lis`, PRECISELY LOCATED. want materialises TWO
// page anchors: r5 = @lbl_80298E34, defined once at 0x570 and SHARED by the
// pre-loop `lfs f12` and both in-loop `lfs f13` selects; r4 = @lbl_80298E38 for
// the two -1.0f loads. ngccc materialises THREE: a private short-lived r9 for
// the pre-loop `lfs f12` (defined at the SAME slot, 0x570, and immediately
// recycled for the `dly` toggle) plus r4/r5 for the two in-loop constants.
// The surplus `lis` therefore sits in the loop preheader and every word from
// 0x570 onward compares one slot off — the ~40 "wrong" lines below are mostly
// correct instructions one position out. Verified against the .o's reloc
// table (ADDR16_HA at 0x62/0x72/0x76, ADDR16_LO pairs, 2 REL24 calls,
// REL14 branches): 3 anchors really are emitted, so this is a cc1 codegen
// decision, not a missing/unwired reloc. (Bonus alignment trap for whoever
// cracks it: ngccc gives r4 to lbl_80298E34=+1.0f and r5 to -1.0f, the
// opposite of want, so 4 words still need the allocator to swap.)
//
// RULED OUT THIS ROUND (all measured with the command above):
//  A. Shared anchor via a pointer alias (`f32 *one = &lbl_80298E34;` used by
//     the f12 load AND both in-loop 1.0f selects) — 12.5%/14.9%. Once the
//     address is a named pseudo that is live across the whole loop, IRA parks
//     it in a CALLEE-SAVED reg (r27/r28), growing the save area and rewriting
//     the prologue: recipes §144's exact trap. Aliasing only ONE of the reads
//     = 11.4%; loading the constant into an `f32` local instead = 10.0%.
//  B. One base for BOTH constants (`f32 *tab = &lbl_80298E38;` + tab[0]/tab[-1])
//     gets the anchor count ngccc needs down to 1 in-loop, but it then REMATs
//     the base INSIDE the loop instead of hoisting it into the preheader; the
//     spin's `mr r0,r9` copy does disappear and ctr moves r6→r5: 13.8%.
//     Reading f12 through that base too = 8.0%, 344B (callee-saved again).
//  C. Reading the +0xC constant INSIDE the loop, so its MEM is literally the
//     same one the in-loop 1.0f select reads and LICM has a single anchor to
//     hoist — ngccc does NOT hoist the load (the loop's `stfs` may alias it),
//     it just loses the pre-loop `lfs f12`: 348B→344B, 32.2% / 28.7%. This
//     also kills the one thing retail proves: that its pre-loop `lfs f12` is a
//     hoisted loop-invariant load sharing one anchor with the loop.
//  D. Spin latch: `while (d--)`, `while (d-- != 0)`, `for (;d!=0;d--)` and
//     `do{--d;}while(d)` all keep ngccc's `mr r0,r9` copy (36.8/36.8/32.2/
//     26.4) — ngccc canonicalises the latch; retail's
//     `cmpwi r9,0; addi r9,r9,-1; bne` (test before decrement, same reg, no
//     copy) is not reachable from C.
//
// MOST PROMISING NEXT IDEA: (A) is a CSE-vs-LICM ordering artifact. At CSE
// time (LICM runs later) the pre-loop `MEM[lbl_80298E34]` has no register, so
// hoist_inv_expr always births a SECOND pseudo for the loop's copy and the two
// can never be coalesced — which is why retail's sharing cannot be reproduced
// by any expression, only by a register that already holds the address. The
// untried lever is keeping that register VOLATILE: every alias tried so far
// makes it loop-carried, so it lands callee-saved. Reading the alias once more
// AFTER the loops (interrupting its live range) or declaring the constants
// array-typed (`extern f32 lbl_80298E34[];` → `lbl[0]` / `lbl[-1]`, which may
// dodge the address-taken pseudo path entirely) are the two shapes not yet
// measured. Everything else in the residual is ≤2 insns and only becomes
// visible once the anchor is cracked.
//
// WIP DRAFT (non-matching) — family=m2c
// range=0x800BD518-0x800BD674 size=348B   (symbols.txt: size:0x15C = 348 ✓)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT 2026-09-27: DIFF 36.8% (55/87 masked insns), want 348B / got 348B,
// flag set = `-O1` (-O2/-O3/-O0 all worse: 35.6 / 35.6 / 0.5). Was 35.6%.
//
// WHAT THIS ROUND FIXED (structure, all verified byte-level):
//  1. LOOP CONTROL — the outer/middle 2-iteration toggles are NOT `t ^= 1` at
//     the latch. Retail computes the NEXT value in the loop HEADER into a
//     second register and copies it back at the latch:
//        0x588 cmpwi cr6,r9,0 | 0x590 xori r3,r9,1  ... 0x658 or. r9,r3,r3
//        0x598 cmpwi cr7,r0,0 | 0x5A0 xori r7,r0,1  ... 0x650 or. r0,r7,r7
//     i.e. `s32 nd = t ^ 1;` as the FIRST body statement + `t = nd;` at the
//     latch. Written that way the latch tails (`or. r0,r7,r7` / `or. r9,r3,r3`
//     + back-edge) now match retail EXACTLY. The inner loop really is
//     in-place (`xori r10,r10,1; cmpwi r10,0; bne`) — mixed form is required.
//  2. `s32 d = cnt - 1;` hoisted ABOVE the `if (cnt)` guard — that alone buys
//     the `addi r9, r30, -1` countdown in r9 and keeps the Mem_Alloc result
//     live in r3 straight through the spin to `stw r3, 0x64(r31)` (no `mr`
//     copy). Guard MUST stay on `cnt`, not on `d` (semantics differ at cnt==1).
//  3. Offset-first addition (§6k-66): `(char *)var_cur + (s32)arg0->unk0x64`
//     puts `cur` in the add's rA slot → `add r9, r11, r0` as in retail
//     (base-first gave `add r9, r0, r11`).
//  4. `fmuls f0, f13, f0` operand order at the +0 slot (f13 first).
//  5. arg1/arg2 are real 3×f32 vectors (file-local V3F) instead of
//     `*((f32 *)&argX->unk0xN)` puns through the shared s32 view.
// Relocs are clean: 2 data syms (lbl_80298E34=1.0f, lbl_80298E38=-1.0f, both
// correct @l targets) + REL24 to Mem_Free2/Mem_Alloc with addend 0.
//
// PRECISE RESIDUAL (this is why it is parked — NOT "regalloc"):
//  A. ANCHOR SURPLUS — the alignment blocker. Retail materialises TWO page
//     anchors: r5 = lbl_80298E34 created at 0x570 (before the
//     `stw r3,0x64(r31)`) and SHARED by the pre-loop `lfs f12` and by both
//     in-loop `lfs f13` selects, plus r4 = lbl_80298E38 in the outer-loop
//     header. ngccc emits THREE: a private short-lived r9 for the pre-loop
//     f12 load (r9 is then recycled for the `dly` toggle) and r4/r5 for the
//     two in-loop invariant symbols. That one surplus `lis` in the loop
//     preheader shifts the whole body by one slot, which is why ~40 masked
//     lines read as different even though most of them are identical modulo
//     the shift. Exhausted: extern-decl order swap; `extern char[] + *(f32*)&`
//     form (§6af-182); pre-loop `f32*`/`char*` alias to the symbol (4 anchors,
//     17.4%); moving the f12 load before/after the field store; and 28 flag
//     combos (-fno-schedule-insns/-insns2/-sched-spec/-sched-interblock/
//     -gcse/-rerun-cse-after-loop/-rerun-loop-opt/-cse-follow-jumps/
//     -cse-skip-blocks/-peephole/-thread-jumps/-expensive-optimizations/
//     -optimize-register-move/-branch-count-reg/-strength-reduce, and -O0..-O3).
//     It is a GCSE/LICM sharing decision in cc1 2.95: the loop-invariant
//     address is sunk into the outer-loop header instead of CSE-ing with the
//     pre-loop load that already has the same address.
//  B. STORE-ADDRESS FORM (2 insns). Retail forms a FRESH base address per
//     store — `lwz rX,0x64(r31); add r9,r11,rX` ×4 — yet leaves +4 and +8
//     unfolded (`addi r9,r9,4|8; stfs f0,0(r9)`) while folding +0 and +0xC
//     into the store displacement. Every spelling that keeps the fresh reload
//     folds 4/8 too (offset-inside, `(f32*)base+1/+2`, base-first,
//     offset-parenthesised — 5 tried). Only an INCREMENTING pointer
//     (`p = (f32*)((char*)p+4); *p = v;`) emits the addi, but it carries the
//     pointer, dropping the per-store `lwz`, and flips the three param homes
//     to r28/r29/r31 (y1 24.1%, y3 26.4%) — a net loss.
//  C. PROLOGUE `li r0,8` / `sth r0,0x94(r31)` placement (2 insns). Retail
//     hoists the `li` above `lwz r3,0x64(r31)` and delays the `sth` past the
//     `mr r28,r4` / `mr r29,r5` param homes; ngccc keeps source order. Moving
//     the store after the free block in source is catastrophic (5.7%): with no
//     intervening call, cc2 constant-propagates `unk0x94 = 8` into the later
//     `lhz` and deletes the `lhz`/`slwi r3,r30,4` pair.
//  D. SPIN-LATCH TEMP (1 insn). Retail tests the countdown in place
//     (`cmpwi r9,0; addi r9,r9,-1; bne`); ngccc copies first
//     (`mr r0,r9; addi r9,r9,-1; cmpwi r0,0; bne`). Operand-swapping the
//     post-decrement to `0 != d--` (recipe §6ar-224) does not remove the copy
//     and costs 10%.
//  E. `fmuls f0, f13, f0` at the +8 slot: retail keeps f13 first, ngccc
//     canonicalises `var_f13 * var_f0` back to `fmuls f0, f0, f13` when the
//     destination aliases the second operand (routing through a third temp
//     fixes the encoding but changes nothing measurable).
//  F. Loop-header compare placement: `cmpwi cr6` / `cmpwi cr7` sit one to two
//     slots later in the got stream (sched2 window); no schedule flag moves
//     them.
//
// FAMILY: doc-15 (call/loop-arg setup + block layout) crossed with doc-32
// (walker/loop-variable role rotation). Retry only with a new idea for (A);
// (B)–(F) are individually <=2 insns and only become visible once (A) is
// cracked.
// FLAG: -O1
#include "types.h"
#include "structs.h"
extern void Mem_Free2(s32);
extern void *Mem_Alloc(s32);
extern f32 lbl_80298E34;   /* 1.0f  */
extern f32 lbl_80298E38;   /* -1.0f */
typedef struct { f32 x; f32 y; f32 z; } V3F;
void fn_800BD518(Unk_8A4B2B78 *arg0, V3F *arg1, V3F *arg2) {
    s32 d;
    u16 cnt;
    f32 var_f12;
    f32 var_f13;
    f32 var_f1;
    f32 var_f0;
    f32 *p;
    void *sp6C;
    s32 var_rowoff;
    s32 var_cur;
    s32 var_ctr;
    s32 var_jtog;
    s32 var_l;
    u32 var_dly;
    s32 ndly;
    s32 nl;

    arg0->unk0x94 = 8U;
    if (arg0->unk0x64 != 0) {
        Mem_Free2(arg0->unk0x64);
    }
    cnt = arg0->unk0x94;
    sp6C = Mem_Alloc(cnt * 0x10);
    d = cnt - 1;
    if (cnt != 0) {
        do {
        } while (d-- != 0);
    }
    arg0->unk0x64 = (s32)sp6C;
    var_f12 = lbl_80298E34;
    var_ctr = 0;
    var_dly = 0;
    do {
        var_jtog = 0;
        ndly = var_dly ^ 1;
        var_rowoff = var_ctr * 0x10;
        do {
            var_l = 0;
            nl = var_jtog ^ 1;
            var_cur = var_rowoff;
            do {
                p = (f32 *)((char *)var_cur + (s32)arg0->unk0x64);
                var_f13 = lbl_80298E34;
                if (var_dly == 0) {
                    var_f13 = lbl_80298E38;
                }
                if (var_jtog != 0) {
                    var_f0 = arg1->x;
                } else {
                    var_f0 = arg2->x;
                }
                var_f1 = var_f13 * var_f0;
                *p = var_f1;
                if (var_jtog != 0) {
                    var_f0 = arg1->y;
                } else {
                    var_f0 = -arg2->y;
                }
                *(f32 *)((char *)var_cur + (s32)arg0->unk0x64 + (s32)0x4) = var_f0;
                var_f13 = lbl_80298E34;
                if (var_l == 0) {
                    var_f13 = lbl_80298E38;
                }
                if (var_jtog != 0) {
                    var_f0 = arg1->z;
                } else {
                    var_f0 = arg2->z;
                }
                var_f0 = var_f13 * var_f0;
                *(f32 *)((char *)var_cur + (s32)arg0->unk0x64 + (s32)0x8) = var_f0;
                var_l ^= 1;
                var_rowoff += 0x10;
                var_ctr += 1;
                *(f32 *)((char *)var_cur + (s32)arg0->unk0x64 + (s32)0xC) = var_f12;
                var_cur += 0x10;
            } while (var_l != 0);
            var_jtog = nl;
        } while (var_jtog);
        var_dly = ndly;
    } while (var_dly);
}
