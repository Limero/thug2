// WIP DRAFT (non-matching) — rebuilt from want disasm + matched siblings
// family=m2c range=0x802359A4-0x80235A9C size=248B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -fno-schedule-insns
//
// PARKED 2026-09-20 — body is structurally correct and semantically fixed,
// but 3 ngccc artifacts remain (all previously documented unreachable
// classes). Do not re-grind without a NEW lever.
//
// What want does (720d demo/screen `MaxPlayers` script command):
//   fn_802358BC(arg0); walker = fn_802358E8(arg0,1); alloc 0xC;
//   arr = fn_80128F94(); fn_80129068(arr, 0xEA6, 1);
//   loop i=0..0xEA5 { fn_80129260(arr, i, walker[i]); }
//   AddArrayPointer(arg1, QB_PARK_EDITOR_MAP, arr);
//   obj = CStruct_ctor(CStruct_new(8));
//   fn_801F50B0(fn_801F672C(), QB_LOAD_SK5ED, obj);
//   fn_80127CD4(arg1, QB_PARK_EDITOR_GOALS, obj);
//   fn_801FAC10(fn_801FC0E0(), arg1);          // r3 chained straight in
//   AddInteger(arg1, QB_MAXPLAYERS, (*arg0)->0x20);
//
// Semantic fixes made 2026-09-20 (the previously committed 56.5% body was
// WRONG on all of these, and its score was positionally inflated — the
// missing fn_802358BC proto emitted a `crclr cr1eq` (+1 word), shifting the
// stream so only the prologue + a handful of load/store-immediate words
// "matched" by coincidence; the real matched-word count is ~10):
//   * fn_802358BC had NO prototype -> `crclr cr1eq` before the first bl.
//   * fn_80129068 is really 3-arg `(arr, 0xEA6, 1)` (m2c dropped arg0, so it
//     emitted li r3,0xEA6 / li r4,1 instead of want's li r4,0xEA6 / li r5,1).
//   * the walker stride was `var_r30 += 4` on an `s32 *` (= +0x10/element);
//     want advances 4 BYTES (`addi r30,r30,4`).
//   * fn_801F50B0 / fn_801FAC10 are CHAINED calls — want sets only r4/r5
//     (and only r4) because r3 is the previous call's result:
//     `fn_801F50B0(fn_801F672C(), ...)` and `fn_801FAC10(fn_801FC0E0(), ..)`.
//   * fn_801F50B0 is 3-arg `(s32, s32, CStruct*)` (see src/fn_801F5188.c);
//     fn_801FAC10 is 2-arg (arg1 = script ctx). fn_801FC0E0 returns the value
//     it passes on (callers fn_801A8848/fn_802261D8 use its result).
//   * QB constants verified against include/qb_constants.h.
//
// Residual (structurally 2-4 words; every one is a known ngccc policy gap):
//   1. `mr r0,r3` / `mr r30,r0` double move after fn_802358E8. ngccc coalesces
//      to a single `mr r30,r3` for EVERY source spelling tried: fn proto
//      void*/s32/u32, walker declared s32*/u32/s32, with/without `(s32*)`
//      cast, implicit decl, explicit `temp_r0` intermediate. The DOL-wide
//      scan (tools) finds only 3 such pairs in .text; in fn_8022DF2C the same
//      artifact comes from GCC homing a local in r0 under pressure. Pure
//      allocator choice, not type-driven.
//   2. Rotated-loop entry-`b` (want `b 0x80235A10` after the fn_80129068
//      call, condition at the loop bottom). ngccc folds the provably-true
//      first test (`var_r29==0 <= 0xEA5`) away in plain `while`/`for`/`do`
//      (loses the `b`) and only the explicit inverted-goto form
//      (`goto test; body: ...; test: if (c) goto body;`) keeps it — but that
//      form SWAPS the two callee-saved homes (walker->r31, arr->r30; want
//      walker->r30, arr->r31). Same entry-`b` class as fn_80184558
// (docs/parkings/15 §) and AGENTS.md recipe 171. Decl-order is
//      inert (0 effect on all 3 orderings tried).
//   3. Loop-latch increment slots: want `addi r30,r30,4` BEFORE the bl and
//      `addi r29,r29,1` AFTER it; ngccc always emits the counter first and
//      sinks the walker increment below the call. Tried separate stmts in
//      both orders and `*var_r30++` in the call argument — identical codegen.
//      doc-15/46 scheduler class.
//
// Flags: -fno-schedule-insns is kept from the prior best (helps the tail);
// the loop artifacts are unchanged by -O1/-Os/-fno-schedule-insns2 too.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_802358BC(void *arg0);
void *fn_802358E8(void *arg0, s32 arg1);
void fn_8003E7CC(s32 arg0);
s32 fn_80128F94(void);
void fn_80129068(Unk_5AA7B5D7 *arg0, s32 arg1, s32 arg2);
void fn_80129260(CStruct *arg0, s32 arg1, s32 arg2);
void AddArrayPointer(CStruct *arg0, s32 arg1, s32 arg2);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 fn_801F672C(void);
void fn_801F50B0(s32 arg0, s32 arg1, CStruct *arg2);
void fn_80127CD4(CStruct *arg0, s32 arg1, s32 arg2);
Unk_C7387A53 *fn_801FC0E0(void);
void fn_801FAC10(Unk_C7387A53 *arg0, CStruct *arg1);
void AddInteger(CStruct *arg0, s32 arg1, s32 arg2);
void fn_802359A4(CStruct **arg0, CStruct *arg1) {
    s32 *var_r30;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r29;

    var_r29 = 0;
    fn_802358BC(arg0);
    var_r30 = (s32 *)fn_802358E8(arg0, 1);
    fn_8003E7CC(0xC);
    temp_r31 = fn_80128F94();
    fn_80129068(temp_r31, 0xEA6, 1);
    while (var_r29 <= 0xEA5) {
        fn_80129260(temp_r31, var_r29, *var_r30++);
        var_r29++;
    }
    AddArrayPointer(arg1, QB_PARK_EDITOR_MAP, temp_r31);
    temp_r30 = CStruct_ctor(CStruct_new(8));
    fn_801F50B0(fn_801F672C(), QB_LOAD_SK5ED, temp_r30);
    fn_80127CD4(arg1, QB_PARK_EDITOR_GOALS, temp_r30);
    fn_801FAC10(fn_801FC0E0(), arg1);
    AddInteger(arg1, QB_MAXPLAYERS, *(s32 *)((char *)(*arg0) + 0x20));
}
