// PARKED 2026-10-06: the worker reconstruction measured
// WORSE than this body and was reverted — worker `sub`-form redraft scored 49.7% vs 91.2%.
// This is the current best-scoring body; kept INERT (not promoted).
// WIP DRAFT — parked NEAR 91.2% (145/159), object 636B == symbol 636B.
// family=m2c range=0x8011562C-0x801158A8 size=636B
// FLAG: -fno-cse-follow-jumps
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SOLVED: 12.6% -> 91.2%, by treating this as the
// N-dimensional sibling of the now-EXACT fn_80115170 (2D) / fn_801153BC (3D)
// (§6gm) and copying that shape. Findings:
//
// 1. **The index loop is a `do/while` guarded by `if (count != 1)`, and the
//    body needs a NAMED temp for the inner getter.**
//        if (((Arr *)sp10)->count != 1) {
//            do {
//                s32 t = fn_801293FC(sp10, i);
//                spC = fn_8012954C(spC, t);
//                i++;
//            } while (i < (u32)(((Arr *)sp10)->count - 1));
//        }
//    Two separate wins, both load-bearing:
//      * `s32 t = ...;` instead of nesting `fn_8012954C(spC, fn_801293FC(sp10,i))`
//        is worth **52.3% vs 22.4%** on its own and fixes the FRAME: nested,
//        cc1 hoists the `spC` reload ABOVE `bl fn_801293FC`, needs a third
//        callee-saved reg and emits `stwu r1,-0x28(r1)` / `stmw r29,0x1c(r1)`.
//        With the named temp the reload lands after the call, exactly like
//        want, and only r30/r31 are saved (frame 0x20).
//      * `(u32)(count - 1)` — want's guard is `cmplw r30,r9`, not `cmpw`, so
//        the loop bound is an UNSIGNED compare (§6gj).
//    `while` instead of `do/while`, a `for` loop, `u32 i`, a named `n` for
//        the count and an `(s32)((u32)c - 1)` spelling all measure WORSE.
//
// 2. **`-fno-cse-follow-jumps` is worth another 52.3% -> 91.2%** and takes
//    the object from 604 B to exactly 636 B. Without it cc1 CSEs the
//    descended-array reload and keeps the value in **r3** across the whole
//    dispatch tree, which deletes the per-case `mr r3,r9` (7 instructions)
//    and the object comes out 32 B short. Same flag family as the 0x80113CC4
//    draft. (`-fno-schedule-insns` = 45.0%, `-fno-strength-reduce` /
//    `-fno-delayed-branch` = no change, `-fno-tree-pre` does not exist.)
//
// 3. **RESIDUAL (8.8%, 14 instructions, all one defect).** want holds the
//    descended array pointer in **r9** across the dispatch tree:
//        lwz r9,0xc(r1) ; mr r4,r3 ; lbz r0,2(r9)
//    and every case block opens with `mr r3,r9`. The draft emits the same
//    636 B but reloads per block:
//        lwz r3,0xc(r1) ; lwz r30,0x18(r31)
//    i.e. one `lwz` where want has one `mr` — same count, wrong register.
//    Tried and rejected (all <= 91.2%, several far worse):
//      * `s32 sub = spC;` named copy, before OR after `idx`, used in the
//        switch and in every case  -> cc1 COALESCES the copy back onto the
//        frame slot; before `idx` it additionally wants a 3rd callee-saved
//        reg (frame 0x28, 79.3%).
//      * `Arr *a = (Arr *)spC;`, `u8 ty = ...->type;`, `s32 *pc = &spC;`,
//        `(char *)spC + 2` byte pun, `Arr *spC` instead of `s32 spC`,
//        `u32 idx`  -> byte-identical output to the base (cc1 normalises all
//        of them).
//      * a separate loop-carried `cur` that is also stored to `spC`
//        -> `cur` must survive `bl fn_801293FC`, so it gets a callee-saved
//        reg and the frame goes to 0x28 (14.4% - 77.4%).
//      * `register s32 sub __asm__("r9")` -> the pin destroys the dispatch
//        tree (33.5%); `__asm__("r28")` / `__asm__("r26")` = 88.7%.
//    So this is a genuine register-residency wall for a value that is live
//    across JUMPS but never across a CALL in any path: plain C will not make
//    cc1 pick a caller-saved reg for it here. Parking.
//
// 2026-10-19: two more levers tried, both byte-identical to base (91.19%):
//   * `register s32 idx __asm__("r4")` — no-op, idx already rides r4.
//   * hoisting case-2 `sc` to function scope — no change.
// New analysis (from WANT disasm, for the next attacker): the prelude
// `mr r4,r3` at 0x80115700 is idx (getter result), NOT spC — idx rides r4
// across the switch into every getter-calling case with no per-case setup.
// So TWO caller-saved webs cross the dispatch (r9=spC, r4=idx); cc1 colours
// the single-def r4 web but splits the spill-reload r9 web back to its
// 0xc(r1) home. spC-in-r9 dies at each case's first `bl`, and r9 is then
// reused as float-case scratch (`mr r9,r3` + lfs off r9) — r9 was never a
// dedicated spC home, just the winning colour for that web. The lever is
// whatever makes the spill-originated web colourable, not r9 occupancy.
//
// 4. `fn_8012954C` is again BOTH the descent (`fn_8012954C(spC, t)`) and the
//    case-12 value getter; `fn_801293FC` is both the per-index getter (inside
//    the loop) and the case-1 value getter (after it). One declaration each.
//    `GetArray(arg1->unk0x18, QB_INDICES, &sp10, 1)` is the THIRD GetArray
//    call in this family and takes 4 args like its siblings (m2c had 2).
//    QB_INDICES = 0xFFC8E484 (lis -0x38 / ori 0xe484).
//
// 5. Case order: source order is 1, 2, 13, 3, 4, 5, 6, 10, 12 — want's
//    binary-search tree is a different order and does not constrain the
//    source. Cases 3 and 4 are DUPLICATED bodies, not a fallthrough (§6gm).
#include "types.h"
#include "qb_constants.h"
typedef struct CStruct CStruct;
typedef struct { char pad0x00[0x18]; s32 unk0x18; } Sc;
typedef struct {
    char pad0x00[2];
    u8 type;
    char pad0x03;
    s32 count;
} Arr;
typedef struct {
    char pad0x00[4];
    f32 a;
    f32 b;
    f32 c;
} V3;
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 GetArray(s32 arg0, s32 arg1, void *arg2, s32 arg3);
void *fn_801259C8(s32 arg0, s32 arg1);
s32 fn_8012954C(s32 arg0, s32 arg1);
s32 fn_80129528(s32 arg0, s32 arg1);
s32 fn_801293FC(s32 arg0, s32 arg1);
f32 fn_80129420(s32 arg0, s32 arg1);
void fn_8012772C(s32 arg0, s32 arg1);
s32 GetChecksum(s32 arg0, s32 arg1);
void AddChecksum(s32 arg0, s32 arg1, s32 arg2);
s32 fn_8012935C(s32 arg0, s32 arg1);
void AddString(s32 arg0, s32 arg1, s32 arg2);
s32 fn_80129504(s32 arg0, s32 arg1);
s32 fn_801294E0(s32 arg0, s32 arg1);
void fn_80127A18(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void fn_8012788C(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
void AddInteger(s32 arg0, s32 arg1, s32 arg2);
void fn_80127C14(s32 arg0, s32 arg1, s32 arg2);
void fn_80127AAC(s32 arg0, s32 arg1, s32 arg2);
bool ScriptGetNDArrayData(CStruct *arg0, Sc *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 i;
    s32 idx;
    V3 *v;

    sp8 = 0;
    GetChecksum_2(arg0, QB_ARRAYNAME, &sp8, 1);
    spC = 0;
    if (GetArray(arg1->unk0x18, sp8, &spC, 0) == 0) {
        spC = (s32)fn_801259C8(sp8, 1);
    }
    sp10 = 0;
    GetArray(arg1->unk0x18, QB_INDICES, &sp10, 1);
    i = 0;
    if (((Arr *)sp10)->count != 1) {
        do {
            s32 t = fn_801293FC(sp10, i);
            spC = fn_8012954C(spC, t);
            i++;
        } while (i < (u32)(((Arr *)sp10)->count - 1));
    }
    idx = fn_801293FC(sp10, i);
    switch (((Arr *)spC)->type) {
    case 1:
        AddInteger(arg1->unk0x18, QB_VAL, fn_801293FC(spC, idx));
        break;
    case 2: {
        s32 sc = arg1->unk0x18;
        fn_80129420(spC, idx);
        fn_8012772C(sc, QB_VAL);
        break;
    }
    case 13:
        AddChecksum(arg1->unk0x18, QB_VAL, GetChecksum(spC, idx));
        break;
    case 3:
        AddString(arg1->unk0x18, QB_VAL, fn_8012935C(spC, idx));
        break;
    case 4:
        AddString(arg1->unk0x18, QB_VAL, fn_8012935C(spC, idx));
        break;
    case 5:
        v = (V3 *)fn_80129504(spC, idx);
        fn_80127A18(arg1->unk0x18, QB_VAL, v->a, v->b);
        break;
    case 6:
        v = (V3 *)fn_801294E0(spC, idx);
        fn_8012788C(arg1->unk0x18, QB_VAL, v->a, v->b, v->c);
        break;
    case 10:
        fn_80127C14(arg1->unk0x18, QB_VAL, fn_80129528(spC, idx));
        break;
    case 12:
        fn_80127AAC(arg1->unk0x18, QB_VAL, fn_8012954C(spC, idx));
        break;
    }
    return true;
}