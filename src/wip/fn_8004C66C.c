// WIP DRAFT — 2026-10-10: 61.7% -> 84.0% (68/81), size-exact 324B, -Os.
// Levers (all register-asm pins, each measured): walker var_r30->r30 (+12.4),
// bestidx var_r24->r24 (+2.4), temp_r10->r10 (+1.3), temp_r11->r11 (+3.7),
// product `prod = var_r24*0x18` pinned ->r9 (+2.5), GetElement arg `&out` ->
// `&out.f0` (+2.4, also fixed the tail mulli). Neutral/reverted: base-var for
// arg0 + decl-order swap (cse folds, byte-identical), commutative add-operand
// swap (canonicalized back), sharing `&out.f0` at BOTH call sites (no hoist).
// REMAINING 13 words = two -Os scheduler coins + one canonicalization:
//  (a) GetElement_2 setup order: want `mr r4,r29 / addi r3,r1,8`, got reversed;
//  (b) want hoists `addi r4,r1,8` (&out for RemoveRefLink) ABOVE `cmpwi cr4`
//      (got computes it after `mr r3,r31`); branch targets downstream differ;
//  (c) `add r9,r9,r29` vs `add r9,r29,r9` (commutative, canonicalized).
// family=m2c range=0x8004C66C-0x8004C7B0 size=324B
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 39.0244% -> 61.7284% per-object flags: -fno-gcse -fno-schedule-insns -> -Os
//
// SCORE (2026-09-26 re-score): 5.9% DIFF flagless / 39.0% DIFF with the header
// flags below (still under test_wip_drafts' 50% NEAR threshold, so it stays
// DIFF tier either way). Was 2.5% DIFF before this round.
//   tools/venv/bin/python tools/score_body.py 0x8004C66C src/wip/fn_8004C66C.c
//   -> "DIFF 39.0%"   (honours the // FLAG: line below)
//   tools/venv/bin/python tools/score_body.py 0x8004C66C src/wip/fn_8004C66C.c "-O2 -G0"
//   -> "DIFF 5.9%"    (flags forced off)
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8004C66C
// Compiles to 82 insns (328B) vs want 81 (324B) => +4B, promote would refuse.
// Flag ladder measured (tools/flag_sweep.py + a manual matrix on top of
// -fno-gcse): -fno-schedule-insns 39.0% (best); the scheduler pairs and
// -fno-sched-spec/-fno-sched-interblock/-fno-expensive-optimizations/
// -fno-cse-follow-jumps/-fno-thread-jumps/-fno-strength-reduce/
// -fno-branch-count-reg all 36.6%; -fno-rerun-cse-after-loop 4.9% (worse);
// -fno-tree-{pre,ter}/-fno-sched-round/-fno-reorder-blocks/-fno-peephole2/
// -fno-ipa-cp/-fno-crossjumping are NOT in ProDG cc1 (compile FAIL).
//
// WHAT IT IS — a 10-entry cull pass over a 0x18-stride table at self+0x5D8
// (self+0x5C4 = live count, self+0x5DC = parallel 0x18-stride array of live
// pointers). For each non-empty slot: fetch the element, and if it is non-NULL
// unlink it (ref-link removed, out-param cleared) and keep the slot; track the
// highest-priority survivor (u32 at slot+0) and its index. If the fetch came
// back NULL, store 0 back and decrement the live count. Afterwards, if any
// entry survived, build a `UnHide` checksum struct, vcall it on the best
// slot's owner object, then delete the struct.
//
// CALLEE SIGNATURES — all six are already matched in src/, so these are ground
// truth (recipe §6y-132 / per-caller arity, recipe 87):
//   GetElement_2        = fn_8004B03C  void* (out12*, self, idx, flag)   4 args
//   CObject_RemoveRefLink = fn_8009DFC0 void  (CStruct*, CStruct*)        2 args, void
//   CStruct_new         = fn_80019D08  void  (s32)   <- returns VOID at its
//                                     promoted src, but its callers here chain
//                                     r3 into CStruct_ctor, so it is declared
//                                     s32 at THIS site (recipe 87/119)
//   CStruct_ctor        = fn_80126EAC  s32   (s32)    -> chained off the above
//   AddChecksum         = fn_801277E4  void  (CStruct*, s32 val, s32 hash) 3 args
//   CStruct_delete      = fn_8012701C  void  (CStruct*, s32 flag)
// Return-type flips on GetElement_2 / CObject_RemoveRefLink / AddChecksum
// (M8.31) were all measured: ZERO codegen effect on the two residual arg-setup
// order diffs, so the draft keeps the real signatures above.
//
// KEY FIX THIS ROUND — the out-param is a 12-BYTE STRUCT, not a bare s32.
// fn_8004B03C's promoted body declares `struct { void *f0; s32 f4; s32 f8; }`
// and CObject_RemoveRefLink reads arg1->unk0x4/unk0x8/unk0x0 — i.e. BOTH callees
// want a 12-byte out block. Declaring it that way reproduces the frame exactly:
// want stwu -0x40 / stmw r23,0x1c / stw r12,0x18 ; was stwu -0x38 / stmw 0x14
// with no CR slot. This single change is what makes the CR machinery below
// land in the right slots.
//
// PARK REASON (unchanged, now precisely characterised) — want keeps ONE cr4
// compare live across `bl CObject_RemoveRefLink` and consumes it TWICE:
//     cmpwi cr4,r31,0 ; beq cr4,store | bl ; stw r23,8(r1) ; beq cr4,store
// plus mfcr r12/stw r12,0x18(r1) in the prologue and lwz r12/mtcrf 8 in the
// epilogue. Both branches are the SAME 16-bit CR field with no second
// compare, so the value must be allocated to the call-preserved cr4.
// Measured with `ngccc -dl` (RTL dump): after jump optimisation BOTH compares
// are still in the RTL (two distinct CC pseudos, insn 63 and insn 80); a LATER
// jump pass deletes the second branch. Every straight-line C spelling of the
// redundant re-test is deleted that way: goto-store x2, if/else, &&-comma,
// ||-form, do/while(0), switch, two-variable copy (t2=t1 after the branch),
// `!t`, `(u32)t`, `t & 0xFFFFFFFF`, `t + 0 == 0`, two distinct store labels
// (crossjumping re-unifies them before threading), local-register pin, `+r`
// barrier, volatile, and label-separated forms. Flags -fno-thread-jumps,
// -fno-gcse, -fno-cse-follow-jumps, -fno-schedule-insns{,2}, -fno-sched-spec,
// -O0/-O1/-O3 are all inert on the straight-line form. A memory-backed re-test
// (`*(volatile s32*)&out == 0`) DOES survive, but costs a reload+compare
// (3 words) and lands in a volatile CR field, so no CR save is emitted.
// => The paired `beq cr4` is NOT reachable from straight-line C. This is a
// new doc-28 sub-signature ("same CR condition used twice, once before and
// once after a call") distinct from the single-use CR-hoist members.
//
// WHAT DOES REACH IT: a bottom-tested (rotated) loop makes ngccc keep the
// cr4 condition across the call, and `-fno-gcse` then keeps the whole register
// allocation identical to want (r23..r31 save, arg0 in r29, max/idx in r25/r24).
// Hence the `do { ... } while (temp_r31 == 0);` in the body below: the
// do-while is a single-pass loop (the entry guard already proved t != 0), so it
// is SEMANTICALLY IDENTICAL to the straight-line form, and it is what buys the
// cr4 + mfcr/mtcrf + 0x40 frame. First confirmed on the matched twin
// src/fn_80135424.c (a loop-head LICM-hoisted `if (g != NULL)` test whose cr4
// is consumed after a call) — the twin scan (cmpwi cr4 -> bl -> beq cr4 with no
// intervening compare, over all 406 mfcr functions in .text) lists
// fn_80135424, fn_8005C9A8, fn_800DFDFC, ScriptCleanup,
// ScriptToggleAlwaysSpecial and fn_801875CC as the already-matched instances
// of this idiom; this function is the unmatched one.
//
// REMAINING DIFFS (39.0% with the header flags; 82 vs 81 insns). Only four
// things are left, and all four are downstream of the same CR-reuse wall:
//  1. `mcrf cr7,cr4` where want spends one word on a second `beq cr4`: the
//     loop-latch test lands in a different basic block, so the condition
//     propagation inserts a CR copy; a straight-line second use has no copy
//     but is jump-threaded away (see PARK REASON).
//  2. the same latch test is `beq cr7` (exits the loop) where want has the
//     unconditional `b latch`; that is also the +1 word (our 82 vs 81).
//  3. Two doc-15 arg-setup order diffs, both measured invariant to callee
//     return type: want `mr r4,r29` before `addi r3,r1,8` at the GetElement_2
//     call, and want's `addi r4,r1,8` hoisted above `cmpwi cr4` at the
//     RemoveRefLink call.
//  4. Consequently the store block and everything after it sit one word late.
// Note `stw r23,8(r1)` (out.f0 = 0) and `lwz r0,0(r30)` now land in want's
// exact slots 0x6E8 / 0x6F0; the frame (0x40 / stmw 0x1c / stw r12 0x18) and
// the whole r23..r31 save + r29/r25/r24 role map are byte-exact.
//
// REJECTED SHAPE (recorded so it is not re-derived, NOT a valid candidate):
// dropping the `goto latch` so the max-tracking falls through into the store
// block scores 87.7% with -fno-gcse at exactly 81 insns, but it is
// SEMANTICALLY WRONG — the non-NULL path would also store 0 and decrement the
// live count, which is the opposite of what want's `b latch` does. Do not
// promote or keep that form.
//
// family=m2c
// FLAG: -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetElement_2(void *arg0, void *arg1, s32 val, s32 flag);
void CObject_RemoveRefLink(void *arg0, void *arg1);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 AddChecksum(s32 arg0, s32 arg1, s32 hash);
void CStruct_delete(s32 arg0, s32 arg1);

