// PARKED 2026-10-03 (b39): NEAR 55.9% (baseline was DIFF 11.9%).
// family=m2c range=0x80036578-0x800367B4 size=572B
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80036578
// Body is now semantically correct AND instruction-for-instruction identical to the want
// (143 words = 572B, the exact symbol size). Every remaining diff is a register NUMBER
// (or a branch displacement that follows from one); no instruction is missing or extra.
// What the semantics pass fixed (each was worth real words):
//   - prototypes for every callee: without them ngccc emits `crclr cr1eq` before each of
//     the 7 `bl`s. WANT has none.
//   - the two `if (0 != 0)` dead asserts are guards on a VARIABLE that is 0 (same as
//     a37/fn_800363BC): `s32 var_r26 = 0; ... if (var_r26 != 0) fn_8000F320(...)`. Keeps
//     WANT's `li r26,0` ... `cmpwi r26,0` + `beq` + `lis r9,-0x7fd0`/`lwz -0x168(r9)`
//     + the dead `bl`. A literal `0 != 0` is constant-folded away.
//   - BOTH `fn_8003A31C(arg1->unk0x8)` results are needed: the first is stored to
//     arg0+0x14, the second call's result is DEAD but the call survives (want has
//     `bl 0x8003A31C` twice in the first block and once in the second block). The count
//     must be cached in a local (`temp_cnt = arg0->unk0x14;`) so ngccc keeps it in a
//     register ACROSS the Mem_Alloc call - re-reading the field gives an extra `lwz`
//     and loses WANT's `addi r31,r30,-1` hoisted above `bl Mem_Alloc`.
//   - loop 1 tail must be a POST-decrement test (`while (var_r31-- != 0)`).
//   - loop 3's inner stride is ONE 0x18-byte chunk (`ptr += 1` on a Chunk18*), not
//     `+= 6` s32 words; m2c's all-s32 cast type gives `addi rX,rX,0x90`.
//   - both outer loops must be written `i = 0; if (i < cnt) { off = 0; do {...} while
//     (i < cnt); }` (NOT `if (cnt > 0)`): the `cmpw rXi,r0; bge` guard with `li rXi,0`
//     above it and `li rOff,0` BELOW the guard is the rotated-`while` shape. `cnt > 0`
//     folds to `cmpwi r0,0; ble` and is a different loop.
//   - loop 4's 0x20-byte record is s32 at +0, s32 at +8, and two `__ps_t` at +0x10/+0x18
//     (`psq_l/psq_st`). To get WANT's TWO-STEP address (`add r9,r8,r9; addi r9,r9,0x10;
//     psq_l f0,0(r9)`) the +0x10 must be its own statement (`p = (ps*)...; p += 2;`);
//     `(__ps_t *)((u8*)b + off) + 2` folds into `psq_l f0,16(reg)` and costs 4 words.
//   - loop 4: form the DEST ps pointer BEFORE the SRC one. That single statement-order
//     swap is what puts the source pointer in r9 and the dest in r11 (as in WANT); the
//     other order gets r11/r9 and loses 20 words. Loop 4 is now byte-exact.
// Concrete remaining diff (all register numbers; nothing structural):
//   (1) LOOP 3 (want[60..93), 34 words) — identical instruction sequence, different regs.
//       WANT base=r7, idx+1=r8, src=r9, idx=r10, dst=r11.  GOT base=r6, idx+1=r7,
//       idx=r8, dst=r10, src=r11.  This is the whole 20-word block's score.
//   (2) the LOOP 1 latch costs one extra word here: want compares r31 against
//       zero, decrements r31 and branches back, while this body first copies
//       r30 across to r0, compares r0 against zero and decrements r30 before
//       the branch (1 extra word), with walker/counter in r31/r30 not r30/r31.
//       The extra `mr r0` disappears if the loop-1 counter is declared `u32` (verified:
//       `u32 c; c = n-1; do{...} while (c-- != 0);` -> `cmpwi rX,0; addi rX,-1; bne`),
//       BUT that drops the body to 142 words and the block-2 counter init that offsets
//       it is lost too, so the length goes 143->142 and the score falls to DIFF.
//   (3) LOOP 2 inner 4-iteration nest: WANT `li r0,4; addi r30,r9,-1; mtctr r0; bdnz`;
//       GOT `li r8,4; addic. r8,r8,-1; bne` + `addi r30,r30,-1` (no CTR loop). In
//       isolation the SAME goto-loop body compiles to WANT's mtctr/bdnz shape (verified
//       with 4 spellings of the empty inner loop), so this is a whole-function
//       register-pressure artefact, not a source-shape bug.
//   (4) BLOCK 2: WANT hoists `addi r9,r30,-1` (loop-2 counter init) above `cmpwi r30,0`;
//       GOT emits `addi r30,r30,-1` below it, because the counter shares r30 with the
//       count. Consequence of (1)/(3)'s allocation.
// Ruled out (all measured, all worse or neutral):
//   - `register ... __asm__("rN")` pins on loop 3's five variables (r7/r8/r9/r10/r11):
//     GOT grows to 145 words, score drops to DIFF. The pins cascade into the rest of
//     the allocation, so pinning is not a shortcut here.
//   - local DECLARATION order (both orders of Chunk18*, and hoisting loop-3 vars) has
//     zero effect on the register assignment.
//   - `base + off` vs `off + base` in the address expressions: no effect. ngccc
//     canonicalises commutative `add`; rA/rB order is its own rule (recipes 4p), not
//     the source's.
//   - reordering the loop-3 statements (src/dst/index first-vs-last): no effect.
//   - `if (cnt > 0)` vs `i = 0; if (i < cnt)`: the latter is required (see above).
//   - `-mps-float` is REQUIRED here (the loop-4 `__ps_t` copies are `psq_l/psq_st`);
//     without it loop 4 collapses and the body loses 8 words.
// Most promising next idea: chase the loop-3 register flip by reducing the number of
// simultaneously-live locals (the block needs exactly 5: base, idx+1, src, idx, dst).
// GOT spends r6/r7/r8/r10/r11 there while loop 4's ps pair owns r9/r11; if loop 3 could
// be made to reuse r9/r11 for its src/dst the whole block goes exact. Everything tried
// from the source side (statement order, declaration order, operand order, types) is a
// no-op, so the lever is probably the live range of `var_r10_2` (WANT computes idx+1 at
// the TOP of the body and `mr r10,r8` at the bottom - i.e. it is a next-index copy, not
// `i++`).
#include "types.h"
#include "structs.h"
// extra_cflags: -mps-float
extern char lbl_802FFE98[];

