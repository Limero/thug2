// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BC14-0x8018BC9C (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 Game_GetGoalManager(void *arg0);
s32 GoalManager_GetGoal(s32, s32, s32);
// 2026-10-15: 67.6% -> 88.2% (30/34, size-exact 136B). TWO NEW LEVERS:
// (1) entry save sunk below the load with a LOAD-DEPENDENT zero-code barrier:
//     `__asm__("" : "+r"(temp_r29) : "r"(var_r31))` after the two entry
//     statements. The input dependency pins the mr after the lwz; a bare
//     "+r" barrier is inert (GCC parks the empty asm immediately after the
//     bl, so the mr stays first). Gives want's [bl][lwz r31][mr r29] exactly.
// (2) anti-coalescing call-arg copy: separate `goalarg` assigned in the check
//     block + zero-code `__asm__("" : "+r"(goalarg))`, call uses goalarg.
//     The barrier blocks cc1's coalesce of test-value/call-arg (which defeated
//     all three 6g4 rename variants) while leaving the pseudo schedulable, so
//     the mr still hoists into the check block. +5 words.
// 2026-10-15 (later): 88.2% -> 94.1% (32/34). Test the COPY, call the LOAD:
//     `goalarg = temp_r0; barrier; if (goalarg != 0) goto body;` with the call
//     on temp_r0. The mr SURVIVES here (copyprop does not fold a barrier'd
//     test-copy into a call-constrained load web the way it folds the reverse
//     arrangement) and the branch becomes want's bne. Asymmetry is structural
//     (which var the load defines), not nominal.
// REVERTED (measured): hard `register ... __asm__("r0")` pin on temp_r0 +
//     the goalarg barrier -> 74.3%: the mr appears but sinks below the bne,
//     and r0's mtlr duty explodes the epilogue. The pin fights reload, not
//     just coloring.
// REVERTED (measured): goalarg assigned in BODY before the call (hoping sched
//     hoists the mr into check) -> 50.0%: no hoist; load IS r0 but mr sits in
//     body and the whole block slides. Also reverted: full role swap
//     (load->goalarg, temp_r0=copy, test temp_r0, call goalarg) -> 73.5% with
//     branch breakup: the load always joins the r4 call-arg web, so the load
//     feeds r4 in every arrangement tried.
// RESIDUAL (2 words, check block only): want [lwz r0,0(r31)][mr r4,r0]; got
//     [lwz r4,0(r31)][mr r0,r4]; cmpwi-r0 + bne match. Roles are right
//     (test=r0, arg=r4) but the load feeds the arg web instead of the test
//     web. Needs a lever that colors the LOAD to scratch while its copy goes
//     to r4 (barriers order but never color; hard pins break sched2 motion).
// PARKED 70%: two doc-15-class expand_call/sched emission artifacts resist
// every lever tried (~15 shapes × 7 flag combos × decl/type permutations):
// (1) entry window — want [bl getter][lwz r31,0x2c(r30)][mr r29,r3] (result-
//     save sunk below the independent load); got always emits [bl][mr r29][lwz]
//     (call-first src) or [lwz][bl][mr] (load-first src). Sibling fn_8018BD34
//     reproduces the want order only because its list-load COALESCES onto the
//     dying arg0 home reg (single-web); here arg0 stays live (+0x1C reads in
//     body) so the entry-load is a fresh web and ngccc fires the save eagerly.
// (2) id handling — want [lwz r0,0(r31)][mr r4,r0][cmpwi r0][bne] (scratch copy
//     + speculative hoist of the call's arg-move into the check block); got
//     coalesces the call arg into r4 ([lwz r4][cmpwi r4]) — no mr ever exists.
//     Hard-pinning the id temp to r0 creates the mr but sched2 refuses to move
//     hard-reg insns across the bne (lands at body-top instead, 44%); a
//     volatile "r4" clobber blocks coalescing but also blocks the hoist.
// Retry hints: needs an emission-order lever for post-bl result-saves, or an
// anti-coalescing mechanism that leaves the pseudo schedulable (soft-reg pin).
// 6g4 REJECTED here (2024-10 round): the §6gd "give the call argument its own
// name so the compare and the call use different pseudos" lever was tried as
// three variants — (A) goalarg assigned inside the check block, (B) assigned
// before the test, (C) two independent field reads. ALL THREE are byte-
// identical to base (vrun 23/33 = 69.70%, 132B, same 10 misses at 0x1c/0x20/0x64-
// 0x80): cc1's coalesce pass has already merged the two pseudos before
// sched2 ever sees them, so renaming cannot split them. Consistent with the
// hard-r0-pin note above (the mr appears, but the hoist does not). The only
// remaining lever is a soft (non-fixed) reg pin that survives coalescing.
void fn_8018BC14(CScript *arg0, s32 arg1) {
    s32 temp_r29;
    CStruct *var_r31;
    Unk_31DE137E *temp_r3;
    s32 temp_r0;
    s32 goalarg;

    temp_r29 = Game_GetGoalManager(arg0);
    var_r31 = *((void * *)&arg0->unk0x2C);
    __asm__("" : "+r"(temp_r29) : "r"(var_r31));
    goto check;
body:
    temp_r3 = (void *)GoalManager_GetGoal(temp_r29, goalarg, 1);
    if (temp_r3 != NULL) {
        temp_r3->unk0x1C =
            temp_r3->unk0x1C | arg0->unk0x1C;
        fn_8018BC14((CScript *)temp_r3, arg1 + 1);
    }
    var_r31 = *((void * *)&var_r31->unk0x4);
check:
    if (var_r31 != NULL) {
        temp_r0 = var_r31->unk0x0;
        goalarg = temp_r0;
        __asm__("" : "+r"(goalarg));
        if (temp_r0 != 0) {
            goto body;
        }
    }
}