void fn_8004C66C(void *arg0) {
    struct { void *f0; s32 f4; s32 f8; } out;
    s32 temp_r31;
    s32 var_r23;
    register s32 var_r24 __asm__("r24");
    u32 var_r25;
    s32 var_r27;
    s32 var_r28;
    register s32 var_r30 __asm__("r30");
    u32 temp_r0;
    char *temp_r26;
    register void *temp_r10 __asm__("r10");
    register void *temp_r11 __asm__("r11");
    register s32 prod __asm__("r9");

    var_r25 = 0U;
    var_r24 = -1;
    if (((Unk_9E4B1D7B *)arg0)->unk0x5C4 > 0) {
        var_r27 = 0;
        temp_r26 = (char *)arg0 + 0x5DC;
        var_r23 = 0;
        var_r30 = (s32)arg0 + 0x5D8;
        var_r28 = 0;
        do {
            if (*(s32 *)((char *)(var_r28 + (s32)temp_r26)) != 0) {
                GetElement_2(&out.f0, arg0, *(s32 *)(var_r30 - 4), 0);
                temp_r31 = (s32)out.f0;
                if (temp_r31 == 0) {
                    goto store;
                }
                CObject_RemoveRefLink((void *)temp_r31, (void *)&out.f0);
                out.f0 = (void *)var_r23;
                do {
                    temp_r0 = *(u32 *)var_r30;
                    if (temp_r0 > var_r25) {
                        var_r25 = temp_r0;
                        var_r24 = var_r27;
                    }
                } while (temp_r31 == 0);
                goto latch;
store:
                *(s32 *)((char *)(var_r28 + (s32)temp_r26)) = temp_r31;
                ((Unk_9E4B1D7B *)arg0)->unk0x5C4 -= 1;
latch: ;
            }
            var_r27 += 1;
            var_r30 += 0x18;
            var_r28 += 0x18;
        } while (var_r27 <= 9);
        if (((Unk_9E4B1D7B *)arg0)->unk0x5C4 > 0) {
            temp_r31 = CStruct_ctor(CStruct_new(8));
            AddChecksum(temp_r31, 0, QB_UNHIDE);
            prod = var_r24 * 0x18;
            temp_r10 = *(void **)((char *)((char *)arg0 + prod) + 0x5C8);
            temp_r11 = *(void **)((char *)temp_r10 + 8);
            ((s32 (*)(void *, void *))*(s32 *)((char *)temp_r11 + 0x14))((char *)temp_r10 + *(s16 *)((char *)temp_r11 + 0x10), (void *)temp_r31);
            if (temp_r31 != 0) {
                CStruct_delete(temp_r31, 3);
            }
        }
    }
}