void fn_8000F320(void *);
void fn_80036370(void *);
void fn_80036864(void *, void *);
s32 fn_800368FC(void *, void *);
s32 fn_8003A31C(void *);
void *Mem_Alloc(s32);

/* arg0: count at +0x14, 0x20-byte rail array at +0x18, 0x60-byte rail array at +0x4 */
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    void *unk0x18;
} RecDst;

/* arg1: rail arrays at +4 (0x60 stride) and +0x18 (0x20 stride), owner at +8 */
typedef struct {
    s32 unk0x0;
    void *unk0x4;
    void *unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    void *unk0x18;
} RecSrc;

/* 0x18-byte all-s32 chunk copied 3x per record */
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
} Chunk18;

/* 0x20-byte rail record: two s32 (at 0 and 8) + two paired-single pairs */
typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    __ps_t p0;
    __ps_t p1;
} Rail20;

void *fn_80036578(RecDst *arg0, RecSrc *arg1) {
    s32 temp_cnt;
    s32 temp_cnt2;
    s32 var_r26;
    s32 var_ctr;
    s32 var_r10;
    s32 var_r10_2;
    s32 var_r31;
    s32 var_r9;
    s32 var_r7;
    s32 var_r8;
    void *var_base;
    void *temp_r3;
    void *temp_r3_2;
    void *var_walk;
    __ps_t *var_sp;
    __ps_t *var_dp;
    Chunk18 *var_r11;
    Chunk18 *var_r9_2;

    var_r26 = 0;
    arg0->unk0x14 = fn_8003A31C(arg1->unk0x8);
    fn_8003A31C(arg1->unk0x8);
    temp_cnt = arg0->unk0x14;
    temp_r3 = Mem_Alloc(temp_cnt << 5);
    var_r31 = temp_cnt - 1;
    var_walk = temp_r3;
    if (temp_cnt != 0) {
        do {
            fn_80036370(var_walk);
            var_walk += 0x20;
        } while (var_r31-- != 0);
    }
    arg0->unk0x18 = temp_r3;
    if (var_r26 != 0) {
        fn_8000F320(*(void **)&lbl_802FFE98);
    }
    var_r26 = 0;
    fn_8003A31C(arg1->unk0x8);
    temp_cnt2 = arg0->unk0x14;
    temp_r3_2 = Mem_Alloc(temp_cnt2 << 6);
    var_r9 = temp_cnt2 - 1;
    if (temp_cnt2 != 0) {
        do {
            var_ctr = 4;
        loop_6:
            var_ctr -= 1;
            if (var_ctr != 0) {
                goto loop_6;
            }
            var_r9 -= 1;
        } while (var_r9 != -1);
    }
    arg0->unk0x4 = temp_r3_2;
    if (var_r26 != 0) {
        fn_8000F320(*(void **)&lbl_802FFE98);
    }
    var_r10 = 0;
    var_base = arg0->unk0x4;
    if (var_r10 < arg0->unk0x14) {
        do {
            var_r10_2 = var_r10 + 1;
            var_r11 = (Chunk18 *)((var_r10 << 6) + (u8 *)var_base);
            var_r9_2 = (Chunk18 *)((var_r10 << 6) + (u8 *)arg1->unk0x4);
            var_ctr = 0x30;
        loop_12:
            var_ctr -= 0x18;
            var_r11->unk0x0 = var_r9_2->unk0x0;
            var_r11->unk0x4 = var_r9_2->unk0x4;
            var_r11->unk0x8 = var_r9_2->unk0x8;
            var_r11->unk0xC = var_r9_2->unk0xC;
            var_r11->unk0x10 = var_r9_2->unk0x10;
            var_r11->unk0x14 = var_r9_2->unk0x14;
            var_r9_2 += 1;
            var_r11 += 1;
            if (var_ctr != 0) {
                goto loop_12;
            }
            var_r11->unk0x0 = var_r9_2->unk0x0;
            var_r11->unk0x4 = var_r9_2->unk0x4;
            var_r11->unk0x8 = var_r9_2->unk0x8;
            var_r11->unk0xC = var_r9_2->unk0xC;
            var_r10 = var_r10_2;
        } while (var_r10 < arg0->unk0x14);
    }
    fn_800368FC(arg0, arg1->unk0x8);
    fn_80036864(arg0, arg1->unk0x8);
    var_r7 = 0;
    if (var_r7 < arg0->unk0x14) {
        var_r8 = 0;
        do {
            var_r7 += 1;
            *(s32 *)((s32 *)(var_r8 + (u8 *)arg0->unk0x18) + 2) =
                *(s32 *)((s32 *)(var_r8 + (u8 *)arg1->unk0x18) + 2);
            *((s32 *)(var_r8 + (u8 *)arg0->unk0x18) + 0) =
                *((s32 *)(var_r8 + (u8 *)arg1->unk0x18) + 0);
            var_dp = (__ps_t *)(var_r8 + (u8 *)arg0->unk0x18);
            var_dp += 2;
            var_sp = (__ps_t *)(var_r8 + (u8 *)arg1->unk0x18);
            var_sp += 2;
            var_dp[0] = var_sp[0];
            var_r8 += 0x20;
            var_dp[1] = var_sp[1];
        } while (var_r7 < arg0->unk0x14);
    }
    arg0->unk0x8 = (s32)arg1->unk0x8;
    arg0->unk0xC = arg1->unk0xC;
    arg0->unk0x0 = arg1->unk0x0;
    arg0->unk0x10 = arg1->unk0x10;
    return arg0;
}