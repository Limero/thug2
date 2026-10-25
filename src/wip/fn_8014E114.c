// WIP DRAFT (non-matching) — ScriptControllerPressed: get the goal "pressed" id
// (GetChecksum_2), then test that one entry (GetInteger path) or all three
// entries (linear walk) through fn_8014DDFC.
// family=m2c range=0x8014E114-0x8014E1DC size=200B
// MATCHED-BEST 80.0% (40/50), object 200B == want 200B — see PARKED note above
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8014DDFC(Unk_31DE137E *, void *);
extern s32 lbl_80305EE4;
// PARKED 80% (was 77.1% at 192B). The length is now EXACT and every
// instruction up to 0x7c matches; the residual is a single ngccc BLOCK-ORDER
// decision, not a codegen wall:
//
// The original lays out a branch to ZERO at 0x7c, the loop preheader at 0x80,
// the loop body at 0x88, a branch-equal to the latch at 0x9c, the return-1
// pair (load 1 into r3 plus branch) at 0xa0, and the latch (word-compare with
// less-or-equal back to 0x88) at 0xa8. This draft lays out the branch to ZERO
// at 0x7c, the return-1 pair at 0x80, the loop preheader at 0x88, the loop
// body at 0x90, a branch-not-equal back to 0x80 at 0xa4, and the latch
// (word-compare with less-or-equal back to 0x90) at 0xa8.
//
// i.e. ngccc TAIL-MERGES the loop's `return 1` with the direct path's
// `return 1` and hoists the merged [li r3,1; b RET1] pair in front of the
// loop; want keeps the loop's copy inline (after the latch branch) and
// leaves the direct path's copy at 0x74. Same 10 words, different order;
// the two `li r3,1` copies are NOT redundant in want — both exist.
//
// Everything tried and rejected (all land on the SAME two objects, sha1
// d3a748937c7dcf773c6a163f1a52b4e2657ae5e5 = 200B, or worse):
//  - direct-path shape: `var_r3=1; if(!t) goto ZERO;` / `return (t!=0);` /
//    `t?1:0` / `res=1; if(t==0) res=0;` / `goto one` / separate one_a/one_b
//    labels. Only the plain `if (f() != 0) return 1; return 0;` reaches 200B.
//  - loop shape: do-while, while, while(1)+break, for(;;), goto latch,
//    continue-in-do-while, continue-in-while(1), countdown counter,
//    `p != end` bound, `found` flag var, `&&`-chained condition,
//    break + `if (t != 0)`. Only do-while/while/while(1) reach 200B; the
//    rest add or drop the latch copy and land at 196/204/208/212/216B.
//  - flags: -fno-thread-jumps/-gcse/-expensive-optimizations/-caller-saves/
//    -branch-count-reg/-cse-follow-jumps/-sched-interblock/-strength-reduce,
//    -O1, -O3 — all inert (identical object). -fno-crossjumping,
//    -fno-tail-merge, -freorder-blocks, -fno-if-conversion, -fno-ivopts,
//    -fno-tree-loop-optimize, -fno-hoist-adjacent-loads do NOT EXIST in this
//    cc1, so the tail-merge/reorder passes cannot be switched off directly.
// Wall: needs a way to keep a `return 1` INSIDE a loop body un-merged with
// the identical `return 1` on another path. Every source shape that makes
// the two returns syntactically distinct (two labels, a variable, a flag)
// also changes the instruction count, so the merge is not the only
// difference any more.
// RE-TRIED 2026-10-16: loop as `== 0 -> goto latch` + fall-through
// `return 1` (matching want's beq/li/b order verbatim) — GCC normalizes it
// to the identical merged object (200B, same sha1 family, still 80%). The
// merge is at RTL on identical tails; no source polarity preserves it.
bool ScriptControllerPressed(CStruct *arg0) {
    char *temp_r9;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    s32 temp_r31;
    s32 t;

    temp_r31 = lbl_80305EE4;
    sp8 = 0;
    if (GetChecksum_2(arg0, 0, &sp8, 0) == 0) {
        goto block_8;
    }
    if (GetInteger(arg0, 0, &spC, 0) != 0) {
        temp_r9 = (char *)temp_r31 + 0x28;
        if (fn_8014DDFC((void *)(*(s32 *)(temp_r9 + (spC * 4))), (void *)sp8) != 0) {
            return true;
        }
        return false;
    } else {
        var_r31 = (s32)((char *)temp_r31 + 0x28);
        do {
            t = *(s32 *)var_r31;
            var_r31 += 4;
            if (fn_8014DDFC((void *)t, (void *)sp8) != 0) {
                return true;
            }
        } while (var_r31 <= (s32)((char *)temp_r31 + 0x34));
block_8:
        ;
    }
    return false;
}