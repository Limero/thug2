// PARKED 2026-10-05: parked NEAR 75.0% (was 73.9%), object 364B vs
// want 368B — ONE word short.
// family=m2c range=0x80115E3C-0x80115FAC size=368B
// FLAG: -fno-rerun-cse-after-loop
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THE FUNCTION DOES: a QB script operator ("for each element in
// array").  sp8 = the `QB_DO` checksum, spC = the `QB_ARRAY` script array,
// sp10 = the `QB_PARAMS` structure.  If QB_PARAMS exists it builds a
// scratch object (`fn_80019d08(8)` + `fn_80126eac()`), and for every array
// element: reset the object, fetch the element, push it, push the params
// struct, run the element script, then free the object.  With no QB_PARAMS
// it just runs each element with no scratch object.  Always returns 1.
//
// RESULT (73.9% -> 75.0%).  The else-branch loop is a
// **nested call**: `fn_80131008(sp8, fn_80129528(spC, i++), arg1->unk0xBC,
// 0, 0)`, not a temporary variable.  That single change reproduces want's
// r30 pair — see the note under "RESIDUAL" (a): with a separate `e`
// temporary GCC sinks the sp8 reload to `lwz r3, 8(r1)` *after* the inner
// call; as the nested arg1 of a call whose arg0 it also is, sp8 must
// survive the inner call, so it goes to the callee-saved r30 and comes
// back as `mr r3, r30`.  Two statement forms were tried and are worse:
// `s32 e = f(spC, i); ... g(sp8, e, ...)` (no r30, 75.6% index-aligned) and
// the same with the whole thing hoisted into a function-scope `v` (47%).
//
// The first (QB_PARAMS) loop, the prologue, the three script getters and
// the epilogue are all word-exact.  `i++` is a separate statement placed
// *before* the trailing `fn_80131008` in that loop (a `for`-header
// increment sinks to the wrong spot).
//
// RESIDUAL (two independent defects, both post-RA artifacts):
//  (a) else-branch loop is ONE word short: want re-loads the array pointer
//      into r3 inside the body (`lwz r3, 0xc(r1)`) *and* keeps it in r9
//      across the loop, i.e. GCC 2.95's loop register allocator put the
//      loop-invariant `spC` pseudo in r9 and reload1 re-materialised r3
//      for the inner call's arg0.  I cannot make my build pick r9: with
//      r3 otherwise unused at the top of that loop body, the loop
//      allocator puts the pseudo straight into r3 and the reload
//      disappears.  What was ruled out: `u32 i`; the bound hoisted into a
//      named local (n) (that makes cc1 if-convert and peel the first
//      iteration instead — worse); `for` header increment; inverting the
//      if/else; -fno-thread-jumps / -fno-crossjumping / -fno-cse-* /
//      -fno-gcse / -fno-iv* (several are not accepted by ngccc);
//      -fschedule-insns; `-fno-schedule-insns2` (30%: the whole tail is
//      rescheduled, so sched2 is load-bearing here).  `volatile s32 spC`
//      does force the reload, but GCC 2.95 then miscompiles it (it loads
//      sp8 into r3 for the inner call), so it is not the original's
//      spelling.  Also wants `addi r29,r29,1` before the inner `bl` while
//      sched2 puts it after in every spelling that has the r30 pair.
//  (b) inside the first loop the `if (sp10 != 0)` guard loads into r4
//      (`lwz r4, 0x10(r1); cmpwi r4, 0`) where the identical guard at
//      function entry uses r0.  A named copy of sp10 does not change it.
//
// Callee facts confirmed off want: fn_8012705C = 1 arg (obj dtor),
// fn_80126F88 is used BOTH as `f(obj)` (sp10 path) and `f(obj, v)` (element
// path) so it needs two prototypes (`fn_80126f88` / `fn_80126f88_2`; REL24
// is relocation-masked so the name is free), fn_80131008 takes 5 args and
// is called with `li r6,0 ; li r7,0`, fn_80126EAC is 0-arg and chained off
// `li r3,8 ; bl fn_80019D08`, and `arg1->unk0xBC` is the script pointer.
#include "types.h"
#include "qb_constants.h"
typedef struct CStruct CStruct;
typedef struct { char pad0x00[0x18]; s32 unk0x18; char pad0x1C[0xA0]; s32 unk0xBC; } Sc;
typedef struct { char pad0x00[4]; s32 count; } Arr;

s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetArray(s32 arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetStructure_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 fn_80019d08(s32 arg0);
s32 fn_80126eac();
void fn_8012705c(s32 arg0);
s32 fn_80129528(s32 arg0, s32 arg1);
void fn_80126f88(s32 arg0);
void fn_80126f88_2(s32 arg0, s32 arg1);
void fn_80131008(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_8012701c(s32 arg0, s32 arg1);

bool ScriptForEachIn(CStruct *arg0, Sc *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 obj;
    s32 i;
    s32 v;

    sp8 = 0;
    GetChecksum_2(arg0, QB_DO, &sp8, 0);
    spC = 0;
    GetArray(arg0, 0, &spC, 0);
    sp10 = 0;
    GetStructure_2(arg0, QB_PARAMS, &sp10, 0);
    if (sp10 != 0) {
        fn_80019d08(8);
        obj = fn_80126eac();
        i = 0;
        while (i < (u32)((Arr *)spC)->count) {
            fn_8012705c(obj);
            v = fn_80129528(spC, i);
            if (v != 0) {
                fn_80126f88_2(obj, v);
            }
            if (sp10 != 0) {
                fn_80126f88(obj);
            }
            i++;
            fn_80131008(sp8, obj, arg1->unk0xBC, 0, 0);
        }
        if (obj != 0) {
            fn_8012701c(obj, 3);
        }
    } else {
        i = 0;
        while (i < (u32)((Arr *)spC)->count) {
            fn_80131008(sp8, fn_80129528(spC, i++), arg1->unk0xBC, 0, 0);
        }
    }
    return true;
}