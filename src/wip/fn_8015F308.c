// WIP DRAFT (non-matching) — hand-fixed from m2c: hidden arg0 + lbl symbol forms + real protos
// family=m2c range=0x8015F308-0x8015F510 size=520B
// ScriptBindTrickToKeyCombo: binds a trick to a key combo — reads the QB property
// tree (arg0) for trick/key names (GetChecksum_4/80128294 string getters), looks up
// the current profile object (fn_801A5DAC/fn_80174A58 via QB_PROFILE), then either
// binds via fn_801A54DC (full combo struct) or updates the single-key binding on the
// profile object (fn_801A568C rehash + fn_801270B4/27684/277E4 setters).
// PARKED 93.8% (2026-09-02 round, up from 89.2/89.9): doc-15 twin-call-site artifact.
// BREAKTHROUGH this round: the fn_801A568C "rehash obj,0xD544AA2D" call is NOT shared
// by both else-arms — only arm-1 (27684 path) consumes its result; arm-2 (277E4 path)
// uses the PRE-call obj. Moving the call INSIDE arm-1 (bK shape) fixed 4 of the 8
// residual insns: want [lis r4][mr r3,r30][ori][bl][mr r30,r3][cmpwi][beq] now matches
// through 01A8; the beq target (arm-2) now emits mr r3,r30 bare-r3-chained 270B4 too.
// Residual (8 insns, ALL in the else-arm region): (1) the arm-1 call group emits
// [bl A568C][lwz r4,0x18][mr r30,r3] — want has [mr r30,r3] BETWEEN bl and the hoisted
// arg load lwz r4,0x18(r1) (call-arg staging hoists the NEXT call's arg load above the
// home copy; "+r" emission barriers after the call (bP 84.4) move the copy but break
// the group order the other way); (2) the beq target (arm-2, 277E4 path) is placed
// AFTER the shared ret-1 block by ngccc, want keeps it BEFORE ret (block-tail order;
// goto-done forms bAK/bAM keep 93.8, don't fix it); (3) the A568C arg2 0xD544AA2D
// lis+ori is fine, non-issue.
// Tried this round: A..AR shapes — shared-call+goto (89.8), call-in-arm1 (93.8),
// call-in-arm1+barrier variants (79.4-84.4), else-if chain (82.8), unpin native r30
// (78.0, regs rotate), old-style unprototyped A568C proto (82.9/89.8), ternary sp8[1]
// (89.8), predicated loads, inverted arm order (88.5), 6 schedule-flag configs on the
// two best shapes (all ≤93.8; -fno-schedule-insns regresses to 86.2). The residual
// is the doc-15 call-arg-staging hoist coin (per-site compiler state), not
// source-reachable with current levers. Best body (bAP) kept below.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
extern char lbl_802A8260[];
extern char lbl_802A826C[];
extern char lbl_802A8274[];
extern char lbl_802A8284[];
extern char lbl_802A828C[];
s32 GetChecksum_4(CStruct *, void *, void *, s32);
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 fn_80128978(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_801A5DAC(s32, s32);
s32 fn_80174A58(void *, CStruct *);
s32 fn_80128A90(CStruct *, void *);
void fn_801A7EB4(Unk_C7387A53 *);
s32 ContainsFlag(CStruct *, s32);
void fn_801A54DC(void *, s32, CStruct *, s32);
s32 fn_801A568C(s32, s32);
void fn_801270B4(CStruct *, s32);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptBindTrickToKeyCombo(CStruct *arg0) {
    s32 sp8[4];
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 var_r29;
    register s32 temp_r30 __asm__("r30");
    s32 var_r28;
    s32 temp_r3;

    GetChecksum_4(arg0, (s32)lbl_802A8260, &sp18, 1);
    temp_r30 = 0;
    sp1C = temp_r30;
    GetChecksum_4(arg0, (s32)lbl_802A826C, &sp1C, 0);
    var_r28 = 0;
    sp20 = temp_r30;
    if (fn_80128294(arg0, (s32)lbl_802A826C, &sp20, 0) != 0) {
        var_r28 = 1;
    }
    var_r29 = 1;
    sp24 = var_r29;
    fn_80128294(arg0, (s32)lbl_802A8274, &sp24, 0);
    if (sp24 == 0) {
        var_r29 = 0;
    }
    if (fn_80128978(arg0, QB_PROFILE) != 0) {
        GetChecksum_2(arg0, QB_PROFILE, &sp28, 1);
        temp_r30 = fn_801A5DAC(lbl_80305EFC, sp28);
    } else {
        temp_r30 = fn_80174A58(lbl_80305EAC, 0);
    }
    if (fn_80128A90(arg0, (s32)lbl_802A8284) != 0) {
        if (fn_80128294(arg0, (s32)lbl_802A828C, &sp2C, 0) == 0) {
            return false;
        }
        fn_801A7EB4(sp8);
        sp8[2] = sp18;
        if (var_r28 != 0) {
            sp8[1] = sp20;
        } else {
            sp8[1] = sp1C;
        }
        temp_r3 = ContainsFlag(arg0, QB_CAT);
        if (temp_r3 != 0) {
            sp8[3] = 1;
        } else {
            sp8[3] = temp_r3;
        }
        fn_801A54DC(temp_r30, sp2C, sp8, var_r29);
    } else {
        if (var_r28 != 0) {
            fn_801270B4((s32)(temp_r30 = fn_801A568C(temp_r30, QB_TRICK_MAPPING)), sp18);
            AddInteger(temp_r30, sp18, sp20);
        } else {
            fn_801270B4(temp_r30, sp18);
            AddChecksum(temp_r30, sp18, sp1C);
        }
    }
    return true;
}
