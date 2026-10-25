// PARKED 2026-10-18: NEAR 95.9%, exact length (292B = symbol size).
// Full hand rewrite of the m2c husk (64.0% -> 67.6% -> 95.9%). The m2c draft
// had four semantic bugs: temp_r29 never assigned (0x80305F9C load missing),
// fn_801745B4 called with a phantom 0x80300000 constant read off a `lis`
// (real call is (lbl_80305EAC, arg1)), fn_8021B574 over-aritied, and a 4-arg
// fn_801EF978 phantom (real: 2 args). The old r9 register pin on the switch
// result fought the r9 global base and is gone; the switch result lives in r3.
//
// Shape findings that hold the score: the sw!=0 arm returns 1 inline between
// the two unk0x54 tests (`if (sw!=0){if(unk54>0)goto ret0;return 1;}` then a
// second `if(unk54>0)goto ret0;`); the tail dispatch is a switch with case 1
// written BEFORE case 0 (source order controls which body lands inline: the
// second-written case falls through after `cmpwi;beq-out;cmpwi;bne-end`). The
// `case 2: break;` in the first switch is load-bearing but semantic-free: it
// keeps the descending range-checked compare chain instead of an if-else peel.
//
// RESIDUAL (3 words, prologue only): want emits `lwz r3; lwz r29; mr r28,r4`
// before the first call; every source shape that passes `arg1` to the three
// calls emits the `mr r28,r4` save first. The parameter's save is emitted by
// expand_function_start, so it has no C source position at all; sched2 is
// free to hoist it above the global loads.
//
// This body instead names a separate local `a1` that carries arg1 across the
// calls: `a1 = arg1;` is an ordinary statement whose RTL position is after
// the temp_r29 load, so the save move is born in the middle of the preheader
// instead of the prologue. The first call still passes the parameter itself
// (r4 already holds it, no argument copy); only the two tail calls take a1
// and therefore copy it into r4, which is what retail does as well.
// WIP DRAFT (non-matching) -- hand rewrite; original bytes in DOL, not
// reproduced here per repo policy.
// family=m2c range=0x8018CAF4-0x8018CC18 size=292B
// INERT: not registered in splits.txt/configure.py -- never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;

s32 fn_801745B4(s32, s32);
s32 GetChecksum_3(s32, s32);
s32 fn_8021B574(s32);
s32 fn_801EFA84(s32);
s32 fn_801EFA9C(s32);
void fn_801EF978(s32, s32);
s32 fn_801EFA44(s32, s32);

s32 fn_8018CAF4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r30;
    s32 sw;
    s32 a1;

    temp_r29 = lbl_80305F9C;
    a1 = arg1;
    temp_r3 = fn_801745B4(lbl_80305EAC, arg1);
    if (temp_r3 == 0) {
        return 1;
    }
    temp_r30 = GetChecksum_3(temp_r3, QB_SKATERENDRUN);
    if (fn_8021B574(temp_r29) == 0) {
        return 1;
    }
    if (!(arg0->unk0x70 & 0x80000)) {
        sw = 0;
        switch (arg0->unk0x28) {
        case 1:
            sw = fn_801EFA84(temp_r30);
            break;
        case 0:
            sw = fn_801EFA9C(temp_r30);
            break;
        case 2:
            break;
        }
        if (sw != 0) {
            if ((s32)arg0->unk0x54 > 0) {
                goto ret0;
            }
            return 1;
        }
        if ((s32)arg0->unk0x54 > 0) {
            goto ret0;
        }
        switch (arg0->unk0x28) {
        case 1:
            arg0->unk0x70 = (s32)(arg0->unk0x70 | QB_UNKNOWN_0x01000000);
            fn_801EF978(temp_r30, a1);
            break;
        case 0:
            arg0->unk0x70 = (s32)(arg0->unk0x70 | QB_UNKNOWN_0x01000000);
            fn_801EFA44(temp_r30, a1);
            break;
        }
    }
ret0:
    return 0;
}
